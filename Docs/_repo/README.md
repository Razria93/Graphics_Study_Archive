# Repo Operations

이 폴더는 그래픽스 학습 아카이브의 repo 운영 문서를 둡니다.

Part/Chapter 최종 문서는 `Docs/Part*_Chapter*/` 아래에 두고, 이 폴더에는 import 기록, 검증 기준, reference, template, 이후 phase 문서가 위치합니다.

## Current Structure

| 위치 | 역할 |
| --- | --- |
| `ImportPhase/` | raw/reference에서 private archive로 선별 반영한 import 단계 기준과 기록 |
| `BuildRunVerificationMatrix.md` | 최신 build/run/capture 상태 기준 문서 |
| `DocumentationPhase/` | import 이후 문서화/정리/포트폴리오 요약 단계 문서 예정 위치 |
| `Safety/` | AI 협업, git/remote/history, troubleshooting 기준 문서 예정 위치 |
| `reference/` | raw/archive 대응과 asset 참고 기준 |
| `templates/` | 예제 README/status/review 템플릿 |

## Import Phase

- [Import Phase](ImportPhase/README.md)
- [Import Policy](ImportPhase/01_ImportPolicy.md)
- [Import Workflow](ImportPhase/02_ImportWorkflow.md)
- [Import Checklist](ImportPhase/03_ImportChecklist.md)
- [Import Verification](ImportPhase/04_ImportVerification.md)
- [Import Manifests](ImportPhase/Manifests/README.md)

## Verification

- [Build / Run Verification Matrix](BuildRunVerificationMatrix.md)
- [Asset Notes](reference/assets.md)

## Future Phases

- [Documentation Phase](DocumentationPhase/README.md)
- [Safety](Safety/README.md)

## Reference

- [Raw to Archive Map](reference/raw-to-archive-map.md)

## Templates

- [Example README Template](templates/example-readme.md)
- [Example Status Template](templates/example-status.md)
- [Study Review Template](templates/study-review-template.md)

## PR Drafts

PR 초안과 원문 사본은 tracked Docs가 아니라 `local/` 계열에서 관리합니다.
