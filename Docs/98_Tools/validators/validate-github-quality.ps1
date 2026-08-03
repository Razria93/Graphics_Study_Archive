param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
    [string]$GitHubRoot = (Join-Path $Root "Docs/07_GitHub")
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "github-visual-rules.ps1")
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

function Test-PseudocodeAllmanStyle {
    param([string]$Path, [string]$Block)

    $blockLines = $Block -split "`r?`n"
    for ($i = 0; $i -lt $blockLines.Count; ++$i) {
        $line = $blockLines[$i]
        $sameLineControl =
            $line -match '^\s*(?:if|for|while)\s*\([^{}]*\)\s*\{' -or
            $line -match '^\s*else(?:\s+if\s*\([^{}]*\))?\s*\{' -or
            $line -match '^\s*\}\s*else\b'
        $sameLineFunction =
            $line -match (
                '^\s*(?!(?:if|for|while)\b)' +
                '(?:[A-Za-z_~][\w:<>,~*&]*\s+)+' +
                '[A-Za-z_~][\w:<>~]*\s*\([^;{}]*\)\s*\{'
            ) -or
            $line -match (
                '^\s*[A-Za-z_~][\w:<>~]*\s*\([^;{}]*\)\s*\{'
            )

        if ($sameLineControl -or $sameLineFunction) {
            Add-Failure $Path (
                "Pseudo C++ block line $($i + 1): " +
                "function and control braces must use Allman style"
            )
        }
    }
}

function Get-RelativePath {
    param([string]$Path)
    return Resolve-Path -Relative $Path
}

function Find-HeadingIndex {
    param([string[]]$Lines, [string]$Heading)
    for ($i = 0; $i -lt $Lines.Count; ++$i) {
        if ($Lines[$i].Trim() -eq $Heading) {
            return $i
        }
    }
    return -1
}

function Get-Section {
    param([string[]]$Lines, [string]$Heading)
    $start = Find-HeadingIndex -Lines $Lines -Heading $Heading
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

function Test-FencedCodeLineLength {
    param([string]$Path, [string[]]$Lines)
    $inFence = $false
    for ($i = 0; $i -lt $Lines.Count; ++$i) {
        $line = $Lines[$i]
        if ($line -match '^\s*```') {
            $inFence = -not $inFence
            continue
        }
        if ($inFence -and $line.Length -gt 120) {
            Add-Failure $Path "line $($i + 1): fenced code exceeds 120 characters"
        }
        elseif ($inFence -and $line.Length -gt 80) {
            Add-Warning $Path "line $($i + 1): fenced code exceeds recommended 80 characters"
        }
    }
}

function Validate-DemoIssue {
    param([System.IO.FileInfo]$File)

    $relative = Get-RelativePath $File.FullName
    $lines = Get-Content -Encoding UTF8 $File.FullName
    $content = $lines -join "`n"
    $Summary = "## " + (New-Text @(0xC694, 0xC57D))
    $Result = "## " + (New-Text @(0xACB0, 0xACFC))
    $CoreImplementation = "## " + (New-Text @(0xD575, 0xC2EC, 0x20, 0xAD6C, 0xD604))
    $Flow = "## " + (New-Text @(0xCC98, 0xB9AC, 0x20, 0xD750, 0xB984))
    $Limits = "## " + (New-Text @(0xAD6C, 0xD604, 0x20, 0xBC94, 0xC704, 0xC640, 0x20, 0xD55C, 0xACC4))
    $Verification = "## " + (New-Text @(0xAC80, 0xC99D))
    $Details = "## " + (New-Text @(0xB354, 0x20, 0xC790, 0xC138, 0xD788, 0x20, 0xBCF4, 0xAE30))
    $required = @(
        $Summary,
        $Result,
        $CoreImplementation,
        $Flow,
        $Limits,
        $Verification,
        $Details
    )

    $previous = -1
    foreach ($heading in $required) {
        $index = Find-HeadingIndex -Lines $lines -Heading $heading
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

    $images = [regex]::Matches(
        $content,
        '!\[[^\]]+\]\((https://github\.com/.+/Docs/_assets/captures/.+\?raw=true|https://raw\.githubusercontent\.com/.+/Docs/_assets/captures/.+)\)'
    )
    if ($images.Count -lt 1) {
        Add-Failure $relative "Demo Issue must contain at least one GitHub Docs/_assets visual URL"
    }
    if (Test-GitHubStandaloneVideoAttachment -Content $content) {
        Add-Failure $relative `
            "Demo Issue body must link a dedicated video comment instead of embedding a standalone video attachment"
    }
    $visualCount = Get-GitHubRepresentativeVisualCount `
        -Content $content `
        -ImageCount $images.Count
    if ($visualCount -gt 3) {
        Add-Failure $relative "Demo Issue must use no more than three representative visuals"
    }

    $detailSection = Get-Section -Lines $lines -Heading $Details
    $detailText = $detailSection -join "`n"
    $coreSection = Get-Section -Lines $lines -Heading $CoreImplementation
    $coreText = $coreSection -join "`n"
    if ($detailText -notmatch '\]\(https://github\.com/.+/Docs/03_Demos/.+\.md\)') {
        Add-Failure $relative "details section must link a detailed Demo document"
    }
    if ($detailText -notmatch '\]\(https://github\.com/.+/Docs/02_Verification/.+\.md\)') {
        Add-Failure $relative "details section must link Verification"
    }
    $sourcePermalinkPattern =
        '\]\(https://github\.com/.+/blob/[0-9a-fA-F]{40}/' +
        '(?:Part[^/]+|Portfolio_RayTracer)/[^)]+\.(?:cpp|h)' +
        '#L\d+(?:-L\d+)?\)'
    if ($coreText -notmatch $sourcePermalinkPattern) {
        Add-Failure $relative `
            "core implementation must link a commit-pinned C++ source line range"
    }

    $PseudocodeWord = New-Text @(0xC758, 0xC0AC, 0xCF54, 0xB4DC)
    $pseudocodeHeadingPattern =
        '(?m)^#{3,}\s+.*' + [regex]::Escape($PseudocodeWord)
    if ($coreText -match $pseudocodeHeadingPattern -or
        $coreText -match 'Pseudo C\+\+') {
        if ($coreText -notmatch '(?ms)```cpp\s*.*?Pseudo C\+\+.*?```') {
            Add-Failure $relative "optional pseudocode must state 'Pseudo C++'"
        }
        $cppBlocks = [regex]::Matches($coreText, '(?ms)```cpp\s*(.*?)```')
        $pseudoBlocks = @($cppBlocks | Where-Object {
            $_.Groups[1].Value -match 'Pseudo C\+\+'
        })
        foreach ($pseudoBlock in $pseudoBlocks) {
            Test-PseudocodeAllmanStyle `
                -Path $relative `
                -Block $pseudoBlock.Groups[1].Value
        }
        if ($coreText -notmatch $sourcePermalinkPattern) {
            Add-Failure $relative `
                "optional pseudocode must include a commit-pinned source line link"
        }
    }

    Test-FencedCodeLineLength -Path $relative -Lines $lines
}

if (-not (Test-Path $GitHubRoot)) {
    throw "GitHub root not found: $GitHubRoot"
}

$demoRoot = Join-Path $GitHubRoot "issues/demo"
$demoFiles = @()
if (Test-Path $demoRoot) {
    $demoFiles = @(Get-ChildItem -Path $demoRoot -Filter "demo_*.md" -File -Recurse)
}
foreach ($file in $demoFiles) {
    Validate-DemoIssue -File $file
}

if ($Warnings.Count -gt 0) {
    Write-Host "GitHub quality warnings:" -ForegroundColor Yellow
    $Warnings | ForEach-Object { Write-Host " - $_" -ForegroundColor Yellow }
}

if ($Failures.Count -gt 0) {
    Write-Host "GitHub quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "GitHub quality validation passed." -ForegroundColor Green
exit 0
