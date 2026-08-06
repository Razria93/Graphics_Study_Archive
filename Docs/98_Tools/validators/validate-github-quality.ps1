param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
    [string]$GitHubRoot = (Join-Path $Root "Docs/07_GitHub"),
    [string[]]$InputPath
)

$ErrorActionPreference = "Stop"

$Failures = New-Object System.Collections.Generic.List[string]
$Warnings = New-Object System.Collections.Generic.List[string]

function New-Text {
    param([int[]]$CodePoints)

    return -join ($CodePoints | ForEach-Object { [char]$_ })
}

function Add-Failure {
    param(
        [string]$Path,
        [string]$Message
    )

    $Failures.Add("$Path :: $Message")
}

function Add-Warning {
    param(
        [string]$Path,
        [string]$Message
    )

    $Warnings.Add("$Path :: $Message")
}

function Get-RelativePath {
    param([string]$Path)
    return Resolve-Path -Relative $Path
}

function Read-Lines {
    param([string]$Path)
    return (Get-Content -Encoding UTF8 $Path)
}

function Find-HeadingIndex {
    param(
        [string[]]$Lines,
        [string]$Heading
    )

    for ($i = 0; $i -lt $Lines.Count; ++$i) {
        if ($Lines[$i].Trim() -eq $Heading) {
            return $i
        }
    }
    return -1
}

function Get-SectionLines {
    param(
        [string[]]$Lines,
        [string]$Heading
    )

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

    if ($end -le ($start + 1)) {
        return @()
    }

    return $Lines[($start + 1)..($end - 1)]
}

function Test-LineLength {
    param(
        [string]$RelativePath,
        [string[]]$Lines,
        [int]$SoftLimit = 100
    )

    for ($i = 0; $i -lt $Lines.Count; ++$i) {
        $line = $Lines[$i]
        if ($line -match '^\s*\|' -or $line -match '^\s*!\[' -or $line -match 'https://') {
            continue
        }

        if ($line.Length -gt $SoftLimit -and $line -match '^\s*[^#\|]') {
            Add-Warning $RelativePath "line $($i + 1): long line ($($line.Length) chars), split for readability"
        }
    }
}

function Test-DemoPseudocode {
    param(
        [string]$RelativePath,
        [string[]]$Lines
    )

    $PseudoHeading = "## " + (New-Text @(0xD575, 0xC2EC, 0x20, 0xB85C, 0xC9C1, 0x20, 0xC758, 0xC0AC, 0xCF54, 0xB4DC))
    $heading = $PseudoHeading
    $section = Get-SectionLines -Lines $Lines -Heading $heading
    if ($null -eq $section) {
        Add-Failure $RelativePath "missing section: $heading"
        return
    }

    $text = ($section -join "`n")

    if ($text -notmatch '```cpp') {
        Add-Failure $RelativePath "pseudocode section must contain cpp fenced blocks"
    }

    if ($text -notmatch 'Pseudo C\+\+') {
        Add-Failure $RelativePath "pseudocode block should state 'Pseudo C++'"
    }

    if ($text -notmatch 'void\s+\w+Pseudo\s*\(') {
        Add-Failure $RelativePath "pseudocode function signature should use *Pseudo naming"
    }

    $SourceCodeLabel = (New-Text @(0xC6D0, 0xBCF8, 0x20, 0xCF54, 0xB4DC))
    $codeLinkCount = ([regex]::Matches($text, ($SourceCodeLabel + ':\s*\[.+\]\(https://github\.com/.+\)'))).Count
    if ($codeLinkCount -lt 1) {
        Add-Failure $RelativePath "pseudocode section must include original source link"
    }
}

function Test-DemoAssetsTable {
    param(
        [string]$RelativePath,
        [string[]]$Lines
    )

    $heading = "## Demo Assets"
    $section = Get-SectionLines -Lines $Lines -Heading $heading
    if ($null -eq $section) {
        Add-Failure $RelativePath "missing section: $heading"
        return
    }

    $text = ($section -join "`n")
    $requiredRows = @("Input screenshot", "Result screenshot", "Result image", "Video")
    foreach ($row in $requiredRows) {
        if ($text -notmatch [regex]::Escape($row)) {
            Add-Failure $RelativePath "Demo Assets table missing row: $row"
        }
    }
}

function Validate-DemoIssue {
    param([System.IO.FileInfo]$File)

    $relative = Get-RelativePath $File.FullName
    $lines = Read-Lines $File.FullName
    $content = ($lines -join "`n")

    $Summary = "## " + (New-Text @(0xC694, 0xC57D))
    $Goals = "## " + (New-Text @(0xD575, 0xC2EC, 0x20, 0xBAA9, 0xD45C))
    $VisualInfo = "## " + (New-Text @(0xC2DC, 0xAC01, 0x20, 0xC815, 0xBCF4))
    $ImplHighlights = "## " + (New-Text @(0xAD6C, 0xD604, 0x20, 0xD558, 0xC774, 0xB77C, 0xC774, 0xD2B8))
    $PseudoHeading = "## " + (New-Text @(0xD575, 0xC2EC, 0x20, 0xB85C, 0xC9C1, 0x20, 0xC758, 0xC0AC, 0xCF54, 0xB4DC))
    $Verify = "## " + (New-Text @(0xAC80, 0xC99D, 0x20, 0xC0C1, 0xD0DC))
    $ImplementationLimits = "## " + (New-Text @(0xAD6C, 0xD604, 0x20, 0xBC94, 0xC704, 0xC640, 0x20, 0xD55C, 0xACC4))
    $RelatedDocs = "## " + (New-Text @(0xAD00, 0xB828, 0x20, 0xBB38, 0xC11C))

    $requiredHeadings = @(
        $Summary,
        $Goals,
        "## Demo Assets",
        $VisualInfo,
        $ImplHighlights,
        $PseudoHeading,
        $Verify,
        $ImplementationLimits,
        $RelatedDocs
    )

    $lastIndex = -1
    foreach ($h in $requiredHeadings) {
        $index = Find-HeadingIndex -Lines $lines -Heading $h
        if ($index -lt 0) {
            Add-Failure $relative "missing required heading: $h"
            continue
        }
        if ($index -lt $lastIndex) {
            Add-Failure $relative "heading order mismatch: $h"
        }
        $lastIndex = $index
    }

    Test-DemoAssetsTable -RelativePath $relative -Lines $lines
    Test-DemoPseudocode -RelativePath $relative -Lines $lines
    Test-LineLength -RelativePath $relative -Lines $lines -SoftLimit 120

    if ($content -notmatch '!\[[^\]]+\]\(https://github\.com/.+\?raw=true\)') {
        Add-Failure $relative "visual section should include GitHub absolute image URLs"
    }
}

function Validate-All {
    if ($InputPath) {
        $demoFiles = foreach ($path in $InputPath) {
            if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
                throw "Input path is not a file: $path"
            }

            $file = Get-Item -LiteralPath $path
            if ($file.DirectoryName -notmatch '[\\/]issues[\\/]demo$' -or
                $file.Name -notmatch '^demo_.+\.md$') {
                throw "Input path is not a Demo Issue candidate: $path"
            }

            $file
        }
    }
    else {
        if (-not (Test-Path $GitHubRoot)) {
            throw "GitHub root not found: $GitHubRoot"
        }

        $demoFiles = Get-ChildItem -Path (Join-Path $GitHubRoot "issues/demo") -Filter "demo_*.md" -File -Recurse
    }

    foreach ($f in @($demoFiles | Sort-Object FullName -Unique)) {
        Validate-DemoIssue -File $f
    }
}

Validate-All

if ($Warnings.Count -gt 0) {
    $Warnings | ForEach-Object { Write-Warning $_ }
}

if ($Failures.Count -gt 0) {
    Write-Host "GitHub quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "GitHub quality validation passed." -ForegroundColor Green
exit 0
