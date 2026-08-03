[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$ExecutablePath,
    [Parameter(Mandatory = $true)]
    [string]$WorkingDirectory,
    [Parameter(Mandatory = $true)]
    [string]$ExpectedTitle,
    [Parameter(Mandatory = $true)]
    [string]$OutputPath,
    [ValidateRange(0, 10000)]
    [int]$CaptureDelayMilliseconds = 750,
    [switch]$Overwrite,
    [switch]$KeepApplicationOpen,
    [switch]$CaptureImmediately,
    [switch]$CenterWindow,
    [ValidateRange(0, 10)]
    [int]$CountdownSeconds = 0
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "window-operation-rules.ps1")

if ($env:OS -ne "Windows_NT") {
    throw "This tool requires Windows."
}
if (-not [Environment]::UserInteractive) {
    throw "This tool requires an interactive desktop session."
}

function Resolve-ExistingPath {
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
    if (-not (Test-Path -LiteralPath $resolved -PathType $PathType)) {
        throw "${Description} not found: $resolved"
    }
    return $resolved
}

$resolvedExecutable = Resolve-ExistingPath `
    -Path $ExecutablePath -Description "Executable" -PathType Leaf
$resolvedWorkingDirectory = Resolve-ExistingPath `
    -Path $WorkingDirectory -Description "Working directory" -PathType Container
$resolvedOutput = [IO.Path]::GetFullPath($OutputPath)
$resolvedOutputDirectory = Split-Path -Parent $resolvedOutput

if (-not (Test-Path -LiteralPath $resolvedOutputDirectory -PathType Container)) {
    throw "Output directory not found: $resolvedOutputDirectory"
}
if ((Test-Path -LiteralPath $resolvedOutput) -and -not $Overwrite) {
    throw "Output already exists. Use -Overwrite to replace it: $resolvedOutput"
}
if ([IO.Path]::GetExtension($resolvedOutput) -ne ".png") {
    throw "OutputPath must use the .png extension: $resolvedOutput"
}

Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;

public static class ExampleWindowCaptureNative
{
    [StructLayout(LayoutKind.Sequential)]
    public struct RECT
    {
        public int Left;
        public int Top;
        public int Right;
        public int Bottom;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct MONITORINFO
    {
        public int Size;
        public RECT Monitor;
        public RECT Work;
        public uint Flags;
    }

    [DllImport("dwmapi.dll")]
    public static extern int DwmGetWindowAttribute(
        IntPtr hwnd, int attribute, out RECT rect, int size
    );

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool SetForegroundWindow(IntPtr hwnd);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool BringWindowToTop(IntPtr hwnd);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool AttachThreadInput(
        uint sourceThread, uint targetThread, bool attach
    );

    [DllImport("user32.dll")]
    public static extern uint GetWindowThreadProcessId(
        IntPtr hwnd, IntPtr processId
    );

    [DllImport("kernel32.dll")]
    public static extern uint GetCurrentThreadId();

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool ShowWindow(IntPtr hwnd, int command);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool IsIconic(IntPtr hwnd);

    [DllImport("user32.dll")]
    public static extern IntPtr GetForegroundWindow();

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool GetWindowRect(IntPtr hwnd, out RECT rect);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool SetWindowPos(
        IntPtr hwnd, IntPtr insertAfter, int x, int y, int width, int height,
        uint flags
    );

    [DllImport("user32.dll")]
    public static extern IntPtr MonitorFromWindow(IntPtr hwnd, uint flags);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool GetMonitorInfo(
        IntPtr monitor, ref MONITORINFO info
    );

    [DllImport("user32.dll")]
    public static extern int GetSystemMetrics(int index);
}
"@

function Get-CaptureBounds
{
    param(
        [Parameter(Mandatory = $true)][Diagnostics.Process]$Process,
        [switch]$AllowOutsideVirtualDesktop
    )

    $Process.Refresh()
    if ($Process.HasExited -or $Process.MainWindowHandle -eq [IntPtr]::Zero)
    {
        throw "Application main window is unavailable."
    }
    if ($Process.MainWindowTitle -cne $ExpectedTitle)
    {
        throw "Application title changed."
    }

    $bounds = New-Object ExampleWindowCaptureNative+RECT
    $dwmResult = [ExampleWindowCaptureNative]::DwmGetWindowAttribute(
        $Process.MainWindowHandle,
        9,
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

    $virtualLeft = [ExampleWindowCaptureNative]::GetSystemMetrics(76)
    $virtualTop = [ExampleWindowCaptureNative]::GetSystemMetrics(77)
    $virtual = [PSCustomObject]@{
        Left = $virtualLeft
        Top = $virtualTop
        Right = $virtualLeft + [ExampleWindowCaptureNative]::GetSystemMetrics(78)
        Bottom = $virtualTop + [ExampleWindowCaptureNative]::GetSystemMetrics(79)
    }
    if (
        -not $AllowOutsideVirtualDesktop -and
        -not (Test-WindowBoundsInsideRectangle $bounds $virtual)
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
    }
}

function Get-CaptureMonitorWorkingArea
{
    param([Parameter(Mandatory = $true)][IntPtr]$WindowHandle)

    $monitor = [ExampleWindowCaptureNative]::MonitorFromWindow($WindowHandle, 2)
    if ($monitor -eq [IntPtr]::Zero)
    {
        throw "The monitor nearest the application window was not found."
    }
    $info = New-Object ExampleWindowCaptureNative+MONITORINFO
    $info.Size = [Runtime.InteropServices.Marshal]::SizeOf($info)
    if (-not [ExampleWindowCaptureNative]::GetMonitorInfo($monitor, [ref]$info))
    {
        throw "GetMonitorInfo failed."
    }
    return $info.Work
}

function Center-CaptureWindow
{
    param([Parameter(Mandatory = $true)][Diagnostics.Process]$Process)

    $bounds = Get-CaptureBounds $Process -AllowOutsideVirtualDesktop
    $workingArea = Get-CaptureMonitorWorkingArea $Process.MainWindowHandle
    $placement = Get-CenteredWindowPlacement $bounds $workingArea
    $nativeBounds = New-Object ExampleWindowCaptureNative+RECT
    if (-not [ExampleWindowCaptureNative]::GetWindowRect(
        $Process.MainWindowHandle,
        [ref]$nativeBounds
    ))
    {
        throw "GetWindowRect failed."
    }
    $targetX = $nativeBounds.Left + $placement.DeltaX
    $targetY = $nativeBounds.Top + $placement.DeltaY
    if (-not [ExampleWindowCaptureNative]::SetWindowPos(
        $Process.MainWindowHandle,
        [IntPtr]::Zero,
        $targetX,
        $targetY,
        0,
        0,
        0x0015
    ))
    {
        throw "SetWindowPos failed while centering the application window."
    }
    Start-Sleep -Milliseconds 250
    $centered = Get-CaptureBounds $Process
    if (-not (Test-WindowBoundsInsideRectangle $centered $workingArea))
    {
        throw "Centered application window does not fit inside the monitor working area."
    }
    return $centered
}

function Test-SameCaptureBounds
{
    param($Expected, $Actual)
    return (
        $Expected.Left -eq $Actual.Left -and
        $Expected.Top -eq $Actual.Top -and
        $Expected.Right -eq $Actual.Right -and
        $Expected.Bottom -eq $Actual.Bottom
    )
}

function Set-CaptureWindowForeground
{
    param([Parameter(Mandatory = $true)][IntPtr]$WindowHandle)

    if ([ExampleWindowCaptureNative]::GetForegroundWindow() -eq $WindowHandle)
    {
        return
    }

    $foregroundHandle = [ExampleWindowCaptureNative]::GetForegroundWindow()
    $currentThread = [ExampleWindowCaptureNative]::GetCurrentThreadId()
    $foregroundThread = [uint32]0
    $inputAttached = $false

    if ($foregroundHandle -ne [IntPtr]::Zero)
    {
        $foregroundThread = [ExampleWindowCaptureNative]::GetWindowThreadProcessId(
            $foregroundHandle,
            [IntPtr]::Zero
        )
    }

    try
    {
        if ($foregroundThread -ne 0 -and $foregroundThread -ne $currentThread)
        {
            $inputAttached = [ExampleWindowCaptureNative]::AttachThreadInput(
                $currentThread,
                $foregroundThread,
                $true
            )
        }

        [void][ExampleWindowCaptureNative]::BringWindowToTop($WindowHandle)
        [void][ExampleWindowCaptureNative]::SetForegroundWindow($WindowHandle)
        Start-Sleep -Milliseconds 100
    }
    finally
    {
        if ($inputAttached)
        {
            [void][ExampleWindowCaptureNative]::AttachThreadInput(
                $currentThread,
                $foregroundThread,
                $false
            )
        }
    }

    if ([ExampleWindowCaptureNative]::GetForegroundWindow() -ne $WindowHandle)
    {
        throw "The application window could not be brought to the foreground."
    }
}

$process = $null
$captureSucceeded = $false
$temporaryOutput = Join-Path `
    $resolvedOutputDirectory `
    (".capture-{0}.png" -f [Guid]::NewGuid().ToString("N"))

try {
    $process = Start-Process `
        -FilePath $resolvedExecutable `
        -WorkingDirectory $resolvedWorkingDirectory `
        -PassThru

    for ($attempt = 0; $attempt -lt 40; ++$attempt) {
        $process.Refresh()
        if ($process.HasExited) {
            throw "Application exited before its main window became available."
        }
        if ($process.MainWindowHandle -ne [IntPtr]::Zero) {
            break
        }
        Start-Sleep -Milliseconds 250
    }
    if ($process.MainWindowHandle -eq [IntPtr]::Zero) {
        throw "Application main window was not found within 10 seconds."
    }
    if ($process.MainWindowTitle -cne $ExpectedTitle) {
        throw (
            "Unexpected window title. Expected '{0}', actual '{1}'." -f `
                $ExpectedTitle, $process.MainWindowTitle
        )
    }

    if ($CenterWindow) {
        [void](Center-CaptureWindow $process)
    }

    if (-not $CaptureImmediately) {
        Write-Host ""
        Write-Host "Adjust the application to the frame to capture."
        Write-Host "Keep the target window visible and press Enter here when ready."
        Read-Host | Out-Null
    }

    $process.Refresh()
    if ($process.HasExited) {
        throw "Application exited before capture."
    }
    if ($process.MainWindowTitle -cne $ExpectedTitle) {
        throw "Application title changed before capture."
    }
    if ([ExampleWindowCaptureNative]::IsIconic($process.MainWindowHandle)) {
        [ExampleWindowCaptureNative]::ShowWindow(
            $process.MainWindowHandle, 9
        ) | Out-Null
        Start-Sleep -Milliseconds 250
    }

    $plannedBounds = Get-CaptureBounds $process

    Set-CaptureWindowForeground $process.MainWindowHandle
    Write-Host "Do not use the mouse or keyboard until capture completes or fails."
    Invoke-WindowOperationCountdown -Seconds $CountdownSeconds
    Start-Sleep -Milliseconds $CaptureDelayMilliseconds

    $process.Refresh()
    if ($process.HasExited -or $process.MainWindowTitle -cne $ExpectedTitle) {
        throw "Application process or title changed during capture preparation."
    }
    if ([ExampleWindowCaptureNative]::GetForegroundWindow() -ne $process.MainWindowHandle) {
        throw "Application lost foreground focus during capture preparation."
    }
    $finalBounds = Get-CaptureBounds $process
    if (-not (Test-SameCaptureBounds $plannedBounds $finalBounds)) {
        throw "Application moved or resized during capture preparation."
    }
    $bounds = $finalBounds
    $width = $bounds.Width
    $height = $bounds.Height

    $bitmap = New-Object Drawing.Bitmap $width, $height
    try {
        $graphics = [Drawing.Graphics]::FromImage($bitmap)
        try {
            $graphics.CopyFromScreen(
                $bounds.Left, $bounds.Top, 0, 0, $bitmap.Size
            )
        }
        finally {
            $graphics.Dispose()
        }
        $bitmap.Save(
            $temporaryOutput,
            [Drawing.Imaging.ImageFormat]::Png
        )
    }
    finally {
        $bitmap.Dispose()
    }

    Move-Item `
        -LiteralPath $temporaryOutput `
        -Destination $resolvedOutput `
        -Force:$Overwrite

    $hash = (Get-FileHash -LiteralPath $resolvedOutput -Algorithm SHA256).Hash
    $captureSucceeded = $true
    Write-Host "Capture succeeded."
    Write-Host "Saved: $resolvedOutput"
    Write-Host "Bounds: $($bounds.Left),$($bounds.Top) ${width}x${height}"
    Write-Host "Dimensions: ${width}x${height}"
    Write-Host "SHA-256: $hash"
}
finally {
    if (Test-Path -LiteralPath $temporaryOutput) {
        Remove-Item -LiteralPath $temporaryOutput -Force
    }

    if ($null -ne $process -and -not $process.HasExited) {
        if ($captureSucceeded -and $KeepApplicationOpen) {
            Write-Host "Application left open by request."
        }
        else {
            $process.CloseMainWindow() | Out-Null
            if (-not $process.WaitForExit(3000)) {
                try {
                    $process.Kill()
                    $process.WaitForExit()
                }
                catch {
                    Write-Warning "Capture state is unchanged, but application shutdown failed: $_"
                }
            }
        }
    }
}
