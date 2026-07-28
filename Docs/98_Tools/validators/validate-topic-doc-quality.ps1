param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
    [string]$TopicsRoot = (Join-Path $Root "Docs/01_Topics")
)

$ErrorActionPreference = "Stop"

$Failures = New-Object System.Collections.Generic.List[string]
$CheckedFileCount = 0

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

function Get-RelativePath {
    param([string]$Path)

    return (Resolve-Path -Relative $Path).Replace("\", "/")
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

function Test-RequiredSection {
    param(
        [string]$RelativePath,
        [string[]]$Lines,
        [string]$Heading
    )

    $section = Get-SectionLines -Lines $Lines -Heading $Heading
    if ($null -eq $section) {
        Add-Failure $RelativePath "missing required heading: $Heading"
        return
    }

    $meaningful = @($section | Where-Object {
        $text = $_.Trim()
        -not [string]::IsNullOrWhiteSpace($text) -and $text -ne "-"
    })

    if ($meaningful.Count -eq 0) {
        Add-Failure $RelativePath "section is empty: $Heading"
    }
}

function Test-TopicDoc {
    param([System.IO.FileInfo]$File)

    $relativePath = Get-RelativePath $File.FullName
    $content = Get-Content -Raw -Encoding UTF8 $File.FullName
    $lines = @(Get-Content -Encoding UTF8 $File.FullName)

    if ($lines.Count -eq 0 -or $lines[0] -notmatch '^#\s+\S') {
        Add-Failure $relativePath "topic document must start with an H1 title"
    }

    $PurposeHeading = "## " + (New-Text @(0xBAA9, 0xC801))
    $ResponsibilityHeading = "## " + (New-Text @(0xCC45, 0xC784, 0x20, 0xBC94, 0xC704))
    $CoreConceptsHeading = "## " + (New-Text @(0xD575, 0xC2EC, 0x20, 0xAC1C, 0xB150))
    $LimitationsHeading = "## " + (New-Text @(0xD55C, 0xACC4))
    $RelatedDocsHeading = "## " + (New-Text @(0xAD00, 0xB828, 0x20, 0xBB38, 0xC11C))

    $requiredHeadings = @(
        $PurposeHeading,
        $ResponsibilityHeading,
        $CoreConceptsHeading,
        $LimitationsHeading,
        $RelatedDocsHeading
    )

    $previousIndex = -1
    foreach ($heading in $requiredHeadings) {
        $index = Find-HeadingIndex -Lines $lines -Heading $heading
        if ($index -ge 0 -and $index -lt $previousIndex) {
            Add-Failure $relativePath "heading order mismatch: $heading"
        }
        if ($index -ge 0) {
            $previousIndex = $index
        }

        Test-RequiredSection -RelativePath $relativePath -Lines $lines -Heading $heading
    }

    $conceptSection = Get-SectionLines -Lines $lines -Heading $CoreConceptsHeading
    if ($null -ne $conceptSection) {
        $conceptHeadings = @($conceptSection | Where-Object { $_ -match '^###\s+\S' })
        if ($conceptHeadings.Count -lt 2) {
            Add-Failure $relativePath "core concepts should contain at least two H3 concept sections"
        }
    }

    if ($content -match '(?im)\bTODO\b|\bTBD\b|<[^>]+>') {
        Add-Failure $relativePath "contains placeholder text (TODO/TBD/<...>)"
    }

    if ($content -match '(?i)(?:^|[(/`])local/' -or
        $content -match 'Docs/99_Legacy') {
        Add-Failure $relativePath "references local or legacy source paths"
    }

    if ($content -notmatch '\[[^\]]+\]\([^)]+/README\.md\)') {
        Add-Failure $relativePath "should link at least one Example README"
    }

    if ($content -notmatch 'Docs/02_Verification') {
        Add-Failure $relativePath "should reference Docs/02_Verification"
    }

    if ($content -notmatch 'Docs/03_Demos') {
        Add-Failure $relativePath "should reference Docs/03_Demos"
    }
}

if (-not (Test-Path -LiteralPath $TopicsRoot)) {
    throw "Topics root not found: $TopicsRoot"
}

$topicFiles = Get-ChildItem -Path $TopicsRoot -Filter "*.md" -File -Recurse |
    Where-Object {
        $_.Name -notin @("README.md", "topic-index.md", "AGENTS.md")
    }

foreach ($file in $topicFiles) {
    ++$CheckedFileCount
    Test-TopicDoc -File $file
}

if ($CheckedFileCount -eq 0) {
    Write-Host "Topic document quality validation failed." -ForegroundColor Red
    Write-Host " - no promoted Topic documents found" -ForegroundColor Red
    exit 1
}

if ($Failures.Count -gt 0) {
    Write-Host "Topic document quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Topic document quality validation passed ($CheckedFileCount file(s))." -ForegroundColor Green
exit 0
