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
    [switch]$CaptureImmediately
)

$ErrorActionPreference = "Stop"

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

    [DllImport("dwmapi.dll")]
    public static extern int DwmGetWindowAttribute(
        IntPtr hwnd, int attribute, out RECT rect, int size
    );

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool SetForegroundWindow(IntPtr hwnd);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool ShowWindow(IntPtr hwnd, int command);
}
"@

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

    [ExampleWindowCaptureNative]::ShowWindow(
        $process.MainWindowHandle, 9
    ) | Out-Null
    if (-not [ExampleWindowCaptureNative]::SetForegroundWindow(
        $process.MainWindowHandle
    )) {
        throw "The application window could not be brought to the foreground."
    }
    Start-Sleep -Milliseconds $CaptureDelayMilliseconds

    $bounds = New-Object ExampleWindowCaptureNative+RECT
    $dwmResult = [ExampleWindowCaptureNative]::DwmGetWindowAttribute(
        $process.MainWindowHandle,
        9,
        [ref]$bounds,
        [Runtime.InteropServices.Marshal]::SizeOf($bounds)
    )
    if ($dwmResult -ne 0) {
        throw "DwmGetWindowAttribute failed with HRESULT $dwmResult."
    }

    $width = $bounds.Right - $bounds.Left
    $height = $bounds.Bottom - $bounds.Top
    if ($width -le 0 -or $height -le 0) {
        throw "DWM returned invalid window bounds: ${width}x${height}."
    }

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
