$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "github-visual-rules.ps1")
$powerShellPath = [Diagnostics.Process]::GetCurrentProcess().MainModule.FileName
$validatorPath = Join-Path $PSScriptRoot "validate-github-quality.ps1"
$fixtureRoot = Join-Path $PSScriptRoot "fixtures/github-visual-quality"

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

$tempRoot = Join-Path ([IO.Path]::GetTempPath()) (
    "github-visual-quality-" + [Guid]::NewGuid().ToString("N")
)
try
{
    $validGitHubRoot = Join-Path $tempRoot "valid/Docs/07_GitHub"
    $validDemoRoot = Join-Path $validGitHubRoot "issues/demo"
    New-Item -ItemType Directory -Path $validDemoRoot -Force | Out-Null

    $fixtureIndex = 0
    Get-ChildItem -LiteralPath (Join-Path $fixtureRoot "valid") `
        -Filter "*.md.txt" | ForEach-Object {
        $fixtureIndex++
        Copy-Item -LiteralPath $_.FullName -Destination (
            Join-Path $validDemoRoot "demo_fixture_$fixtureIndex.md"
        )
    }

    & $powerShellPath -NoProfile -ExecutionPolicy Bypass `
        -File $validatorPath `
        -Root (Join-Path $tempRoot "valid") `
        -GitHubRoot $validGitHubRoot
    if ($LASTEXITCODE -ne 0)
    {
        throw "Valid Demo Issue visual fixtures failed."
    }

    $invalidGitHubRoot = Join-Path $tempRoot "invalid/Docs/07_GitHub"
    $invalidDemoRoot = Join-Path $invalidGitHubRoot "issues/demo"
    New-Item -ItemType Directory -Path $invalidDemoRoot -Force | Out-Null
    Copy-Item -LiteralPath (
        Join-Path $fixtureRoot "invalid/standalone-video.md.txt"
    ) -Destination (Join-Path $invalidDemoRoot "demo_fixture.md")

    $invalidOutput = & $powerShellPath -NoProfile -ExecutionPolicy Bypass `
        -File $validatorPath `
        -Root (Join-Path $tempRoot "invalid") `
        -GitHubRoot $invalidGitHubRoot 2>&1 | Out-String
    if ($LASTEXITCODE -eq 0)
    {
        throw "Standalone Demo Issue video attachment fixture passed."
    }
    if ($invalidOutput -notmatch (
        "must link a dedicated video comment instead of embedding"
    ))
    {
        throw "Standalone video fixture did not report the expected failure."
    }
}
finally
{
    if (Test-Path -LiteralPath $tempRoot)
    {
        Remove-Item -LiteralPath $tempRoot -Recurse -Force
    }
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
