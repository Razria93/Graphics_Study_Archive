[CmdletBinding()]
param()

$ErrorActionPreference = "Stop"
$scriptRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$toolsRoot = Split-Path -Parent $scriptRoot
$scriptsRoot = Join-Path $toolsRoot "scripts"
$helperPath = Join-Path $scriptsRoot "window-operation-rules.ps1"
$capturePath = Join-Path $scriptsRoot "capture-example-window.ps1"
$recorderPath = Join-Path $scriptsRoot "record-example-window.ps1"

. $helperPath

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

$workingArea = [PSCustomObject]@{
    Left = 0
    Top = 0
    Right = 1920
    Bottom = 1040
}
$bounds = [PSCustomObject]@{
    Left = 10
    Top = 10
    Right = 1292
    Bottom = 1002
}
$centered = Get-CenteredWindowPlacement -Bounds $bounds -WorkingArea $workingArea
Assert-Equal 319 $centered.Left "Primary-monitor horizontal centering failed."
Assert-Equal 24 $centered.Top "Primary-monitor vertical centering failed."
Assert-True `
    (Test-WindowBoundsInsideRectangle $centered $workingArea) `
    "Centered bounds must fit inside the working area."

$negativeArea = [PSCustomObject]@{
    Left = -1920
    Top = -200
    Right = 0
    Bottom = 880
}
$negativeBounds = [PSCustomObject]@{
    Left = -1800
    Top = -100
    Right = -800
    Bottom = 700
}
$negativeCentered = Get-CenteredWindowPlacement `
    -Bounds $negativeBounds -WorkingArea $negativeArea
Assert-Equal -1460 $negativeCentered.Left "Negative-monitor horizontal centering failed."
Assert-Equal -60 $negativeCentered.Top "Negative-monitor vertical centering failed."
Assert-True `
    (Test-WindowBoundsInsideRectangle $negativeCentered $negativeArea) `
    "Negative-coordinate centered bounds must fit inside the working area."

$outside = [PSCustomObject]@{
    Left = -1921
    Top = -200
    Right = 0
    Bottom = 880
}
Assert-True `
    (-not (Test-WindowBoundsInsideRectangle $outside $negativeArea)) `
    "Out-of-bounds geometry was incorrectly accepted."

$oversized = [PSCustomObject]@{
    Left = 0
    Top = 0
    Right = 2000
    Bottom = 1200
}
$oversizeFailed = $false
try
{
    [void](Get-CenteredWindowPlacement `
        -Bounds $oversized -WorkingArea $workingArea)
}
catch
{
    $oversizeFailed = $true
}
Assert-True $oversizeFailed "An oversized window must fail centering."

Invoke-WindowOperationCountdown -Seconds 0

foreach ($path in @($helperPath, $capturePath, $recorderPath))
{
    $tokens = $null
    $errors = $null
    [void][Management.Automation.Language.Parser]::ParseFile(
        $path,
        [ref]$tokens,
        [ref]$errors
    )
    Assert-Equal 0 $errors.Count "PowerShell parser errors found in $path."
}

function Get-ScriptParameterNames
{
    param([Parameter(Mandatory = $true)][string]$Path)

    $tokens = $null
    $errors = $null
    $ast = [Management.Automation.Language.Parser]::ParseFile(
        $Path,
        [ref]$tokens,
        [ref]$errors
    )
    return @($ast.ParamBlock.Parameters | ForEach-Object {
        $_.Name.VariablePath.UserPath
    })
}

$captureParameters = Get-ScriptParameterNames $capturePath
foreach ($name in @(
    "ExecutablePath",
    "WorkingDirectory",
    "ExpectedTitle",
    "OutputPath",
    "CaptureDelayMilliseconds",
    "Overwrite",
    "KeepApplicationOpen",
    "CaptureImmediately",
    "CenterWindow",
    "CountdownSeconds"
))
{
    Assert-True ($captureParameters -contains $name) `
        "Screenshot parameter contract is missing $name."
}

$recorderParameters = Get-ScriptParameterNames $recorderPath
foreach ($name in @(
    "ExecutablePath",
    "WorkingDirectory",
    "ExpectedTitle",
    "OutputDirectory",
    "BaseName",
    "FfmpegPath",
    "FrameRate",
    "StartTimeoutSeconds",
    "ForegroundDelayMilliseconds",
    "KeepApplicationOpen",
    "OverwriteSelection",
    "CenterWindow",
    "CountdownSeconds"
))
{
    Assert-True ($recorderParameters -contains $name) `
        "Recorder parameter contract is missing $name."
}

$captureText = Get-Content -LiteralPath $capturePath -Raw
$recorderText = Get-Content -LiteralPath $recorderPath -Raw
foreach ($text in @($captureText, $recorderText))
{
    Assert-True ($text -match '\[switch\]\$CenterWindow') `
        "CenterWindow parameter is missing."
    Assert-True ($text -match '\[int\]\$CountdownSeconds\s*=\s*0') `
        "CountdownSeconds must default to zero for backward compatibility."
    Assert-True ($text -match '\[ValidateRange\(0,\s*10\)\]') `
        "CountdownSeconds must be limited to 0 through 10 seconds."
}

Assert-True ($recorderText -match '"STARTING"') `
    "Recorder STARTING feedback is missing."
Assert-True ($recorderText -match 'Drawing\.Size\(280,\s*142\)') `
    "Recorder status window must fit beside the common 1282-pixel capture."
Assert-True ($recorderText -notmatch 'BlockInput') `
    "Capture tools must not block global user input."
Assert-True ($captureText -notmatch 'BlockInput') `
    "Capture tools must not block global user input."

$isIconicCall = '[ExampleWindowCaptureNative]::IsIconic('
$showWindowCall = '[ExampleWindowCaptureNative]::ShowWindow('
$plannedBoundsAssignment = '$plannedBounds = Get-CaptureBounds $process'
$isIconicCallIndex = $captureText.LastIndexOf($isIconicCall)
$showWindowCallIndex = $captureText.LastIndexOf($showWindowCall)
$plannedBoundsIndex = $captureText.IndexOf($plannedBoundsAssignment)
Assert-True ($isIconicCallIndex -ge 0) `
    "Screenshot capture must detect a minimized window before restoring it."
Assert-True ($showWindowCallIndex -gt $isIconicCallIndex) `
    "Screenshot restore must be guarded by the minimized-window check."
Assert-True ($plannedBoundsIndex -gt $showWindowCallIndex) `
    "Screenshot restore must finish before planned bounds are recorded."

Write-Host "Window capture tool tests passed."
