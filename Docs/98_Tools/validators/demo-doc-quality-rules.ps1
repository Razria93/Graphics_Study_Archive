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

function Get-DemoPseudocodeFenceIssue {
    param([string]$Content)

    $issues = [System.Collections.Generic.List[string]]::new()
    $fences = [regex]::Matches(
        $Content,
        '(?ms)^```(?<lang>cpp|text)[ \t]*\r?\n(?<body>.*?)^```[ \t]*$'
    )

    foreach ($fence in $fences) {
        $language = $fence.Groups['lang'].Value
        $body = $fence.Groups['body'].Value
        $bodyLines = $body -split "`r?`n"
        $meaningful = @($bodyLines | Where-Object {
            -not [string]::IsNullOrWhiteSpace($_)
        })

        if ($language -eq 'cpp') {
            if ($meaningful.Count -eq 0 -or
                $meaningful[0] -notmatch '^// Pseudo C\+\+:\s*\S') {
                $issues.Add(
                    "cpp fence must start with a descriptive " +
                    "'// Pseudo C++:' marker"
                )
            }
            continue
        }

        for ($i = 0; $i -lt $meaningful.Count - 1; ++$i) {
            $looksLikeFunction =
                $meaningful[$i] -match (
                    '^\s*[A-Za-z_~][\w:<>,~*&\s]*' +
                    '\([^;{}]*\)\s*$'
                )
            if ($looksLikeFunction -and
                $meaningful[$i + 1] -match '^\s*\{\s*$') {
                $issues.Add(
                    "C++-shaped pseudocode must use a cpp fence and " +
                    "a '// Pseudo C++:' marker"
                )
                break
            }
        }
    }

    return @($issues)
}
