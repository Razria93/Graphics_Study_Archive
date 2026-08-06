param(
    [string]$ValidatorPath = (
        Join-Path $PSScriptRoot "validate-markdown-render-quality.ps1"
    )
)

$ErrorActionPreference = "Stop"
$powerShellPath = [Diagnostics.Process]::GetCurrentProcess().MainModule.FileName
$FixtureRoot = Join-Path $PSScriptRoot "fixtures/markdown-render-quality"
$Failures = [System.Collections.Generic.List[string]]::new()

function Invoke-Fixture {
    param(
        [string]$Name,
        [string]$Path,
        [int]$ExpectedExitCode,
        [string]$ExpectedId,
        [int]$ExpectedLine
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
    -ExpectedExitCode 0
$invalidCases = @(
    @{
        Name = "list range pair"
        File = "single-tilde-ranges.md.txt"
        Line = 1
    },
    @{
        Name = "table range pair"
        File = "table-cell.md.txt"
        Line = 3
    },
    @{
        Name = "inline code range delimiter"
        File = "inline-code-range.md.txt"
        Line = 1
    }
)

foreach ($case in $invalidCases) {
    Invoke-Fixture `
        -Name $case.Name `
        -Path (Join-Path (Join-Path $FixtureRoot "invalid") $case.File) `
        -ExpectedExitCode 1 `
        -ExpectedId "MDRENDER-001" `
        -ExpectedLine $case.Line
}

if ($Failures.Count -gt 0) {
    Write-Host "Markdown render fixture validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Markdown render fixture validation passed." -ForegroundColor Green
exit 0
