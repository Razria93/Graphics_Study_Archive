[CmdletBinding()]
param(
    [string]$TargetProcessName,
    [string]$ExpectedTitle,
    [Nullable[DateTime]]$SinceTime,
    [string[]]$Pattern,
    [string]$SessionLockPath = "local/capture-run/session.json",
    [switch]$AsJson,
    [switch]$FailOnFound
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "example-error-window-utils.ps1")

function Resolve-OptionalFullPath
{
    param([string]$Path)
    if ([string]::IsNullOrWhiteSpace($Path))
    {
        return $null
    }
    return [IO.Path]::GetFullPath($Path)
}

function Get-SafeProcessSnapshot
{
    param([string]$ProcessName)

    if ([string]::IsNullOrWhiteSpace($ProcessName))
    {
        return @()
    }

    $normalized = [IO.Path]::GetFileNameWithoutExtension($ProcessName)
    if ([string]::IsNullOrWhiteSpace($normalized))
    {
        return @()
    }

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

    $processes = @(Get-Process -Name $normalized -ErrorAction SilentlyContinue)
    return @($processes | ForEach-Object {
        [PSCustomObject]@{
            Id = $_.Id
            ProcessName = $_.ProcessName
            MainWindowTitle = $_.MainWindowTitle
            HasExited = $false
        }
    })
}

function Get-CaptureSessionLockState
{
    param([string]$Path)

    $resolved = Resolve-OptionalFullPath $Path
    if ($null -eq $resolved -or -not (Test-Path -LiteralPath $resolved -PathType Leaf))
    {
        return $null
    }

    $content = Get-Content -LiteralPath $resolved -Encoding UTF8 -Raw
    $data = $null
    try
    {
        $data = $content | ConvertFrom-Json
    }
    catch
    {
        $data = [PSCustomObject]@{
            parseError = $_.Exception.Message
            raw = $content
        }
    }

    $runnerAlive = $false
    $exampleAlive = $false
    if ($data.runnerProcessId)
    {
        $runnerAlive = $null -ne (Get-Process -Id $data.runnerProcessId -ErrorAction SilentlyContinue)
    }
    if ($data.exampleProcessId)
    {
        $exampleAlive = $null -ne (Get-Process -Id $data.exampleProcessId -ErrorAction SilentlyContinue)
    }

    return [PSCustomObject]@{
        Path = $resolved
        Data = $data
        RunnerAlive = $runnerAlive
        ExampleAlive = $exampleAlive
    }
}

$lock = Get-CaptureSessionLockState -Path $SessionLockPath
$exampleProcesses = @(Get-SafeProcessSnapshot -ProcessName $TargetProcessName)
$errorDialogs = @(Get-ExampleErrorWindowCandidate `
    -TargetProcessName $TargetProcessName `
    -ExpectedTitle $ExpectedTitle `
    -SinceTime $SinceTime `
    -Pattern $Pattern)

$state = [PSCustomObject]@{
    SessionLock = $lock
    ExampleProcesses = $exampleProcesses
    ErrorDialogs = $errorDialogs
    HasFindings = (($null -ne $lock) -or ($exampleProcesses.Count -gt 0) -or ($errorDialogs.Count -gt 0))
}

if ($AsJson)
{
    $state | ConvertTo-Json -Depth 8
}
else
{
    if (-not $state.HasFindings)
    {
        Write-Host "PASS: capture/run state is quiet."
    }
    else
    {
        Write-Host "FOUND: capture/run state is not quiet."
        if ($null -ne $lock)
        {
            Write-Host "Session lock: $($lock.Path)"
            Write-Host "Runner alive: $($lock.RunnerAlive)"
            Write-Host "Example alive: $($lock.ExampleAlive)"
        }
        if ($exampleProcesses.Count -gt 0)
        {
            Write-Host "Example process candidate(s):"
            $exampleProcesses | Format-Table Id, ProcessName, MainWindowTitle -AutoSize
        }
        if ($errorDialogs.Count -gt 0)
        {
            Write-Host "Error dialog candidate(s):"
            $errorDialogs | Format-Table `
                Handle, Title, ClassName, ProcessId, ProcessName, MessageText, Fingerprint -AutoSize
        }
    }
}

if ($FailOnFound -and $state.HasFindings)
{
    exit 2
}
exit 0
