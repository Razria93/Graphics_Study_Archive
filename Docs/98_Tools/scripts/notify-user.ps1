param(
    [ValidateSet("Complete", "Attention", "Blocked")]
    [string]$Event = "Attention",

    [ValidateRange(0, 300)]
    [int]$DelaySeconds = 0,

    [switch]$ScheduledPlayback
)

try
{
    if ($DelaySeconds -gt 0 -and -not $ScheduledPlayback)
    {
        $powerShellPath = [Diagnostics.Process]::GetCurrentProcess().MainModule.FileName
        $quotedScriptPath = '"{0}"' -f $PSCommandPath.Replace('"', '""')
        $arguments = @(
            "-NoProfile",
            "-ExecutionPolicy",
            "Bypass",
            "-File",
            $quotedScriptPath,
            "-Event",
            $Event,
            "-DelaySeconds",
            $DelaySeconds,
            "-ScheduledPlayback"
        )

        Start-Process -FilePath $powerShellPath -ArgumentList $arguments -WindowStyle Hidden | Out-Null
        return
    }

    if ($ScheduledPlayback -and $DelaySeconds -gt 0)
    {
        Start-Sleep -Seconds $DelaySeconds
    }

    if ([Environment]::OSVersion.Platform -ne [PlatformID]::Win32NT)
    {
        Write-Warning "User notification sound is available only on Windows."
        return
    }

    $windowsDirectory = if ($env:WINDIR)
    {
        $env:WINDIR
    }
    else
    {
        "C:\Windows"
    }

    $soundPath = Join-Path $windowsDirectory "Media\Windows Logon.wav"
    if (-not (Test-Path -LiteralPath $soundPath -PathType Leaf))
    {
        Write-Warning "User notification sound file was not found."
        return
    }

    $player = New-Object System.Media.SoundPlayer -ArgumentList $soundPath
    try
    {
        $player.PlaySync()
    }
    finally
    {
        $player.Dispose()
    }
}
catch
{
    Write-Warning "User notification sound could not be played."
}
