[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$ExecutablePath,
    [Parameter(Mandatory = $true)]
    [string]$WorkingDirectory,
    [Parameter(Mandatory = $true)]
    [string]$ExpectedTitle,
    [Parameter(Mandatory = $true)]
    [string]$OutputDirectory,
    [Parameter(Mandatory = $true)]
    [ValidatePattern("^[A-Za-z0-9][A-Za-z0-9._-]*$")]
    [string]$BaseName,
    [string]$FfmpegPath,
    [ValidateRange(1, 120)]
    [int]$FrameRate = 30,
    [ValidateRange(1, 120)]
    [int]$StartTimeoutSeconds = 10,
    [ValidateRange(0, 10000)]
    [int]$ForegroundDelayMilliseconds = 500,
    [switch]$KeepApplicationOpen,
    [switch]$OverwriteSelection
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "video-quality-rules.ps1")

if ($env:OS -ne "Windows_NT")
{
    throw "This tool requires Windows."
}
if (-not [Environment]::UserInteractive)
{
    throw "This tool requires an interactive desktop session."
}

function Resolve-ExistingPath
{
    param(
        [Parameter(Mandatory = $true)]
        [string]$Path,
        [Parameter(Mandatory = $true)]
        [string]$Description,
        [Parameter(Mandatory = $true)]
        [ValidateSet("Leaf", "Container")]
        [string]$PathType
    )

    $resolved = [IO.Path]::GetFullPath($Path)
    if (-not (Test-Path -LiteralPath $resolved -PathType $PathType))
    {
        throw "${Description} not found: $resolved"
    }
    return $resolved
}

function ConvertTo-NativeArgument
{
    param([Parameter(Mandatory = $true)][string]$Value)

    if ($Value.Length -gt 0 -and $Value -notmatch '[\s"]')
    {
        return $Value
    }

    $builder = New-Object Text.StringBuilder
    [void]$builder.Append('"')
    $backslashes = 0
    foreach ($character in $Value.ToCharArray())
    {
        if ($character -eq '\')
        {
            ++$backslashes
            continue
        }
        if ($character -eq '"')
        {
            [void]$builder.Append(('\' * (($backslashes * 2) + 1)))
            [void]$builder.Append('"')
            $backslashes = 0
            continue
        }
        if ($backslashes -gt 0)
        {
            [void]$builder.Append(('\' * $backslashes))
            $backslashes = 0
        }
        [void]$builder.Append($character)
    }
    if ($backslashes -gt 0)
    {
        [void]$builder.Append(('\' * ($backslashes * 2)))
    }
    [void]$builder.Append('"')
    return $builder.ToString()
}

function Join-NativeArguments
{
    param([Parameter(Mandatory = $true)][string[]]$Values)
    return (($Values | ForEach-Object { ConvertTo-NativeArgument $_ }) -join ' ')
}

$repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot "../../.."))
$localRoot = [IO.Path]::GetFullPath((Join-Path $repoRoot "local"))
$resolvedExecutable = Resolve-ExistingPath `
    -Path $ExecutablePath -Description "Executable" -PathType Leaf
$resolvedWorkingDirectory = Resolve-ExistingPath `
    -Path $WorkingDirectory -Description "Working directory" -PathType Container
$resolvedOutputDirectory = Resolve-ExistingPath `
    -Path $OutputDirectory -Description "Output directory" -PathType Container

$localPrefix = $localRoot.TrimEnd('\') + '\'
if (-not $resolvedOutputDirectory.StartsWith(
    $localPrefix,
    [StringComparison]::OrdinalIgnoreCase
))
{
    throw "OutputDirectory must be inside the repository local directory: $localRoot"
}

if ($FfmpegPath)
{
    $resolvedFfmpeg = Resolve-ExistingPath `
        -Path $FfmpegPath -Description "FFmpeg" -PathType Leaf
}
else
{
    $ffmpegCommand = Get-Command ffmpeg -ErrorAction SilentlyContinue
    if ($null -ne $ffmpegCommand)
    {
        $resolvedFfmpeg = $ffmpegCommand.Source
    }
    else
    {
        $localFfmpeg = Join-Path $localRoot "tools/ffmpeg/bin/ffmpeg.exe"
        $resolvedFfmpeg = Resolve-ExistingPath `
            -Path $localFfmpeg -Description "Local FFmpeg" -PathType Leaf
    }
}

$resolvedFfprobe = Join-Path (Split-Path -Parent $resolvedFfmpeg) "ffprobe.exe"
$resolvedFfprobe = Resolve-ExistingPath `
    -Path $resolvedFfprobe -Description "FFprobe" -PathType Leaf

$deviceOutput = (& $resolvedFfmpeg -hide_banner -devices 2>&1 | Out-String)
if ($deviceOutput -notmatch '(?m)^\s*D\s+gdigrab\s')
{
    throw "FFmpeg does not provide the gdigrab input device."
}
$encoderOutput = (& $resolvedFfmpeg -hide_banner -encoders 2>&1 | Out-String)
if ($encoderOutput -notmatch '(?m)^\s*V[^\r\n]*\slibx264\s')
{
    throw "FFmpeg does not provide the libx264 encoder."
}
& $resolvedFfprobe -version | Out-Null
if ($LASTEXITCODE -ne 0)
{
    throw "FFprobe preflight failed."
}

Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
Add-Type @"
using System;
using System.Runtime.InteropServices;

public static class ExampleWindowRecorderNative
{
    public const uint WM_HOTKEY = 0x0312;
    public const uint PM_REMOVE = 0x0001;
    public const uint MOD_CONTROL = 0x0002;
    public const uint MOD_SHIFT = 0x0004;
    public const uint MOD_NOREPEAT = 0x4000;
    public const int DWMWA_EXTENDED_FRAME_BOUNDS = 9;
    public const int DWMWA_CLOAKED = 14;

    [StructLayout(LayoutKind.Sequential)]
    public struct RECT
    {
        public int Left;
        public int Top;
        public int Right;
        public int Bottom;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct POINT
    {
        public int X;
        public int Y;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct MSG
    {
        public IntPtr Hwnd;
        public uint Message;
        public UIntPtr WParam;
        public IntPtr LParam;
        public uint Time;
        public POINT Point;
    }

    [DllImport("dwmapi.dll")]
    public static extern int DwmGetWindowAttribute(
        IntPtr hwnd, int attribute, out RECT rect, int size
    );

    [DllImport("dwmapi.dll")]
    public static extern int DwmGetWindowAttribute(
        IntPtr hwnd, int attribute, out int value, int size
    );

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool RegisterHotKey(
        IntPtr hwnd, int id, uint modifiers, uint virtualKey
    );

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool UnregisterHotKey(IntPtr hwnd, int id);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool PeekMessage(
        out MSG message,
        IntPtr hwnd,
        uint minimum,
        uint maximum,
        uint remove
    );

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool SetForegroundWindow(IntPtr hwnd);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool ShowWindow(IntPtr hwnd, int command);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool IsIconic(IntPtr hwnd);

    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int index);
}
"@

function Set-RecorderStatusWindowPosition
{
    param(
        [Parameter(Mandatory = $true)]$StatusWindow,
        [Parameter(Mandatory = $true)]$Bounds
    )

    $form = $StatusWindow.Form
    $virtualLeft = [ExampleWindowRecorderNative]::GetSystemMetrics(76)
    $virtualTop = [ExampleWindowRecorderNative]::GetSystemMetrics(77)
    $virtualRight = $virtualLeft + [ExampleWindowRecorderNative]::GetSystemMetrics(78)
    $virtualBottom = $virtualTop + [ExampleWindowRecorderNative]::GetSystemMetrics(79)
    $margin = 12
    $outsideTarget = $true

    if ($Bounds.Right + $margin + $form.Width -le $virtualRight)
    {
        $left = $Bounds.Right + $margin
        $top = [Math]::Max($virtualTop, $Bounds.Top)
    }
    elseif ($Bounds.Left - $margin - $form.Width -ge $virtualLeft)
    {
        $left = $Bounds.Left - $margin - $form.Width
        $top = [Math]::Max($virtualTop, $Bounds.Top)
    }
    elseif ($Bounds.Bottom + $margin + $form.Height -le $virtualBottom)
    {
        $left = [Math]::Max($virtualLeft, $Bounds.Left)
        $top = $Bounds.Bottom + $margin
    }
    elseif ($Bounds.Top - $margin - $form.Height -ge $virtualTop)
    {
        $left = [Math]::Max($virtualLeft, $Bounds.Left)
        $top = $Bounds.Top - $margin - $form.Height
    }
    else
    {
        $left = $virtualRight - $form.Width - 16
        $top = $virtualTop + 16
        $outsideTarget = $false
    }

    $form.Location = New-Object Drawing.Point($left, $top)
    if (-not $outsideTarget)
    {
        Write-Warning "The status window could not be placed outside the capture bounds. Move the application before recording."
    }
    return $outsideTarget
}

function New-RecorderStatusWindow
{
    param([Parameter(Mandatory = $true)]$Bounds)

    $form = New-Object Windows.Forms.Form
    $form.Text = "Example Video Recorder"
    $form.FormBorderStyle = [Windows.Forms.FormBorderStyle]::FixedToolWindow
    $form.StartPosition = [Windows.Forms.FormStartPosition]::Manual
    $form.TopMost = $true
    $form.ShowInTaskbar = $true
    $form.ControlBox = $false
    $form.ClientSize = New-Object Drawing.Size(400, 142)
    $form.BackColor = [Drawing.Color]::FromArgb(28, 32, 38)

    $statusLabel = New-Object Windows.Forms.Label
    $statusLabel.Location = New-Object Drawing.Point(12, 12)
    $statusLabel.Size = New-Object Drawing.Size(376, 46)
    $statusLabel.Font = New-Object Drawing.Font("Segoe UI", 18, [Drawing.FontStyle]::Bold)
    $statusLabel.ForeColor = [Drawing.Color]::White
    $statusLabel.TextAlign = [Drawing.ContentAlignment]::MiddleCenter
    $form.Controls.Add($statusLabel)

    $detailLabel = New-Object Windows.Forms.Label
    $detailLabel.Location = New-Object Drawing.Point(12, 62)
    $detailLabel.Size = New-Object Drawing.Size(376, 66)
    $detailLabel.Font = New-Object Drawing.Font("Segoe UI", 9)
    $detailLabel.ForeColor = [Drawing.Color]::Gainsboro
    $detailLabel.TextAlign = [Drawing.ContentAlignment]::MiddleCenter
    $detailLabel.Text = "F9 Start  |  F10 Save  |  F8 Discard`r`nF7 Restart app  |  F11 Accept latest`r`nUse Ctrl+Shift with every function key"
    $form.Controls.Add($detailLabel)

    $statusWindow = [PSCustomObject]@{
        Form = $form
        StatusLabel = $statusLabel
        DetailLabel = $detailLabel
        OutsideTarget = $false
    }
    $statusWindow.OutsideTarget = Set-RecorderStatusWindowPosition `
        -StatusWindow $statusWindow -Bounds $Bounds
    $form.Show()
    [Windows.Forms.Application]::DoEvents()
    return $statusWindow
}

function Set-RecorderStatus
{
    param(
        [Parameter(Mandatory = $true)]$StatusWindow,
        [Parameter(Mandatory = $true)]
        [ValidateSet("READY", "RECORDING", "FINALIZING", "SAVED", "DISCARDED", "RESTARTED", "ERROR", "SELECTED")]
        [string]$State,
        [string]$Detail
    )

    $colors = @{
        READY = [Drawing.Color]::FromArgb(36, 77, 118)
        RECORDING = [Drawing.Color]::FromArgb(155, 24, 24)
        FINALIZING = [Drawing.Color]::FromArgb(145, 92, 16)
        SAVED = [Drawing.Color]::FromArgb(35, 112, 63)
        DISCARDED = [Drawing.Color]::FromArgb(145, 92, 16)
        RESTARTED = [Drawing.Color]::FromArgb(36, 77, 118)
        ERROR = [Drawing.Color]::FromArgb(155, 24, 24)
        SELECTED = [Drawing.Color]::FromArgb(35, 112, 63)
    }
    $display = $State
    $StatusWindow.Form.BackColor = $colors[$State]
    $StatusWindow.StatusLabel.Text = $display
    if ($Detail)
    {
        $StatusWindow.DetailLabel.Text = $Detail
    }
    $StatusWindow.Form.Refresh()
    [Windows.Forms.Application]::DoEvents()
}

function Start-ExampleApplication
{
    $process = Start-Process `
        -FilePath $resolvedExecutable `
        -WorkingDirectory $resolvedWorkingDirectory `
        -PassThru

    $attempts = $StartTimeoutSeconds * 4
    for ($attempt = 0; $attempt -lt $attempts; ++$attempt)
    {
        $process.Refresh()
        if ($process.HasExited)
        {
            throw "Application exited before its main window became available."
        }
        if ($process.MainWindowHandle -ne [IntPtr]::Zero)
        {
            break
        }
        Start-Sleep -Milliseconds 250
    }
    $process.Refresh()
    if ($process.MainWindowHandle -eq [IntPtr]::Zero)
    {
        throw "Application main window was not found within $StartTimeoutSeconds seconds."
    }
    if ($process.MainWindowTitle -cne $ExpectedTitle)
    {
        throw (
            "Unexpected window title. Expected '{0}', actual '{1}'." -f `
                $ExpectedTitle, $process.MainWindowTitle
        )
    }
    return $process
}

function Stop-ExampleApplication
{
    param([Diagnostics.Process]$Process)

    if ($null -eq $Process)
    {
        return
    }
    try
    {
        $Process.Refresh()
        if ($Process.HasExited)
        {
            return
        }
        $Process.CloseMainWindow() | Out-Null
        if (-not $Process.WaitForExit(3000))
        {
            $Process.Kill()
            $Process.WaitForExit()
        }
    }
    catch
    {
        Write-Warning "Application shutdown failed: $_"
    }
}

function Get-ApplicationBounds
{
    param([Parameter(Mandatory = $true)][Diagnostics.Process]$Process)

    $Process.Refresh()
    if ($Process.HasExited)
    {
        throw "Application is not running. Use Ctrl+Shift+F7 to restart it."
    }
    if ($Process.MainWindowHandle -eq [IntPtr]::Zero)
    {
        throw "Application main window is unavailable."
    }
    if ($Process.MainWindowTitle -cne $ExpectedTitle)
    {
        throw "Application title changed."
    }
    if ([ExampleWindowRecorderNative]::IsIconic($Process.MainWindowHandle))
    {
        throw "Application window is minimized."
    }

    $cloaked = 0
    $cloakResult = [ExampleWindowRecorderNative]::DwmGetWindowAttribute(
        $Process.MainWindowHandle,
        [ExampleWindowRecorderNative]::DWMWA_CLOAKED,
        [ref]$cloaked,
        4
    )
    if ($cloakResult -eq 0 -and $cloaked -ne 0)
    {
        throw "Application window is cloaked."
    }

    $bounds = New-Object ExampleWindowRecorderNative+RECT
    $dwmResult = [ExampleWindowRecorderNative]::DwmGetWindowAttribute(
        $Process.MainWindowHandle,
        [ExampleWindowRecorderNative]::DWMWA_EXTENDED_FRAME_BOUNDS,
        [ref]$bounds,
        [Runtime.InteropServices.Marshal]::SizeOf($bounds)
    )
    if ($dwmResult -ne 0)
    {
        throw "DwmGetWindowAttribute failed with HRESULT $dwmResult."
    }

    $width = $bounds.Right - $bounds.Left
    $height = $bounds.Bottom - $bounds.Top
    if ($width -le 0 -or $height -le 0)
    {
        throw "DWM returned invalid window bounds: ${width}x${height}."
    }

    $virtualLeft = [ExampleWindowRecorderNative]::GetSystemMetrics(76)
    $virtualTop = [ExampleWindowRecorderNative]::GetSystemMetrics(77)
    $virtualWidth = [ExampleWindowRecorderNative]::GetSystemMetrics(78)
    $virtualHeight = [ExampleWindowRecorderNative]::GetSystemMetrics(79)
    if (
        $bounds.Left -lt $virtualLeft -or
        $bounds.Top -lt $virtualTop -or
        $bounds.Right -gt ($virtualLeft + $virtualWidth) -or
        $bounds.Bottom -gt ($virtualTop + $virtualHeight)
    )
    {
        throw "Application window must fit inside the Windows virtual desktop."
    }

    return [PSCustomObject]@{
        Left = $bounds.Left
        Top = $bounds.Top
        Right = $bounds.Right
        Bottom = $bounds.Bottom
        Width = $width
        Height = $height
        PaddedWidth = $width + ($width % 2)
        PaddedHeight = $height + ($height % 2)
    }
}

function Test-SameBounds
{
    param($Expected, $Actual)
    return (
        $Expected.Left -eq $Actual.Left -and
        $Expected.Top -eq $Actual.Top -and
        $Expected.Right -eq $Actual.Right -and
        $Expected.Bottom -eq $Actual.Bottom
    )
}

function Start-Recording
{
    param([Diagnostics.Process]$ApplicationProcess)

    if ([ExampleWindowRecorderNative]::IsIconic($ApplicationProcess.MainWindowHandle))
    {
        [ExampleWindowRecorderNative]::ShowWindow(
            $ApplicationProcess.MainWindowHandle,
            9
        ) | Out-Null
        Start-Sleep -Milliseconds 250
    }
    if (-not [ExampleWindowRecorderNative]::SetForegroundWindow(
        $ApplicationProcess.MainWindowHandle
    ))
    {
        throw "The application window could not be brought to the foreground."
    }
    Start-Sleep -Milliseconds $ForegroundDelayMilliseconds
    $bounds = Get-ApplicationBounds $ApplicationProcess
    $partial = Join-Path $resolvedOutputDirectory (
        "{0}.recording-{1}.partial.mp4" -f `
            $BaseName, [Guid]::NewGuid().ToString("N")
    )

    $arguments = @(
        "-hide_banner",
        "-loglevel", "warning",
        "-y",
        "-f", "gdigrab",
        "-framerate", $FrameRate.ToString(),
        "-offset_x", $bounds.Left.ToString(),
        "-offset_y", $bounds.Top.ToString(),
        "-video_size", ("{0}x{1}" -f $bounds.Width, $bounds.Height),
        "-draw_mouse", "0",
        "-i", "desktop",
        "-an",
        "-c:v", "libx264",
        "-preset", "veryfast",
        "-crf", "18",
        "-vf", ("fps={0},pad=ceil(iw/2)*2:ceil(ih/2)*2" -f $FrameRate),
        "-pix_fmt", "yuv420p",
        "-fps_mode", "cfr",
        "-map_metadata", "-1",
        "-metadata", "encoder=",
        "-metadata:s:v", "encoder=",
        "-movflags", "+faststart",
        $partial
    )

    $startInfo = New-Object Diagnostics.ProcessStartInfo
    $startInfo.FileName = $resolvedFfmpeg
    $startInfo.Arguments = Join-NativeArguments $arguments
    $startInfo.WorkingDirectory = $resolvedOutputDirectory
    $startInfo.UseShellExecute = $false
    $startInfo.CreateNoWindow = $true
    $startInfo.RedirectStandardInput = $true
    $startInfo.RedirectStandardError = $true

    $process = New-Object Diagnostics.Process
    $process.StartInfo = $startInfo
    if (-not $process.Start())
    {
        throw "FFmpeg could not be started."
    }
    $errorTask = $process.StandardError.ReadToEndAsync()
    Start-Sleep -Milliseconds 500
    if ($process.HasExited)
    {
        $errorText = $errorTask.GetAwaiter().GetResult()
        throw "FFmpeg exited before recording: $errorText"
    }

    Write-Host "Recording started."
    Write-Host ("Bounds: {0},{1} {2}x{3}" -f `
        $bounds.Left, $bounds.Top, $bounds.Width, $bounds.Height)
    return [PSCustomObject]@{
        Process = $process
        ErrorTask = $errorTask
        PartialPath = $partial
        Bounds = $bounds
    }
}

function Stop-FfmpegProcess
{
    param($Recording, [switch]$AllowForceCleanup)

    if ($null -eq $Recording -or $null -eq $Recording.Process)
    {
        return [PSCustomObject]@{ Graceful = $true; ErrorText = "" }
    }

    $process = $Recording.Process
    $graceful = $false
    try
    {
        if (-not $process.HasExited)
        {
            $process.StandardInput.WriteLine("q")
            $process.StandardInput.Flush()
            $process.StandardInput.Close()
            $graceful = $process.WaitForExit(15000)
        }
        else
        {
            $graceful = $true
        }
    }
    catch
    {
        Write-Warning "FFmpeg graceful stop failed: $_"
    }

    if (-not $graceful -and $AllowForceCleanup)
    {
        try
        {
            $process.Kill()
            $process.WaitForExit()
        }
        catch
        {
            Write-Warning "FFmpeg cleanup failed: $_"
        }
    }

    $errorText = ""
    try
    {
        $errorText = $Recording.ErrorTask.GetAwaiter().GetResult()
    }
    catch
    {
        $errorText = $_.Exception.Message
    }
    return [PSCustomObject]@{
        Graceful = ($graceful -and $process.ExitCode -eq 0)
        ErrorText = $errorText
    }
}

function Test-RecordedVideo
{
    param([Parameter(Mandatory = $true)]$Recording)

    return Test-ExampleVideoFile `
        -Path $Recording.PartialPath `
        -FfprobePath $resolvedFfprobe `
        -FfmpegPath $resolvedFfmpeg `
        -ExpectedFrameRate $FrameRate `
        -ExpectedWidth $Recording.Bounds.PaddedWidth `
        -ExpectedHeight $Recording.Bounds.PaddedHeight
}

function Get-NextAttemptPath
{
    $pattern = "{0}_attempt-*.mp4" -f $BaseName
    $maximum = 0
    foreach ($file in Get-ChildItem -LiteralPath $resolvedOutputDirectory -Filter $pattern -File)
    {
        if ($file.BaseName -match '_attempt-(\d+)$')
        {
            $maximum = [Math]::Max($maximum, [int]$Matches[1])
        }
    }
    return Join-Path $resolvedOutputDirectory (
        "{0}_attempt-{1:D2}.mp4" -f $BaseName, ($maximum + 1)
    )
}

function Complete-RecordingAttempt
{
    param([Parameter(Mandatory = $true)]$Recording)

    $stop = Stop-FfmpegProcess $Recording -AllowForceCleanup
    if (-not $stop.Graceful)
    {
        throw "FFmpeg did not finalize the MP4 gracefully: $($stop.ErrorText)"
    }
    $details = Test-RecordedVideo $Recording
    $attemptPath = Get-NextAttemptPath
    Move-Item -LiteralPath $Recording.PartialPath -Destination $attemptPath
    $hash = (Get-FileHash -LiteralPath $attemptPath -Algorithm SHA256).Hash
    $size = (Get-Item -LiteralPath $attemptPath).Length
    Write-Host "Attempt saved: $attemptPath"
    Write-Host ("Video: {0} {1} {2}x{3} {4:N3} fps {5:N3} s" -f `
        $details.Codec,
        $details.PixelFormat,
        $details.Width,
        $details.Height,
        $details.FrameRate,
        $details.Duration)
    Write-Host "Audio streams: $($details.AudioStreams)"
    Write-Host "Size: $size"
    Write-Host "SHA-256: $hash"
    return $attemptPath
}

function Abort-Recording
{
    param($Recording)

    if ($null -eq $Recording)
    {
        return
    }
    [void](Stop-FfmpegProcess $Recording -AllowForceCleanup)
    if (Test-Path -LiteralPath $Recording.PartialPath)
    {
        Remove-Item -LiteralPath $Recording.PartialPath -Force
    }
    Write-Host "Current recording discarded. Completed attempts were preserved."
}

$hotkeys = @(
    @{ Id = 7; Key = 0x76; Name = "Ctrl+Shift+F7 restart application" },
    @{ Id = 8; Key = 0x77; Name = "Ctrl+Shift+F8 discard recording" },
    @{ Id = 9; Key = 0x78; Name = "Ctrl+Shift+F9 start recording" },
    @{ Id = 10; Key = 0x79; Name = "Ctrl+Shift+F10 stop and save" },
    @{ Id = 11; Key = 0x7A; Name = "Ctrl+Shift+F11 accept latest" }
)
$registeredHotkeys = New-Object Collections.Generic.List[int]
$mutexCreated = $false
$mutex = New-Object Threading.Mutex(
    $true,
    "Local\GraphicsStudyArchiveExampleWindowRecorder",
    [ref]$mutexCreated
)
if (-not $mutexCreated)
{
    $mutex.Dispose()
    throw "Another Example Window Recorder instance is already running."
}

$applicationProcess = $null
$recording = $null
$latestAttempt = $null
$accepted = $false
$statusWindow = $null

try
{
    $message = New-Object ExampleWindowRecorderNative+MSG
    [void][ExampleWindowRecorderNative]::PeekMessage(
        [ref]$message,
        [IntPtr]::Zero,
        [ExampleWindowRecorderNative]::WM_HOTKEY,
        [ExampleWindowRecorderNative]::WM_HOTKEY,
        0
    )
    $modifiers = (
        [ExampleWindowRecorderNative]::MOD_CONTROL -bor
        [ExampleWindowRecorderNative]::MOD_SHIFT -bor
        [ExampleWindowRecorderNative]::MOD_NOREPEAT
    )
    foreach ($hotkey in $hotkeys)
    {
        if (-not [ExampleWindowRecorderNative]::RegisterHotKey(
            [IntPtr]::Zero,
            $hotkey.Id,
            $modifiers,
            $hotkey.Key
        ))
        {
            throw "Global hotkey registration failed: $($hotkey.Name)"
        }
        $registeredHotkeys.Add($hotkey.Id)
    }

    $applicationProcess = Start-ExampleApplication
    $initialBounds = Get-ApplicationBounds $applicationProcess
    $statusWindow = New-RecorderStatusWindow $initialBounds
    Set-RecorderStatus $statusWindow "READY" "F9 starts recording. F10 saves and validates.`r`nF11 requires a SAVED attempt."
    [void][ExampleWindowRecorderNative]::SetForegroundWindow(
        $applicationProcess.MainWindowHandle
    )
    Write-Host ""
    Write-Host "Example Window Recorder ready."
    foreach ($hotkey in $hotkeys)
    {
        Write-Host "- $($hotkey.Name)"
    }
    Write-Host "Keep the target window visible. Moving or resizing it aborts the current recording."
    Write-Host "Completed attempts remain in local storage until reviewed."

    while (-not $accepted)
    {
        while ([ExampleWindowRecorderNative]::PeekMessage(
            [ref]$message,
            [IntPtr]::Zero,
            [ExampleWindowRecorderNative]::WM_HOTKEY,
            [ExampleWindowRecorderNative]::WM_HOTKEY,
            [ExampleWindowRecorderNative]::PM_REMOVE
        ))
        {
            $id = [int]$message.WParam.ToUInt32()
            try
            {
                switch ($id)
                {
                    7
                    {
                        Set-RecorderStatus $statusWindow "RESTARTED" "Stopping only the application started by this tool..."
                        Abort-Recording $recording
                        $recording = $null
                        Stop-ExampleApplication $applicationProcess
                        $applicationProcess = Start-ExampleApplication
                        $restartBounds = Get-ApplicationBounds $applicationProcess
                        $statusWindow.OutsideTarget = Set-RecorderStatusWindowPosition `
                            -StatusWindow $statusWindow -Bounds $restartBounds
                        Set-RecorderStatus $statusWindow "RESTARTED" "Application restarted. F9 starts a new recording."
                        Write-Host "Application restarted and recorder ready."
                    }
                    8
                    {
                        if ($null -eq $recording)
                        {
                            Set-RecorderStatus $statusWindow "READY" "No active recording. F9 starts recording."
                            Write-Host "No active recording. Recorder remains ready."
                        }
                        else
                        {
                            Abort-Recording $recording
                            $recording = $null
                            Set-RecorderStatus $statusWindow "DISCARDED" "Current partial removed. F9 starts a retake."
                        }
                    }
                    9
                    {
                        if ($null -ne $recording)
                        {
                            Write-Host "Recording is already active."
                        }
                        else
                        {
                            $readyBounds = Get-ApplicationBounds $applicationProcess
                            $statusWindow.OutsideTarget = Set-RecorderStatusWindowPosition `
                                -StatusWindow $statusWindow -Bounds $readyBounds
                            $recording = Start-Recording $applicationProcess
                            Set-RecorderStatus $statusWindow "RECORDING" "F10 stops and validates. F8 discards this take."
                        }
                    }
                    10
                    {
                        if ($null -eq $recording)
                        {
                            Set-RecorderStatus $statusWindow "READY" "No active recording. F9 starts recording."
                            Write-Host "No active recording."
                        }
                        else
                        {
                            Set-RecorderStatus $statusWindow "FINALIZING" "Stopping FFmpeg and validating the MP4..."
                            $latestAttempt = Complete-RecordingAttempt $recording
                            $recording = $null
                            Set-RecorderStatus $statusWindow "SAVED" "Validated attempt saved. F9 retakes or F11 accepts latest."
                        }
                    }
                    11
                    {
                        if ($null -ne $recording)
                        {
                            Set-RecorderStatus $statusWindow "RECORDING" "F10 must save the active recording before F11."
                            Write-Host "Stop the active recording with Ctrl+Shift+F10 first."
                        }
                        elseif (-not $latestAttempt)
                        {
                            Set-RecorderStatus $statusWindow "READY" "No SAVED attempt. Use F9, then F10 before F11."
                            Write-Host "No validated attempt is available."
                        }
                        else
                        {
                            $selectedPath = Join-Path $resolvedOutputDirectory (
                                "{0}_selected.mp4" -f $BaseName
                            )
                            if (
                                (Test-Path -LiteralPath $selectedPath) -and
                                -not $OverwriteSelection
                            )
                            {
                                Write-Host "Selection already exists. Restart with -OverwriteSelection to replace it."
                            }
                            else
                            {
                                $selectionTemp = Join-Path $resolvedOutputDirectory (
                                    ".selection-{0}.mp4" -f [Guid]::NewGuid().ToString("N")
                                )
                                Copy-Item -LiteralPath $latestAttempt -Destination $selectionTemp
                                $attemptHash = (Get-FileHash `
                                    -LiteralPath $latestAttempt `
                                    -Algorithm SHA256).Hash
                                $temporaryHash = (Get-FileHash `
                                    -LiteralPath $selectionTemp `
                                    -Algorithm SHA256).Hash
                                if ($attemptHash -ne $temporaryHash)
                                {
                                    Remove-Item -LiteralPath $selectionTemp -Force
                                    throw "Selected copy hash does not match the validated attempt."
                                }
                                Move-Item `
                                    -LiteralPath $selectionTemp `
                                    -Destination $selectedPath `
                                    -Force:$OverwriteSelection
                                $selectedHash = (Get-FileHash `
                                    -LiteralPath $selectedPath `
                                    -Algorithm SHA256).Hash
                                if ($attemptHash -ne $selectedHash)
                                {
                                    throw "Selected file hash does not match the validated attempt."
                                }
                                $accepted = $true
                                Set-RecorderStatus $statusWindow "SELECTED" "Latest validated attempt selected. Recorder is closing."
                                Write-Host "Selected: $selectedPath"
                                Write-Host "SHA-256: $selectedHash"
                            }
                        }
                    }
                }
            }
            catch
            {
                Write-Warning $_
                Set-RecorderStatus $statusWindow "ERROR" $_.Exception.Message
                if ($null -ne $recording -and $recording.Process.HasExited)
                {
                    Abort-Recording $recording
                    $recording = $null
                }
            }
        }

        if ($null -ne $recording)
        {
            try
            {
                if ($recording.Process.HasExited)
                {
                    throw "FFmpeg exited unexpectedly."
                }
                $currentBounds = Get-ApplicationBounds $applicationProcess
                if (-not (Test-SameBounds $recording.Bounds $currentBounds))
                {
                    throw "Application moved or resized during recording."
                }
            }
            catch
            {
                Write-Warning $_
                Abort-Recording $recording
                $recording = $null
                Set-RecorderStatus $statusWindow "ERROR" $_.Exception.Message
            }
        }
        [Windows.Forms.Application]::DoEvents()
        Start-Sleep -Milliseconds 100
    }
}
finally
{
    if ($null -ne $recording)
    {
        Abort-Recording $recording
    }
    if ($null -ne $statusWindow -and -not $statusWindow.Form.IsDisposed)
    {
        $statusWindow.Form.Close()
        $statusWindow.Form.Dispose()
    }
    foreach ($id in $registeredHotkeys)
    {
        [void][ExampleWindowRecorderNative]::UnregisterHotKey(
            [IntPtr]::Zero,
            $id
        )
    }
    if ($null -ne $applicationProcess -and -not $applicationProcess.HasExited)
    {
        if ($accepted -and $KeepApplicationOpen)
        {
            Write-Host "Application left open by request."
        }
        else
        {
            Stop-ExampleApplication $applicationProcess
        }
    }
    if ($mutexCreated)
    {
        $mutex.ReleaseMutex()
    }
    $mutex.Dispose()
}

if ($accepted)
{
    Write-Host "Recording workflow completed."
}
