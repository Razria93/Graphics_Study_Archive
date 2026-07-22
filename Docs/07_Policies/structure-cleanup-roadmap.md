# Structure Cleanup Roadmap

이 문서는 Graphics Study Archive 문서 구조 정리 작업의 진행 기준을 정의한다. `Docs/00_Index`부터 `Docs/06_Publication`까지의 산출물 축 구조는 유지하고, 남은 작업은 운영 규칙, legacy 기록, local 작업장, 용어, 참조 관계를 잠그는 방향으로 진행한다.

## 기준 결정

- 산출물 축 구조는 유지한다.
- 루트 코드 폴더는 이동하지 않는다.
- 구조를 다시 엎기보다 중복 책임, stale reference, 깨진 생성 흔적, 용어 혼재를 정리한다.
- 예외적으로 후속 검수에 영향을 주는 깨진 문서는 로드맵 순서 밖이어도 먼저 수정할 수 있다.
- 매 작업 종료 후 이 문서를 갱신한다.

## 핵심 보완 축

| 순서 | 작업 | 상태 | 기준 |
| --- | --- | --- | --- |
| 1 | 정책 이름과 GitHub workflow 정리 | 완료 | `07_Policies` 정책 파일명과 승인 흐름을 정리한다. |
| 2 | `98_Tools/templates` 실사용 연결 정리 | 완료 | 실제 작업 단계에서 쓰는 템플릿만 남기고 책임을 명확히 한다. |
| 3 | `ImportPhase`를 `ImportHistory`로 변경 | 대기 | import가 현재 단계가 아니라 과거 기록임을 이름에 반영한다. |
| 4 | `_repo` 내부 안내 제거 | 대기 | 고유 정본이 없는 `_repo` 문서를 정책, tools, legacy, index로 흡수한다. |
| 5 | `local/` inventory 작성 | 대기 | tracked Docs로 승격할 후보와 폐기/유지 대상을 구분한다. |
| 6 | 문서 용어 통일 | 대기 | 루트 코드 폴더, Legacy 문서, Legacy PartDocs, local-only 작업장 용어를 통일한다. |
| 7 | 문서 구조 최종 검수 | 대기 | 링크, 참조, 문체, 폴더 책임, stale 문서를 최종 점검한다. |

## 예외 처리 기록

| 작업 | 상태 | 사유 |
| --- | --- | --- |
| WorkLog 생성 흔적 정리 | 완료 | `Docs/05_WorkLogs/WU-*.md`에 생성 스크립트 흔적이 남아 있어 후속 검수 전에 수정했다. |

## 작업 종료 보고 기준

각 작업 종료 시 다음 항목을 확인하고 보고한다.

- 이번 작업이 핵심 보완 축 어디에 해당하는지 기록한다.
- 계획 밖 예외 처리가 있었으면 사유와 영향을 기록한다.
- 변경 파일, 검증 결과, 커밋 여부를 요약한다.
- 이 로드맵의 상태를 갱신한다.
- 다음 작업을 핵심 보완 축 기준으로 제안한다.

## 현재 진행 상태

- 완료: 정책 이름과 GitHub workflow 정리
- 완료: `98_Tools/templates` 실사용 연결 정리
- 완료: WorkLog 생성 흔적 정리
- 다음 작업: `ImportPhase`를 `ImportHistory`로 변경

## 다음 작업 기준

다음 작업은 `Docs/99_Legacy/ImportPhase` 계열을 `ImportHistory`로 바꾸고 관련 링크와 표현을 갱신하는 것이다. 이때 `ImportPhase`를 현재 진행 중 단계처럼 표현한 문구는 과거 import 기록으로 고친다.
