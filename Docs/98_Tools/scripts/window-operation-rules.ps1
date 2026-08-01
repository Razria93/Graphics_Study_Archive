function Test-WindowBoundsInsideRectangle
{
    param(
        [Parameter(Mandatory = $true)]$Bounds,
        [Parameter(Mandatory = $true)]$Container
    )

    return (
        $Bounds.Left -ge $Container.Left -and
        $Bounds.Top -ge $Container.Top -and
        $Bounds.Right -le $Container.Right -and
        $Bounds.Bottom -le $Container.Bottom
    )
}

function Get-CenteredWindowPlacement
{
    param(
        [Parameter(Mandatory = $true)]$Bounds,
        [Parameter(Mandatory = $true)]$WorkingArea
    )

    $width = $Bounds.Right - $Bounds.Left
    $height = $Bounds.Bottom - $Bounds.Top
    $areaWidth = $WorkingArea.Right - $WorkingArea.Left
    $areaHeight = $WorkingArea.Bottom - $WorkingArea.Top
    if ($width -le 0 -or $height -le 0)
    {
        throw "Window bounds must have positive dimensions."
    }
    if ($width -gt $areaWidth -or $height -gt $areaHeight)
    {
        throw (
            "Application window ${width}x${height} is larger than " +
            "the monitor working area ${areaWidth}x${areaHeight}."
        )
    }

    $left = $WorkingArea.Left + [Math]::Floor(($areaWidth - $width) / 2)
    $top = $WorkingArea.Top + [Math]::Floor(($areaHeight - $height) / 2)
    return [PSCustomObject]@{
        Left = [int]$left
        Top = [int]$top
        Right = [int]($left + $width)
        Bottom = [int]($top + $height)
        DeltaX = [int]($left - $Bounds.Left)
        DeltaY = [int]($top - $Bounds.Top)
    }
}

function Invoke-WindowOperationCountdown
{
    param(
        [ValidateRange(0, 10)]
        [int]$Seconds,
        [scriptblock]$OnTick
    )

    for ($remaining = $Seconds; $remaining -gt 0; --$remaining)
    {
        if ($null -ne $OnTick)
        {
            & $OnTick $remaining
        }
        else
        {
            Write-Host "Starting in $remaining..."
        }
        Start-Sleep -Seconds 1
    }
}
