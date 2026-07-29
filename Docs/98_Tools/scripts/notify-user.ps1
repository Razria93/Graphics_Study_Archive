param(
    [ValidateSet("Complete", "Attention", "Blocked")]
    [string]$Event = "Attention"
)

try
{
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
