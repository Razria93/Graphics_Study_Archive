param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
    [string]$TrackedPathsFile,
    [string[]]$AllowedPath = @()
)

$ErrorActionPreference = "Stop"
$Failures = New-Object System.Collections.Generic.List[string]

if ($TrackedPathsFile)
{
    $trackedPaths = @(Get-Content -LiteralPath $TrackedPathsFile -Encoding UTF8 |
        Where-Object { $_.Trim() -and -not $_.Trim().StartsWith("#") })
}
else
{
    $trackedPaths = @(& git -C $Root ls-files -- "*.mp4" "*.mov" "*.webm")
    if ($LASTEXITCODE -ne 0)
    {
        throw "Failed to enumerate tracked video files."
    }
}

foreach ($path in $trackedPaths)
{
    $normalized = $path.Replace('\', '/')
    if ($AllowedPath -contains $normalized)
    {
        continue
    }
    $Failures.Add("$normalized :: tracked video requires an explicit Publication exception and user approval")
}

if ($Failures.Count -gt 0)
{
    Write-Host "Video asset quality validation failed." -ForegroundColor Red
    $Failures | ForEach-Object { Write-Host " - $_" -ForegroundColor Red }
    exit 1
}

Write-Host "Video asset quality validation passed ($($trackedPaths.Count) tracked video file(s))." -ForegroundColor Green
exit 0
