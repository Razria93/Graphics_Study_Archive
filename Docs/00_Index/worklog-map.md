# WorkLog Map

이 문서는 Work Unit 작업 기록과 Issue/PR 요약의 연결 방식을 정의한다.

## WorkLog 책임

`Docs/05_WorkLogs`는 작업 종료 시점의 요약을 둔다. 예제 설명, Topic, Verification, Demo, Publication 정본을 대체하지 않는다.

## Work Unit 기본 단위

| Work Unit 후보 | 범위 | 주요 산출물 |
| --- | --- | --- |
| `WU-Part1` | `Part1_Chapter01-02`, `Part1_Chapter03`, `Portfolio_RayTracer` 기초 연결 | Ray tracing 예제/Topic/검증 요약 |
| `WU-Part2` | `Part2_Chapter04`, `Part2_Chapter05-08` | Rasterization, DirectX11 pipeline, texturing 정리 |
| `WU-Part3` | `Part3_Chapter09`, `Part3_Chapter10-13` | camera, interaction, shadow, PBR/IBL 후보 정리 |
| `WU-Part4` | `Part4_Chapter14-20` | compute/simulation/advanced demo 정리 |
| `WU-Publication` | public subset 후보 정리 | 공개 가능 문서와 evidence 후보 정리 |

## GitHub 연결

| 단계 | 위치 | 책임 |
| --- | --- | --- |
| 초안 | `local/github/draft` | Issue/PR/comment 초안 작성 |
| 게시 후보 | `local/github/public` | 게시 직전 문체와 민감 정보 검수 |
| 원격 게시 | GitHub remote | 사용자가 명시 요청한 경우만 진행 |
| 게시 후 사본 | `local/github/snapshots` | 게시 본문과 리뷰 대응 사본 보존 |
| 요약 | `Docs/05_WorkLogs` | 게시 번호, 검증 요약, follow-up 기록 |
