# Canonical Docs Policy

이 문서는 Graphics Study Archive의 문서 정본 위치와 책임 경계를 정의한다.

## 원칙

- 문서 정본은 산출물 축 폴더에 둔다.
- 같은 내용을 여러 위치에 원문 복사하지 않는다.
- 상세 본문은 정본 위치에 두고 다른 문서에는 링크와 상태만 둔다.
- 기존 `Docs/99_Legacy/PartDocs` 문서는 전환기 참고 자료로만 읽는다.
- `local-only 자료 영역`의 원문 메모는 tracked Docs로 그대로 옮기지 않는다.
- 반복 용어는 `terminology-policy.md`의 표준 용어를 따른다.
- 현재 코드, raw/reference, origin 또는 원본 예제 기준, 직접 검증 결과를 기존 Docs보다 우선한다.

## 신뢰도 기준

| 자료 | 신뢰도 | 사용 방식 |
| --- | --- | --- |
| 현재 루트 코드 폴더 | 높음 | 실제 archive 상태와 구현 확인 기준 |
| raw/reference code/docs | 높음 | 작성 의도와 원본 맥락 확인 기준 |
| origin 또는 원본 예제 기준 | 높음 | 사용자가 채운 구현과 차이 확인 기준 |
| 직접 build/run/capture 결과 | 높음 | Verification과 Demo 상태 판단 기준 |
| `Docs/99_Legacy/PartDocs` | 낮음 | stale 검토 전까지 참고자료이며 정본 후보가 아님 |
| 기존 tracked Docs | 낮음 | stale 검토 전까지 참고자료이며 정본 후보가 아님 |
| local draft와 개인 메모 | 낮음 | tracked Docs로 그대로 승격 금지 |

기존 Docs와 현재 코드가 충돌하면 현재 코드를 우선한다. 기존 Docs와 직접 검증 결과가 충돌하면 직접 검증 결과를 우선한다.

## 정본 위치

| 산출물 | 위치 | 책임 |
| --- | --- | --- |
| 전체 진입점과 map | `Docs/00_Index/` | 산출물 위치와 작업 흐름 안내 |
| 예제 설명 | `Docs/01_Examples/` | 예제 목적, 코드 위치, 관련 문서 링크 |
| graphics 개념 | `Docs/02_Topics/` | 여러 예제를 관통하는 Topic 설명 |
| build/run/capture 검증 | `Docs/03_Verification/` | 검증 상태와 known issue |
| demo 계획과 evidence 설명 | `Docs/04_Demos/` | capture/video 후보와 시연 포인트 |
| 작업 마감 요약 | `Docs/05_WorkLogs/` | Work Unit 요약과 follow-up |
| public subset 판단 | `Docs/06_Publication/` | 공개 후보, 제외, redaction 기준 |
| 반복 적용 정책 | `Docs/07_Policies/` | repo 운영과 문서 작성 규칙 |
| 도구와 템플릿 | `Docs/98_Tools/` | validator, template, troubleshooting |
| 과거 기록 | `Docs/99_Legacy/` | import 기록과 이전 문서 구조 |

## 작성 기준

- 평서형 현재형을 사용한다.
- 존댓말, 대화체, 감상문체를 사용하지 않는다.
- raw/reference 문서는 필요한 범위만 읽고 직접 이해한 설명으로 재작성한다.
- raw/reference, origin, existing Docs를 비교한 여부를 Example, Topic, WorkLog 중 적절한 위치에 남긴다.
- source comment inventory의 원문은 `local/study-review`에 두고, tracked Docs에는 분류 결과와 이관 여부만 요약한다.
- 직접 확인하지 않은 build/run/capture 상태는 `미확인`으로 기록한다.
- 공개 가능성 판단은 `Docs/06_Publication` 기준으로 분리한다.
