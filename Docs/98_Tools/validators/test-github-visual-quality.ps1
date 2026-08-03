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

if (-not (Test-GitHubStandaloneVideoAttachment -Content $videoUrl))
{
    throw "Standalone video attachment should be detected for PR body policy checks."
}

if (Test-GitHubStandaloneVideoAttachment -Content "[video comment]($videoUrl)")
{
    throw "Linked video reference should not be treated as an embedded attachment."
}

function New-UnicodeText
{
    param([int[]]$CodePoints)

    return -join ($CodePoints | ForEach-Object { [char]$_ })
}

$templatesRoot = Join-Path $PSScriptRoot "../templates"
$demoIssueTemplate = Get-Content -Encoding UTF8 `
    (Join-Path $templatesRoot "demo-issue.md") -Raw
$prBodyTemplate = Get-Content -Encoding UTF8 `
    (Join-Path $templatesRoot "pr-body.md") -Raw
$videoCommentTemplate = Get-Content -Encoding UTF8 `
    (Join-Path $templatesRoot "demo-video-comment.md") -Raw

if (Test-GitHubStandaloneVideoAttachment -Content $demoIssueTemplate)
{
    throw "Demo Issue template must not embed a video attachment."
}

if (Test-GitHubStandaloneVideoAttachment -Content $prBodyTemplate)
{
    throw "PR body template must not embed a video attachment."
}

$requiredFields = @(
    "- $(New-UnicodeText @(0xC870, 0xC791)):"
    "- $(New-UnicodeText @(0xAD00, 0xCC30)):"
    "- $(New-UnicodeText @(0xB300, 0xC751)) Demo:"
)

foreach ($requiredField in $requiredFields)
{
    if ($videoCommentTemplate -notmatch [regex]::Escape($requiredField))
    {
        throw "Demo video comment template is missing field: $requiredField"
    }
}

if ($videoCommentTemplate -notmatch [regex]::Escape(
    "https://github.com/user-attachments/assets/<attachment-id>"))
{
    throw "Demo video comment template must contain one attachment placeholder."
}

Write-Host "GitHub visual fixture validation passed." -ForegroundColor Green
exit 0
