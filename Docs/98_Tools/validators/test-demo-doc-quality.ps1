param(
    [string]$RulesPath = (Join-Path $PSScriptRoot "demo-doc-quality-rules.ps1")
)

$ErrorActionPreference = "Stop"
. $RulesPath

$FixtureRoot = Join-Path $PSScriptRoot "fixtures/demo-doc-link-label"
$PseudocodeFixtureRoot = Join-Path $PSScriptRoot "fixtures/demo-doc-pseudocode"
$Failures = [System.Collections.Generic.List[string]]::new()

function ConvertTo-LineEnding {
    param(
        [string]$Content,
        [ValidateSet("LF", "CRLF")]
        [string]$LineEnding
    )

    $normalized = $Content -replace "`r`n", "`n"
    $normalized = $normalized -replace "`r", "`n"
    if ($LineEnding -eq "CRLF") {
        return $normalized -replace "`n", "`r`n"
    }

    return $normalized
}

$validLines = Get-Content -LiteralPath `
    (Join-Path $FixtureRoot "valid.md.txt") -Encoding utf8
foreach ($line in $validLines) {
    $issues = @(Get-DemoCodeEvidenceLinkIssue -Line $line)
    if ($issues.Count -gt 0) {
        $Failures.Add("valid fixture rejected: $line")
    }
}

$invalidLines = Get-Content -LiteralPath `
    (Join-Path $FixtureRoot "invalid.md.txt") -Encoding utf8
foreach ($line in $invalidLines) {
    $issues = @(Get-DemoCodeEvidenceLinkIssue -Line $line)
    if ($issues.Count -eq 0) {
        $Failures.Add("invalid fixture accepted: $line")
    }
}

$validPseudocodeSource = Get-Content -Raw -LiteralPath `
    (Join-Path $PseudocodeFixtureRoot "valid.md.txt") -Encoding utf8
$invalidPseudocodeSource = Get-Content -Raw -LiteralPath `
    (Join-Path $PseudocodeFixtureRoot "invalid.md.txt") -Encoding utf8

foreach ($lineEnding in @("LF", "CRLF")) {
    $validPseudocode = ConvertTo-LineEnding `
        -Content $validPseudocodeSource `
        -LineEnding $lineEnding
    $validPseudocodeIssues = @(
        Get-DemoPseudocodeFenceIssue -Content $validPseudocode
    )
    if ($validPseudocodeIssues.Count -gt 0) {
        $Failures.Add(
            "valid $lineEnding pseudocode fixture rejected"
        )
    }

    $invalidPseudocode = ConvertTo-LineEnding `
        -Content $invalidPseudocodeSource `
        -LineEnding $lineEnding
    $invalidPseudocodeIssues = @(
        Get-DemoPseudocodeFenceIssue -Content $invalidPseudocode
    )
    if ($invalidPseudocodeIssues.Count -ne 2) {
        $Failures.Add(
            "invalid $lineEnding pseudocode fixture expected 2 issues, got " +
            $invalidPseudocodeIssues.Count
        )
    }
}

if ($Failures.Count -gt 0) {
    Write-Host "Demo document fixture validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Demo document fixture validation passed." -ForegroundColor Green
exit 0
