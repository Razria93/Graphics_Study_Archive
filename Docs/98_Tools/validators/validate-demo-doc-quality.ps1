param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
    [string]$DemosRoot = (Join-Path $Root "Docs/03_Demos")
)

$ErrorActionPreference = "Stop"
$Failures = New-Object System.Collections.Generic.List[string]
$Warnings = New-Object System.Collections.Generic.List[string]

function New-Text {
    param([int[]]$CodePoints)
    return -join ($CodePoints | ForEach-Object { [char]$_ })
}

function Add-Failure {
    param([string]$Path, [string]$Message)
    $Failures.Add("$Path :: $Message")
}

function Add-Warning {
    param([string]$Path, [string]$Message)
    $Warnings.Add("$Path :: $Message")
}

function Get-RelativePath {
    param([string]$Path)
    $rootPath = [IO.Path]::GetFullPath($Root).TrimEnd('\') + '\'
    $fullPath = [IO.Path]::GetFullPath($Path)
    if (-not $fullPath.StartsWith(
        $rootPath,
        [StringComparison]::OrdinalIgnoreCase
    )) {
        throw "Path is outside repository root: $Path"
    }
    return $fullPath.Substring($rootPath.Length).Replace('\', '/')
}

function Get-Section {
    param([string[]]$Lines, [string]$Heading)

    $start = [Array]::IndexOf($Lines, $Heading)
    if ($start -lt 0) {
        return $null
    }

    $end = $Lines.Count
    for ($i = $start + 1; $i -lt $Lines.Count; ++$i) {
        if ($Lines[$i] -match '^##\s+') {
            $end = $i
            break
        }
    }

    if ($end -le $start + 1) {
        return @()
    }
    return $Lines[($start + 1)..($end - 1)]
}

function Test-TrackedAsset {
    param([string]$RelativePath, [string]$ResolvedPath)

    $repoRelative = Get-RelativePath $ResolvedPath
    & git -C $Root ls-files --error-unmatch -- $repoRelative *> $null
    if ($LASTEXITCODE -ne 0) {
        Add-Failure $RelativePath "public asset is not tracked: $repoRelative"
    }
}

function Validate-DemoDocument {
    param([System.IO.FileInfo]$File)

    $relative = Get-RelativePath $File.FullName
    $lines = Get-Content -Encoding UTF8 $File.FullName
    $content = $lines -join "`n"
    $PseudocodeWord = New-Text @(0xC758, 0xC0AC, 0xCF54, 0xB4DC)
    $required = @(
        ("## " + (New-Text @(0xBAA9, 0xC801))),
        ("## " + (New-Text @(0xCC45, 0xC784, 0x20, 0xBC94, 0xC704))),
        ("## " + (New-Text @(0xACB0, 0xACFC, 0x20, 0xBBF8, 0xB9AC, 0xBCF4, 0xAE30))),
        ("## " + (New-Text @(0xC785, 0xB825, 0xACFC, 0x20, 0xCD9C, 0xB825))),
        ("## " + (New-Text @(0xAD6C, 0xD604, 0x20, 0xD750, 0xB984))),
        ("## " + (New-Text @(0xD575, 0xC2EC, 0x20, 0xAD6C, 0xD604))),
        ("## " + (New-Text @(0xC2DC, 0xAC01, 0x20, 0xACB0, 0xACFC))),
        ("## " + (New-Text @(0xAD6C, 0xD604, 0x20, 0xBC94, 0xC704, 0xC640, 0x20, 0xD55C, 0xACC4))),
        ("## " + (New-Text @(0xAC80, 0xC99D))),
        ("## " + (New-Text @(0xAD00, 0xB828, 0x20, 0xCF54, 0xB4DC))),
        ("## " + (New-Text @(0xAD00, 0xB828, 0x20, 0xBB38, 0xC11C)))
    )

    if ($lines.Count -eq 0 -or $lines[0] -notmatch '^#\s+.+') {
        Add-Failure $relative "document must start with an H1"
    }

    $previous = -1
    foreach ($heading in $required) {
        $index = [Array]::IndexOf($lines, $heading)
        if ($index -lt 0) {
            Add-Failure $relative "missing required heading: $heading"
            continue
        }
        if ($index -lt $previous) {
            Add-Failure $relative "heading order mismatch: $heading"
        }
        $previous = $index

        $section = Get-Section -Lines $lines -Heading $heading
        $meaningful = @($section | Where-Object {
            -not [string]::IsNullOrWhiteSpace($_) -and $_ -notmatch '^\s*-\s*$'
        })
        if ($meaningful.Count -eq 0) {
            Add-Failure $relative "empty required section: $heading"
        }
    }

    if ($content -match '<[^>]+>|\bTODO\b|\bTBD\b') {
        Add-Failure $relative "placeholder text is not allowed"
    }
    if ($content -match '(?i)(^|[\s(`])local/' -or
        $content -match 'Docs/99_Legacy|Docs/01_Examples|Docs/_repo') {
        Add-Failure $relative "local, Legacy, or stale paths are not allowed"
    }

    for ($i = 0; $i -lt $lines.Count; ++$i) {
        $line = $lines[$i]
        if ($line.Length -gt 120 -and $line -notmatch '^\s*\|' -and
            $line -notmatch '^\s*!\[' -and $line -notmatch 'https://') {
            Add-Failure $relative "line $($i + 1): exceeds 120 characters"
        }
    }

    $links = [regex]::Matches($content, '!?\[[^\]]*\]\(([^)]+)\)')
    $hasExample = $false
    $hasTopic = $false
    $hasVerification = $false
    $imageCount = 0
    foreach ($match in $links) {
        $target = $match.Groups[1].Value.Split('#')[0]
        if ($target -match '^https?://' -or [string]::IsNullOrWhiteSpace($target)) {
            continue
        }

        $resolved = [IO.Path]::GetFullPath((Join-Path $File.DirectoryName $target))
        if (-not (Test-Path -LiteralPath $resolved)) {
            Add-Failure $relative "broken relative link: $target"
            continue
        }

        $repoTarget = Get-RelativePath $resolved
        if ($repoTarget -match '^(?:Part[^/]+/.+|Portfolio_RayTracer(?:/.+)?)\/README\.md$') {
            $hasExample = $true
        }
        if ($repoTarget -match '^Docs/01_Topics/') {
            $hasTopic = $true
        }
        if ($repoTarget -match '^Docs/02_Verification/') {
            $hasVerification = $true
        }
        if ($match.Value.StartsWith('![')) {
            ++$imageCount
            if ($repoTarget -notmatch '^Docs/_assets/') {
                Add-Failure $relative "image must use Docs/_assets: $target"
            }
            else {
                Test-TrackedAsset -RelativePath $relative -ResolvedPath $resolved
            }
        }
    }

    if (-not $hasExample) {
        Add-Failure $relative "missing Example README Markdown link"
    }
    if (-not $hasTopic) {
        Add-Failure $relative "missing Topic Markdown link"
    }
    if (-not $hasVerification) {
        Add-Failure $relative "missing Verification Markdown link"
    }
    if ($imageCount -eq 0) {
        Add-Warning $relative "representative visual is missing"
    }

    if ($content -match $PseudocodeWord) {
        $cppBlocks = [regex]::Matches($content, '(?ms)```cpp\s*(.*?)```')
        $pseudoBlocks = @($cppBlocks | Where-Object {
            $_.Groups[1].Value -match 'Pseudo C\+\+'
        })
        if ($pseudoBlocks.Count -eq 0) {
            Add-Failure $relative "pseudocode must use a cpp fence and state 'Pseudo C++'"
        }

        $sourceLinks = [regex]::Matches(
            $content,
            '\[[^\]]+\]\((?!https?://)[^)]*\.(?:cpp|h)#L\d+(?:-L\d+)?\)'
        )
        if ($sourceLinks.Count -lt $pseudoBlocks.Count) {
            Add-Failure $relative "each pseudocode block must have a source line link"
        }
    }

    $indexPath = Join-Path $File.DirectoryName "demo-index.md"
    if (-not (Test-Path $indexPath) -or
        (Get-Content -Raw -Encoding UTF8 $indexPath) -notmatch
        [regex]::Escape("]($($File.Name))")) {
        Add-Failure $relative "demo-index.md must link this detailed Demo"
    }
}

if (-not (Test-Path $DemosRoot)) {
    throw "Demos root not found: $DemosRoot"
}

$demoFiles = @(Get-ChildItem -Path $DemosRoot -File -Recurse |
    Where-Object { $_.Name -match '^\d{2}_.+\.md$' })
if ($demoFiles.Count -eq 0) {
    $Failures.Add("Docs/03_Demos :: no detailed Demo documents found")
}
else {
    foreach ($file in $demoFiles) {
        Validate-DemoDocument -File $file
    }
}

if ($Warnings.Count -gt 0) {
    Write-Host "Demo document quality warnings:" -ForegroundColor Yellow
    $Warnings | ForEach-Object { Write-Host " - $_" -ForegroundColor Yellow }
}

if ($Failures.Count -gt 0) {
    Write-Host "Demo document quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Demo document quality validation passed ($($demoFiles.Count) file(s))." `
    -ForegroundColor Green
exit 0
