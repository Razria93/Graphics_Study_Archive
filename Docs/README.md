# Docs

Private graphics study/archive repo의 문서 입구입니다.

`Docs`는 Part/Chapter 중심 예제 문서를 우선으로 두고, repo 운영 문서는 `_repo` 아래로 분리합니다.

## 주요 위치

| 위치 | 역할 |
| --- | --- |
| [Part1_Chapter01-02](Part1_Chapter01-02/README.md) | DirectX11 setup, ImGui, bloom 예제 문서 |
| [Part1_Chapter03](Part1_Chapter03/README.md) | CPU ray tracing step별 예제 문서 |
| [Part2_Chapter04](Part2_Chapter04/README.md) | Software rasterization step별 예제 문서 |
| [Part2_Chapter05-08](Part2_Chapter05-08/README.md) | D3D11 pipeline, modeling, shader toy 예제 문서 |
| [Portfolio_RayTracer](Portfolio_RayTracer/README.md) | 대표 ray tracing 작업물 문서 |
| [_repo](_repo/) | repo 운영 문서, workflow, tracking, reference, manifests, templates |

## 자주 보는 문서

- [Migration Workflow](_repo/workflow/migration-workflow.md)
- [Part Import Workflow](_repo/workflow/part-import-workflow.md)
- [Chapter Start Checklist](_repo/workflow/chapter-start-checklist.md)
- [Session Troubleshooting Notes](_repo/workflow/session-troubleshooting.md)
- [Migration Board](_repo/tracking/migration-board.md)
- [Build Guide](_repo/tracking/build-guide.md)
- [Public 공개 준비 기준](_repo/workflow/public-readiness.md)
- [Raw to Archive 대응표](_repo/reference/raw-to-archive-map.md)
- [Asset Notes](_repo/reference/assets.md)
- [Local Study Review Workflow](_repo/workflow/local-study-review-workflow.md)
- [Study Review Template](_repo/templates/study-review-template.md)

## 운영 메모

- 예제별 tracked 문서는 `Docs/Part*_Chapter*/ExampleName/README.md`와 `status.md`에 둡니다.
- 코드에서 분리한 원문 메모, raw 문서 원문 검토, 개인 검토 초안은 tracked 문서가 아니라 `local/` 아래에 둡니다.
- build/run은 사용자가 직접 확인하기 전까지 `미확인`으로 기록합니다.
- private repo 정리가 끝나기 전에는 public repo를 별도로 구성하지 않습니다.