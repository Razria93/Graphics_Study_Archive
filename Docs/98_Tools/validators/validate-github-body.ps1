param(
	[string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path,
	[string]$GitHubRoot = (Join-Path $Root "Docs/07_GitHub"),
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

function Test-GitHubImageUrl {
	param([string]$Url)

	if ($Url -match '^https://github\.com/[^/]+/[^/]+/blob/.+/Docs/_assets/captures/.+\?raw=true$') {
		return $true
	}

	if ($Url -match '^https://raw\.githubusercontent\.com/[^/]+/[^/]+/.+/Docs/_assets/captures/.+') {
		return $true
	}

	return $false
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
		[string[]]$Lines,
		[bool]$RequireGitHubImageUrl = $false
	)

	$NoneText = "- " + (New-Text @(0xC5C6, 0xC74C))
	$ScreenshotsHeading = "## " + (New-Text @(0xC2A4, 0xD06C, 0xB9B0, 0xC0F7))
	$Section = Get-Section -Lines $Lines -Heading $ScreenshotsHeading
	if ($null -eq $Section) {
		Add-Failure $Path "missing screenshots section"
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

			if ($RequireGitHubImageUrl -and -not (Test-GitHubImageUrl -Url $ImageUrl)) {
				Add-Failure $Path "screenshot image URL must use a GitHub absolute URL for GitHub body rendering: $Line"
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
		'(?m)^# PR',
		'(?m)^## Branch$',
		'(?m)^## Governance Rules$',
		'(?m)^## Naming Rules$',
		'(?m)^## Documentation Structure$',
		[regex]::Escape($PrPending),
		([regex]::Escape($PrBody) + '.*' + [regex]::Escape($Attach)),
		'local/',
		'Docs/_repo',
		'(?-i)Docs/Part[0-9]',
		'(?m)^## Metadata$',
		'Status: Draft'
	)

	foreach ($Pattern in $BannedPatterns) {
		if ($Content -match $Pattern) {
			Add-Failure $Path "contains banned GitHub body pattern: $Pattern"
		}
	}
}

function Test-PublicBody {
	param(
		[System.IO.FileInfo]$File,
		[string[]]$RequiredSections,
		[bool]$RequireScreenshots,
		[bool]$RequireGitHubImageUrl = $false,
		[bool]$RequireLeadingH1 = $false
	)

	$RelativePath = Get-RelativePath $File.FullName
	$Content = Get-Content -Encoding UTF8 $File.FullName -Raw
	$Lines = $Content -split "`r?`n"

	Test-CommonPublicRules -Path $RelativePath -Content $Content

	if ($RequireLeadingH1) {
		$FirstMeaningfulLine = $null
		foreach ($Line in $Lines) {
			if (-not [string]::IsNullOrWhiteSpace($Line)) {
				$FirstMeaningfulLine = $Line
				break
			}
		}

		if ($null -eq $FirstMeaningfulLine -or $FirstMeaningfulLine -notmatch '^#\s+.+') {
			Add-Failure $RelativePath "Issue/PR body must start with an H1 title source"
		}
	}

	if ($Content -match '(?im)\bTODO\b|\bTBD\b|<[^>]+>') {
		Add-Failure $RelativePath "contains placeholder text (TODO/TBD/<...>)"
	}

    foreach ($Section in $RequiredSections) {
        $Heading = "## $Section"
        if (-not ($Lines | Where-Object { $_ -eq $Heading })) {
            Add-Failure $RelativePath "missing required section: ## $Section"
        }
		else {
			$SectionLines = Get-Section -Lines $Lines -Heading $Heading
			if ($null -eq $SectionLines -or $SectionLines.Count -eq 0) {
				Add-Failure $RelativePath "required section is empty: $Heading"
			}
			else {
				$MeaningfulLines = @($SectionLines | Where-Object {
					$Trimmed = $_.Trim()
					-not [string]::IsNullOrWhiteSpace($Trimmed) -and $Trimmed -ne "-"
				})

				if ($MeaningfulLines.Count -eq 0) {
					Add-Failure $RelativePath "required section has no meaningful content: $Heading"
				}
			}
		}
    }

	Test-SectionOrder -Path $RelativePath -Lines $Lines -RequiredHeadings ($RequiredSections | ForEach-Object { "## $_" })

	if ($RequireScreenshots) {
		Test-ScreenshotsSection -Path $RelativePath -Lines $Lines -RequireGitHubImageUrl $RequireGitHubImageUrl
	}
}

function Test-CommentBodyRules {
	param(
		[System.IO.FileInfo]$File,
		[string]$Content,
		[string[]]$Lines
	)

	$RelativePath = Get-RelativePath $File.FullName
	if ($Content -match '(?m)^#\s+') {
		Add-Failure $RelativePath "comment body must not contain H1 heading"
	}

	$ThisDoc = New-Text @(0xC774, 0x20, 0xBB38, 0xC11C, 0xB294)
	$CandidateBody = New-Text @(0xD6C4, 0xBCF4, 0x20, 0xBCF8, 0xBB38)
	$PostingCandidate = New-Text @(0xAC8C, 0xC2DC, 0x20, 0xD6C4, 0xBCF4)
	$InternalGuidePatterns = @(
		$ThisDoc,
		$CandidateBody,
		$PostingCandidate
	)

	foreach ($Pattern in $InternalGuidePatterns) {
		if ($Content.Contains($Pattern)) {
			Add-Failure $RelativePath "comment body contains internal guidance phrase: $Pattern"
		}
	}
}

function Test-PlanProgressComment {
	param([System.IO.FileInfo]$File)

	$RelativePath = Get-RelativePath $File.FullName
	$Content = Get-Content -Encoding UTF8 $File.FullName -Raw
	$Lines = $Content -split "`r?`n"

	$ProgressSummary = "Graphics Study " + (New-Text @(0xC9C4, 0xD589, 0x20, 0xC694, 0xC57D))
	$Completed = New-Text @(0xC644, 0xB8CC)
	$Next = New-Text @(0xC9C4, 0xD589, 0x20, 0xC608, 0xC815)
	Test-PublicBody -File $File -RequiredSections @($ProgressSummary, $Completed, $Next, "Related PRs") -RequireScreenshots $false
	Test-CommentBodyRules -File $File -Content $Content -Lines $Lines

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

function Test-ChapterBundleCompletionComment {
	param([System.IO.FileInfo]$File)

	$RelativePath = Get-RelativePath $File.FullName
	$Content = Get-Content -Encoding UTF8 $File.FullName -Raw
	$Lines = $Content -split "`r?`n"

	Test-CommonPublicRules -Path $RelativePath -Content $Content
	Test-CommentBodyRules -File $File -Content $Content -Lines $Lines
	if ($Content -match '(?im)\bTODO\b|\bTBD\b|<[^>]+>') {
		Add-Failure $RelativePath "contains placeholder text (TODO/TBD/<...>)"
	}

	$CompletionRecord = New-Text @(0xC644, 0xB8CC, 0x20, 0xAE30, 0xB85D)
	$KoreanPattern = "^## Phase .+ " + [regex]::Escape($CompletionRecord) + "$"
	if ($Lines.Count -eq 0 -or $Lines[0] -notmatch $KoreanPattern) {
		Add-Failure $RelativePath "Chapter/Bundle completion comment must start with the Korean heading pattern: ## Phase <n-n> ..."
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
			$Trimmed = $Line.Trim()
			if (-not [string]::IsNullOrWhiteSpace($Trimmed) -and $Trimmed -ne "-") {
				$HasContent = $true
				break
			}
		}

		if (-not $HasContent) {
			Add-Failure $RelativePath "section is empty: $Heading"
		}
	}

	if ($Content -match '(?m)^## Screenshots$') {
		Add-Failure $RelativePath "Chapter/Bundle completion comment must not contain ## Screenshots"
	}

	$RelatedPrSection = Get-Section -Lines $Lines -Heading "## Related PR"
	if ($null -ne $RelatedPrSection) {
		$RelatedPrText = $RelatedPrSection -join "`n"
		$Scheduled = New-Text @(0xC608, 0xC815)
		if ($RelatedPrText -notmatch 'PR #|https://github\.com/.+/pull/[0-9]+' -and $RelatedPrText -notmatch [regex]::Escape($Scheduled)) {
			Add-Failure $RelativePath "Related PR must contain PR #, a pull request URL, or 예정"
		}
	}
}

function Test-ProgressIssue {
	param([System.IO.FileInfo]$File)

	$DefaultPublishingObjects = New-Text @(0xAE30, 0xBCF8, 0x20, 0xAC8C, 0xC2DC, 0x20, 0xAC1D, 0xCCB4)
	$OptionalIssueCriteria = (New-Text @(0xC120, 0xD0DD, 0x20)) + "Issue " + (New-Text @(0xC0DD, 0xC131, 0x20, 0xAE30, 0xC900))

	$RequiredSections = @(
		$SummarySection,
		$GoalSection,
		("Phase " + $ScopeSection),
		$DoneCriteriaSection,
		$DefaultPublishingObjects,
		$OptionalIssueCriteria,
		$RelatedDocsSection,
		$ExcludedScopeSection
	)

	Test-PublicBody -File $File -RequiredSections $RequiredSections -RequireScreenshots $false
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

			if (-not (Test-GitHubImageUrl -Url $Url)) {
				Add-Failure $RelativePath "screenshot image URL must use a GitHub absolute URL for GitHub body rendering: $Line"
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

$SummarySection = New-Text @(0xC694, 0xC57D)
$CoreConceptsSection = New-Text @(0xD575, 0xC2EC, 0x20, 0xAC1C, 0xB150)
$RepresentativeExamplesSection = New-Text @(0xB300, 0xD45C, 0x20, 0xC608, 0xC81C)
$VerificationSection = New-Text @(0xAC80, 0xC99D)
$ScreenshotsSection = New-Text @(0xC2A4, 0xD06C, 0xB9B0, 0xC0F7)
$UnverifiedLimitationsSection = New-Text @(0xBBF8, 0xD655, 0xC778, 0x20, 0x2F, 0x20, 0xC81C, 0xD55C)
$DocumentationSection = New-Text @(0xBB38, 0xC11C)
$RelatedIssuesSection = New-Text @(0xAD00, 0xB828, 0x20, 0xC774, 0xC288)
$NextStepSection = New-Text @(0xB2E4, 0xC74C, 0x20, 0xB2E8, 0xACC4)
$UnverifiedSection = New-Text @(0xBBF8, 0xD655, 0xC778)
$RelatedPrSectionName = New-Text @(0xAD00, 0xB828, 0x20, 0x0050, 0x0052)
$ScopeSection = New-Text @(0xBC94, 0xC704)
$ConceptNotesSection = New-Text @(0xAC1C, 0xB150, 0x20, 0xBA54, 0xBAA8)
$RelatedExamplesSection = New-Text @(0xAD00, 0xB828, 0x20, 0xC608, 0xC81C)
$GoalSection = New-Text @(0xBAA9, 0xD45C)
$CoreTasksSection = New-Text @(0xD575, 0xC2EC, 0x20, 0xC791, 0xC5C5)
$VerificationCriteriaSection = New-Text @(0xAC80, 0xC99D, 0x20, 0xAE30, 0xC900)
$DemoCaptureNeedSection = "Demo/Capture " + (New-Text @(0xD544, 0xC694, 0x20, 0xC5EC, 0xBD80))
$DoneCriteriaSection = New-Text @(0xC644, 0xB8CC, 0x20, 0xC870, 0xAC74)
$RelatedDocsSection = New-Text @(0xAD00, 0xB828, 0x20, 0xBB38, 0xC11C)
$ExcludedScopeSection = New-Text @(0xC81C, 0xC678, 0x20, 0xBC94, 0xC704)

$PrRequiredSections = @(
	$SummarySection,
	$ScopeSection,
	$CoreConceptsSection,
	$RepresentativeExamplesSection,
	$VerificationSection,
	$ScreenshotsSection,
	$UnverifiedLimitationsSection,
	$DocumentationSection,
	$RelatedIssuesSection,
	$NextStepSection
)

$VerificationRequiredSections = @(
	$SummarySection,
	("Build " + $VerificationSection),
	("Run " + $VerificationSection),
	("Capture " + $VerificationSection),
	$ScreenshotsSection,
	$UnverifiedSection,
	$DocumentationSection,
	$RelatedPrSectionName
)

$TopicRequiredSections = @(
	$SummarySection,
	$ScopeSection,
	$ConceptNotesSection,
	$RelatedExamplesSection,
	$DocumentationSection,
	$RelatedPrSectionName
)

$WorkUnitRequiredSections = @(
    $SummarySection,
    $GoalSection,
    $ScopeSection,
    $CoreTasksSection,
    $VerificationCriteriaSection,
    $DemoCaptureNeedSection,
    $DoneCriteriaSection,
    $RelatedDocsSection,
    $ExcludedScopeSection
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

function Test-IsGuidanceMarkdown {
	param([System.IO.FileInfo]$File)

	return ($File.Name -eq "README.md" -or $File.Name -eq "AGENTS.md")
}

$CheckedFileCount = 0

Get-OptionalMarkdownFiles -Path (Join-Path $GitHubRoot "prs") -Recurse | ForEach-Object {
	if (Test-IsGuidanceMarkdown -File $_) {
		return
	}

	++$CheckedFileCount
	Test-PublicBody -File $_ -RequiredSections $PrRequiredSections -RequireScreenshots $true -RequireGitHubImageUrl $true -RequireLeadingH1 $true
}

Get-OptionalMarkdownFiles -Path (Join-Path $GitHubRoot "plan") -Filter "plan-body.md" | ForEach-Object {
	++$CheckedFileCount
	$RelativePath = Get-RelativePath $_.FullName
	$Raw = Get-Content -Encoding UTF8 $_.FullName -Raw
	$Lines = $Raw -split "`r?`n"
	$FirstMeaningfulLine = $null
	foreach ($Line in $Lines) {
		if (-not [string]::IsNullOrWhiteSpace($Line)) {
			$FirstMeaningfulLine = $Line
			break
		}
	}

	if ($null -eq $FirstMeaningfulLine -or $FirstMeaningfulLine -notmatch '^#\s+.+') {
		Add-Failure $RelativePath "Issue/PR body must start with an H1 title source"
	}

	Test-ProgressIssue -File $_
}

Get-OptionalMarkdownFiles -Path (Join-Path $GitHubRoot "issues/work-unit") -Filter "work-unit_*.md" | ForEach-Object {
    ++$CheckedFileCount
	Test-PublicBody -File $_ -RequiredSections $WorkUnitRequiredSections -RequireScreenshots $false -RequireLeadingH1 $true
}

Get-OptionalMarkdownFiles -Path (Join-Path $GitHubRoot "issues/topic") -Filter "topic_*.md" | ForEach-Object {
	++$CheckedFileCount
	Test-TopicIssue -File $_
}

Get-OptionalMarkdownFiles -Path (Join-Path $GitHubRoot "issues/verification") -Filter "verification_*.md" | ForEach-Object {
	++$CheckedFileCount
	Test-PublicBody -File $_ -RequiredSections $VerificationRequiredSections -RequireScreenshots $true -RequireGitHubImageUrl $true -RequireLeadingH1 $true
}

$PlanProgressPath = Join-Path $GitHubRoot "plan/plan-progress.md"
if (Test-Path $PlanProgressPath) {
	++$CheckedFileCount
	Test-PlanProgressComment -File (Get-Item $PlanProgressPath)
}

Get-OptionalMarkdownFiles -Path (Join-Path $GitHubRoot "plan/comments") -Filter "*.md" | ForEach-Object {
	++$CheckedFileCount
	Test-ChapterBundleCompletionComment -File $_
}

Get-OptionalMarkdownFiles -Path $GitHubRoot -Recurse | ForEach-Object {
	if (Test-IsGuidanceMarkdown -File $_) {
		return
	}

	$RelativePath = (Get-RelativePath $_.FullName) -replace '\\', '/'
	if ($RelativePath -match '/prs/.+\.md$') {
		return
	}

	if ($RelativePath -match '/plan/plan-body\.md$' -or $RelativePath -match '/plan/plan-progress\.md$' -or $RelativePath -match '/plan/comments/.+\.md$') {
		return
	}

	if ($RelativePath -match '/issues/work-unit/work-unit_.+\.md$' -or $RelativePath -match '/issues/topic/topic_.+\.md$' -or $RelativePath -match '/issues/verification/verification_.+\.md$' -or $RelativePath -match '/issues/demo/demo_.+\.md$') {
		return
	}

	Add-Failure $RelativePath "unsupported GitHub body path"
}

Test-Templates

if ($Warnings.Count -gt 0) {
	$Warnings | ForEach-Object { Write-Warning $_ }
}

if ($Failures.Count -gt 0) {
	$Failures | ForEach-Object { Write-Output "ERROR: $_" }
	exit 1
}

Write-Output "GitHub body validation passed."
