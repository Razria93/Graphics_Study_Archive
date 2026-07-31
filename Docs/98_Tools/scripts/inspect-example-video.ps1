[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$Path,
    [string]$FfmpegPath,
    [ValidateRange(1, 120)]
    [int]$ExpectedFrameRate = 30,
    [ValidateRange(0, 16384)]
    [int]$ExpectedWidth = 0,
    [ValidateRange(0, 16384)]
    [int]$ExpectedHeight = 0
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "video-quality-rules.ps1")

function Resolve-ToolPath
{
    param(
        [string]$ExplicitPath,
        [string]$CommandName,
        [string]$LocalPath
    )

    if ($ExplicitPath)
    {
        $resolved = [IO.Path]::GetFullPath($ExplicitPath)
        if (-not (Test-Path -LiteralPath $resolved -PathType Leaf))
        {
            throw "Tool not found: $resolved"
        }
        return $resolved
    }

    $command = Get-Command $CommandName -ErrorAction SilentlyContinue
    if ($null -ne $command)
    {
        return $command.Source
    }

    $resolvedLocal = [IO.Path]::GetFullPath($LocalPath)
    if (-not (Test-Path -LiteralPath $resolvedLocal -PathType Leaf))
    {
        throw "Tool not found: $resolvedLocal"
    }
    return $resolvedLocal
}

$repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot "../../.."))
$localFfmpeg = Join-Path $repoRoot "local/tools/ffmpeg/bin/ffmpeg.exe"
$resolvedFfmpeg = Resolve-ToolPath `
    -ExplicitPath $FfmpegPath `
    -CommandName "ffmpeg" `
    -LocalPath $localFfmpeg
$resolvedFfprobe = Join-Path (Split-Path -Parent $resolvedFfmpeg) "ffprobe.exe"
if (-not (Test-Path -LiteralPath $resolvedFfprobe -PathType Leaf))
{
    throw "FFprobe not found: $resolvedFfprobe"
}

$result = Test-ExampleVideoFile `
    -Path $Path `
    -FfprobePath $resolvedFfprobe `
    -FfmpegPath $resolvedFfmpeg `
    -ExpectedFrameRate $ExpectedFrameRate `
    -ExpectedWidth $ExpectedWidth `
    -ExpectedHeight $ExpectedHeight

$result | Format-List
