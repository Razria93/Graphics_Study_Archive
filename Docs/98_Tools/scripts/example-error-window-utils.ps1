$ErrorActionPreference = "Stop"

if ($env:OS -ne "Windows_NT")
{
    throw "This helper requires Windows."
}
if (-not [Environment]::UserInteractive)
{
    throw "This helper requires an interactive desktop session."
}

if (-not ("ExampleErrorWindowNative" -as [type]))
{
    Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;

public static class ExampleErrorWindowNative
{
    public delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool EnumWindows(EnumWindowsProc lpEnumFunc, IntPtr lParam);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool EnumChildWindows(IntPtr hWndParent, EnumWindowsProc lpEnumFunc, IntPtr lParam);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool IsWindowVisible(IntPtr hWnd);

    [DllImport("user32.dll", CharSet = CharSet.Unicode)]
    public static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

    [DllImport("user32.dll", CharSet = CharSet.Unicode)]
    public static extern int GetClassName(IntPtr hWnd, StringBuilder lpClassName, int nMaxCount);

    [DllImport("user32.dll")]
    public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint lpdwProcessId);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool PostMessage(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);

    [DllImport("user32.dll")]
    public static extern IntPtr SendMessage(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool IsWindow(IntPtr hWnd);
}
"@
}

function Get-TopLevelWindowSnapshot
{
    $windows = New-Object System.Collections.Generic.List[object]
    $callback = [ExampleErrorWindowNative+EnumWindowsProc]{
        param([IntPtr]$WindowHandle, [IntPtr]$Parameter)

        $titleBuilder = New-Object Text.StringBuilder 1024
        [void][ExampleErrorWindowNative]::GetWindowText(
            $WindowHandle,
            $titleBuilder,
            $titleBuilder.Capacity
        )
        $classBuilder = New-Object Text.StringBuilder 256
        [void][ExampleErrorWindowNative]::GetClassName(
            $WindowHandle,
            $classBuilder,
            $classBuilder.Capacity
        )
        $processId = [uint32]0
        [void][ExampleErrorWindowNative]::GetWindowThreadProcessId(
            $WindowHandle,
            [ref]$processId
        )

        $processName = $null
        $processStartTime = $null
        if ($processId -ne 0)
        {
            try
            {
                $process = Get-Process -Id $processId -ErrorAction Stop
                $processName = $process.ProcessName
                try
                {
                    $processStartTime = $process.StartTime
                }
                catch
                {
                    $processStartTime = $null
                }
            }
            catch
            {
                $processName = $null
            }
        }

        $windows.Add([PSCustomObject]@{
            Handle = ("0x{0:X}" -f $WindowHandle.ToInt64())
            HandleInt64 = $WindowHandle.ToInt64()
            Title = $titleBuilder.ToString()
            ClassName = $classBuilder.ToString()
            ProcessId = [int]$processId
            ProcessName = $processName
            ProcessStartTime = $processStartTime
            Visible = [ExampleErrorWindowNative]::IsWindowVisible($WindowHandle)
        })
        return $true
    }

    [void][ExampleErrorWindowNative]::EnumWindows($callback, [IntPtr]::Zero)
    return @($windows.ToArray())
}

function ConvertTo-ErrorWindowPattern
{
    param([string[]]$Pattern)

    if ($Pattern -and $Pattern.Count -gt 0)
    {
        return ($Pattern | ForEach-Object { [regex]::Escape($_) }) -join "|"
    }
    $defaultPattern = @(
        "assimp",
        "dll",
        "error",
        "failed",
        "cannot",
        "system error",
        "오류",
        "찾을 수 없습니다"
    )
    return ($defaultPattern | ForEach-Object { [regex]::Escape($_) }) -join "|"
}

function Get-WindowChildTextSnapshot
{
    param([IntPtr]$WindowHandle)

    $children = New-Object System.Collections.Generic.List[object]
    $callback = [ExampleErrorWindowNative+EnumWindowsProc]{
        param([IntPtr]$ChildHandle, [IntPtr]$Parameter)

        $titleBuilder = New-Object Text.StringBuilder 2048
        [void][ExampleErrorWindowNative]::GetWindowText(
            $ChildHandle,
            $titleBuilder,
            $titleBuilder.Capacity
        )
        $classBuilder = New-Object Text.StringBuilder 256
        [void][ExampleErrorWindowNative]::GetClassName(
            $ChildHandle,
            $classBuilder,
            $classBuilder.Capacity
        )

        $text = $titleBuilder.ToString()
        if (-not [string]::IsNullOrWhiteSpace($text))
        {
            $children.Add([PSCustomObject]@{
                Handle = ("0x{0:X}" -f $ChildHandle.ToInt64())
                HandleInt64 = $ChildHandle.ToInt64()
                ClassName = $classBuilder.ToString()
                Text = $text
            })
        }
        return $true
    }

    [void][ExampleErrorWindowNative]::EnumChildWindows(
        $WindowHandle,
        $callback,
        [IntPtr]::Zero
    )
    return @($children.ToArray())
}

function New-ErrorWindowFingerprint
{
    param(
        [string]$Title,
        [string]$ClassName,
        [int]$ProcessId,
        [string]$ProcessName,
        [Nullable[DateTime]]$ProcessStartTime,
        [string]$MessageText,
        [string]$ButtonText
    )

    $start = ""
    if ($null -ne $ProcessStartTime)
    {
        $start = ([DateTime]$ProcessStartTime).ToString("o")
    }
    return @(
        $Title,
        $ClassName,
        $ProcessId,
        $ProcessName,
        $start,
        $MessageText,
        $ButtonText
    ) -join "|"
}

function Get-ExampleErrorWindowCandidate
{
    [CmdletBinding()]
    param(
        [string]$TargetProcessName,
        [string]$ExpectedTitle,
        [Nullable[DateTime]]$SinceTime,
        [string[]]$Pattern
    )

    $regex = ConvertTo-ErrorWindowPattern -Pattern $Pattern
    $snapshot = Get-TopLevelWindowSnapshot
    $candidates = foreach ($window in $snapshot)
    {
        if (-not $window.Visible)
        {
            continue
        }
        if ([string]::IsNullOrWhiteSpace($window.Title))
        {
            continue
        }
        if ($ExpectedTitle -and $window.Title -eq $ExpectedTitle)
        {
            continue
        }

        $matchesPattern = ($window.Title -match $regex) -or
            ($window.ClassName -match "#32770")
        $matchesTargetProcess = $false
        if ($TargetProcessName)
        {
            $normalizedTarget = [IO.Path]::GetFileNameWithoutExtension(
                $TargetProcessName
            )
            $matchesTargetProcess =
                ($window.ProcessName -eq $normalizedTarget) -or
                ($window.Title -like "*$normalizedTarget*")
        }
        $matchesSinceTime = $false
        if ($SinceTime -and $window.ProcessStartTime)
        {
            $matchesSinceTime = $window.ProcessStartTime -ge $SinceTime
        }

        $isCandidate = $matchesPattern
        if ($TargetProcessName)
        {
            $isCandidate = $isCandidate -and $matchesTargetProcess
        }
        elseif ($SinceTime)
        {
            $isCandidate = $isCandidate -and $matchesSinceTime
        }

        if ($isCandidate)
        {
            $childTexts = @(Get-WindowChildTextSnapshot `
                -WindowHandle ([IntPtr]$window.HandleInt64))
            $messageParts = @($childTexts |
                Where-Object { $_.ClassName -eq "Static" } |
                Select-Object -ExpandProperty Text)
            $buttonParts = @($childTexts |
                Where-Object { $_.ClassName -eq "Button" } |
                Select-Object -ExpandProperty Text)
            $messageText = [string]::Join(" ", $messageParts).Trim()
            $buttonText = [string]::Join(" ", $buttonParts).Trim()
            $fingerprint = New-ErrorWindowFingerprint `
                -Title $window.Title `
                -ClassName $window.ClassName `
                -ProcessId $window.ProcessId `
                -ProcessName $window.ProcessName `
                -ProcessStartTime $window.ProcessStartTime `
                -MessageText $messageText `
                -ButtonText $buttonText

            [PSCustomObject]@{
                Handle = $window.Handle
                HandleInt64 = $window.HandleInt64
                Title = $window.Title
                ClassName = $window.ClassName
                ProcessId = $window.ProcessId
                ProcessName = $window.ProcessName
                ProcessStartTime = $window.ProcessStartTime
                MessageText = $messageText
                ButtonText = $buttonText
                Fingerprint = $fingerprint
                ChildTexts = $childTexts
                Visible = $window.Visible
                MatchesPattern = $matchesPattern
                MatchesTargetProcess = $matchesTargetProcess
                MatchesSinceTime = $matchesSinceTime
            }
        }
    }

    return @($candidates)
}

function Close-ExampleErrorWindow
{
    [CmdletBinding(SupportsShouldProcess = $true)]
    param(
        [Parameter(Mandatory = $true)]
        [Int64]$HandleInt64
    )

    $handle = [IntPtr]$HandleInt64
    if (-not [ExampleErrorWindowNative]::IsWindow($handle))
    {
        return $false
    }
    if ($PSCmdlet.ShouldProcess(("0x{0:X}" -f $HandleInt64), "WM_CLOSE"))
    {
        $posted = [ExampleErrorWindowNative]::PostMessage(
            $handle,
            0x0010,
            [IntPtr]::Zero,
            [IntPtr]::Zero
        )
        if ($posted)
        {
            Start-Sleep -Milliseconds 500
            if (-not [ExampleErrorWindowNative]::IsWindow($handle))
            {
                return $true
            }
        }

        try
        {
            Add-Type -AssemblyName UIAutomationClient
            $element = [Windows.Automation.AutomationElement]::FromHandle($handle)
            if ($element)
            {
                $pattern = $element.GetCurrentPattern(
                    [Windows.Automation.WindowPattern]::Pattern
                )
                if ($pattern)
                {
                    $pattern.Close()
                    Start-Sleep -Milliseconds 500
                    return (-not [ExampleErrorWindowNative]::IsWindow($handle))
                }
            }
        }
        catch
        {
        }

        $button = @(Get-WindowChildTextSnapshot -WindowHandle $handle |
            Where-Object { $_.ClassName -eq "Button" } |
            Select-Object -First 1)
        if ($button.Count -gt 0)
        {
            [void][ExampleErrorWindowNative]::SendMessage(
                ([IntPtr]$button[0].HandleInt64),
                0x00F5,
                [IntPtr]::Zero,
                [IntPtr]::Zero
            )
            Start-Sleep -Milliseconds 500
        }

        return (-not [ExampleErrorWindowNative]::IsWindow($handle))
    }
    return $true
}
