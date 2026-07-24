# Canonical Docs Policy

이 문서는 Graphics Study Archive의 문서 정본 위치와 책임 경계를 정의한다.

## 원칙

- 같은 내용을 여러 위치에 본문으로 복제하지 않는다.
- 예제별 README 정본은 코드 폴더 아래에 둔다.
- `Docs/01_Examples`는 전환기 경로이며 장기적으로 폐기한다.
- Topic, Verification, Demo, WorkLog, Publication은 각자 다른 책임을 가진다.
- 기존 `Docs/99_Legacy/PartDocs`와 초기 tracked Docs는 stale 검토 전까지 참고자료로만 사용한다.
- raw/reference 문서는 필요한 범위만 읽고 직접 이해한 설명으로 재작성한다.
- 직접 확인하지 않은 build/run/capture 상태는 `미확인`으로 둔다.

## 신뢰도 기준

| 자료 | 신뢰도 | 사용 방식 |
| --- | --- | --- |
| 현재 루트 코드 폴더 | 높음 | 실제 archive 상태와 구현 확인 기준 |
| raw/reference code/docs | 높음 | 작성 의도와 학습 흔적 확인 기준 |
| origin 또는 원본 예제 기준 | 높음 | 사용자가 채운 구현과 차이 확인 기준 |
| 직접 build/run/capture 결과 | 높음 | Verification과 Demo 상태 판단 기준 |
| `Docs/99_Legacy/PartDocs` | 낮음 | stale 검토 전까지 참고자료 |
| 기존 tracked Docs | 낮음 | current code와 비교 후 재작성 후보 |
| local draft와 개인 메모 | 낮음 | tracked Docs로 직접 승격 금지 |

## 정본 위치

| 산출물 | 위치 | 책임 |
| --- | --- | --- |
| 전체 진입점과 map | `Docs/00_Index/` | 산출물 위치와 작업 흐름 안내 |
| 예제별 README | `Part*_Chapter*/ExampleName/README.md` | 예제 목적, 핵심 개념, 코드 위치, 실행 요약 |
| Part별 예제 지도 | `Part*_Chapter*/README.md`, `Docs/00_Index/study-map.md` | 예제 목록과 대표 예제 안내 |
| graphics 개념 | `Docs/02_Topics/` | 여러 예제를 관통하는 Topic 설명 |
| build/run/capture 검증 | `Docs/03_Verification/` | 검증 상태와 known issue |
| demo 계획과 evidence 설명 | `Docs/04_Demos/`, `Docs/_assets/` | capture/video 후보와 시연 포인트 |
| 작업 마감 요약 | `Docs/05_WorkLogs/` | Work Unit 요약과 follow-up |
| 조사 판단 요약 | `Docs/05_WorkLogs/reviews/` | local 상세 조사에서 재사용 가능한 결론과 승격/제외 분류 요약 |
| public subset 판단 | `Docs/06_Publication/` | 공개 후보, 제외, redaction 기준 |
| 반복 적용 정책 | `Docs/07_Policies/` | repo 운영과 문서 작성 규칙 |
| 도구와 템플릿 | `Docs/98_Tools/` | validator, template, troubleshooting |
| 과거 기록 | `Docs/99_Legacy/` | import 기록과 이전 문서 구조 |

## 작성 기준

- 문서는 한국어 평서형으로 작성한다.
- 예제 README에는 public-facing 설명만 둔다.
- raw/reference, origin, current code 비교와 source comment inventory는 README에 노출하지 않는다.
- 상세 source comment inventory와 raw/current/origin 비교 원문은 `local/study-review/`에 둔다.
- tracked review summary에는 승격한 항목, 승격하지 않은 항목의 분류, 후속 판단 기준만 남긴다.
- build/run/capture 상태는 `Docs/03_Verification`에 기록한다.
- 공개 가능성 판단은 `Docs/06_Publication`에서 분리한다.
