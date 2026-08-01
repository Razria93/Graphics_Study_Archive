function Get-GitHubVideoAttachmentUrls
{
    param([Parameter(Mandatory = $true)][string]$Content)

    $matches = [regex]::Matches(
        $Content,
        '(?im)^\s*(https://github\.com/user-attachments/assets/[0-9a-f-]{36})\s*$'
    )
    return @($matches | ForEach-Object { $_.Groups[1].Value } | Select-Object -Unique)
}

function Get-GitHubRepresentativeVisualCount
{
    param(
        [Parameter(Mandatory = $true)][string]$Content,
        [Parameter(Mandatory = $true)][int]$ImageCount
    )

    $videoUrls = @(Get-GitHubVideoAttachmentUrls -Content $Content)
    return $ImageCount + $videoUrls.Count
}
