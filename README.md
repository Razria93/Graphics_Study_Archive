# Graphics Study Archive

이 저장소는 DirectX11 graphics study examples와 개인 확장 작업을 private archive 형태로 정리하는 공간이다. 목표는 raw 자료를 그대로 공개하는 것이 아니라, 코드 확인, 문서 재작성, 검증 기록, demo evidence, GitHub Issue/PR 요약을 통해 설명 가능한 portfolio archive를 만드는 것이다.

## 구조

| 위치 | 책임 |
| --- | --- |
| `Part*_Chapter*` | code/build 기준 예제 프로젝트 |
| `Portfolio_RayTracer` | Part1 기반 ray tracing 확장 작업 |
| `Docs/01_Examples` | 예제 설명 정본 |
| `Docs/02_Topics` | graphics 개념 정본 |
| `Docs/03_Verification` | build/run/capture 검증 정본 |
| `Docs/04_Demos` | demo capture/video evidence 정본 |
| `Docs/05_WorkLogs` | Issue/PR 작업 기록 정본 |
| `Docs/06_Publication` | public subset 판단 정본 |
| `Docs/07_Policies` | 문서화, 검증, demo, GitHub 운영, 공개 정책 |
| `Docs/98_Tools` | templates, validator, troubleshooting |
| `Docs/99_Legacy` | import 기록과 이전 Docs 구조 |

## 운영 원칙

- root code folder는 이동하지 않는다.
- 기존 `Docs/Part*` 문서는 `Docs/99_Legacy/PartDocs`에 보존하고 새 정본으로 사용하지 않는다.
- 새 예제 설명은 `Docs/01_Examples`에 작성한다.
- build/run/capture 최신 상태는 `Docs/03_Verification`에 기록한다.
- public 공개 기준은 `Docs/07_Policies/publication-policy.md`를 따른다.
- 직접 확인하지 않은 항목은 `미확인`으로 기록한다.

## 먼저 볼 문서

- [Docs](Docs/README.md)
- [Canonical Docs Policy](Docs/07_Policies/canonical-docs-policy.md)
- [Docs Authoring Flow Policy](Docs/07_Policies/docs-authoring-flow-policy.md)
- [Verification Policy](Docs/07_Policies/verification-policy.md)
- [Publication Policy](Docs/07_Policies/publication-policy.md)
- [Legacy Import History](Docs/99_Legacy/ImportHistory/README.md)
