$ErrorActionPreference = "Stop"

$validator = Join-Path $PSScriptRoot "validate-demo-index-quality.ps1"
$validRoot = Join-Path $PSScriptRoot "fixtures/demo-index-video/valid"
$invalidRoot = Join-Path $PSScriptRoot "fixtures/demo-index-video/invalid"

& powershell -NoProfile -ExecutionPolicy Bypass `
    -File $validator `
    -Root $validRoot `
    -DemosRoot (Join-Path $validRoot "Docs/03_Demos")
if ($LASTEXITCODE -ne 0)
{
    throw "Valid Demo index video fixture failed."
}

$invalidOutput = (& powershell -NoProfile -ExecutionPolicy Bypass `
    -File $validator `
    -Root $invalidRoot `
    -DemosRoot (Join-Path $invalidRoot "Docs/03_Demos") 2>&1 | Out-String)
if ($LASTEXITCODE -eq 0)
{
    throw "Invalid Demo index video fixture passed."
}
if ($invalidOutput -notmatch 'has no tracked asset, selected local video, or published Demo Issue')
{
    throw "Invalid Demo index video fixture did not report the expected failure."
}

Write-Host "Demo index video fixture validation passed." -ForegroundColor Green
exit 0
