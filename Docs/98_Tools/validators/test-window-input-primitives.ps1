[CmdletBinding()]
param()

$ErrorActionPreference = "Stop"
$scriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$toolsRoot = Split-Path -Parent $scriptRoot
$scriptsRoot = Join-Path $toolsRoot "scripts"
$helperPath = Join-Path $scriptsRoot "window-input-primitives.ps1"

function Assert-True
{
    param([bool]$Condition, [string]$Message)
    if (-not $Condition)
    {
        throw $Message
    }
}

function Assert-Equal
{
    param($Expected, $Actual, [string]$Message)
    if ($Expected -ne $Actual)
    {
        throw "$Message Expected '$Expected', actual '$Actual'."
    }
}

Assert-True (Test-Path -LiteralPath $helperPath -PathType Leaf) `
    "Window input primitive helper is missing."

$tokens = $null
$errors = $null
[void][Management.Automation.Language.Parser]::ParseFile(
    $helperPath,
    [ref]$tokens,
    [ref]$errors
)
Assert-Equal 0 $errors.Count "PowerShell parser errors found in $helperPath."

. $helperPath

foreach ($functionName in @(
    "Resolve-ExampleVirtualKey",
    "Assert-ExampleWindowStable",
    "Set-ExampleWindowFocus",
    "Send-ExampleKeyTap",
    "Send-ExampleKeyHold",
    "Move-ExampleMouse",
    "Invoke-ExampleMouseClick",
    "Invoke-ExampleModifiedMouseClick",
    "Send-ExampleModifiedKeyTap",
    "Invoke-ExampleMouseDrag",
    "Invoke-ExampleNumericInput"
))
{
    Assert-True `
        ($null -ne (Get-Command -Name $functionName -CommandType Function -ErrorAction SilentlyContinue)) `
        "Window input primitive function is missing: $functionName."
}

Assert-Equal ([byte][char]'F') (Resolve-ExampleVirtualKey -Key "F") `
    "Letter virtual key resolution failed."
Assert-Equal ([byte][char]'W') (Resolve-ExampleVirtualKey -Key "w") `
    "Lowercase virtual key resolution failed."
Assert-Equal ([byte]0x70) (Resolve-ExampleVirtualKey -Key "F1") `
    "Function virtual key resolution failed."
Assert-Equal ([byte]0x20) (Resolve-ExampleVirtualKey -Key "Space") `
    "Named virtual key resolution failed."
Assert-Equal ([byte]0xBD) (Resolve-ExampleVirtualKey -Key "-") `
    "Minus virtual key resolution failed."
Assert-Equal ([byte]0xBD) (Resolve-ExampleVirtualKey -Key "OEM_MINUS") `
    "Named minus virtual key resolution failed."

$unsupportedFailed = $false
try
{
    [void](Resolve-ExampleVirtualKey -Key "UnsupportedKey")
}
catch
{
    $unsupportedFailed = $true
}
Assert-True $unsupportedFailed "Unsupported keys must fail explicitly."

$helperText = Get-Content -LiteralPath $helperPath -Raw
Assert-True ($helperText -match 'SetForegroundWindow') `
    "Focus primitive must use foreground recovery."
Assert-True ($helperText -match 'BringWindowToTop') `
    "Focus primitive must raise the target window."
Assert-True ($helperText -match 'GetForegroundWindow\(\) -ne \$WindowHandle') `
    "Focus primitive must verify actual foreground state."
Assert-True ($helperText -match 'keybd_event') `
    "Keyboard primitive must use explicit key down and key up events."
Assert-True ($helperText -match 'Send-ExampleModifiedKeyTap') `
    "Modified key tap primitive must be implemented for strict numeric input selection."
Assert-True ($helperText -match 'SetCursorPos') `
    "Mouse primitive must support explicit cursor origin placement."
Assert-True ($helperText -match 'mouse_event') `
    "Mouse click and drag primitive must support button down and up events."
Assert-True ($helperText -match 'Invoke-ExampleModifiedMouseClick') `
    "Modified mouse click primitive must be implemented for numeric input activation."
Assert-True ($helperText -notmatch 'BlockInput') `
    "Input primitives must not block global user input."

foreach ($functionName in @(
    "Set-ExampleWindowFocus",
    "Send-ExampleKeyTap",
    "Send-ExampleKeyHold",
    "Send-ExampleModifiedKeyTap",
    "Move-ExampleMouse",
    "Invoke-ExampleMouseClick",
    "Invoke-ExampleModifiedMouseClick",
    "Invoke-ExampleMouseDrag"
))
{
    $command = Get-Command -Name $functionName -CommandType Function
    Assert-True `
        ($command.Parameters.ContainsKey("DelayAfterMilliseconds")) `
        "$functionName must expose stabilization delay."
}

Assert-True `
    ((Get-Command Send-ExampleKeyHold).Parameters.ContainsKey("HoldMilliseconds")) `
    "Axis key hold primitive must expose hold duration."
Assert-True `
    ((Get-Command Invoke-ExampleMouseDrag).Parameters.ContainsKey("DurationMilliseconds")) `
    "Mouse drag primitive must expose drag duration."
Assert-True `
    ((Get-Command Invoke-ExampleModifiedMouseClick).Parameters.ContainsKey("ModifierKeys")) `
    "Modified click primitive must expose modifier key input."
Assert-True `
    ((Get-Command Send-ExampleModifiedKeyTap).Parameters.ContainsKey("ModifierKeys")) `
    "Modified key tap primitive must expose modifier key input."

$numericInputCommand = Get-Command Invoke-ExampleNumericInput -CommandType Function
foreach ($parameterName in @(
    "WindowHandle",
    "X",
    "Y",
    "Value",
    "FocusDelayMilliseconds",
    "MoveDelayMilliseconds",
    "CtrlClickDelayMilliseconds",
    "SelectAllDelayMilliseconds",
    "ClearDelayMilliseconds",
    "ValueDelayMilliseconds",
    "EnterDelayMilliseconds"
))
{
    Assert-True `
        ($numericInputCommand.Parameters.ContainsKey($parameterName)) `
        "Invoke-ExampleNumericInput must expose parameter $parameterName."
}

Write-Host "Window input primitive tests passed."
