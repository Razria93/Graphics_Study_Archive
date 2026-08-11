param(
    [string]$ValidatorPath = (Join-Path $PSScriptRoot "validate-github-body.ps1")
)

$ErrorActionPreference = "Stop"
$powerShellPath = [Diagnostics.Process]::GetCurrentProcess().MainModule.FileName
$FixtureRoot = Join-Path $PSScriptRoot "fixtures/github-body"
$Failures = [System.Collections.Generic.List[string]]::new()

function Invoke-Fixture {
    param(
        [string]$Name,
        [string]$Path,
        [int]$ExpectedExitCode,
        [string]$ExpectedPattern
    )

    $Output = & $powerShellPath `
        -NoProfile `
        -ExecutionPolicy Bypass `
        -File $ValidatorPath `
        -InputPath $Path 2>&1 | Out-String
    if ($LASTEXITCODE -ne $ExpectedExitCode) {
        $Failures.Add(
            "$Name expected exit $ExpectedExitCode but received $LASTEXITCODE"
        )
    }
    elseif ($Output -notmatch [regex]::Escape($ExpectedPattern)) {
        $Failures.Add("$Name did not report expected text: $ExpectedPattern")
    }
}

$Cases = @(
    @{
        Name = "valid Chapter PR"
        Path = "valid/chapter/prs/chapter.md"
        ExpectedExitCode = 0
        ExpectedPattern = "GitHub body validation passed."
    }
    @{
        Name = "valid maintenance PR"
        Path = "valid/maintenance/prs/maintenance.md"
        ExpectedExitCode = 0
        ExpectedPattern = "GitHub body validation passed."
    }
    @{
        Name = "maintenance PR missing verification"
        Path = "invalid/maintenance-missing-section/prs/maintenance.md"
        ExpectedExitCode = 1
        ExpectedPattern = "missing required section"
    }
    @{
        Name = "maintenance PR mixed with Chapter section"
        Path = "invalid/maintenance-mixed/prs/maintenance.md"
        ExpectedExitCode = 1
        ExpectedPattern = "maintenance PR mixes Chapter-only section"
    }
    @{
        Name = "Chapter PR missing screenshots"
        Path = "invalid/chapter-missing-screenshots/prs/chapter.md"
        ExpectedExitCode = 1
        ExpectedPattern = "missing required section"
    }
)

foreach ($Case in $Cases) {
    Invoke-Fixture `
        -Name $Case.Name `
        -Path (Join-Path $FixtureRoot $Case.Path) `
        -ExpectedExitCode $Case.ExpectedExitCode `
        -ExpectedPattern $Case.ExpectedPattern
}

if ($Failures.Count -gt 0) {
    Write-Host "GitHub body fixture validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "GitHub body fixture validation passed." -ForegroundColor Green
exit 0
