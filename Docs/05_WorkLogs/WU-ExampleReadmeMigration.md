# WU-ExampleReadmeMigration

## 목적

`Docs/01_Examples`에 있던 예제 설명 문서를 루트 코드 폴더 아래 예제 README로 이관한다. 예제별 README는 코드 폴더의 얼굴이므로 public-safe 설명만 담고, 내부 검토 기록은 `local/study-review/`와 `Docs/05_WorkLogs/reviews/`로 분리한다.

이 Work Unit은 단순한 `02_Bloom` README 이관만이 아니라, 예제 설명 정본 위치를 코드 폴더로 옮기고 `Docs` 산출물 축 번호를 재정렬하는 구조 전환 흐름을 함께 추적한다. 실제 작업과 커밋은 단계별로 분리한다.

## 결정 사항

- 예제별 README 정본은 코드 폴더 아래에 둔다.
- `Docs/01_Examples`는 전환기 링크 허브로만 사용하고 장기적으로 폐기한다.
- `Docs/01_Examples` 폐기 후 `Docs/02_Topics`부터 `Docs/07_Policies`까지의 번호를 한 칸씩 당긴다.
- `Docs/98_Tools`, `Docs/99_Legacy`, `Docs/_assets`는 번호 재정렬 대상에서 제외한다.
- `status.md`는 코드 폴더로 내리지 않는다. 빌드, 실행, capture 상태는 Verification 축에서 관리한다.
- source review, raw/reference, origin 비교, 기존 Docs stale 판단은 public-facing README에 쓰지 않는다.
- 상세 조사 원문은 `local/study-review/`에 두고, 재사용 가능한 판단 요약만 `Docs/05_WorkLogs/reviews/`에 남긴다.
- tracked Docs에서 `local/` 파일로 직접 링크하지 않는다. local 문서에서 tracked 문서로 연결하는 것은 허용한다.

## 최종 목표 구조

| 산출물 | 현재 위치 | 재정렬 후 목표 위치 | 책임 |
| --- | --- | --- | --- |
| 예제별 README | 코드 폴더 | 코드 폴더 | 예제 목적, 핵심 개념, 빌드/실행 요약, 대표 결과, 한계 |
| Part별 예제 지도 | `Docs/00_Index/study-map.md` 또는 코드 폴더 README | 유지 | 예제 목록과 대표 예제 안내 |
| Topic 문서 | `Docs/02_Topics/` | `Docs/01_Topics/` | 여러 예제를 관통하는 graphics concept 설명 |
| Verification | `Docs/03_Verification/` | `Docs/02_Verification/` | build/run/capture 상태와 known issue |
| Demo 계획/evidence | `Docs/04_Demos/`, `Docs/_assets/` | `Docs/03_Demos/`, `Docs/_assets/` | capture/video 후보, 파일명, evidence 연결 |
| WorkLog | `Docs/05_WorkLogs/` | `Docs/04_WorkLogs/` | 작업 경위, source review 요약, follow-up |
| Publication 판단 | `Docs/06_Publication/` | `Docs/05_Publication/` | public 후보, private-only, 제외, 검토 필요 상태 |
| Policy | `Docs/07_Policies/` | `Docs/06_Policies/` | 문서 작성, 검증, GitHub 운영, 공개 정책 |
| Tools | `Docs/98_Tools/` | 유지 | templates, validators, troubleshooting |
| Legacy | `Docs/99_Legacy/` | 유지 | 과거 import 기록과 이전 문서 구조 |
| 상세 local review | `local/study-review/` | 유지 | raw/current/origin 비교, source comment inventory, stale 판단 상세 |

## README 포함 기준

예제 README에는 아래 내용을 둔다.

- 예제가 무엇을 보여주는지
- 주요 그래픽스 개념
- 코드 위치와 핵심 함수
- 빌드/실행 방법 또는 확인 상태
- 대표 capture가 있으면 1장 연결
- 한계와 known issue
- 관련 Topic, Verification, Demo 링크

예제 README에는 아래 내용을 두지 않는다.

- raw/reference, origin, current code 비교표
- source comment inventory 전문
- 기존 Docs stale 판단
- 문서화 workflow 적용 여부
- publication 후보 판정 과정
- 개인 학습 메모, 계정, 절대 경로, 환경 정보

## 내부 조사 기록 분리 기준

| 내용 | 위치 | 기준 |
| --- | --- | --- |
| 상세 조사 원문 | `local/study-review/` | raw/current/origin 비교, source comment inventory, stale 판단 상세 |
| tracked 판단 요약 | `Docs/05_WorkLogs/reviews/` | 승격 항목, 제외 분류, 반복 판단 기준, 후속 known issue |
| Work Unit 마감 요약 | `Docs/05_WorkLogs/` | 작업 범위, 산출물, follow-up |

tracked review summary에는 상세 조사 원문을 복사하지 않는다. 다음 작업자가 반복 조사하지 않아도 되는 결론만 남긴다. `Docs/05_WorkLogs/reviews/`는 현재 경로 기준이며, 번호 재정렬 후에는 `Docs/04_WorkLogs/reviews/`로 이동한다.

## 이관 절차

1. 대상 예제를 하나 선택한다.
2. current code, raw/reference, origin, 기존 Docs를 확인한다.
3. public-facing README에 필요한 내용과 내부 검토 기록을 분리한다.
4. 예제 README를 코드 폴더 아래로 작성한다.
5. `Docs/01_Examples`의 해당 예제 문서는 제거하거나 전환기 redirect로 축소한다.
6. `status.md` 내용은 Verification 축에 흡수한다.
7. 상세 source review는 `local/study-review/`에 두고, 반복 가능한 판단 요약은 `Docs/05_WorkLogs/reviews/`에 남긴다.
8. Topic, Verification, Demo, Publication, Index 링크를 새 README 위치로 갱신한다.
9. 링크와 validator를 확인한다.
10. 사용자 검토 후 커밋 여부를 결정한다.

## 구조 전환 작업 흐름

이 흐름은 하나의 구조 전환 작업으로 추적하되, 실제 커밋은 단계별로 분리한다.

1. 내부 조사 기록 분리 정책을 커밋한다.
2. 이 WorkLog에 `Docs/01_Examples` 폐기와 번호 재정렬 계획을 고정한다.
3. `Docs/01_Examples` 참조를 전수 검색하고 제거/대체 대상을 분류한다.
4. `Docs/01_Examples`를 삭제하고 예제 README 링크를 코드 폴더로 교체한다.
5. 산출물 축 번호를 재정렬한다.
   - `Docs/02_Topics` -> `Docs/01_Topics`
   - `Docs/03_Verification` -> `Docs/02_Verification`
   - `Docs/04_Demos` -> `Docs/03_Demos`
   - `Docs/05_WorkLogs` -> `Docs/04_WorkLogs`
   - `Docs/06_Publication` -> `Docs/05_Publication`
   - `Docs/07_Policies` -> `Docs/06_Policies`
6. README, AGENTS, templates, policies, WorkLogs, code README의 링크를 갱신한다.
7. `git diff --check`, stale path 검색, 에이전트 검수를 수행한다.
8. `02_Bloom` build/run/capture 검증으로 pilot을 마감한다.
9. `CubemapEnvironment` 초안은 재정렬 후 RayTracing 후속 작업으로 살릴지 폐기할지 결정한다.

## Pilot 순서

1. `Part1_Chapter01-02/02_Bloom`
2. `Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment`
3. Part1 나머지 예제 목록 정리
4. Part2 이후 Work Unit으로 확장

## 02_Bloom 적용 상태

- `Part1_Chapter01-02/02_Bloom/README.md`를 예제 README 정본으로 작성했다.
- `Docs/01_Examples/Part1_Chapter01-02/02_Bloom/README.md` 전환기 redirect는 `Docs/01_Examples` 폐기 단계에서 제거한다.
- `Docs/01_Examples/Part1_Chapter01-02/02_Bloom/status.md`는 코드 폴더로 옮기지 않고 `Docs/01_Examples` 폐기 단계에서 제거한다.
- build/run/capture 상태는 `Docs/03_Verification/Part1_Chapter01-02/verification-index.md`에 `미확인`으로 유지했다.
- demo 계획은 `Docs/04_Demos/Part1_Chapter01-02/demo-index.md`에 유지한다.
- publication 상태는 `Docs/06_Publication/candidate-list.md`에서 `검토 필요`로 유지한다.
- `02_Bloom` build/run/capture 검증은 아직 미완료다.

## Done 기준

- 코드 폴더 README가 public-safe 문서로 존재한다.
- `Docs/01_Examples`에 같은 예제 설명 본문이 중복으로 남지 않는다.
- `Docs/01_Examples` 폐기 여부와 번호 재정렬 여부가 이 WorkLog에 고정되어 있다.
- 관련 Topic, Verification, Demo, WorkLog, Publication 링크가 새 위치를 가리킨다.
- 내부 검토 내용이 README에 노출되지 않는다.
- 직접 확인하지 않은 build/run/capture는 `미확인`으로 유지된다.
- `git diff --check`와 tracked validator를 통과한다.
