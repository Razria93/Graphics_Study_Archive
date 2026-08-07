[CmdletBinding()]
param(
    [string]$TargetProcessName,
    [string]$ExpectedTitle,
    [Nullable[DateTime]]$SinceTime,
    [string[]]$Pattern,
    [string]$SessionLockPath = "local/capture-run/session.json",
    [ValidateRange(1, 300)]
    [int]$TimeoutSeconds = 30,
    [ValidateRange(1, 30)]
    [int]$QuietSeconds = 3,
    [ValidateRange(100, 5000)]
    [int]$PollMilliseconds = 1000
)

$ErrorActionPreference = "Stop"
$deadline = [DateTime]::UtcNow.AddSeconds($TimeoutSeconds)
$quietStart = $null
$lastState = $null

while ([DateTime]::UtcNow -lt $deadline)
{
    $arguments = @(
        "-NoProfile",
        "-ExecutionPolicy",
        "Bypass",
        "-File",
        (Join-Path $PSScriptRoot "find-capture-run-state.ps1"),
        "-SessionLockPath",
        $SessionLockPath,
        "-AsJson"
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

    $json = & powershell @arguments
    $state = $json | ConvertFrom-Json
    $lastState = $state
    if (-not $state.HasFindings)
    {
        if ($null -eq $quietStart)
        {
            $quietStart = [DateTime]::UtcNow
        }
        $elapsed = ([DateTime]::UtcNow - $quietStart).TotalSeconds
        if ($elapsed -ge $QuietSeconds)
        {
            Write-Host "PASS: capture/run state stayed quiet for ${QuietSeconds}s."
            exit 0
        }
    }
    else
    {
        $quietStart = $null
    }

    Start-Sleep -Milliseconds $PollMilliseconds
}

Write-Host "FAIL: capture/run state did not stay quiet within ${TimeoutSeconds}s."
if ($null -ne $lastState)
{
    if ($null -ne $lastState.SessionLock)
    {
        Write-Host "Last session lock: $($lastState.SessionLock.Path)"
        Write-Host "Last runner alive: $($lastState.SessionLock.RunnerAlive)"
        Write-Host "Last example alive: $($lastState.SessionLock.ExampleAlive)"
    }
    $lastProcesses = @($lastState.ExampleProcesses)
    if ($lastProcesses.Count -gt 0)
    {
        Write-Host "Last example process candidate(s):"
        $lastProcesses | Format-Table Id, ProcessName, MainWindowTitle -AutoSize
    }
    $lastDialogs = @($lastState.ErrorDialogs)
    if ($lastDialogs.Count -gt 0)
    {
        Write-Host "Last error dialog candidate(s):"
        $lastDialogs | Format-Table `
            Handle, Title, ClassName, ProcessId, ProcessName, MessageText, Fingerprint -AutoSize
    }
}
exit 2
