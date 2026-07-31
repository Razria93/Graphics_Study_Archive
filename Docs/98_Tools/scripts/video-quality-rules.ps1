$ErrorActionPreference = "Stop"

function ConvertFrom-VideoRate
{
    param(
        [Parameter(Mandatory = $true)]
        [string]$Value,
        [Parameter(Mandatory = $true)]
        [string]$Description
    )

    $parts = $Value -split '/'
    if ($parts.Count -ne 2 -or [double]$parts[1] -eq 0)
    {
        throw "Invalid ${Description}: $Value."
    }

    return [double]$parts[0] / [double]$parts[1]
}

function Test-ExampleVideoFile
{
    param(
        [Parameter(Mandatory = $true)]
        [string]$Path,
        [Parameter(Mandatory = $true)]
        [string]$FfprobePath,
        [Parameter(Mandatory = $true)]
        [string]$FfmpegPath,
        [ValidateRange(1, 120)]
        [int]$ExpectedFrameRate = 30,
        [ValidateRange(0, 16384)]
        [int]$ExpectedWidth = 0,
        [ValidateRange(0, 16384)]
        [int]$ExpectedHeight = 0
    )

    $resolvedPath = [IO.Path]::GetFullPath($Path)
    if (-not (Test-Path -LiteralPath $resolvedPath -PathType Leaf))
    {
        throw "Video not found: $resolvedPath"
    }
    if ([IO.Path]::GetExtension($resolvedPath) -ne ".mp4")
    {
        throw "Expected an MP4 file: $resolvedPath"
    }
    if ((Get-Item -LiteralPath $resolvedPath).Length -le 0)
    {
        throw "Video is empty: $resolvedPath"
    }

    $probeText = (& $FfprobePath `
        -v error -show_streams -show_format -of json `
        $resolvedPath 2>&1 | Out-String)
    if ($LASTEXITCODE -ne 0)
    {
        throw "FFprobe validation failed: $probeText"
    }

    $probe = $probeText | ConvertFrom-Json
    $formatNames = @([string]$probe.format.format_name -split ',')
    if ($formatNames -notcontains "mp4")
    {
        throw "Unexpected video container: $($probe.format.format_name)."
    }

    $videoStreams = @($probe.streams | Where-Object { $_.codec_type -eq "video" })
    $audioStreams = @($probe.streams | Where-Object { $_.codec_type -eq "audio" })
    if ($videoStreams.Count -ne 1 -or $audioStreams.Count -ne 0)
    {
        throw "Expected one video stream and no audio streams."
    }

    $video = $videoStreams[0]
    if ($video.codec_name -ne "h264" -or $video.pix_fmt -ne "yuv420p")
    {
        throw "Unexpected video format: $($video.codec_name), $($video.pix_fmt)."
    }
    if ($ExpectedWidth -gt 0 -and [int]$video.width -ne $ExpectedWidth)
    {
        throw "Unexpected video width: $($video.width)."
    }
    if ($ExpectedHeight -gt 0 -and [int]$video.height -ne $ExpectedHeight)
    {
        throw "Unexpected video height: $($video.height)."
    }

    $averageRate = ConvertFrom-VideoRate `
        -Value $video.avg_frame_rate `
        -Description "average frame rate"
    $realRate = ConvertFrom-VideoRate `
        -Value $video.r_frame_rate `
        -Description "real frame rate"
    if (
        [Math]::Abs($averageRate - $ExpectedFrameRate) -gt 0.1 -or
        [Math]::Abs($realRate - $ExpectedFrameRate) -gt 0.1 -or
        [Math]::Abs($averageRate - $realRate) -gt 0.01
    )
    {
        throw "Unexpected CFR values: avg=$averageRate, real=$realRate."
    }

    $duration = [double]$probe.format.duration
    if ($duration -le 0)
    {
        throw "Video duration is not positive."
    }
    $frameCount = $null
    if ($null -ne $video.nb_frames -and "$($video.nb_frames)" -match '^\d+$')
    {
        $frameCount = [int]$video.nb_frames
        $expectedFrames = $duration * $ExpectedFrameRate
        if ([Math]::Abs($frameCount - $expectedFrames) -gt 1.0)
        {
            throw "Frame count is inconsistent with CFR duration: $($video.nb_frames)."
        }
    }

    $sensitiveTagNames = @(
        "artist",
        "author",
        "comment",
        "copyright",
        "creation_time",
        "date",
        "description",
        "gps",
        "location",
        "software",
        "title"
    )
    $technicalTags = New-Object System.Collections.Generic.List[string]
    $tagContainers = @($probe.format.tags)
    foreach ($stream in @($probe.streams))
    {
        $tagContainers += $stream.tags
    }
    foreach ($tags in $tagContainers)
    {
        if ($null -eq $tags)
        {
            continue
        }
        foreach ($property in $tags.PSObject.Properties)
        {
            $lowerName = $property.Name.ToLowerInvariant()
            if ($sensitiveTagNames -contains $lowerName)
            {
                throw "Sensitive metadata tag remains: $($property.Name)."
            }
            $technicalTags.Add("$($property.Name)=$($property.Value)")
        }
    }

    $nullDevice = if ($env:OS -eq "Windows_NT") { "NUL" } else { "/dev/null" }
    $decodeText = (& $FfmpegPath `
        -v error -i $resolvedPath -f null $nullDevice 2>&1 | Out-String)
    if ($LASTEXITCODE -ne 0)
    {
        throw "Video decode validation failed: $decodeText"
    }

    $file = Get-Item -LiteralPath $resolvedPath
    return [PSCustomObject]@{
        Path = $resolvedPath
        Container = "mp4"
        Codec = $video.codec_name
        Profile = $video.profile
        PixelFormat = $video.pix_fmt
        Width = [int]$video.width
        Height = [int]$video.height
        FrameRate = $averageRate
        Duration = $duration
        Frames = $frameCount
        VideoStreams = $videoStreams.Count
        AudioStreams = $audioStreams.Count
        Size = $file.Length
        SHA256 = (Get-FileHash -LiteralPath $resolvedPath -Algorithm SHA256).Hash
        TechnicalMetadata = @($technicalTags)
        Decode = "PASS"
    }
}
