param(
    [string]$RulesPath = (Join-Path $PSScriptRoot "demo-doc-quality-rules.ps1")
)

$ErrorActionPreference = "Stop"
. $RulesPath

$FixtureRoot = Join-Path $PSScriptRoot "fixtures/demo-doc-link-label"
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

if ($Failures.Count -gt 0) {
    Write-Host "Demo document fixture validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Demo document fixture validation passed." -ForegroundColor Green
exit 0
