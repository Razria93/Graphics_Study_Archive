function Get-DemoCodeEvidenceLinkIssue {
    param([string]$Line)

    $pattern = (
        '^\s*-\s+\[([^\]]+)\]' +
        '\((?!https?://)[^)]*\.(?:cpp|h|hpp|hlsl)' +
        '#L\d+(?:-L\d+)?\)(\.)?\s*$'
    )
    if ($Line -notmatch $pattern) {
        return @()
    }

    $label = $Matches[1]
    $issues = [System.Collections.Generic.List[string]]::new()
    $forbiddenEndings = @(
        (-join (@(0xD655, 0xC778, 0xD55C, 0xB2E4) |
            ForEach-Object { [char]$_ })),
        (-join (@(0xC0B4, 0xD3B4, 0xBCF8, 0xB2E4) |
            ForEach-Object { [char]$_ })),
        (-join (@(0xCC38, 0xC870, 0xD55C, 0xB2E4) |
            ForEach-Object { [char]$_ })),
        (-join (@(0xBE44, 0xAD50, 0xD55C, 0xB2E4) |
            ForEach-Object { [char]$_ })),
        (-join (@(
            0xD655, 0xC778, 0xD560, 0x20, 0xC218, 0x20, 0xC788, 0xB2E4
        ) | ForEach-Object { [char]$_ }))
    )
    $hasForbiddenEnding = @($forbiddenEndings | Where-Object {
        $label.EndsWith($_, [StringComparison]::Ordinal)
    }).Count -gt 0
    if ($hasForbiddenEnding) {
        $issues.Add(
            "code evidence link label must use a noun phrase: '$label'"
        )
    }
    if ($Matches[2] -eq ".") {
        $issues.Add(
            "code evidence link bullet must not end with a period: '$label'"
        )
    }

    return @($issues)
}
