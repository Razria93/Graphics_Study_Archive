# Canonical Docs Policy

이 문서는 Graphics Study Archive의 문서 정본 위치와 책임 경계를 정의한다.

## 원칙

- 같은 내용을 여러 위치에 본문으로 복제하지 않는다.
- Root README는 내부 운영표가 아니라 부분 공개 가능한 portfolio archive의 첫 화면으로 작성한다.
- 예제별 README 정본은 코드 폴더 아래에 둔다.
- `Docs/01_Examples`는 폐기된 예전 경로이며 정본으로 사용하지 않는다.
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
| Root README | `README.md` | repository의 목적, 대표 graphics 주제, 현재 pilot/result, 주요 문서 진입점 안내 |
| 전체 진입점과 map | `Docs/00_Index/` | 산출물 위치와 작업 흐름 안내 |
| Chapter README | `Part*_Chapter*/README.md` | Chapter 또는 Chapter 묶음의 목표, 예제 구성, 대표 Topic, Demo, Verification 링크 |
| 예제별 README | `Part*_Chapter*/ExampleName/README.md` | 예제 목적, 핵심 개념, 코드 위치, 실행 요약 |
| Part별 예제 지도 | `Part*_Chapter*/README.md`, `Docs/00_Index/study-map.md` | 예제 목록과 대표 예제 안내 |
| graphics 개념 | `Docs/01_Topics/` | 여러 예제를 관통하는 Topic 설명 |
| build/run/capture 검증 | `Docs/02_Verification/` | 검증 상태와 known issue |
| demo 계획과 capture/result 설명 | `Docs/03_Demos/`, `Docs/_assets/` | capture/result 후보와 시연 포인트 |
| 작업 마감 요약 | `Docs/04_WorkLogs/` | Work Unit 요약과 follow-up |
| 조사 판단 요약 | `Docs/04_WorkLogs/reviews/` | local 상세 조사에서 재사용 가능한 결론과 승격/제외 분류 요약 |
| public subset 판단 | `Docs/05_Publication/` | 공개 후보, 제외, redaction 기준 |
| 반복 적용 정책 | `Docs/06_Policies/` | repo 운영과 문서 작성 규칙 |
| GitHub 게시 후보 | `Docs/07_GitHub/` | Issue, PR, comment body의 게시 후보 정본 |
| 도구와 템플릿 | `Docs/98_Tools/` | validator, template, troubleshooting |
| 과거 기록 | `Docs/99_Legacy/` | import 기록과 이전 문서 구조 |

## 문서 위계

외부 독자와 신규 agent는 아래 순서로 문서를 읽는다.

```text
Root README / BUILD / TOPICS / DEMOS
-> Chapter README
-> Example README
-> Topic / Verification / Demo / Publication
-> GitHub PR body
```

Chapter README는 해당 Chapter 또는 Chapter 묶음의 지도 역할을 한다. 본문 설명을 길게 반복하지 않고 목표, 예제 구성, 핵심 Topic, 대표 Demo, 검증 상태, 관련 문서 링크를 제공한다.

Example README는 예제 하나의 설명 정본이다. 목적, 구현 흐름, 핵심 코드, build/run 요약, capture/result, limitation을 둔다.

GitHub PR body는 README의 미러가 아니다. 게시 시점에 reviewer가 볼 요약과 링크만 제공하고, 최신 상태 정본은 README, Topic, Verification, Demo, Publication 문서에 둔다.

## Root README 기준

Root README는 private archive 내부 운영 문서처럼 작성하지 않는다. 이 저장소가 부분적으로 공개될 수 있는 portfolio archive라는 점을 전제로, 처음 보는 독자가 아래 내용을 빠르게 파악하도록 구성한다.

- 이 저장소가 보여주는 graphics study/portfolio 범위
- 대표 Topic과 Part/Chapter 흐름
- 현재 검증된 pilot 또는 대표 visual result
- build, topic, demo, documentation으로 들어가는 짧은 링크
- private archive와 public subset 분리 원칙

정책, stale 문서, legacy import 기록, validator 세부 규칙은 Root README 상단에 길게 두지 않는다. 필요한 경우 하단의 maintainer notes나 `Docs/README.md`, `Docs/06_Policies` 링크로 넘긴다.

## README 계층별 책임

README는 위치에 따라 다른 책임을 가진다. 같은 내용을 여러 README에 본문으로 반복하지 않고, 상위 README는 하위 문서로 들어가는 짧은 안내와 대표 링크만 제공한다.

| README | 책임 | 포함 기준 | 제외 기준 |
| --- | --- | --- | --- |
| Root README | portfolio archive의 첫 화면 | repository 목적, 대표 graphics 주제, 현재 pilot/result, 주요 guide 링크 | 내부 조사 기록, stale 판단, raw/origin 비교, 정책 원문 |
| Chapter README | Chapter 또는 Chapter 묶음의 지도 | Chapter 목표, 예제 목록, 대표 Topic/Demo/Verification, 상태 요약 | 예제별 코드 상세, Topic 본문 전체, WorkLog 상세 |
| Example README | 예제 하나의 설명 정본 | 예제 목적, 핵심 개념, 핵심 코드 위치, 실행 요약, capture/result, limitation | raw/reference 원문, source comment inventory, stale 판단 상세 |
| Docs README | Docs 산출물 축의 입구 | 폴더 구조, 각 축의 책임, 먼저 볼 문서 | 세부 정책 원문, 예제별 상세 설명 |
| Folder README | 해당 폴더의 하위 안내 | 하위 문서 목록, 작성 위치, 관련 정책 링크 | 다른 폴더 책임의 본문 반복 |
| GitHub body | review/posting용 요약 | 게시 시점의 요약, 핵심 링크, 검증 요약 | README 본문 복제, 내부 draft/metadata |

## README 갱신 기준

README는 무조건 함께 수정하지 않는다. Work Unit 종료 전 아래 기준으로 갱신 필요 여부를 판단하고, 갱신하지 않는 경우 WorkLog 또는 검토 보고에 이유를 남긴다.

| README | 갱신 조건 |
| --- | --- |
| Root README | 대표 pilot/result가 바뀌거나, Study Map 상태가 바뀌거나, archive/public 방향이 바뀔 때 |
| Chapter README | Chapter 예제 목록, 대표 Topic/Demo/Verification 링크, build/run/capture 요약이 바뀔 때 |
| Example README | 예제의 코드 흐름, 핵심 개념, capture/result, limitation, 관련 문서 링크가 바뀔 때 |
| Docs README | Docs 폴더 구조, 산출물 축 책임, 먼저 볼 문서가 바뀔 때 |
| Folder README | 하위 문서 목록, 폴더 책임, template/policy 링크가 바뀔 때 |
| GitHub body | 게시 대상 Issue/PR/comment의 범위, 검증 요약, 연결 링크가 바뀔 때 |

## 작성 기준

- 문서는 한국어 평서형으로 작성한다.
- 예제 README에는 public-facing 설명만 둔다.
- raw/reference, origin, current code 비교와 source comment inventory는 README에 노출하지 않는다.
- 상세 source comment inventory와 raw/current/origin 비교 원문은 `local/study-review/`에 둔다.
- tracked review summary에는 승격한 항목, 승격하지 않은 항목의 분류, 후속 판단 기준만 남긴다.
- build/run/capture 상태는 `Docs/02_Verification`에 기록한다.
- capture/result가 확보된 예제 README에는 대표 screenshot, video link, result image 링크를 포함한다.
- 공개 가능성 판단은 `Docs/05_Publication`에서 분리한다.
