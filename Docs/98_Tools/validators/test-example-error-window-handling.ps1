[CmdletBinding()]
param(
    [string]$ExampleRoot = "Part3_Chapter10-13/10_GeometryPipeline_Step3_NormalLines",
    [ValidateSet("Debug", "Release")]
    [string]$Configuration = "Debug",
    [ValidateRange(1, 20)]
    [int]$DialogWaitSeconds = 5
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

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot "../../..")).Path
$scriptsRoot = Join-Path $repoRoot "Docs/98_Tools/scripts"
$findScript = Join-Path $scriptsRoot "find-example-error-windows.ps1"
$clearScript = Join-Path $scriptsRoot "clear-example-error-windows.ps1"

foreach ($path in @($findScript, $clearScript))
{
    Assert-True (Test-Path -LiteralPath $path -PathType Leaf) `
        "Required script is missing: $path"
}

$examplePath = Join-Path $repoRoot $ExampleRoot
$outputPath = Join-Path $examplePath "x64/$Configuration"
$exePath = Join-Path $outputPath "10_GeometryPipeline_Step3_NormalLines.exe"
$dllPath = Join-Path $outputPath "assimp-vc143-mtd.dll"
$renamedDllPath = "$dllPath.codex-missing-test"
$expectedTitle = "ComputerGraphics - Chapter10 Step3 NormalLines"
$targetProcessName = [IO.Path]::GetFileNameWithoutExtension($exePath)

Assert-True (Test-Path -LiteralPath $exePath -PathType Leaf) `
    "Example executable is missing: $exePath"
Assert-True (Test-Path -LiteralPath $dllPath -PathType Leaf) `
    "Assimp DLL is missing before test: $dllPath"
Assert-True (-not (Test-Path -LiteralPath $renamedDllPath)) `
    "Temporary DLL path already exists: $renamedDllPath"

$startedProcess = $null
$sinceTime = Get-Date
try
{
    Rename-Item -LiteralPath $dllPath -NewName ([IO.Path]::GetFileName($renamedDllPath))

    $startedProcess = Start-Process `
        -FilePath $exePath `
        -WorkingDirectory $examplePath `
        -PassThru `
        -WindowStyle Normal

    Start-Sleep -Seconds $DialogWaitSeconds

    $json = & powershell -NoProfile -ExecutionPolicy Bypass `
        -File $findScript `
        -TargetProcessName $targetProcessName `
        -ExpectedTitle $expectedTitle `
        -SinceTime $sinceTime `
        -AsJson
    $candidates = @()
    if (-not [string]::IsNullOrWhiteSpace(($json | Out-String)))
    {
        $parsed = $json | ConvertFrom-Json
        if ($parsed)
        {
            $candidates = @($parsed)
        }
    }

    Assert-True ($candidates.Count -gt 0) `
        "Expected an assimp runtime dialog candidate."

    & powershell -NoProfile -ExecutionPolicy Bypass `
        -File $clearScript `
        -TargetProcessName $targetProcessName `
        -ExpectedTitle $expectedTitle `
        -SinceTime $sinceTime `
        -Close
    if ($LASTEXITCODE -ne 0)
    {
        throw "clear-example-error-windows.ps1 failed with exit code $LASTEXITCODE."
    }

    $postJson = & powershell -NoProfile -ExecutionPolicy Bypass `
        -File $findScript `
        -TargetProcessName $targetProcessName `
        -ExpectedTitle $expectedTitle `
        -SinceTime $sinceTime `
        -AsJson
    $postCandidates = @()
    if (-not [string]::IsNullOrWhiteSpace(($postJson | Out-String)))
    {
        $postParsed = $postJson | ConvertFrom-Json
        if ($postParsed)
        {
            $postCandidates = @($postParsed)
        }
    }
    Assert-True ($postCandidates.Count -eq 0) `
        "Error dialog candidate remained after safe close."
}
finally
{
    if ($startedProcess)
    {
        try
        {
            $process = Get-Process -Id $startedProcess.Id -ErrorAction SilentlyContinue
            if ($process)
            {
                Stop-Process -Id $startedProcess.Id -Force -ErrorAction SilentlyContinue
            }
        }
        catch
        {
        }
    }
    if ((Test-Path -LiteralPath $renamedDllPath -PathType Leaf) -and
        -not (Test-Path -LiteralPath $dllPath))
    {
        Rename-Item -LiteralPath $renamedDllPath -NewName ([IO.Path]::GetFileName($dllPath))
    }
}

Assert-True (Test-Path -LiteralPath $dllPath -PathType Leaf) `
    "Assimp DLL was not restored: $dllPath"
Assert-True (-not (Test-Path -LiteralPath $renamedDllPath)) `
    "Temporary DLL remained after test: $renamedDllPath"

$remainingJson = & powershell -NoProfile -ExecutionPolicy Bypass `
    -File $findScript `
    -TargetProcessName $targetProcessName `
    -ExpectedTitle $expectedTitle `
    -SinceTime $sinceTime `
    -AsJson
$remaining = @()
if (-not [string]::IsNullOrWhiteSpace(($remainingJson | Out-String)))
{
    $remainingParsed = $remainingJson | ConvertFrom-Json
    if ($remainingParsed)
    {
        $remaining = @($remainingParsed)
    }
}
Assert-True ($remaining.Count -eq 0) `
    "Example error window candidate remained after test cleanup."

Write-Host "PASS: example error window handling test passed."
