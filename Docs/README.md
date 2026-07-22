# Docs

이 폴더는 Graphics Study Archive의 문서 산출물 공간이다. 문서 정본은 산출물 종류별 폴더에 둔다.

## 구조

| 위치 | 책임 |
| --- | --- |
| [00_Index](00_Index/README.md) | 전체 map과 문서 진입점 |
| [01_Examples](01_Examples/README.md) | 예제 설명 정본 |
| [02_Topics](02_Topics/README.md) | graphics 개념 정본 |
| [03_Verification](03_Verification/README.md) | build/run/capture 검증 정본 |
| [04_Demos](04_Demos/README.md) | demo capture/video evidence 정본 |
| [05_WorkLogs](05_WorkLogs/README.md) | Issue/PR 작업 기록 정본 |
| [06_Publication](06_Publication/README.md) | public subset 판단 정본 |
| [07_Policies](07_Policies/README.md) | 문서화, 검증, demo, GitHub 운영, 공개 정책 정본 |
| [98_Tools](98_Tools/README.md) | validator, templates, troubleshooting |
| [99_Legacy](99_Legacy/README.md) | import 기록과 이전 문서 구조 |
| [_assets](_assets/README.md) | 검토된 capture/image/video reference |

## 운영 원칙

- root의 `Part*_Chapter*`와 `Portfolio_RayTracer`는 코드와 build 기준으로 유지한다.
- 기존 `Docs/Part*` 문서는 `Docs/99_Legacy/PartDocs`로 내리고 정본으로 사용하지 않는다.
- 예제 설명, 검증, demo, 작업 기록, publication 판단은 각 산출물 축 폴더에 작성한다.
- 정책은 `Docs/07_Policies`에만 둔다.
- import 기록과 이전 workflow는 `Docs/99_Legacy`에 둔다.
- repo 내부 운영 안내는 root `AGENTS.md`, `Docs/README.md`, `Docs/07_Policies`를 기준으로 한다.
