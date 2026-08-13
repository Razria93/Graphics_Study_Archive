# WU-GraphicsLab-Architecture WorkLog

## 범위

| 항목 | 내용 |
| --- | --- |
| Work Unit | `WU-GraphicsLab-Architecture` |
| Phase | Phase S, Phase A, WU-A0 |
| 코드 범위 | `Portfolio_GraphicsLab` architecture와 Part1 roadmap |
| Evidence 범위 | original 단계별 source와 local media의 read-only 조사 |
| 제외 범위 | renderer code, asset import, build contract 변경, raw/reference와 local media 수정 |

## 0단계부터 5단계까지의 수행 결과

| 단계 | 수행 내용 | 결과 |
| --- | --- | --- |
| 0단계 | WU-R0 merge 기준점, branch, README·AGENTS와 raw/media read-only 범위 확인 | `portfolio/graphics-lab-architecture`에서 시작, 원본 변경 없음 |
| 1단계 | Phase S reconstruction 전략과 저작·계보 표현 결정 | decision 정본 작성 |
| 2단계 | Phase A source·media inventory, 마지막 snapshot hash와 known issue 재확인 | tracked review와 local evidence baseline 작성 |
| 3단계 | Part1부터 Part4까지 capability와 original 구조 비교 | stable boundary와 deferred abstraction 분류 |
| 4단계 | WU-A0 module, ownership, coordinate, error, threading과 Part1 roadmap 작성 | architecture 정본 작성 |
| 5단계 | index·publication 연결, Markdown·UTF-8·link·Git 검사 | 초기 검수 후 책임 구조 상세화와 PR push 전 검증으로 확장 |

## Phase S 결과

- original evidence를 보존하면서 canonical source를 기능 단위로 새로 작성하는 verified reconstruction 전략을 채택한다.
- bulk import 후 전면 refactoring과 original lineage를 지우는 독립 재작성을 채택하지 않는다.
- feature Work Unit마다 intent, observed evidence, canonical decision, implementation과 verification을 연결한다.

## Phase A 결과

- 단계별 source snapshot, refactoring 전후 자료, 54개 MP4와 22개 PNG를 read-only evidence로 확인했다.
- original Git history는 없으며 현재 repository history와 동일시하지 않는다.
- 마지막 두 source snapshot의 evidence 파일 51개가 모두 동일해 마지막 단계 이름을 sampling 완료 증거로 사용하지 않는다.
- original texture는 재배포 권한 확인 전까지 canonical/public tree에서 제외한다.
- detailed path, hash와 inventory는 local evidence 문서에 유지한다.

## WU-A0 결과

- application, platform, asset, scene, rendering common, D3D11 presentation과 CPU ray tracing 책임을 분리한다.
- ownership, error, threading, coordinate와 object transform contract를 정한다.
- Part1 reconstruction을 WU-R1부터 WU-R14까지 기능과 검증 단위로 나눈다.
- Part2부터 Part4까지의 기능은 future capability constraint로만 반영하고 선행 engine framework는 만들지 않는다.

## 책임 구조 상세화 결과

- Architecture 정본에서 전체 책임 지도, frame·asset 실행 흐름과 Application·Window·Scene·Frame·Asset lifetime을 구분한다.
- Application부터 미래 D3D11 graphics pipeline까지 11개 module을 같은 schema로 설명한다.
- 각 module에 역할, 담당하지 않는 것, 구성 근거, 현재 범위와 확장 조건을 기록한다.
- Unreal Engine의 구체 class hierarchy를 복제하지 않고 module encapsulation, lifetime 기반 subsystem, asset reference와 rendering resource 분리 방향을 참고한다.
- `World`, Object/Component, lifetime subsystem, Asset Registry, rendering frontend, common D3D11 backend, Render Graph, job system과 RHI의 도입 조건을 명시한다.
- 새로운 공통 abstraction은 최소 두 concrete consumer에서 반복 책임을 확인한 뒤 별도 decision으로 검수한다.

## 변경 산출물

| 산출물 | 책임 |
| --- | --- |
| `Docs/04_WorkLogs/decisions/graphics-lab-reconstruction-strategy.md` | reconstruction 전략과 변경 기준 |
| `Docs/04_WorkLogs/decisions/graphics-lab-architecture-evolution.md` | Unreal 지향 책임 원칙, 채택·보류 구조와 도입 조건 |
| `Docs/04_WorkLogs/reviews/graphics-lab-original-evidence.md` | public-safe original evidence 판단 요약 |
| `Portfolio_GraphicsLab/ARCHITECTURE.md` | module, data, transform와 Part1 roadmap 정본 |
| `Portfolio_GraphicsLab/README.md` | 정본 문서 진입점과 현재 상태 |
| `Docs/04_WorkLogs/work-unit-index.md` | Work Unit 상태 연결 |
| `Docs/00_Index/study-map.md` | project README와 architecture route |
| `Docs/05_Publication/candidate-list.md` | reconstruction 설명의 public 후보와 제한 |
| `local/Portfolio_GraphicsLab/original-evidence-baseline.md` | 절대 경로와 source/media local 기준선 |
| `local/Portfolio_GraphicsLab/part1-part4-architecture-analysis.md` | Part별 capability와 deferred abstraction 분석 |

## 검증 범위

이번 Work Unit은 source와 project를 변경하지 않으므로 build/run을 다시 수행하지 않는다. 책임 구조 상세화 범위의 tracked Markdown 7개가 render, table, wrap 검사를 통과했다. 저장소 전체 validator 18종, Markdown 470개와 table 536개 전수 검사를 통과했다. 변경 문서의 strict UTF-8과 상대 링크 검사, `git diff --check`를 통과했다. raw/reference source와 local media에는 쓰기 작업을 수행하지 않았다.

## PR #41 review와 merge

- Architecture 작업 PR은 [PR #41](https://github.com/Razria93/Graphics_Study_Archive/pull/41)로 게시했다.
- Work Unit 상태의 `검증 중` 표현이 build/run/capture 상태 정의와 맞지 않는다는 P2 review를 반영했다.
- `e943237`에서 상태를 `진행 중`으로 되돌리고 비고와 다음 gate를 PR review 단계로 교정했다.
- Markdown validator, strict UTF-8, 상대 링크, `git diff --check`와 Docs Validation 2건을 통과했다.
- Review thread를 해결하고 일반 merge commit `9566afa`로 `main`에 병합했다.
- Architecture 작업 branch는 삭제하지 않고 증빙 branch로 유지한다.

## PR #42 전환기 closeout 결과

- PR #41이 Work Unit finalization 정책 확정 전에 merge되어 같은 작업 PR에 마감 기록을 추가할 수 없다.
- [PR #42](https://github.com/Razria93/Graphics_Study_Archive/pull/42)는 이 누락을 복구하고 기본 finalization 정책을 정립하는 전환기 예외 closeout PR이다.
- Draft 사용자 검수와 Ready 전환을 완료하고, P2 review 2건을 `92581d3`에서 교정했다.
- Review 대응 commit의 저장소 전체 validator 18종, strict UTF-8, 상대 링크, `git diff --check`와 Docs Validation 2건을 통과했다.
- Review thread 2건에 원인, 대응, 검증과 반영 commit을 답글로 남기고 모두 resolve했다.
- Finalization commit `5d16e2b`에서 WU-A0 상태, PR #42 연결과 Progress Issue #7 누적·완료 payload를 확정했다.
- PR #42를 일반 merge commit `415417ff`로 병합하고 merge commit의 Docs Validation 성공을 확인했다.
- WU-A0 architecture와 reconstruction 진입 기준은 기본 branch에서 `마감` 상태다.

## 마감 lifecycle 확정

- Review 전 검사, Ready 전환, Review 대응, pre-merge finalization, merge 전 검사와 terminal execution의 6단계로 단순화한다.
- 같은 작업 branch의 finalization에서 tracked 마감 snapshot과 Progress payload를 모두 완성한다.
- Merge와 merge 성공을 조건으로 한 Progress 동기화를 한 작업 목표로 묶고 둘 다 성공해야 종료한다.
- 실제 merge, 게시 여부와 comment ID·URL은 GitHub remote에 두며 tracked 역동기화와 후속 closeout을 만들지 않는다.
- WorkLog는 마감 snapshot, Work Unit Index는 lifecycle, GitHub Index는 안정적인 객체와 payload 연결만 담당한다.

## 사용자 검수 결과

- Verified reconstruction과 original evidence 구분을 승인했다.
- Application, Scene, Asset, Rendering과 backend resource 분리 방향을 승인했다.
- Unreal Engine과 유사한 module·lifetime 중심 책임 구조로 확장하되 구체 class hierarchy는 복제하지 않는 방향을 승인했다.
- Architecture를 전체 구성, module 역할, 구성 근거와 확장 조건 순서로 언제든 다시 읽을 수 있게 상세화하는 방향을 승인했다.
- Left-handed coordinate, column-vector matrix와 WU-R1부터 WU-R14까지의 순서는 이 architecture 기준으로 유지한다.

## 다음 작업

WU-R1 Window/Presentation 계획을 작성한다. WU-R1은 window lifecycle, resize, CPU framebuffer upload와 D3D11 presentation까지만 포함한다.

## 판정

WU-A0 구현, architecture 결정, PR review 대응, finalization과 일반 merge를 완료했다. Work Unit은 기본 branch에서 `마감`이며 WU-R1을 시작할 기술 blocker는 없다.
