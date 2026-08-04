[CmdletBinding()]
param(
    [string]$TargetProcessName,
    [string]$ExpectedTitle,
    [Nullable[DateTime]]$SinceTime,
    [string[]]$Pattern,
    [switch]$AsJson,
    [switch]$FailOnFound
)

$ErrorActionPreference = "Stop"
. (Join-Path $PSScriptRoot "example-error-window-utils.ps1")

$candidates = @(Get-ExampleErrorWindowCandidate `
    -TargetProcessName $TargetProcessName `
    -ExpectedTitle $ExpectedTitle `
    -SinceTime $SinceTime `
    -Pattern $Pattern)

if ($AsJson)
{
    $candidates | ConvertTo-Json -Depth 5
}
else
{
    if ($candidates.Count -eq 0)
    {
        Write-Host "PASS: no example error windows found."
    }
    else
    {
        Write-Host "FOUND: $($candidates.Count) example error window candidate(s)."
        $candidates | Format-Table `
            Handle, Title, ClassName, ProcessId, ProcessName -AutoSize
    }
}

if ($FailOnFound -and $candidates.Count -gt 0)
{
    exit 2
}
exit 0
