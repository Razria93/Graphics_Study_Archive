if (-not ("ExampleWindowInputNative" -as [type]))
{
    Add-Type @"
using System;
using System.Runtime.InteropServices;

public static class ExampleWindowInputNative
{
    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool SetForegroundWindow(IntPtr hwnd);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool BringWindowToTop(IntPtr hwnd);

    [DllImport("user32.dll")]
    public static extern IntPtr GetForegroundWindow();

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool IsWindow(IntPtr hwnd);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool SetCursorPos(int x, int y);

    [DllImport("user32.dll")]
    public static extern void keybd_event(byte virtualKey, byte scanCode, uint flags, UIntPtr extraInfo);

    [DllImport("user32.dll")]
    public static extern void mouse_event(uint flags, uint dx, uint dy, uint data, UIntPtr extraInfo);
}
"@
}

function Resolve-ExampleVirtualKey
{
    param([Parameter(Mandatory = $true)][string]$Key)

    $normalized = $Key.Trim().ToUpperInvariant()
    if ($normalized.Length -eq 1)
    {
        $code = [int][char]$normalized
        if (
            ($code -ge [int][char]'A' -and $code -le [int][char]'Z') -or
            ($code -ge [int][char]'0' -and $code -le [int][char]'9')
        )
        {
            return [byte]$code
        }
    }

    switch ($normalized)
    {
        "SPACE" { return [byte]0x20 }
        "ENTER" { return [byte]0x0D }
        "ESC" { return [byte]0x1B }
        "ESCAPE" { return [byte]0x1B }
        "LEFT" { return [byte]0x25 }
        "UP" { return [byte]0x26 }
        "RIGHT" { return [byte]0x27 }
        "DOWN" { return [byte]0x28 }
        default
        {
            if ($normalized -match '^F([1-9]|1[0-2])$')
            {
                return [byte](0x70 + [int]$Matches[1] - 1)
            }
            throw "Unsupported key: $Key"
        }
    }
}

function Assert-ExampleWindowStable
{
    param(
        [Parameter(Mandatory = $true)][IntPtr]$WindowHandle,
        [switch]$RequireForeground
    )

    if ($WindowHandle -eq [IntPtr]::Zero)
    {
        throw "Window handle is empty."
    }
    if (-not [ExampleWindowInputNative]::IsWindow($WindowHandle))
    {
        throw "Window handle is not a live window."
    }
    if (
        $RequireForeground -and
        [ExampleWindowInputNative]::GetForegroundWindow() -ne $WindowHandle
    )
    {
        throw "Target window is not the foreground window."
    }
}

function Set-ExampleWindowFocus
{
    param(
        [Parameter(Mandatory = $true)][IntPtr]$WindowHandle,
        [ValidateRange(0, 5000)][int]$DelayAfterMilliseconds = 1000
    )

    Assert-ExampleWindowStable -WindowHandle $WindowHandle
    [void][ExampleWindowInputNative]::BringWindowToTop($WindowHandle)
    [void][ExampleWindowInputNative]::SetForegroundWindow($WindowHandle)
    Start-Sleep -Milliseconds $DelayAfterMilliseconds
    Assert-ExampleWindowStable -WindowHandle $WindowHandle -RequireForeground
}

function Send-ExampleKeyTap
{
    param(
        [Parameter(Mandatory = $true)][string]$Key,
        [ValidateRange(0, 5000)][int]$DelayAfterMilliseconds = 1000
    )

    $virtualKey = Resolve-ExampleVirtualKey -Key $Key
    [ExampleWindowInputNative]::keybd_event($virtualKey, 0, 0, [UIntPtr]::Zero)
    [ExampleWindowInputNative]::keybd_event($virtualKey, 0, 0x0002, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds $DelayAfterMilliseconds
}

function Send-ExampleKeyHold
{
    param(
        [Parameter(Mandatory = $true)][string]$Key,
        [ValidateRange(1, 60000)][int]$HoldMilliseconds,
        [ValidateRange(0, 5000)][int]$DelayAfterMilliseconds = 1000
    )

    $virtualKey = Resolve-ExampleVirtualKey -Key $Key
    [ExampleWindowInputNative]::keybd_event($virtualKey, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds $HoldMilliseconds
    [ExampleWindowInputNative]::keybd_event($virtualKey, 0, 0x0002, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds $DelayAfterMilliseconds
}

function Move-ExampleMouse
{
    param(
        [Parameter(Mandatory = $true)][int]$X,
        [Parameter(Mandatory = $true)][int]$Y,
        [ValidateRange(0, 5000)][int]$DelayAfterMilliseconds = 1000
    )

    if (-not [ExampleWindowInputNative]::SetCursorPos($X, $Y))
    {
        throw "Failed to move cursor to ${X},${Y}."
    }
    Start-Sleep -Milliseconds $DelayAfterMilliseconds
}

function Invoke-ExampleMouseClick
{
    param(
        [ValidateSet("Left", "Right")][string]$Button = "Left",
        [int]$X,
        [int]$Y,
        [switch]$MoveFirst,
        [ValidateRange(0, 5000)][int]$DelayAfterMilliseconds = 1000
    )

    if ($MoveFirst)
    {
        Move-ExampleMouse -X $X -Y $Y -DelayAfterMilliseconds 250
    }

    if ($Button -eq "Left")
    {
        [ExampleWindowInputNative]::mouse_event(0x0002, 0, 0, 0, [UIntPtr]::Zero)
        [ExampleWindowInputNative]::mouse_event(0x0004, 0, 0, 0, [UIntPtr]::Zero)
    }
    else
    {
        [ExampleWindowInputNative]::mouse_event(0x0008, 0, 0, 0, [UIntPtr]::Zero)
        [ExampleWindowInputNative]::mouse_event(0x0010, 0, 0, 0, [UIntPtr]::Zero)
    }
    Start-Sleep -Milliseconds $DelayAfterMilliseconds
}

function Invoke-ExampleMouseDrag
{
    param(
        [Parameter(Mandatory = $true)][int]$StartX,
        [Parameter(Mandatory = $true)][int]$StartY,
        [Parameter(Mandatory = $true)][int]$EndX,
        [Parameter(Mandatory = $true)][int]$EndY,
        [ValidateRange(1, 60000)][int]$DurationMilliseconds,
        [ValidateRange(1, 240)][int]$Steps = 30,
        [ValidateRange(0, 5000)][int]$DelayAfterMilliseconds = 1000
    )

    Move-ExampleMouse -X $StartX -Y $StartY -DelayAfterMilliseconds 250
    [ExampleWindowInputNative]::mouse_event(0x0002, 0, 0, 0, [UIntPtr]::Zero)
    $stepDelay = [Math]::Max(1, [Math]::Floor($DurationMilliseconds / $Steps))
    for ($step = 1; $step -le $Steps; ++$step)
    {
        $ratio = $step / $Steps
        $x = [int][Math]::Round($StartX + (($EndX - $StartX) * $ratio))
        $y = [int][Math]::Round($StartY + (($EndY - $StartY) * $ratio))
        [void][ExampleWindowInputNative]::SetCursorPos($x, $y)
        Start-Sleep -Milliseconds $stepDelay
    }
    [ExampleWindowInputNative]::mouse_event(0x0004, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds $DelayAfterMilliseconds
}
