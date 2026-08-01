param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
    [string]$DemosRoot = (Join-Path $Root "Docs/03_Demos")
)

$ErrorActionPreference = "Stop"

$Failures = New-Object System.Collections.Generic.List[string]

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

    return Resolve-Path -Relative $Path
}

function Get-HeadingIndex {
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

    $start = Get-HeadingIndex -Lines $Lines -Heading $Heading
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

function Split-MarkdownRow {
    param([string]$Line)

    $trimmed = $Line.Trim()
    if (-not ($trimmed.StartsWith("|") -and $trimmed.EndsWith("|"))) {
        return @()
    }

    $inner = $trimmed.Substring(1, $trimmed.Length - 2)
    return @($inner.Split("|") | ForEach-Object { $_.Trim() })
}

function Test-RequiredHeadingOrder {
    param(
        [string]$RelativePath,
        [string[]]$Lines
    )

    $Scope = "## " + (New-Text @(0xBC94, 0xC704))
    $DemoList = "## Demo " + (New-Text @(0xBAA9, 0xB85D))
    $UpdateRules = "## " + (New-Text @(0xAC31, 0xC2E0, 0x20, 0xAE30, 0xC900))

    $required = @($Scope, $DemoList, $UpdateRules)
    $prev = -1

    foreach ($h in $required) {
        $idx = Get-HeadingIndex -Lines $Lines -Heading $h
        if ($idx -lt 0) {
            Add-Failure $RelativePath "missing required heading: $h"
            continue
        }

        if ($idx -lt $prev) {
            Add-Failure $RelativePath "heading order mismatch: $h"
        }

        $prev = $idx
    }
}

function Test-ScopeSection {
    param(
        [string]$RelativePath,
        [string[]]$Lines
    )

    $Scope = "## " + (New-Text @(0xBC94, 0xC704))
    $section = Get-SectionLines -Lines $Lines -Heading $Scope
    if ($null -eq $section) {
        return
    }

    $MainDemoLabel = "- " + (New-Text @(0xC8FC, 0xC694, 0x20, 0x64, 0x65, 0x6D, 0x6F, 0x20, 0xD6C4, 0xBCF4)) + ":"
    $NoteLabel = "- " + (New-Text @(0xBE44, 0xACE0)) + ":"

    $text = ($section -join "`n")
    if ($text -notmatch [regex]::Escape($MainDemoLabel)) {
        Add-Failure $RelativePath "scope section should include '- 주요 demo 후보:'"
    }
    if ($text -notmatch [regex]::Escape($NoteLabel)) {
        Add-Failure $RelativePath "scope section should include '- 비고:'"
    }
}

function Test-UpdateRulesSection {
    param(
        [string]$RelativePath,
        [string[]]$Lines
    )

    $UpdateRules = "## " + (New-Text @(0xAC31, 0xC2E0, 0x20, 0xAE30, 0xC900))
    $section = Get-SectionLines -Lines $Lines -Heading $UpdateRules
    if ($null -eq $section) {
        return
    }

    $bullets = @($section | Where-Object { $_.Trim().StartsWith("- ") })
    if ($bullets.Count -lt 3) {
        Add-Failure $RelativePath "update rules section should have at least 3 bullet rules"
    }
}

function Test-DemoTable {
    param(
        [string]$RelativePath,
        [string]$FileDirectory,
        [string[]]$Lines
    )

    $DemoList = "## Demo " + (New-Text @(0xBAA9, 0xB85D))
    $section = Get-SectionLines -Lines $Lines -Heading $DemoList
    if ($null -eq $section) {
        return
    }

    $table = @($section | Where-Object { $_ -match '^\|' })
    if ($table.Count -lt 5) {
        Add-Failure $RelativePath "demo table is too short"
        return
    }

    $header = Split-MarkdownRow -Line $table[0]
    $ColDemoCandidate = "Demo " + (New-Text @(0xD6C4, 0xBCF4))
    $ColDetailedDemo = (New-Text @(0xC0C1, 0xC138)) + " Demo"
    $ColExample = (New-Text @(0xC5F0, 0xACB0)) + " Example"
    $ColTopic = (New-Text @(0xC5F0, 0xACB0)) + " Topic"
    $ColCaptureResult = "Capture/Result"
    $ColGitHubIssue = "GitHub Demo Issue"
    $ColStatus = (New-Text @(0xC0C1, 0xD0DC))
    $ColNote = (New-Text @(0xBE44, 0xACE0))

    $RowMinCapture = (New-Text @(0xCD5C, 0xC18C)) + " capture"
    $RowRepresentativeCapture = (New-Text @(0xB300, 0xD45C)) + " capture"
    $RowVideo = "video"

    $StatusUnknown = (New-Text @(0xBBF8, 0xD655, 0xC778))
    $StatusCandidate = (New-Text @(0xD6C4, 0xBCF4))
    $StatusReady = (New-Text @(0xD655, 0xBCF4))
    $StatusHold = (New-Text @(0xBCF4, 0xB958))
    $StatusExcluded = (New-Text @(0xC81C, 0xC678))
    $NoneText = (New-Text @(0xC5C6, 0xC74C))
    $IssueCandidate = (New-Text @(0xAC8C, 0xC2DC, 0x20, 0xD6C4, 0xBCF4))
    $IssueUnpublished = (New-Text @(0xBBF8, 0xAC8C, 0xC2DC))
    $requiredHeader = @(
        $ColDemoCandidate,
        $ColDetailedDemo,
        $ColExample,
        $ColTopic,
        "Verification",
        $ColCaptureResult,
        $ColGitHubIssue,
        $ColStatus,
        $ColNote
    )

    foreach ($h in $requiredHeader) {
        if (-not ($header -contains $h)) {
            Add-Failure $RelativePath "demo table missing column: $h"
        }
    }

    $rows = @()
    for ($i = 2; $i -lt $table.Count; ++$i) {
        $cells = Split-MarkdownRow -Line $table[$i]
        if ($cells.Count -lt $header.Count) {
            Add-Failure $RelativePath "demo row has fewer columns than its header: $($table[$i])"
            continue
        }
        $rows += ,$cells
    }

    $requiredRows = @($RowMinCapture, $RowRepresentativeCapture, $RowVideo)
    foreach ($required in $requiredRows) {
        $found = $false
        foreach ($row in $rows) {
            if ($row[0] -eq $required) {
                $found = $true
                break
            }
        }
        if (-not $found) {
            Add-Failure $RelativePath "demo table missing row: $required"
        }
    }

    $allowedStatuses = @(
        $StatusUnknown,
        $StatusCandidate,
        $StatusReady,
        $StatusHold,
        $StatusExcluded
    )

    foreach ($row in $rows) {
        $name = $row[[Array]::IndexOf($header, $ColDemoCandidate)]
        $detailedDemo = $row[[Array]::IndexOf($header, $ColDetailedDemo)]
        $example = $row[[Array]::IndexOf($header, $ColExample)]
        $verification = $row[[Array]::IndexOf($header, "Verification")]
        $capture = $row[[Array]::IndexOf($header, $ColCaptureResult)]
        $githubIssue = $row[[Array]::IndexOf($header, $ColGitHubIssue)]
        $status = $row[[Array]::IndexOf($header, $ColStatus)]
        $note = $row[[Array]::IndexOf($header, $ColNote)]

        if (-not ($allowedStatuses -contains $status)) {
            Add-Failure $RelativePath "row '$name' has invalid status: $status"
        }

        if ($verification -notmatch '(Docs/)?02_Verification') {
            Add-Failure $RelativePath "row '$name' should reference Docs/02_Verification"
        }

        if ([string]::IsNullOrWhiteSpace($note) -or $note -eq "-") {
            Add-Failure $RelativePath "row '$name' should include a non-empty note"
        }

        if ($status -eq $StatusReady) {
            if ($detailedDemo -notmatch '\[[^\]]+\]\(([^)]+\.md)\)') {
                Add-Failure $RelativePath "row '$name' is '확보' but does not link a detailed Demo"
            }

            if ($capture -eq $NoneText) {
                Add-Failure $RelativePath "row '$name' is '확보' but Capture/Result is '없음'"
            }

            $usesTrackedAsset = $capture -match '(Docs/)?_assets/(captures|videos|diagrams)'
            $usesSelectedLocalVideo = (
                $name -eq $RowVideo -and
                $capture -match '(?i)\bselected local video\b'
            )
            $usesPublishedDemoIssue = (
                $name -eq $RowVideo -and
                $capture -match 'https://github\.com/[^/]+/[^/]+/issues/\d+'
            )
            if (-not ($usesTrackedAsset -or $usesSelectedLocalVideo -or $usesPublishedDemoIssue)) {
                Add-Failure $RelativePath "row '$name' is '확보' but Capture/Result has no tracked asset, selected local video, or published Demo Issue"
            }
            if ($usesPublishedDemoIssue -and $githubIssue -notmatch 'https://github\.com/[^/]+/[^/]+/issues/\d+') {
                Add-Failure $RelativePath "row '$name' references a published video without a GitHub Demo Issue"
            }
        }

        foreach ($cell in @($detailedDemo, $githubIssue)) {
            $matches = [regex]::Matches($cell, '\[[^\]]+\]\(([^)]+)\)')
            foreach ($match in $matches) {
                $target = $match.Groups[1].Value.Split('#')[0]
                if ($target -notmatch '^https?://') {
                    $resolved = [IO.Path]::GetFullPath((Join-Path $FileDirectory $target))
                    if (-not (Test-Path -LiteralPath $resolved)) {
                        Add-Failure $RelativePath "row '$name' has a broken Demo link: $target"
                    }
                }
            }
        }

        if ($githubIssue -match [regex]::Escape($IssueCandidate) -and
            $githubIssue -notmatch '\[[^\]]+\]\([^)]+07_GitHub/issues/demo/[^)]+\.md\)') {
            Add-Failure $RelativePath "row '$name' marks a Demo Issue candidate without linking its tracked candidate"
        }

        if ($githubIssue -ne $IssueUnpublished -and
            $githubIssue -notmatch [regex]::Escape($IssueCandidate) -and
            $githubIssue -notmatch 'https://github\.com/[^/]+/[^/]+/issues/\d+') {
            Add-Failure $RelativePath "row '$name' has an invalid GitHub Demo Issue value"
        }

        if ($name -eq $RowVideo -and $status -eq $StatusExcluded -and $capture -ne $NoneText) {
            Add-Failure $RelativePath "video row is '제외' but Capture/Result is not '없음'"
        }

        if ($name -eq $RowMinCapture -and $example -eq $StatusUnknown) {
            Add-Failure $RelativePath "minimum capture row should identify target Example"
        }
    }
}

function Validate-DemoIndex {
    param([System.IO.FileInfo]$File)

    $relative = Get-RelativePath $File.FullName
    $content = Get-Content -Encoding UTF8 $File.FullName -Raw
    $lines = $content -split "`r?`n"

    if ($content -match '(?im)\bTODO\b|\bTBD\b|<[^>]+>') {
        Add-Failure $relative "contains placeholder text (TODO/TBD/<...>)"
    }

    Test-RequiredHeadingOrder -RelativePath $relative -Lines $lines
    Test-ScopeSection -RelativePath $relative -Lines $lines
    Test-DemoTable -RelativePath $relative -FileDirectory $File.DirectoryName -Lines $lines
    Test-UpdateRulesSection -RelativePath $relative -Lines $lines
}

function Validate-All {
    if (-not (Test-Path $DemosRoot)) {
        throw "Demos root not found: $DemosRoot"
    }

    $demoIndexFiles = Get-ChildItem -Path $DemosRoot -Filter "demo-index.md" -File -Recurse
    foreach ($file in $demoIndexFiles) {
        Validate-DemoIndex -File $file
    }
}

Validate-All

if ($Failures.Count -gt 0) {
    Write-Host "Demo index quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Demo index quality validation passed." -ForegroundColor Green
exit 0
