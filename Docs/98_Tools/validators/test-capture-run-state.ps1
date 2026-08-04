[CmdletBinding()]
param(
    [string]$SessionLockPath = "local/capture-run/fixture-session.json",
    [ValidateRange(1, 30)]
    [int]$DialogTimeoutSeconds = 10
)

$ErrorActionPreference = "Stop"

function Assert-True
{
    param([bool]$Condition, [string]$Message)
    if (-not $Condition)
    {
        throw $Message
    }
}

function Invoke-ExpectExitCode
{
    param(
        [Parameter(Mandatory = $true)]
        [scriptblock]$ScriptBlock,
        [Parameter(Mandatory = $true)]
        [int[]]$ExpectedExitCode,
        [Parameter(Mandatory = $true)]
        [string]$Message
    )

    & $ScriptBlock
    $actual = $LASTEXITCODE
    Assert-True ($ExpectedExitCode -contains $actual) "$Message Expected $($ExpectedExitCode -join ', '), got $actual."
}

function Start-FixtureDialog
{
    param([string]$Title, [string]$Message)

    $encodedCommand = [Convert]::ToBase64String([Text.Encoding]::Unicode.GetBytes(@"
Add-Type -AssemblyName System.Windows.Forms
[void][System.Windows.Forms.MessageBox]::Show('$Message', '$Title')
"@))

    return Start-Process `
        -FilePath powershell `
        -ArgumentList @("-NoProfile", "-ExecutionPolicy", "Bypass", "-EncodedCommand", $encodedCommand) `
        -WindowStyle Hidden `
        -PassThru
}

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "../../..")).Path
$scriptsRoot = Join-Path $repoRoot "Docs/98_Tools/scripts"
$findScript = Join-Path $scriptsRoot "find-capture-run-state.ps1"
$clearScript = Join-Path $scriptsRoot "clear-capture-run-state.ps1"
$waitScript = Join-Path $scriptsRoot "wait-capture-run-quiet.ps1"
$lockPath = [IO.Path]::GetFullPath((Join-Path $repoRoot $SessionLockPath))
$lockDirectory = Split-Path -Parent $lockPath
$fixtureTitle = "CaptureRunFixtureError"
$dialogProcesses = @()
$dialogSinceTime = Get-Date

foreach ($path in @($findScript, $clearScript, $waitScript))
{
    Assert-True (Test-Path -LiteralPath $path -PathType Leaf) "Required script is missing: $path"
}

try
{
    if (-not (Test-Path -LiteralPath $lockDirectory -PathType Container))
    {
        New-Item -ItemType Directory -Path $lockDirectory -Force | Out-Null
    }
    if (Test-Path -LiteralPath $lockPath -PathType Leaf)
    {
        Remove-Item -LiteralPath $lockPath -Force
    }

    Invoke-ExpectExitCode `
        -ExpectedExitCode 0 `
        -Message "Quiet preflight failed." `
        -ScriptBlock {
            & powershell -NoProfile -ExecutionPolicy Bypass `
                -File $waitScript `
                -SessionLockPath $lockPath `
                -TimeoutSeconds 5 `
                -QuietSeconds 1 `
                -PollMilliseconds 250
        }

    $fixtureLock = [PSCustomObject]@{
        sessionId = "fixture-capture-run-state"
        createdAt = (Get-Date).ToString("o")
        runnerProcessId = $PID
        exampleProcessId = $null
        reason = "controlled stale session lock fixture"
    }
    $fixtureLock | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath $lockPath -Encoding UTF8

    Invoke-ExpectExitCode `
        -ExpectedExitCode 2 `
        -Message "Stale session lock was not detected." `
        -ScriptBlock {
            & powershell -NoProfile -ExecutionPolicy Bypass `
                -File $findScript `
                -SessionLockPath $lockPath `
                -FailOnFound
        }

    Invoke-ExpectExitCode `
        -ExpectedExitCode 2 `
        -Message "Quiet wait did not fail on stale session lock." `
        -ScriptBlock {
            & powershell -NoProfile -ExecutionPolicy Bypass `
                -File $waitScript `
                -SessionLockPath $lockPath `
                -TimeoutSeconds 2 `
                -QuietSeconds 1 `
                -PollMilliseconds 250
        }

    Invoke-ExpectExitCode `
        -ExpectedExitCode 0 `
        -Message "Session lock cleanup failed." `
        -ScriptBlock {
            & powershell -NoProfile -ExecutionPolicy Bypass `
                -File $clearScript `
                -SessionLockPath $lockPath `
                -RemoveSessionLock `
                -QuietSeconds 1
        }
    Assert-True (-not (Test-Path -LiteralPath $lockPath -PathType Leaf)) "Fixture session lock remained after cleanup."

    foreach ($protectedName in @("powershell", "explorer"))
    {
        $previousErrorActionPreference = $ErrorActionPreference
        $ErrorActionPreference = "Continue"
        try
        {
            $output = & powershell -NoProfile -ExecutionPolicy Bypass `
                -File $findScript `
                -TargetProcessName $protectedName `
                -FailOnFound 2>&1
            $exitCode = $LASTEXITCODE
        }
        finally
        {
            $ErrorActionPreference = $previousErrorActionPreference
        }
        $text = ($output | Out-String)
        Assert-True (($exitCode -ne 0) -and ($text -like "*Refusing broad or protected process target*")) `
            "Protected process target was not refused: $protectedName"
    }

    $dialogSinceTime = Get-Date
    $dialogProcesses += Start-FixtureDialog -Title $fixtureTitle -Message "Fixture dialog 1"
    $dialogProcesses += Start-FixtureDialog -Title $fixtureTitle -Message "Fixture dialog 2"

    $deadline = [DateTime]::UtcNow.AddSeconds($DialogTimeoutSeconds)
    $detectedCount = 0
    while ([DateTime]::UtcNow -lt $deadline)
    {
        $json = & powershell -NoProfile -ExecutionPolicy Bypass `
            -File $findScript `
            -SinceTime $dialogSinceTime `
            -Pattern $fixtureTitle `
            -AsJson
        $state = $json | ConvertFrom-Json
        $detectedCount = @($state.ErrorDialogs).Count
        if ($detectedCount -ge 2)
        {
            break
        }
        Start-Sleep -Milliseconds 250
    }
    Assert-True ($detectedCount -ge 2) "Expected two fixture dialogs, detected $detectedCount."

    Invoke-ExpectExitCode `
        -ExpectedExitCode 0 `
        -Message "Fixture dialog drain failed." `
        -ScriptBlock {
            & powershell -NoProfile -ExecutionPolicy Bypass `
                -File $clearScript `
                -SinceTime $dialogSinceTime `
                -Pattern $fixtureTitle `
                -CloseErrorDialogs `
                -MaxDrainPasses 5 `
                -QuietSeconds 1
        }

    Invoke-ExpectExitCode `
        -ExpectedExitCode 0 `
        -Message "Quiet wait failed after fixture dialog drain." `
        -ScriptBlock {
            & powershell -NoProfile -ExecutionPolicy Bypass `
                -File $waitScript `
                -SinceTime $dialogSinceTime `
                -Pattern $fixtureTitle `
                -TimeoutSeconds 5 `
                -QuietSeconds 1 `
                -PollMilliseconds 250
        }
}
finally
{
    foreach ($process in @($dialogProcesses))
    {
        if ($process)
        {
            $live = Get-Process -Id $process.Id -ErrorAction SilentlyContinue
            if ($live)
            {
                Stop-Process -Id $process.Id -Force -ErrorAction SilentlyContinue
            }
        }
    }
    if (Test-Path -LiteralPath $lockPath -PathType Leaf)
    {
        Remove-Item -LiteralPath $lockPath -Force
    }
}

Write-Host "PASS: capture/run state rehearsal passed."
