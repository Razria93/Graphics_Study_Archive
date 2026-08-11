param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "../../..")).Path,
    [string[]]$InputPath,
    [switch]$WarningAsFailure
)

$ErrorActionPreference = "Stop"
$Failures = [System.Collections.Generic.List[string]]::new()
$Warnings = [System.Collections.Generic.List[string]]::new()

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
        [string]$Message
    )

    $Failures.Add("${Path}:${Line}: ${Message}")
}

function Add-Warning {
    param(
        [string]$Path,
        [int]$Line,
        [string]$Message
    )

    $Warnings.Add("${Path}:${Line}: ${Message}")
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

function Test-StructuralLine {
    param([string]$Line)

    if ([string]::IsNullOrWhiteSpace($Line)) {
        return $true
    }

    return (
        $Line -match '^\s{0,3}(?:#{1,6}\s|>\s?|[-*_]\s*[-*_]\s*[-*_])' -or
        $Line -match '^\s*(?:!\[[^\]]*\]\([^)]+\)|\[[^\]]+\]:\s+\S+)\s*$' -or
        $Line -match '^\s*\|.*\|\s*$' -or
        $Line -match '^\s*<[/!?A-Za-z][^>]*>\s*$'
    )
}

function Test-ListMarker {
    param([string]$Line)

    return $Line -match '^(\s*)(?:[-+*]|\d+[.)])\s+\S'
}

function Test-NestedListMarker {
    param([string]$Line)

    return $Line -match '^\s{2,}(?:[-+*]|\d+[.)])\s+\S'
}

function Test-ExplicitHardBreak {
    param([string]$Line)

    return $Line -match '(?: {2,}|\\)$'
}

function Test-MarkdownFile {
    param([System.IO.FileInfo]$File)

    $relative = Get-RelativePath $File.FullName
    $lines = @(Get-Content -LiteralPath $File.FullName -Encoding utf8)
    $inFence = $false
    $fenceCharacter = $null
    $fenceLength = 0
    $inFrontMatter = $false
    $inHtmlComment = $false
    $htmlBlockTag = $null
    $previousKind = "none"
    $previousLine = ""
    $previousLineNumber = 0
    $previousListIndent = -1

    for ($index = 0; $index -lt $lines.Count; $index++) {
        $line = $lines[$index]
        $lineNumber = $index + 1

        if ($lineNumber -eq 1 -and $line -eq "---") {
            $inFrontMatter = $true
            $previousKind = "structural"
            continue
        }

        if ($inFrontMatter) {
            if ($lineNumber -gt 1 -and $line -eq "---") {
                $inFrontMatter = $false
            }
            $previousKind = "structural"
            continue
        }

        if ($inHtmlComment) {
            if ($line -match '-->') {
                $inHtmlComment = $false
            }
            $previousKind = "structural"
            continue
        }

        if ($htmlBlockTag) {
            if ($line -match "^\s*</$htmlBlockTag\s*>") {
                $htmlBlockTag = $null
            }
            $previousKind = "structural"
            continue
        }

        if ($line -match '^\s*<!--') {
            if ($line -notmatch '-->') {
                $inHtmlComment = $true
            }
            $previousKind = "structural"
            continue
        }

        if ($line -match '^\s*<(details|div|table|pre|script|style)(?:\s[^>]*)?>\s*$') {
            $htmlBlockTag = $Matches[1]
            $previousKind = "structural"
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
            $previousKind = "structural"
            continue
        }

        if ($inFence) {
            $previousKind = "structural"
            continue
        }

        if (Test-StructuralLine $line) {
            $previousKind = "structural"
            $previousLine = $line
            $previousLineNumber = $lineNumber
            $previousListIndent = -1
            continue
        }

        if (Test-ListMarker $line) {
            $indent = ([regex]::Match($line, '^\s*')).Value.Length
            $previousKind = "list"
            $previousLine = $line
            $previousLineNumber = $lineNumber
            $previousListIndent = $indent
            continue
        }

        $isIndentedCode = $line -match '^ {4,}\S'
        if ($isIndentedCode -or (Test-NestedListMarker $line)) {
            $previousKind = "structural"
            $previousLine = $line
            $previousLineNumber = $lineNumber
            $previousListIndent = -1
            continue
        }

        if ($previousKind -eq "list" -or $previousKind -eq "list-continuation") {
            $indent = ([regex]::Match($line, '^\s*')).Value.Length
            if ($indent -gt $previousListIndent) {
                Add-Failure $relative $lineNumber `
                    "one list item is split across physical lines"
                $previousKind = "list-continuation"
                $previousLine = $line
                $previousLineNumber = $lineNumber
                continue
            }
        }

        $isPlain = $line -match '^\S'
        if ($isPlain -and $previousKind -eq "plain" -and
            -not (Test-ExplicitHardBreak $previousLine)) {
            Add-Failure $relative $lineNumber `
                "one paragraph is split across physical lines"
        }

        if ($isPlain) {
            $previousKind = "plain"
        } else {
            Add-Warning $relative $lineNumber `
                "indented continuation requires manual review"
            $previousKind = "other"
        }

        $previousLine = $line
        $previousLineNumber = $lineNumber
        $previousListIndent = -1
    }
}

try {
    $files = @(Get-MarkdownFiles)
} catch {
    Write-Host "Markdown wrap quality validation failed." -ForegroundColor Red
    Write-Host " - $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}

if ($files.Count -eq 0) {
    Write-Host "Markdown wrap quality validation failed." -ForegroundColor Red
    Write-Host " - no Markdown input files found" -ForegroundColor Red
    exit 1
}

foreach ($file in $files) {
    Test-MarkdownFile $file
}

if ($Warnings.Count -gt 0) {
    Write-Host "Markdown wrap quality warnings:" -ForegroundColor Yellow
    $Warnings | ForEach-Object { Write-Host " - $_" -ForegroundColor Yellow }
}

if ($Failures.Count -gt 0 -or ($WarningAsFailure -and $Warnings.Count -gt 0)) {
    Write-Host "Markdown wrap quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    if ($WarningAsFailure -and $Warnings.Count -gt 0) {
        Write-Host " - warnings are treated as failures" -ForegroundColor Red
    }
    exit 1
}

Write-Host "Markdown wrap quality validation passed ($($files.Count) file(s))." `
    -ForegroundColor Green
exit 0
