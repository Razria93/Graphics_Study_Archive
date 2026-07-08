# Docs

Private portfolio archive용 문서 입구입니다. `Docs`는 Part/Chapter 중심 예제 문서를 우선하고, repo 운영 문서는 `_repo` 아래로 분리합니다.

## 주요 위치

| 위치 | 역할 |
| --- | --- |
| [Part1_Chapter01-02](Part1_Chapter01-02/README.md) | Part/Chapter 중심 예제 문서 |
| [Part1_Chapter03](Part1_Chapter03/README.md) | CPU ray tracing Step별 예제 문서 |
| [Portfolio_RayTracer](Portfolio_RayTracer/README.md) | 대표 ray tracing 작업물 문서 |
| [_repo](_repo/) | repo 운영 문서, workflow, tracking, reference, manifests, templates |

## 자주 보는 문서

- [Migration Workflow](_repo/workflow/migration-workflow.md)
- [Migration Board](_repo/tracking/migration-board.md)
- [Public 공개 준비 기준](_repo/workflow/public-readiness.md)
- [Raw to Archive 대응표](_repo/reference/raw-to-archive-map.md)
- [Asset Notes](_repo/reference/assets.md)

## 운영 메모

- 예제별 최종 문서는 `Docs/Part*_Chapter*/ExampleName/README.md`에 둡니다.
- 작업 상태는 `Docs/Part*_Chapter*/ExampleName/status.md`와 [Migration Board](_repo/tracking/migration-board.md)에 기록합니다.
- 코드에서 분리한 원문 메모, raw 문서 원문, 개인 검토 초안은 tracked 문서가 아니라 `.gitignore`에 등록된 `local/` 아래에 둡니다.
- private repo 정리가 끝나기 전에는 public repo를 별도로 만들지 않습니다.
