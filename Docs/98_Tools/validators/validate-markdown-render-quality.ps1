param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "../../..")).Path,
    [string[]]$InputPath
)

$ErrorActionPreference = "Stop"
$Failures = [System.Collections.Generic.List[string]]::new()

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
        $RelativePath -eq "Portfolio_RayTracer/README.md" -or
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

function Test-MarkdownFile {
    param([System.IO.FileInfo]$File)

    $relative = Get-RelativePath $File.FullName
    $lines = @(Get-Content -LiteralPath $File.FullName -Encoding utf8)
    $inFence = $false
    $fenceCharacter = $null
    $fenceLength = 0

    for ($index = 0; $index -lt $lines.Count; $index++) {
        $line = $lines[$index]
        $lineNumber = $index + 1

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

        if ($inFence) {
            continue
        }

        # Preserve code-span boundaries so `Ex1501`~`Ex1503` remains detectable.
        $plain = [regex]::Replace($line, '`[^`]*`', 'CODE')
        $plain = [regex]::Replace($plain, '\]\([^)]+\)', ']()')
        $plain = [regex]::Replace($plain, '<https?://[^>]+>', '')
        $plain = [regex]::Replace($plain, '\\\~', '')
        $plain = [regex]::Replace($plain, '~~.*?~~', '')
        $rangeTilde = [regex]::Match(
            $plain,
            '(?:CODE|\w+)\s*~\s*(?:CODE|\w+)'
        )

        if ($rangeTilde.Success) {
            $Failures.Add(
                "${relative}:${lineNumber}: MDRENDER-001 " +
                "single tilde ranges may render as strikethrough; " +
                "use '부터 ... 까지' wording for ranges"
            )
        }
    }
}

try {
    $files = @(Get-MarkdownFiles)
} catch {
    Write-Host "Markdown render quality validation failed." -ForegroundColor Red
    Write-Host " - $($_.Exception.Message)" -ForegroundColor Red
    exit 1
}

if ($files.Count -eq 0) {
    Write-Host "Markdown render quality validation failed." -ForegroundColor Red
    Write-Host " - no Markdown input files found" -ForegroundColor Red
    exit 1
}

foreach ($file in $files) {
    Test-MarkdownFile $file
}

if ($Failures.Count -gt 0) {
    Write-Host "Markdown render quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Markdown render quality validation passed ($($files.Count) file(s))." `
    -ForegroundColor Green
exit 0
