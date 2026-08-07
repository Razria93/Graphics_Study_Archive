param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
    [string]$ExampleDocsRoot = (Join-Path $Root "Part4_Chapter14-20\ExampleDocs")
)

$ErrorActionPreference = "Stop"
$Failures = New-Object System.Collections.Generic.List[string]

function Add-Failure {
    param([string]$Path, [string]$Message)
    $Failures.Add("$Path :: $Message")
}

function New-Text {
    param([int[]]$CodePoints)
    return -join ($CodePoints | ForEach-Object { [char]$_ })
}

function Get-RelativePath {
    param([string]$Path)
    $rootPath = [IO.Path]::GetFullPath($Root).TrimEnd('\') + '\'
    $fullPath = [IO.Path]::GetFullPath($Path)
    return $fullPath.Substring($rootPath.Length).Replace('\', '/')
}

if (-not (Test-Path -LiteralPath $ExampleDocsRoot)) {
    throw "ExampleDocs root not found: $ExampleDocsRoot"
}

$files = @(Get-ChildItem -Path $ExampleDocsRoot -Filter '*.md' -File |
    Where-Object { $_.Name -ne 'README.md' })
if ($files.Count -eq 0) {
    $Failures.Add("Part4_Chapter14-20/ExampleDocs :: no ExampleDocs found")
}

foreach ($file in $files) {
    $relativePath = Get-RelativePath $file.FullName
    $content = Get-Content -Raw -Encoding UTF8 $file.FullName
    $requiredHeadings = @(
        '## Overview',
        '## ' + (New-Text @(0xC2E4, 0xD589, 0x20, 0xC9C4, 0xC785, 0xC810)),
        '## Code Map',
        '## Capture/Result',
        '## Verification',
        '## Limitations',
        '## Related Docs'
    )
    foreach ($heading in $requiredHeadings) {
        if ($content -notmatch [regex]::Escape($heading)) {
            Add-Failure $relativePath "missing required heading: $heading"
        }
    }
    if ($content -notmatch '(?m)^#\s+\S') {
        Add-Failure $relativePath 'document must start with an H1 title'
    }
    if ($content -match '<[^>]+>|\bTODO\b|\bTBD\b') {
        Add-Failure $relativePath 'placeholder text is not allowed'
    }
    if ($content -notmatch 'Examples\.sln|Examples\.exe\s+\d{4}') {
        Add-Failure $relativePath 'missing Part4 solution or command argument'
    }
    if ($content -notmatch 'Docs/01_Topics/' -or
        $content -notmatch 'Docs/02_Verification/' -or
        $content -notmatch 'Docs/03_Demos/') {
        Add-Failure $relativePath 'missing Topic, Verification, or Demo link'
    }
}

if ($Failures.Count -gt 0) {
    Write-Host 'ExampleDocs quality validation failed.' -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "ExampleDocs quality validation passed ($($files.Count) file(s))." -ForegroundColor Green
exit 0