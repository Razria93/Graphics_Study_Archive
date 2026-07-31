param(
    [string]$RulesPath = (Join-Path $PSScriptRoot "demo-doc-quality-rules.ps1")
)

$ErrorActionPreference = "Stop"
. $RulesPath

$FixtureRoot = Join-Path $PSScriptRoot "fixtures/demo-doc-link-label"
$PseudocodeFixtureRoot = Join-Path $PSScriptRoot "fixtures/demo-doc-pseudocode"
$Failures = [System.Collections.Generic.List[string]]::new()

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

$validPseudocode = Get-Content -Raw -LiteralPath `
    (Join-Path $PseudocodeFixtureRoot "valid.md.txt") -Encoding utf8
$validPseudocodeIssues = @(
    Get-DemoPseudocodeFenceIssue -Content $validPseudocode
)
if ($validPseudocodeIssues.Count -gt 0) {
    $Failures.Add("valid pseudocode fixture rejected")
}

$invalidPseudocode = Get-Content -Raw -LiteralPath `
    (Join-Path $PseudocodeFixtureRoot "invalid.md.txt") -Encoding utf8
$invalidPseudocodeIssues = @(
    Get-DemoPseudocodeFenceIssue -Content $invalidPseudocode
)
if ($invalidPseudocodeIssues.Count -ne 2) {
    $Failures.Add(
        "invalid pseudocode fixture expected 2 issues, got " +
        $invalidPseudocodeIssues.Count
    )
}

if ($Failures.Count -gt 0) {
    Write-Host "Demo document fixture validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Demo document fixture validation passed." -ForegroundColor Green
exit 0
