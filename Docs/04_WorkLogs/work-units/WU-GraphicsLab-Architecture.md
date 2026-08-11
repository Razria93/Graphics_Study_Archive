# WU-GraphicsLab-Architecture WorkLog

## 범위

| 항목 | 내용 |
| --- | --- |
| Work Unit | `WU-GraphicsLab-Architecture` |
| Phase | Phase S, Phase A, WU-A0 |
| 코드 범위 | `Portfolio_GraphicsLab` architecture와 Part1 roadmap |
| Evidence 범위 | original 단계별 source와 local media의 read-only 조사 |
| 제외 범위 | renderer code, asset import, build contract 변경, remote 작업 |

## 0단계부터 5단계까지의 수행 결과

| 단계 | 수행 내용 | 결과 |
| --- | --- | --- |
| 0단계 | WU-R0 merge 기준점, branch, README·AGENTS와 raw/media read-only 범위 확인 | `portfolio/graphics-lab-architecture`에서 시작, 원본 변경 없음 |
| 1단계 | Phase S reconstruction 전략과 저작·계보 표현 결정 | decision 정본 작성 |
| 2단계 | Phase A source·media inventory, 마지막 snapshot hash와 known issue 재확인 | tracked review와 local evidence baseline 작성 |
| 3단계 | Part1부터 Part4까지 capability와 original 구조 비교 | stable boundary와 deferred abstraction 분류 |
| 4단계 | WU-A0 module, ownership, coordinate, error, threading과 Part1 roadmap 작성 | architecture 정본 작성 |
| 5단계 | index·publication 연결, Markdown·UTF-8·link·Git 검사 | 사용자 1차 검수 전 상태로 정렬 |

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

## 변경 산출물

| 산출물 | 책임 |
| --- | --- |
| `Docs/04_WorkLogs/decisions/graphics-lab-reconstruction-strategy.md` | reconstruction 전략과 변경 기준 |
| `Docs/04_WorkLogs/reviews/graphics-lab-original-evidence.md` | public-safe original evidence 판단 요약 |
| `Portfolio_GraphicsLab/ARCHITECTURE.md` | module, data, transform와 Part1 roadmap 정본 |
| `Portfolio_GraphicsLab/README.md` | 정본 문서 진입점과 현재 상태 |
| `Docs/04_WorkLogs/work-unit-index.md` | Work Unit 상태 연결 |
| `Docs/00_Index/study-map.md` | project README와 architecture route |
| `Docs/05_Publication/candidate-list.md` | reconstruction 설명의 public 후보와 제한 |
| `local/Portfolio_GraphicsLab/original-evidence-baseline.md` | 절대 경로와 source/media local 기준선 |
| `local/Portfolio_GraphicsLab/part1-part4-architecture-analysis.md` | Part별 capability와 deferred abstraction 분석 |

## 검증 범위

이번 Work Unit은 source와 project를 변경하지 않으므로 build/run을 다시 수행하지 않는다. 변경 tracked Markdown 9개의 render, table, wrap 검사를 통과했다. 저장소 전체 validator 18종과 Markdown 465개 전수 검사를 통과했다. 변경 문서의 strict UTF-8과 상대 링크 검사, `git diff --check`를 통과했다. raw/reference source와 local media에는 쓰기 작업을 수행하지 않았다.

## 사용자 검수 기준

- verified reconstruction이 original authorship와 canonical history를 올바르게 구분하는지 확인한다.
- module 경계가 현재 Part1에 충분하면서 speculative engine 구조를 만들지 않는지 확인한다.
- left-handed coordinate, column-vector matrix와 transform contract를 승인할지 확인한다.
- WU-R1부터 WU-R14까지의 기능 순서와 완료 기준을 확인한다.
- 기존 texture를 제외하고 replacement asset을 사용하는 기준을 확인한다.

## 다음 작업

사용자 검수와 commit 이후 WU-R1 Window/Presentation 계획을 작성한다. WU-R1은 window lifecycle, resize, CPU framebuffer upload와 D3D11 presentation까지만 포함한다.

## 판정

WU-A0 문서 기준으로 WU-R1을 시작할 기술 blocker는 없다. coordinate·ownership contract와 WU-R1부터 WU-R14까지의 순서는 사용자 1차 검수 전 상태이며, 승인 전에는 code 구현과 commit을 진행하지 않는다.
