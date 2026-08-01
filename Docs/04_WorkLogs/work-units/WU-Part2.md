# WU-Part2 WorkLog

## 범위

| 항목 | 내용 |
| --- | --- |
| Work Unit | `WU-Part2` |
| 현재 마감 대상 | `Part2_Chapter05-08` Chapter05 순차 정규화 |
| 후속 코드 범위 | Chapter05 Step3부터 Chapter08까지 |
| 주요 문서 축 | 코드 폴더 README, `01_Topics`, `02_Verification`, `03_Demos`, `05_Publication` |

## Chapter04 마감 snapshot

- Step1 Triangle부터 Step10 Lights까지 순차 Example README와 상세 Demo 정규화를 완료한다.
- Step1A Triangle To Circle은 사용자가 Step1을 확장한 Personal Extension으로 분리한다.
- Debug/Release x64 build/run과 capture 사실은 [Verification](../../02_Verification/Part2_Chapter04/verification-index.md)에 위임한다.
- Chapter 대표·보조·확장·시간 변화 구성은 [Demo Index](../../03_Demos/Part2_Chapter04/demo-index.md)와 [Demo Priority](../../03_Demos/demo-priority.md)에 위임한다.
- Step별 공개 가능성과 게시 선정 판단은 [Publication](../../05_Publication/candidate-list.md)에 위임한다.

## 결정

- Step1 Triangle을 최소 기준선으로 둔다.
- Step8 PerspectiveProjection을 Chapter 대표 Demo로 둔다.
- Step10 Lights를 기술 보조 Demo로 둔다.
- Step1A Triangle To Circle을 사용자 확장 Demo로 둔다.
- Step4 Animation2D를 시간 변화 Demo로 둔다.
- selected video는 조작과 시간 변화를 확인하는 local evidence로 유지하고 일반 Git history에는 추가하지 않는다.

## 정본 연결

| 책임 | 정본 |
| --- | --- |
| Chapter와 Example 흐름 | [Part2 Chapter04 README](../../../Part2_Chapter04/README.md) |
| build/run/capture 사실 | [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md) |
| 순차·대표 Demo | [Demo Index](../../03_Demos/Part2_Chapter04/demo-index.md) |
| video 필요성과 상태 | [Video Plan](../../03_Demos/video-plan.md) |
| 공개 후보와 미선정 판단 | [Candidate List](../../05_Publication/candidate-list.md) |
| GitHub 게시 상태 | [Work Unit GitHub Index](../work-unit-github-index.md) |

## 게시 snapshot

- [Chapter04 Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14) 게시와 실제 URL 동기화를 완료했다.
- [Chapter04 PR #15](https://github.com/Razria93/Graphics_Study_Archive/pull/15)을 일반 merge commit 방식으로 병합해 실제 URL과 최종 상태 동기화를 완료했다.
- [누적 Progress 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)을 Chapter04 상태로 갱신했다.
- [Phase 3-1 완료 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5150875726) 게시와 실제 URL 동기화를 완료했다.

## 후속 작업

- Chapter05 Step1 Matrix(GLM)의 Debug/Release x64 현재 재검증과 문서 정규화를 완료했다.
- Step1은 결정적 console 예제로 screenshot과 video를 제외하고 Step2에서 Chapter 최소 visual을 확보했다.
- Chapter05 Step2 Lights(GLM)의 Debug/Release x64 현재 재검증, 기본·non-uniform scale screenshot과 상세 Demo 정규화를 완료했다.
- Step2를 Chapter 최초 graphics Example과 최소 visual로 두고 video는 정지 image 두 장으로 차이를 설명할 수 있어 제외한다.
- Chapter05 Step3 DirectXMath를 다음 순차 Example로 정규화한다.
- `RowPitch`, `Map()` 실패, runtime shader path와 Step1A project identity는 별도 code task로 둔다.
