$ErrorActionPreference = "Stop"
$powerShellPath = [Diagnostics.Process]::GetCurrentProcess().MainModule.FileName

$validator = Join-Path $PSScriptRoot "validate-video-asset-quality.ps1"
$validFixture = Join-Path $PSScriptRoot "fixtures/video-asset-quality/valid/paths.txt"
$invalidFixture = Join-Path $PSScriptRoot "fixtures/video-asset-quality/invalid/paths.txt"

& $powerShellPath -NoProfile -ExecutionPolicy Bypass -File $validator -TrackedPathsFile $validFixture
if ($LASTEXITCODE -ne 0)
{
    throw "Valid video asset fixture failed."
}

$invalidOutput = (& $powerShellPath -NoProfile -ExecutionPolicy Bypass `
    -File $validator -TrackedPathsFile $invalidFixture 2>&1 | Out-String)
if ($LASTEXITCODE -eq 0)
{
    throw "Invalid video asset fixture passed."
}
if ($invalidOutput -notmatch 'tracked video requires an explicit Publication exception')
{
    throw "Invalid video asset fixture did not report the expected failure."
}

Write-Host "Video asset fixture validation passed." -ForegroundColor Green
exit 0
