$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "github-visual-rules.ps1")

$videoUrl = "https://github.com/user-attachments/assets/12345678-1234-1234-1234-123456789abc"
$duplicateContent = "$videoUrl`n`n$videoUrl"

if ((Get-GitHubRepresentativeVisualCount -Content "text" -ImageCount 1) -ne 1)
{
    throw "Image-only visual count is incorrect."
}
if ((Get-GitHubRepresentativeVisualCount -Content $videoUrl -ImageCount 1) -ne 2)
{
    throw "Image and video visual count is incorrect."
}
if ((Get-GitHubRepresentativeVisualCount -Content $duplicateContent -ImageCount 0) -ne 1)
{
    throw "Duplicate video URL should be counted once."
}
if ((Get-GitHubRepresentativeVisualCount `
    -Content "[video]($videoUrl)" `
    -ImageCount 0) -ne 0)
{
    throw "Non-standalone attachment URL should not be treated as an embedded video."
}

Write-Host "GitHub visual fixture validation passed." -ForegroundColor Green
exit 0
