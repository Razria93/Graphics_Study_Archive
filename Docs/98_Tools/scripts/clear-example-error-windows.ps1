[CmdletBinding()]
param(
    [string]$TargetProcessName,
    [string]$ExpectedTitle,
    [Nullable[DateTime]]$SinceTime,
    [string[]]$Pattern,
    [switch]$Close,
    [string]$DiagnosticsDirectory = "local/diagnostics/example-error-windows",
    [ValidateRange(1, 10)]
    [int]$MaxDrainPasses = 5,
    [ValidateRange(1, 10)]
    [int]$QuietSeconds = 3
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "example-error-window-utils.ps1")

$diagnosticsPath = [IO.Path]::GetFullPath($DiagnosticsDirectory)
if (-not (Test-Path -LiteralPath $diagnosticsPath -PathType Container))
{
    [void](New-Item -ItemType Directory -Path $diagnosticsPath -Force)
}

$timestamp = Get-Date -Format "yyyyMMdd_HHmmss"
$beforePath = Join-Path $diagnosticsPath "error-window-candidates-$timestamp.json"
$afterPath = Join-Path $diagnosticsPath "error-window-candidates-$timestamp-after.json"

$before = @(Get-ExampleErrorWindowCandidate `
    -TargetProcessName $TargetProcessName `
    -ExpectedTitle $ExpectedTitle `
    -SinceTime $SinceTime `
    -Pattern $Pattern)
$before | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $beforePath -Encoding UTF8

if ($before.Count -eq 0)
{
    Write-Host "PASS: no example error windows found."
    Write-Host "Diagnostics: $beforePath"
    exit 0
}

if (-not $Close)
{
    Write-Host "DRY-RUN: $($before.Count) candidate(s) recorded. Use -Close to send WM_CLOSE."
    Write-Host "Diagnostics: $beforePath"
    $before | Format-Table Handle, Title, ClassName, ProcessId, ProcessName -AutoSize
    exit 2
}

$current = $before
for ($pass = 1; $pass -le $MaxDrainPasses -and $current.Count -gt 0; ++$pass)
{
    Write-Host "Drain pass ${pass}: closing $($current.Count) candidate(s)."
    foreach ($candidate in $current)
    {
        [void](Close-ExampleErrorWindow `
            -HandleInt64 $candidate.HandleInt64 `
            -Confirm:$false)
    }

    Start-Sleep -Seconds 1
    $current = @(Get-ExampleErrorWindowCandidate `
        -TargetProcessName $TargetProcessName `
        -ExpectedTitle $ExpectedTitle `
        -SinceTime $SinceTime `
        -Pattern $Pattern)
}

if ($current.Count -eq 0)
{
    Start-Sleep -Seconds $QuietSeconds
}
$after = @(Get-ExampleErrorWindowCandidate `
    -TargetProcessName $TargetProcessName `
    -ExpectedTitle $ExpectedTitle `
    -SinceTime $SinceTime `
    -Pattern $Pattern)
$after | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath $afterPath -Encoding UTF8

if ($after.Count -gt 0)
{
    Write-Host "FAIL: $($after.Count) example error window candidate(s) remain."
    Write-Host "Before: $beforePath"
    Write-Host "After: $afterPath"
    $after | Format-Table Handle, Title, ClassName, ProcessId, ProcessName -AutoSize
    exit 3
}

Write-Host "PASS: closed $($before.Count) example error window candidate(s)."
Write-Host "Before: $beforePath"
Write-Host "After: $afterPath"
exit 0
