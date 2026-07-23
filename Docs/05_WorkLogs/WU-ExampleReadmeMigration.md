# WU-ExampleReadmeMigration

## 목적

`Docs/01_Examples`에 있던 예제 설명 문서를 루트 코드 폴더 아래 예제 README로 이관한다. 예제별 README는 코드 폴더의 얼굴이므로 public-safe 설명만 담고, 내부 검토 기록은 `Docs` 또는 `local/`의 적절한 위치로 분리한다.

## 결정 사항

- `Docs/01_Examples`는 장기적으로 폐기한다.
- 번호 체계는 당장 재정렬하지 않는다. `01_Examples`가 비더라도 `02_Topics`, `03_Verification`, `04_Demos` 번호는 유지한다.
- 예제별 README 정본은 코드 폴더 아래에 둔다.
- `status.md`는 코드 폴더로 내리지 않는다. 빌드, 실행, capture 상태는 `Docs/03_Verification`에서 관리한다.
- source review, raw/reference, origin 비교, 기존 Docs stale 판단은 public-facing README에 쓰지 않는다.
- detailed source comment inventory는 `local/`에 두고, tracked 문서에는 필요한 요약만 남긴다.

## 최종 책임 분리

| 산출물 | 정본 위치 | 책임 |
| --- | --- | --- |
| 예제별 README | `Part*_Chapter*/ExampleName/README.md` | 예제 목적, 핵심 개념, 빌드/실행 요약, 대표 결과, 한계 |
| Part별 예제 지도 | `Part*_Chapter*/README.md` 또는 `Docs/00_Index/study-map.md` | 예제 목록과 대표 예제 안내 |
| Topic 문서 | `Docs/02_Topics/` | 여러 예제를 관통하는 graphics concept 설명 |
| Verification | `Docs/03_Verification/` | build/run/capture 상태와 known issue |
| Demo 계획/evidence | `Docs/04_Demos/`, `Docs/_assets/` | capture/video 후보, 파일명, evidence 연결 |
| WorkLog | `Docs/05_WorkLogs/` | 작업 경위, source review 요약, follow-up |
| Publication 판단 | `Docs/06_Publication/` | public 후보, private-only, 제외, 검토 필요 상태 |
| 상세 local review | `local/` | raw/current/origin 비교, source comment inventory, 임시 초안 |

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

## 이관 절차

1. 대상 예제를 하나 선택한다.
2. current code, raw/reference, origin, 기존 Docs를 확인한다.
3. public-facing README에 필요한 내용과 내부 검토 기록을 분리한다.
4. 예제 README를 코드 폴더 아래로 작성한다.
5. `Docs/01_Examples`의 해당 예제 문서는 제거하거나 전환기 redirect로 축소한다.
6. `status.md` 내용은 `Docs/03_Verification`에 흡수한다.
7. source review 요약은 `Docs/05_WorkLogs`에 남기고, 상세 inventory는 `local/`로 내린다.
8. Topic, Verification, Demo, Publication, Index 링크를 새 README 위치로 갱신한다.
9. 링크와 validator를 확인한다.
10. 사용자 검토 후 커밋 여부를 결정한다.

## Pilot 순서

1. `Part1_Chapter01-02/02_Bloom`
2. `Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment`
3. Part1 나머지 예제 목록 정리
4. Part2 이후 Work Unit으로 확장

## 02_Bloom 적용 계획

- `Docs/01_Examples/Part1_Chapter01-02/02_Bloom/README.md`의 public-safe 내용만 `Part1_Chapter01-02/02_Bloom/README.md`로 옮긴다.
- `source 기준 조사`, `source comment inventory`, `기존 Docs stale 판단`은 README에서 제거한다.
- `Docs/01_Examples/Part1_Chapter01-02/02_Bloom/status.md`는 코드 폴더로 옮기지 않는다.
- build/run/capture 상태는 `Docs/03_Verification/Part1_Chapter01-02/verification-index.md`에 유지한다.
- demo 계획은 `Docs/04_Demos/Part1_Chapter01-02/demo-index.md`에 유지한다.
- publication 상태는 `Docs/06_Publication/candidate-list.md`에서 `검토 필요`로 유지한다.

## Done 기준

- 코드 폴더 README가 public-safe 문서로 존재한다.
- `Docs/01_Examples`에 같은 예제 설명 본문이 중복으로 남지 않는다.
- 관련 Topic, Verification, Demo, WorkLog, Publication 링크가 새 위치를 가리킨다.
- 내부 검토 내용이 README에 노출되지 않는다.
- 직접 확인하지 않은 build/run/capture는 `미확인`으로 유지된다.
- `git diff --check`와 tracked validator를 통과한다.
