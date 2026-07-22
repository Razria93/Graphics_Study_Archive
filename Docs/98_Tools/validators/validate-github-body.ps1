param(
	[string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
	[string]$PublicRoot = (Join-Path $Root "local/github/public"),
	[string]$TemplatesRoot = (Join-Path $Root "Docs/98_Tools/templates")
)

$ErrorActionPreference = "Stop"

$Failures = New-Object System.Collections.Generic.List[string]
$Warnings = New-Object System.Collections.Generic.List[string]

function New-Text {
	param([int[]]$CodePoints)

	return -join ($CodePoints | ForEach-Object { [char]$_ })
}

function Add-Failure {
	param(
		[string]$Path,
		[string]$Message
	)

	$Failures.Add("$Path :: $Message")
}

function Add-Warning {
	param(
		[string]$Path,
		[string]$Message
	)

	$Warnings.Add("$Path :: $Message")
}

function Get-RelativePath {
	param([string]$Path)

	return Resolve-Path -Relative $Path
}

function Get-Section {
	param(
		[string[]]$Lines,
		[string]$Heading
	)

	$Start = -1
	for ($Index = 0; $Index -lt $Lines.Count; ++$Index) {
		if ($Lines[$Index] -eq $Heading) {
			$Start = $Index
			break
		}
	}

	if ($Start -lt 0) {
		return $null
	}

	$End = $Lines.Count
	for ($Index = $Start + 1; $Index -lt $Lines.Count; ++$Index) {
		if ($Lines[$Index] -match '^## ') {
			$End = $Index
			break
		}
	}

	if ($End -le ($Start + 1)) {
		return @()
	}

	return $Lines[($Start + 1)..($End - 1)]
}

function Test-SectionOrder {
	param(
		[string]$Path,
		[string[]]$Lines,
		[string[]]$RequiredHeadings
	)

	$PreviousIndex = -1
	foreach ($Heading in $RequiredHeadings) {
		$FoundIndex = -1
		for ($Index = 0; $Index -lt $Lines.Count; ++$Index) {
			if ($Lines[$Index] -eq $Heading) {
				$FoundIndex = $Index
				break
			}
		}

		if ($FoundIndex -lt 0) {
			Add-Failure $Path "missing required heading: $Heading"
			continue
		}

		if ($FoundIndex -lt $PreviousIndex) {
			Add-Failure $Path "heading order mismatch: $Heading"
		}

		$PreviousIndex = $FoundIndex
	}
}

function Test-ScreenshotsSection {
	param(
		[string]$Path,
		[string[]]$Lines
	)

	$NoneText = "- " + (New-Text @(0xC5C6, 0xC74C))
	$Section = Get-Section -Lines $Lines -Heading "## Screenshots"
	if ($null -eq $Section) {
		Add-Failure $Path "missing ## Screenshots section"
		return
	}

	$HasImage = $false
	$HasNone = $false
	for ($Index = 0; $Index -lt $Section.Count; ++$Index) {
		$Line = $Section[$Index]
		if ($Line -eq $NoneText) {
			$HasNone = $true
		}

		if ($Line -match '^!\[[^\]]+\]\(([^)]+)\)$') {
			$HasImage = $true
			$ImageUrl = $Matches[1]
			$UsesCaptureAssetPath = $ImageUrl -match 'Docs/_assets/captures/'
			if (-not $UsesCaptureAssetPath) {
				Add-Failure $Path "screenshot image URL must point to Docs/_assets/captures: $Line"
			}

			if ($UsesCaptureAssetPath -and $ImageUrl -notmatch '\?raw=true' -and $ImageUrl -notmatch '^https://raw\.githubusercontent\.com/') {
				Add-Warning $Path "screenshot image URL should use ?raw=true unless it is a raw.githubusercontent.com URL: $Line"
			}

			$Previous = $Index - 1
			$FoundTitle = $false
			while ($Previous -ge 0) {
				if ($Section[$Previous] -match '^!\[[^\]]+\]\([^)]+\)$') {
					break
				}

				if ($Section[$Previous] -match '^### .+') {
					$FoundTitle = $true
					break
				}

				--$Previous
			}

			if (-not $FoundTitle) {
				Add-Failure $Path "image is missing a preceding ### screenshot title: $Line"
			}
			else {
				$DescriptionIndex = $Index - 1
				while ($DescriptionIndex -ge 0 -and [string]::IsNullOrWhiteSpace($Section[$DescriptionIndex])) {
					--$DescriptionIndex
				}

				if ($DescriptionIndex -lt 0 -or $Section[$DescriptionIndex] -match '^### .+' -or $Section[$DescriptionIndex] -match '^!\[[^\]]+\]\([^)]+\)$') {
					Add-Failure $Path "image is missing a description sentence before image Markdown: $Line"
				}
			}
		}

		if ($Line -match '^- `Docs/_assets/captures/') {
			Add-Failure $Path "Screenshots section uses a path-only bullet instead of image Markdown"
		}
	}

	if (-not $HasImage -and -not $HasNone) {
		Add-Failure $Path "Screenshots section must contain image Markdown or '- 없음'"
	}

	if ($HasImage -and $HasNone) {
		Add-Failure $Path "Screenshots section mixes images with '- 없음'"
	}
}

function Test-CommonPublicRules {
	param(
		[string]$Path,
		[string]$Content
	)

	$Nida = New-Text @(0xB2C8, 0xB2E4)
	$Nikka = New-Text @(0xB2C8, 0xAE4C)
	$PrPending = "PR " + (New-Text @(0xC0DD, 0xC131, 0x20, 0xD6C4, 0x20, 0xC5F0, 0xACB0, 0xD55C, 0xB2E4))
	$PrBody = "PR " + (New-Text @(0xBCF8, 0xBB38, 0xC5D0))
	$Attach = New-Text @(0xCCA8, 0xBD80, 0xD55C, 0xB2E4)

	$BannedPatterns = @(
		[regex]::Escape($Nida),
		[regex]::Escape($Nikka),
		'^# PR',
		'^## Branch$',
		'^## Governance Rules$',
		'^## Naming Rules$',
		'^## Documentation Structure$',
		[regex]::Escape($PrPending),
		([regex]::Escape($PrBody) + '.*' + [regex]::Escape($Attach)),
		'local/github/draft',
		'local/pr',
		'local/prompts',
		'Docs/_repo',
		'Docs/Part[0-9]',
		'^## Metadata$',
		'Status: Draft'
	)

	foreach ($Pattern in $BannedPatterns) {
		if ($Content -match $Pattern) {
			Add-Failure $Path "contains banned public-body pattern: $Pattern"
		}
	}
}

function Test-PublicBody {
	param(
		[System.IO.FileInfo]$File,
		[string[]]$RequiredSections,
		[bool]$RequireScreenshots
	)

	$RelativePath = Get-RelativePath $File.FullName
	$Content = Get-Content -Encoding UTF8 $File.FullName -Raw
	$Lines = $Content -split "`r?`n"

	Test-CommonPublicRules -Path $RelativePath -Content $Content

	foreach ($Section in $RequiredSections) {
		if ($Content -notmatch "(?m)^## $([regex]::Escape($Section))$") {
			Add-Failure $RelativePath "missing required section: ## $Section"
		}
	}

	Test-SectionOrder -Path $RelativePath -Lines $Lines -RequiredHeadings ($RequiredSections | ForEach-Object { "## $_" })

	if ($RequireScreenshots) {
		Test-ScreenshotsSection -Path $RelativePath -Lines $Lines
	}
}

function Test-PlanProgressComment {
	param([System.IO.FileInfo]$File)

	$RelativePath = Get-RelativePath $File.FullName
	$Content = Get-Content -Encoding UTF8 $File.FullName -Raw
	$Lines = $Content -split "`r?`n"

	$ProgressSummary = "MVP " + (New-Text @(0xC9C4, 0xD589, 0x20, 0xC694, 0xC57D))
	$Completed = New-Text @(0xC644, 0xB8CC)
	$Next = New-Text @(0xC9C4, 0xD589, 0x20, 0xC608, 0xC815)
	Test-PublicBody -File $File -RequiredSections @($ProgressSummary, $Completed, $Next, "Related PRs") -RequireScreenshots $false

	if ($Content -notmatch '(?m)^### Phase ') {
		Add-Failure $RelativePath "Plan Progress must contain at least one ### Phase heading"
	}

	$BannedDetails = @(
		(New-Text @(0xBE4C, 0xB4DC, 0x20, 0xC131, 0xACF5)),
		(New-Text @(0xBE4C, 0xB4DC, 0x20, 0xD655, 0xC778)),
		(New-Text @(0xC218, 0xB3D9, 0x20, 0xD655, 0xC778)),
		(New-Text @(0xC2A4, 0xD06C, 0xB9B0, 0xC0F7)),
		"Screenshots",
		"Unverified",
		(New-Text @(0xB0A8, 0xC740, 0x20, 0xC81C, 0xD55C))
	)
	foreach ($Term in $BannedDetails) {
		if ($Content.Contains($Term)) {
			Add-Failure $RelativePath "Plan Progress contains detailed verification-only term: $Term"
		}
	}

	$PhaseIndexes = @()
	for ($Index = 0; $Index -lt $Lines.Count; ++$Index) {
		if ($Lines[$Index] -match '^### Phase ') {
			$PhaseIndexes += $Index
		}
	}

	for ($Phase = 0; $Phase -lt $PhaseIndexes.Count; ++$Phase) {
		$Start = $PhaseIndexes[$Phase]
		$End = $Lines.Count
		if (($Phase + 1) -lt $PhaseIndexes.Count) {
			$End = $PhaseIndexes[$Phase + 1]
		}
		else {
			for ($Index = $Start + 1; $Index -lt $Lines.Count; ++$Index) {
				if ($Lines[$Index] -match '^## ') {
					$End = $Index
					break
				}
			}
		}

		$BulletCount = 0
		for ($Index = $Start + 1; $Index -lt $End; ++$Index) {
			if ($Lines[$Index] -match '^- ') {
				++$BulletCount
			}
		}

		if ($BulletCount -gt 2) {
			Add-Warning $RelativePath "Plan Progress phase has more than two bullets: $($Lines[$Start])"
		}
	}
}

function Test-PlanFeatureComment {
	param([System.IO.FileInfo]$File)

	$RelativePath = Get-RelativePath $File.FullName
	$Content = Get-Content -Encoding UTF8 $File.FullName -Raw
	$Lines = $Content -split "`r?`n"

	Test-CommonPublicRules -Path $RelativePath -Content $Content

	$ProgressRecord = New-Text @(0xC9C4, 0xD589, 0x20, 0xAE30, 0xB85D)
	if ($Lines.Count -eq 0 -or $Lines[0] -notmatch ("^## Phase .+ " + [regex]::Escape($ProgressRecord) + "$")) {
		Add-Failure $RelativePath "Plan Feature Comment must start with '## Phase <n-n> progress record'"
	}

	$FeatureHeadings = New-Object System.Collections.Generic.List[string]
	$FeatureHeadings.Add("## " + (New-Text @(0xC644, 0xB8CC, 0x20, 0xB0B4, 0xC6A9)))
	$FeatureHeadings.Add("## " + (New-Text @(0xAC80, 0xC99D)))
	$FeatureHeadings.Add("## " + (New-Text @(0xB0A8, 0xC740, 0x20, 0xC81C, 0xD55C)))
	$FeatureHeadings.Add("## Related PR")

	Test-SectionOrder -Path $RelativePath -Lines $Lines -RequiredHeadings $FeatureHeadings.ToArray()

	foreach ($Heading in $FeatureHeadings) {
		$Section = Get-Section -Lines $Lines -Heading $Heading
		if ($null -eq $Section) {
			Add-Failure $RelativePath "missing required heading: $Heading"
			continue
		}

		$HasContent = $false
		foreach ($Line in $Section) {
			if (-not [string]::IsNullOrWhiteSpace($Line)) {
				$HasContent = $true
				break
			}
		}

		if (-not $HasContent) {
			Add-Failure $RelativePath "section is empty: $Heading"
		}
	}

	if ($Content -match '(?m)^## Screenshots$') {
		Add-Failure $RelativePath "Plan Feature Comment must not contain ## Screenshots"
	}

	$RelatedPrSection = Get-Section -Lines $Lines -Heading "## Related PR"
	if ($null -ne $RelatedPrSection) {
		$RelatedPrText = $RelatedPrSection -join "`n"
		if ($RelatedPrText -notmatch 'PR #|https://github\.com/.+/pull/[0-9]+') {
			Add-Failure $RelativePath "Related PR must contain PR # or a pull request URL"
		}
	}
}

function Test-PrScreenshotComment {
	param([System.IO.FileInfo]$File)

	$RelativePath = Get-RelativePath $File.FullName
	$Content = Get-Content -Encoding UTF8 $File.FullName -Raw
	$Lines = $Content -split "`r?`n"

	Test-CommonPublicRules -Path $RelativePath -Content $Content

	if ($Lines.Count -eq 0 -or $Lines[0] -ne "## Verification Screenshots") {
		Add-Failure $RelativePath "PR Screenshot Comment must start with ## Verification Screenshots"
	}

	$Section = Get-Section -Lines $Lines -Heading "## Verification Screenshots"
	if ($null -eq $Section) {
		Add-Failure $RelativePath "missing ## Verification Screenshots section"
		return
	}

	for ($Index = 0; $Index -lt $Section.Count; ++$Index) {
		$Line = $Section[$Index]
		if ([string]::IsNullOrWhiteSpace($Line)) {
			continue
		}

		if ($Line -notmatch '^### .+') {
			Add-Failure $RelativePath "first non-empty line under ## Verification Screenshots must be a ### title"
		}

		break
	}

	$ImageCount = 0
	for ($Index = 0; $Index -lt $Section.Count; ++$Index) {
		$Line = $Section[$Index]
		if ($Line -match '^!\[[^\]]+\]\(([^)]+)\)$') {
			++$ImageCount
			$Url = $Matches[1]
			$UsesCaptureAssetPath = $Url -match 'Docs/_assets/captures/'
			if (-not $UsesCaptureAssetPath) {
				Add-Failure $RelativePath "screenshot image URL must point to Docs/_assets/captures: $Line"
			}

			if ($UsesCaptureAssetPath -and $Url -notmatch '\?raw=true' -and $Url -notmatch '^https://raw\.githubusercontent\.com/') {
				Add-Warning $RelativePath "screenshot image URL should use ?raw=true unless it is a raw.githubusercontent.com URL: $Line"
			}

			$Previous = $Index - 1
			while ($Previous -ge 0 -and [string]::IsNullOrWhiteSpace($Section[$Previous])) {
				--$Previous
			}

			if ($Previous -lt 0 -or $Section[$Previous] -match '^### .+' -or $Section[$Previous] -match '^!\[[^\]]+\]\([^)]+\)$') {
				Add-Failure $RelativePath "image is missing a description sentence before image Markdown: $Line"
			}

			$TitleIndex = $Previous - 1
			$FoundTitle = $false
			while ($TitleIndex -ge 0) {
				if ($Section[$TitleIndex] -match '^!\[[^\]]+\]\([^)]+\)$') {
					break
				}

				if ($Section[$TitleIndex] -match '^### .+') {
					$FoundTitle = $true
					break
				}

				--$TitleIndex
			}

			if (-not $FoundTitle) {
				Add-Failure $RelativePath "image is missing a preceding ### screenshot title: $Line"
			}
		}
	}

	if ($ImageCount -eq 0) {
		Add-Failure $RelativePath "PR Screenshot Comment must contain at least one image Markdown"
	}
}

function Test-TopicIssue {
	param([System.IO.FileInfo]$File)

	$RelativePath = Get-RelativePath $File.FullName
	$Lines = Get-Content -Encoding UTF8 $File.FullName

	if ($Lines.Count -eq 0 -or $Lines[0] -notmatch '^# .+') {
		Add-Failure $RelativePath "Topic Issue must start with an H1 title"
	}

	Test-PublicBody -File $File -RequiredSections $TopicRequiredSections -RequireScreenshots $false
}

function Test-Templates {
	if (-not (Test-Path $TemplatesRoot)) {
		return
	}

	Get-ChildItem $TemplatesRoot -File -Filter *.md | ForEach-Object {
		$RelativePath = Get-RelativePath $_.FullName
		$Content = Get-Content -Encoding UTF8 $_.FullName -Raw
		if ($Content -match 'Issue #2') {
			Add-Failure $RelativePath "template must not hard-code Issue #2"
		}
	}
}

$PrRequiredSections = @(
	"Summary",
	"Key Changes",
	"Verification",
	"Screenshots",
	"Unverified / Limitations",
	"Documentation",
	"Related Issues",
	"Next Step"
)

$VerificationRequiredSections = @(
	"Summary",
	"Build Verification",
	"Run Verification",
	"Capture Verification",
	"Screenshots",
	"Unverified",
	"Documentation",
	"Related PR"
)

$TopicRequiredSections = @(
	"Summary",
	"Scope",
	"Concept Notes",
	"Related Examples",
	"Documentation",
	"Related PR"
)

function Get-OptionalMarkdownFiles {
	param(
		[string]$Path,
		[switch]$Recurse,
		[string]$Filter = "*.md"
	)

	if (-not (Test-Path $Path)) {
		return @()
	}

	if ($Recurse) {
		return Get-ChildItem $Path -Recurse -File -Filter $Filter
	}

	return Get-ChildItem $Path -File -Filter $Filter
}

$CheckedFileCount = 0

Get-OptionalMarkdownFiles -Path (Join-Path $PublicRoot "prs") -Recurse | ForEach-Object {
	++$CheckedFileCount
	Test-PublicBody -File $_ -RequiredSections $PrRequiredSections -RequireScreenshots $true
}

Get-OptionalMarkdownFiles -Path (Join-Path $PublicRoot "issues/topic") | ForEach-Object {
	++$CheckedFileCount
	Test-TopicIssue -File $_
}

Get-OptionalMarkdownFiles -Path (Join-Path $PublicRoot "issues/verification") | ForEach-Object {
	++$CheckedFileCount
	Test-PublicBody -File $_ -RequiredSections $VerificationRequiredSections -RequireScreenshots $true
}

$PlanProgressPath = Join-Path $PublicRoot "issues/plan-comments/plan_progress_summary_comment.md"
if (Test-Path $PlanProgressPath) {
	++$CheckedFileCount
	Test-PlanProgressComment -File (Get-Item $PlanProgressPath)
}

Get-OptionalMarkdownFiles -Path (Join-Path $PublicRoot "issues/plan-comments") -Filter "*_worklog_comment.md" | ForEach-Object {
	++$CheckedFileCount
	Test-PlanFeatureComment -File $_
}

Get-OptionalMarkdownFiles -Path (Join-Path $PublicRoot "pr-comments") | ForEach-Object {
	++$CheckedFileCount
	Test-PrScreenshotComment -File $_
}

Test-Templates

if ($Warnings.Count -gt 0) {
	$Warnings | ForEach-Object { Write-Warning $_ }
}

if ($Failures.Count -gt 0) {
	$Failures | ForEach-Object { Write-Output "ERROR: $_" }
	exit 1
}

Write-Output "GitHub public body validation passed."
