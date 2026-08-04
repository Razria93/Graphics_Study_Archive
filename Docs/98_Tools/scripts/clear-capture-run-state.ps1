[CmdletBinding()]
param(
    [string]$TargetProcessName,
    [string]$ExpectedTitle,
    [Nullable[DateTime]]$SinceTime,
    [string[]]$Pattern,
    [string]$SessionLockPath = "local/capture-run/session.json",
    [switch]$CloseErrorDialogs,
    [switch]$KillExampleProcess,
    [switch]$RemoveSessionLock,
    [ValidateRange(1, 10)]
    [int]$MaxDrainPasses = 5,
    [ValidateRange(1, 10)]
    [int]$QuietSeconds = 3
)

$ErrorActionPreference = "Stop"

if (-not $CloseErrorDialogs -and -not $KillExampleProcess -and -not $RemoveSessionLock)
{
    Write-Host "DRY-RUN: no cleanup switch was provided."
    $scanArguments = @(
        "-NoProfile",
        "-ExecutionPolicy",
        "Bypass",
        "-File",
        (Join-Path $PSScriptRoot "find-capture-run-state.ps1"),
        "-SessionLockPath",
        $SessionLockPath
    )
    if ($TargetProcessName)
    {
        $scanArguments += @("-TargetProcessName", $TargetProcessName)
    }
    if ($ExpectedTitle)
    {
        $scanArguments += @("-ExpectedTitle", $ExpectedTitle)
    }
    & powershell @scanArguments
    exit $LASTEXITCODE
}

if ($KillExampleProcess)
{
    if ([string]::IsNullOrWhiteSpace($TargetProcessName))
    {
        throw "-KillExampleProcess requires -TargetProcessName."
    }
    $normalized = [IO.Path]::GetFileNameWithoutExtension($TargetProcessName)
    $protectedNames = @(
        "Code",
        "Code - Insiders",
        "explorer",
        "ChatGPT",
        "Codex",
        "powershell",
        "pwsh",
        "WindowsTerminal",
        "OpenConsole"
    )
    if ($protectedNames -contains $normalized)
    {
        throw "Refusing broad or protected process target: $normalized"
    }

    $targets = @(Get-Process -Name $normalized -ErrorAction SilentlyContinue)
    if ($targets.Count -eq 0)
    {
        Write-Host "PASS: no example process candidates found for $normalized."
    }
    else
    {
        Write-Host "Stopping example process candidate(s):"
        $targets | Format-Table Id, ProcessName, MainWindowTitle -AutoSize
        foreach ($process in $targets)
        {
            Stop-Process -Id $process.Id -Force
        }
    }
}

if ($CloseErrorDialogs)
{
    $arguments = @(
        "-NoProfile",
        "-ExecutionPolicy",
        "Bypass",
        "-File",
        (Join-Path $PSScriptRoot "clear-example-error-windows.ps1"),
        "-Close",
        "-MaxDrainPasses",
        $MaxDrainPasses,
        "-QuietSeconds",
        $QuietSeconds
    )
    if ($TargetProcessName)
    {
        $arguments += @("-TargetProcessName", $TargetProcessName)
    }
    if ($ExpectedTitle)
    {
        $arguments += @("-ExpectedTitle", $ExpectedTitle)
    }
    if ($SinceTime)
    {
        $arguments += @("-SinceTime", $SinceTime.ToString("o"))
    }
    foreach ($item in @($Pattern))
    {
        if (-not [string]::IsNullOrWhiteSpace($item))
        {
            $arguments += @("-Pattern", $item)
        }
    }
    & powershell @arguments
    if ($LASTEXITCODE -ne 0)
    {
        exit $LASTEXITCODE
    }
}

if ($RemoveSessionLock)
{
    $resolvedLock = [IO.Path]::GetFullPath($SessionLockPath)
    if (Test-Path -LiteralPath $resolvedLock -PathType Leaf)
    {
        Remove-Item -LiteralPath $resolvedLock -Force
        Write-Host "Removed session lock: $resolvedLock"
    }
    else
    {
        Write-Host "PASS: no session lock found."
    }
}

$waitArguments = @(
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-File",
    (Join-Path $PSScriptRoot "wait-capture-run-quiet.ps1"),
    "-SessionLockPath",
    $SessionLockPath,
    "-QuietSeconds",
    $QuietSeconds,
    "-TimeoutSeconds",
    ([Math]::Max(10, $QuietSeconds + 5))
)
if ($TargetProcessName)
{
    $waitArguments += @("-TargetProcessName", $TargetProcessName)
}
if ($ExpectedTitle)
{
    $waitArguments += @("-ExpectedTitle", $ExpectedTitle)
}
& powershell @waitArguments
exit $LASTEXITCODE
