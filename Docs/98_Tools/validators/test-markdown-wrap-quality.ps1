param(
    [string]$ValidatorPath = (Join-Path $PSScriptRoot "validate-markdown-wrap-quality.ps1")
)

$ErrorActionPreference = "Stop"
$FixtureRoot = Join-Path $PSScriptRoot "fixtures/markdown-wrap"
$Failures = [System.Collections.Generic.List[string]]::new()

function Invoke-Fixture {
    param(
        [string]$Name,
        [string]$Path,
        [int]$ExpectedExitCode,
        [switch]$WarningAsFailure
    )

    $arguments = @(
        "-NoProfile",
        "-ExecutionPolicy", "Bypass",
        "-File", $ValidatorPath,
        "-InputPath", $Path
    )
    if ($WarningAsFailure) {
        $arguments += "-WarningAsFailure"
    }

    & powershell @arguments *> $null
    if ($LASTEXITCODE -ne $ExpectedExitCode) {
        $Failures.Add(
            "$Name expected exit $ExpectedExitCode but received $LASTEXITCODE"
        )
    }
}

Invoke-Fixture `
    -Name "valid fixtures" `
    -Path (Join-Path $FixtureRoot "valid") `
    -ExpectedExitCode 0
Invoke-Fixture `
    -Name "invalid fixtures" `
    -Path (Join-Path $FixtureRoot "invalid") `
    -ExpectedExitCode 1
Invoke-Fixture `
    -Name "warning fixtures" `
    -Path (Join-Path $FixtureRoot "warning") `
    -ExpectedExitCode 0
Invoke-Fixture `
    -Name "strict warning fixtures" `
    -Path (Join-Path $FixtureRoot "warning") `
    -ExpectedExitCode 1 `
    -WarningAsFailure

if ($Failures.Count -gt 0) {
    Write-Host "Markdown wrap fixture validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Markdown wrap fixture validation passed." -ForegroundColor Green
exit 0
