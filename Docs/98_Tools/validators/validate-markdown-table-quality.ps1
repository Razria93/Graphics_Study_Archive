param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "../../..")).Path,
    [string[]]$InputPath
)

$ErrorActionPreference = "Stop"
$Failures = [System.Collections.Generic.List[string]]::new()
$TableCount = 0

function Get-RelativePath {
    param([string]$Path)

    $rootPath = [System.IO.Path]::GetFullPath($Root).TrimEnd("\", "/") + "\"
    $filePath = [System.IO.Path]::GetFullPath($Path)
    $rootUri = [System.Uri]::new($rootPath)
    $fileUri = [System.Uri]::new($filePath)
    return [System.Uri]::UnescapeDataString(
        $rootUri.MakeRelativeUri($fileUri).ToString()
    ).Replace("\", "/")
}

function Add-Failure {
    param(
        [string]$Path,
        [int]$Line,
        [string]$Id,
        [string]$Message
    )

    $Failures.Add("${Path}:${Line}: ${Id} ${Message}")
}

function Test-ExcludedPath {
    param([string]$RelativePath)

    return (
        $RelativePath -match '^(?:Docs/99_Legacy|local)/' -or
        $RelativePath -match '/(?:x64|Debug|Release|\.vs)/' -or
        $RelativePath -match '^Docs/98_Tools/validators/fixtures/'
    )
}

function Test-IncludedPath {
    param([string]$RelativePath)

    return (
        $RelativePath -eq "README.md" -or
        $RelativePath -eq "AGENTS.md" -or
        $RelativePath -match '^Part[^/]+/(?:.+/)?README\.md$' -or
        $RelativePath -match '^Part4_Chapter14-20/ExampleDocs/.+\.md$' -or
        $RelativePath -eq "Portfolio_GraphicsLab/README.md" -or
        $RelativePath -match '^Docs/(?:0[0-7]_[^/]+|98_Tools)/.+\.md$' -or
        $RelativePath -match '^\.github/.+\.md$'
    )
}

function Get-MarkdownFiles {
    if ($InputPath) {
        $resolved = foreach ($item in $InputPath) {
            if (-not (Test-Path -LiteralPath $item)) {
                throw "Input path does not exist: $item"
            }

            $entry = Get-Item -LiteralPath $item
            if ($entry.PSIsContainer) {
                Get-ChildItem -LiteralPath $entry.FullName -File -Recurse |
                    Where-Object { $_.Name -match '\.md(?:\.txt)?$' }
            } else {
                $entry
            }
        }

        return @($resolved | Sort-Object FullName -Unique)
    }

    $tracked = & git -C $Root ls-files -- "*.md" "AGENTS.md"
    if ($LASTEXITCODE -ne 0) {
        throw "git ls-files failed while collecting Markdown files"
    }

    return @(
        $tracked |
            Where-Object {
                $_ -and
                (Test-IncludedPath $_) -and
                -not (Test-ExcludedPath $_) -and
                (Test-Path -LiteralPath (Join-Path $Root $_) -PathType Leaf)
            } |
            ForEach-Object { Get-Item -LiteralPath (Join-Path $Root $_) }
    )
}

function Test-PipeRow {
    param([string]$Line)

    return $Line -match '^\s{0,3}\|.*\|\s*$'
}

function Split-MarkdownRow {
    param([string]$Line)

    $trimmed = $Line.Trim()
    $content = $trimmed.Substring(1, $trimmed.Length - 2)
    $cells = [System.Collections.Generic.List[string]]::new()
    $current = [System.Text.StringBuilder]::new()

    for ($index = 0; $index -lt $content.Length; $index++) {
        $character = $content[$index]
        if ($character -eq "|") {
            $backslashCount = 0
            for ($scan = $index - 1; $scan -ge 0 -and
                $content[$scan] -eq "\"; $scan--) {
                $backslashCount++
            }

            if ($backslashCount % 2 -eq 0) {
                $cells.Add($current.ToString().Trim())
                $null = $current.Clear()
                continue
            }
        }

        $null = $current.Append($character)
    }

    $cells.Add($current.ToString().Trim())
    return @($cells)
}

function Test-SeparatorCell {
    param([string]$Cell)

    return $Cell -match '^:?-+:?$'
}

function Test-SeparatorCandidate {
    param([string[]]$Cells)

    if ($Cells.Count -eq 0) {
        return $false
    }

    return @($Cells | Where-Object { Test-SeparatorCell $_ }).Count -gt 0
}

function Get-EligibleLines {
    param([string[]]$Lines)

    $eligible = [bool[]]::new($Lines.Count)
    $inFence = $false
    $fenceCharacter = $null
    $fenceLength = 0
    $inFrontMatter = $false
    $inHtmlComment = $false
    $htmlBlockTag = $null

    for ($index = 0; $index -lt $Lines.Count; $index++) {
        $line = $Lines[$index]
        $lineNumber = $index + 1

        if ($lineNumber -eq 1 -and $line -eq "---") {
            $inFrontMatter = $true
            continue
        }

        if ($inFrontMatter) {
            if ($lineNumber -gt 1 -and $line -eq "---") {
                $inFrontMatter = $false
            }
            continue
        }

        if ($inHtmlComment) {
            if ($line -match '-->') {
                $inHtmlComment = $false
            }
            continue
        }

        if ($htmlBlockTag) {
            if ($line -match "^\s*</$htmlBlockTag\s*>") {
                $htmlBlockTag = $null
            }
            continue
        }

        if ($line -match '^\s*<!--') {
            if ($line -notmatch '-->') {
                $inHtmlComment = $true
            }
            continue
        }

        if ($line -match '^\s*<(details|div|table|pre|script|style)(?:\s[^>]*)?>\s*$') {
            $htmlBlockTag = $Matches[1]
            continue
        }

        if ($line -match '^\s*(`{3,}|~{3,})') {
            $marker = $Matches[1]
            if (-not $inFence) {
                $inFence = $true
                $fenceCharacter = $marker[0]
                $fenceLength = $marker.Length
            } elseif ($marker[0] -eq $fenceCharacter -and
                $marker.Length -ge $fenceLength) {
                $inFence = $false
                $fenceCharacter = $null
                $fenceLength = 0
            }
            continue
        }

        if (-not $inFence) {
            $eligible[$index] = $true
        }
    }

    return $eligible
}

function Test-MarkdownFile {
    param([System.IO.FileInfo]$File)

    $relative = Get-RelativePath $File.FullName
    $lines = @(Get-Content -LiteralPath $File.FullName -Encoding utf8)
    $eligible = Get-EligibleLines $lines

    for ($index = 0; $index -lt $lines.Count - 1; $index++) {
        if (-not $eligible[$index] -or -not $eligible[$index + 1]) {
            continue
        }

        if (-not (Test-PipeRow $lines[$index]) -or
            -not (Test-PipeRow $lines[$index + 1])) {
            continue
        }

        $headerCells = @(Split-MarkdownRow $lines[$index])
        $separatorCells = @(Split-MarkdownRow $lines[$index + 1])
        if (-not (Test-SeparatorCandidate $separatorCells)) {
            continue
        }

        $script:TableCount++
        $separatorLine = $index + 2

        if ($headerCells.Count -ne $separatorCells.Count) {
            Add-Failure $relative $separatorLine "TABLE-001" (
                "header $($headerCells.Count) columns, separator " +
                "$($separatorCells.Count) columns"
            )
        }

        for ($cellIndex = 0; $cellIndex -lt $separatorCells.Count; $cellIndex++) {
            if (-not (Test-SeparatorCell $separatorCells[$cellIndex])) {
                Add-Failure $relative $separatorLine "TABLE-002" (
                    "invalid separator cell at column $($cellIndex + 1)"
                )
            }
        }

        $rowIndex = $index + 2
        while ($rowIndex -lt $lines.Count -and $eligible[$rowIndex] -and
            (Test-PipeRow $lines[$rowIndex])) {
            $dataCells = @(Split-MarkdownRow $lines[$rowIndex])
            if ($dataCells.Count -ne $headerCells.Count) {
                Add-Failure $relative ($rowIndex + 1) "TABLE-003" (
                    "header $($headerCells.Count) columns, data row " +
                    "$($dataCells.Count) columns"
                )
            }
            $rowIndex++
        }

        $index = $rowIndex - 1
    }
}

try {
    $files = @(Get-MarkdownFiles)
} catch {
    Write-Host "Markdown table quality validation failed." -ForegroundColor Red
    Write-Host " - $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}

if ($files.Count -eq 0) {
    Write-Host "Markdown table quality validation failed." -ForegroundColor Red
    Write-Host " - no Markdown input files found" -ForegroundColor Red
    exit 1
}

foreach ($file in $files) {
    Test-MarkdownFile $file
}

if ($Failures.Count -gt 0) {
    Write-Host "Markdown table quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host (
    "Markdown table quality validation passed " +
    "($($files.Count) file(s), $TableCount table(s))."
) -ForegroundColor Green
exit 0
