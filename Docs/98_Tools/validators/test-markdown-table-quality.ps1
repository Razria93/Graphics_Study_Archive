param(
    [string]$ValidatorPath = (
        Join-Path $PSScriptRoot "validate-markdown-table-quality.ps1"
    )
)

$ErrorActionPreference = "Stop"
$powerShellPath = [Diagnostics.Process]::GetCurrentProcess().MainModule.FileName
$FixtureRoot = Join-Path $PSScriptRoot "fixtures/markdown-table-quality"
$Failures = [System.Collections.Generic.List[string]]::new()

function Invoke-Fixture {
    param(
        [string]$Name,
        [string]$Path,
        [int]$ExpectedExitCode,
        [string]$ExpectedId,
        [int]$ExpectedLine,
        [int]$ExpectedDiagnosticCount
    )

    $output = & $powerShellPath `
        -NoProfile `
        -ExecutionPolicy Bypass `
        -File $ValidatorPath `
        -InputPath $Path 2>&1 | Out-String
    $exitCode = $LASTEXITCODE

    if ($exitCode -ne $ExpectedExitCode) {
        $Failures.Add(
            "$Name expected exit $ExpectedExitCode but received $exitCode"
        )
        return
    }

    $diagnosticCount = [regex]::Matches(
        $output,
        'TABLE-\d{3}'
    ).Count
    if ($diagnosticCount -ne $ExpectedDiagnosticCount) {
        $Failures.Add(
            "$Name expected $ExpectedDiagnosticCount diagnostic(s) but " +
            "received $diagnosticCount"
        )
    }

    if ($ExpectedId -and $output -notmatch [regex]::Escape($ExpectedId)) {
        $Failures.Add("$Name did not report $ExpectedId")
    }

    if ($ExpectedLine -gt 0 -and
        $output -notmatch ":${ExpectedLine}:\s+$ExpectedId") {
        $Failures.Add(
            "$Name did not report $ExpectedId at line $ExpectedLine"
        )
    }
}

Invoke-Fixture `
    -Name "valid fixtures" `
    -Path (Join-Path $FixtureRoot "valid") `
    -ExpectedExitCode 0 `
    -ExpectedDiagnosticCount 0

$invalidCases = @(
    @{
        Name = "separator extra column"
        File = "separator-extra.md.txt"
        Id = "TABLE-001"
        Line = 2
    },
    @{
        Name = "separator missing column"
        File = "separator-missing.md.txt"
        Id = "TABLE-001"
        Line = 2
    },
    @{
        Name = "data extra column"
        File = "data-extra.md.txt"
        Id = "TABLE-003"
        Line = 3
    },
    @{
        Name = "data missing column"
        File = "data-missing.md.txt"
        Id = "TABLE-003"
        Line = 3
    },
    @{
        Name = "invalid separator"
        File = "invalid-separator.md.txt"
        Id = "TABLE-002"
        Line = 2
    }
)

foreach ($case in $invalidCases) {
    Invoke-Fixture `
        -Name $case.Name `
        -Path (Join-Path (Join-Path $FixtureRoot "invalid") $case.File) `
        -ExpectedExitCode 1 `
        -ExpectedId $case.Id `
        -ExpectedLine $case.Line `
        -ExpectedDiagnosticCount 1
}

if ($Failures.Count -gt 0) {
    Write-Host "Markdown table fixture validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Markdown table fixture validation passed." -ForegroundColor Green
exit 0
