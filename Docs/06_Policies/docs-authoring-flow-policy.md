# Docs Authoring Flow Policy

이 문서는 산출물 축 구조에서 문서를 작성하는 순서를 정의한다. 전체 Work Unit 흐름은 `work-unit-workflow-policy.md`를 기준으로 한다.

## Source 기준

문서 작성 시 기존 tracked Docs는 참고자료로만 사용한다. 신뢰 기준은 다음 순서로 둔다.

1. 현재 루트 코드 폴더의 current code와 주석
2. raw/reference repo의 관련 code/docs
3. origin 기준 또는 `OriginalExamples` 기준 코드
4. 직접 수행한 build/run/capture 결과
5. `Docs/99_Legacy/PartDocs`와 기존 tracked Docs

기존 Docs 설명이 code, raw/reference, origin 기준, 직접 검증 결과와 충돌하면 기존 Docs를 정본으로 보지 않는다. Source 신뢰도 기준은 `canonical-docs-policy.md`를 따른다. tracked Docs에는 raw/reference 원문을 복사하지 않고 직접 이해한 설명으로 재작성한다.

## 용어 기준

이 문서에서 `origin 또는 원본 예제 기준`은 Git remote `origin`만 뜻하지 않는다. 비교 기준은 다음 중 작업자가 실제로 확인 가능한 기준점을 말한다.

- `OriginalExamples/`의 수정 전 예제
- raw/reference repo의 원본성 코드
- Git 원격 또는 이전 커밋에 남아 있는 기준 코드

어떤 기준점을 사용했는지는 `local/study-review`와 WorkLog에 명시한다. 기준점을 확인하지 못하면 `미확인`으로 둔다.

## Markdown 원문 가독성

- 일반 문단은 문단당 하나의 물리적 줄로 작성하고 특정 글자 수 상한을 두지 않는다. 문장이 길면 수동 개행 대신 문장 자체를 나눌지 판단한다.
- GitHub public body의 화면 줄바꿈은 브라우저의 자연스러운 wrapping에 맡긴다.
- 일반 문장의 단계·숫자·날짜 범위는 en dash(`–`)로 표기한다. 한 줄에 단일 `~` 범위가 둘 이상 있으면 GitHub가 사이 내용을 의도하지 않은 취소선으로 해석할 수 있다.
- heading, 빈 줄, 서로 다른 목록 항목, 인용문, 표, fenced code block처럼 Markdown 구조에 필요한 개행은 유지한다.
- Markdown 링크와 뒤따르는 조사·서술어는 같은 물리 줄에 둔다.
- 하나의 목록 항목은 의미상 한 항목이면 한 물리적 줄로 유지한다.
- 목록의 `코드:`, `관련 코드:`, `Shader:` 같은 포괄적 label을 별도 줄에 두지 않고, 링크 label에서 확인할 구현 역할을 설명한다.
- 상세 Demo의 source line 코드 근거 bullet은 구현 대상과 역할을 나타내는 명사형 link label을 사용한다. `확인한다`, `살펴본다`, `참조한다`, `비교한다`, `확인할 수 있다` 같은 행동·서술 종결형 label과 bullet 끝 마침표는 사용하지 않는다.
- 의사코드와 code block은 뷰포트 가독성을 위해 한 줄 80자 내외를 권장하고 120자를 상한으로 둔다.
- 일반 본문은 line-length validator 대상으로 삼지 않는다. 같은 문단·목록 항목의 연속 물리 줄처럼 구조적으로 확실한 인위적 soft-wrap은 validator로 검사하고, 문장 흐름과 렌더링 가독성처럼 문맥 판단이 필요한 항목은 agent 또는 수동 검수에서 확인한다.
- 공개 문서의 table, 목록과 visual은 source 구조 검사와 실제 GitHub UI 표본 검수를 구분한다. 반복 가능한 구조 결함은 validator로 환류하고 렌더링 절차는 [Validation Tools](../98_Tools/validation-tools.md)를 따른다.
- 의미와 문단 구조를 바꾸는 자동 reflow는 사용하지 않는다.

## 작성 순서

1. 대상 Part/Chapter/Example 범위를 확정한다.
2. 현재 코드 구조와 실행 진입점, shader, asset path를 확인한다.
3. 관련 소스 주석을 전수조사하고 `local/study-review`에 inventory를 둔다. inventory에는 파일/위치/분류/처리 판단을 기록하고, 주석 원문 전체를 무조건 보관하지 않는다.
4. raw/reference code/docs와 origin 또는 원본 예제 기준 코드를 확인한다.
5. current/raw/origin 차이를 조사하고 사용자가 채운 구현 후보와 원본 유지 코드를 구분한다.
6. 챕터 목표, 핵심 개념, 핵심 코드, 결과물 후보, 학습 고민 흔적을 추출한다.
7. 코드 주석은 사용자 검토 가능한 후보를 만든 뒤 선별 정리한다.
8. 예제 README는 대상 코드 폴더 아래에 작성한다.
9. 연결 Topic은 `Docs/01_Topics`에 작성하거나 갱신한다.
10. build/run/capture 상태는 `Docs/02_Verification`에 기록한다.
11. 검증 단계에서 screenshot, video, result image가 필요한지 판단하고, 필요하면 사용자에게 촬영 또는 생성 조건을 구체적으로 요청한다.
12. Demo capture/result와 시연 포인트는 `Docs/03_Demos`에 기록한다.
13. 검토 완료된 대표 capture/result는 코드 폴더 README에 최대 1개 연결하고, 전후 비교와 다중 시각 자료는 상세 Demo에 세로 배치한다.
14. public subset 판단은 `Docs/05_Publication`에 기록한다.
15. 작업 과정과 마감 요약은 `Docs/04_WorkLogs`에 기록한다.
16. 전체 map은 `Docs/00_Index`에서 필요한 범위만 갱신한다.
17. Root, Chapter, Example, Docs, Folder README 중 갱신이 필요한 문서가 있는지 `canonical-docs-policy.md`의 README 갱신 기준으로 확인한다.
18. 사용자 검토 요청 전 문체, 링크, 중복, 금지 요소, `미확인` 표기를 검수한다.
19. 사용자 검토 요청 후 commit readiness를 보고한다.

## current/raw/origin 비교 최소 범위

| 항목 | 확인 기준 |
| --- | --- |
| source/header | 사용자가 채운 구현, 변경된 수식, resource lifetime, 주요 data flow 확인 |
| shader | stage, input/output semantic, constant/resource binding, sampling 방식 확인 |
| project file | solution, project, include/lib path, working directory 영향 확인 |
| asset path | texture, model, shader, runtime file lookup 경로 확인 |
| 결과물 후보 | screenshot/video로 보여줄 수 있는 상태인지 확인 |
| 기존 Docs | 코드와 설명이 충돌하는지 확인 |

## capture/result 요청 기준

예제 문서화 중 build/run 확인 단계에 들어가면 capture/result 필요 여부를 함께 판단한다. 필요하다고 판단한 경우 사용자가 바로 실행할 수 있도록 다음 조건을 명시해 요청한다.

- screenshot, video, result image 중 필요한 유형
- 찍어야 할 화면, 입력 장면, 결과 파일
- before/after 또는 input/result 비교 필요 여부
- 강의명, 강사명, 워터마크, 개인 식별자, 계정, 로컬 경로를 피해야 한다는 조건
- README에 연결할 대표 자료인지, local 검토 후보인지

검토 완료된 screenshot 또는 result image는 코드 폴더 README에 대표 자료를 최대 1개 연결한다. 전후 비교와 다중 시각 자료는 상세 Demo에 둔다. capture/result가 필요 없으면 `Docs/03_Demos`와 `Docs/02_Verification`에 `제외` 사유를 남긴다.

## README 갱신 확인 기준

문서 작성 또는 검증 결과가 생겼다고 모든 README를 수정하지 않는다. 각 README는 계층별 책임이 다르므로 아래 기준으로 필요한 문서만 갱신한다.

- Root README는 대표 pilot/result 또는 전체 Study Map이 바뀐 경우에만 갱신한다.
- Chapter README는 Chapter 범위의 예제 목록, 대표 결과, Topic/Verification/Demo 링크가 바뀌면 갱신한다.
- Example README는 해당 예제의 설명, 핵심 코드 위치, capture/result, limitation이 바뀌면 갱신한다.
- Docs와 Folder README는 폴더 책임, 하위 문서, 정책 링크가 바뀐 경우에만 갱신한다.
- GitHub body는 README 내용을 복제하지 않고 게시 시점의 요약과 링크만 갱신한다.

README에 넣지 않는 내부 조사 기록은 `local/study-review/` 또는 `Docs/04_WorkLogs/reviews/`로 분리한다.

## source comment inventory 범위

source comment inventory는 repo 전체 주석 조사가 아니다. 대상 Work Unit에 직접 관련된 파일만 확인한다.

기본 범위:

- 대상 예제의 source/header
- 대상 예제의 shader
- solution/project/include/lib path에 영향을 주는 project file
- texture, model, shader, runtime file lookup에 영향을 주는 asset path 관련 파일
- 사용자가 채운 구현 후보와 직접 연결되는 코드

제외 기준:

- 대상 예제와 직접 관련 없는 Part/Chapter 전체 주석
- Legacy 문서 전체 문장 검토
- raw/reference repo 전체 주석 조사
- build output, generated file, IDE cache

## 주석 정리 기준

소스 주석은 전체 삭제하지 않는다. 먼저 전수조사하고 다음 기준으로 분류한다.

| 분류 | 처리 |
| --- | --- |
| 구현 의도 | 코드에 짧게 유지하거나 더 간결하게 정리 |
| 학습 고민 흔적 | Example, Topic, WorkLog, local study review로 이관 |
| 강의 원문성 설명 | tracked Docs로 복사하지 않고 직접 재작성 |
| 임시 메모, 중복 설명, 오래된 흔적 | 제거 후보로 표시 |
| 민감 정보, 개인 메모, 공개 위험 정보 | tracked Docs로 승격 금지 |

코드에 남기는 주석은 구현 의도, 비자명한 수식, resource lifetime, shader/asset path처럼 유지보수에 필요한 짧은 설명으로 제한한다.

source comment inventory는 tracked Docs가 아니라 local-only 검토 자료다. tracked Docs에는 주석 원문을 길게 옮기지 않고, 사용자가 무엇을 이해했는지와 어떤 구현 판단을 했는지만 재작성한다.


## 내부 조사 기록 분리 기준

README에서 제외한 내부 조사 내용은 두 단계로 분리한다.

| 내용 | 위치 | 기준 |
| --- | --- | --- |
| current/raw/origin 비교 상세 | `local/study-review/` | 원문성, 경로, 민감 판단, 상세 비교표를 포함할 수 있다. |
| source comment inventory 상세 | `local/study-review/` | 주석 원문과 학습 흔적은 tracked Docs로 직접 옮기지 않는다. |
| 기존 Docs stale 판단 상세 | `local/study-review/` | 내부 판단 근거와 폐기 이유를 보관한다. |
| 승격/제외 판단 요약 | `Docs/04_WorkLogs/reviews/` | 다음 작업자가 반복 조사하지 않아도 되는 결론만 남긴다. |
| Work Unit 마감 요약 | `Docs/04_WorkLogs/` | 작업 범위, 산출물, follow-up을 요약한다. |

tracked review summary에는 상세 조사 원문을 복사하지 않는다. 남기는 내용은 검토 범위, README/Topic/Verification/Demo로 승격한 항목, 승격하지 않은 항목의 분류, 후속 known issue, 반복 적용할 판단 기준으로 제한한다.

tracked Docs에서 `local/` 파일로 직접 링크하지 않는다. local 문서에서 tracked 문서로 연결하는 것은 허용한다.
## 작성 위치 결정 규칙

| 내용 | 작성 위치 |
| --- | --- |
| 예제 하나가 무엇을 보여주는지 | 대상 코드 폴더 `README.md` |
| 여러 예제를 관통하는 graphics 개념 | `Docs/01_Topics` |
| build/run/capture 상태 | `Docs/02_Verification` |
| 구현 선택, capture/result 비교, 결과 해석, limitation | `Docs/03_Demos` |
| public 후보와 제외 판단 | `Docs/05_Publication` |
| 작업 과정과 리뷰 대응 요약 | `Docs/04_WorkLogs` |
| 정리된 조사 판단 요약 | `Docs/04_WorkLogs/reviews` |
| 상세 조사 원문과 민감 판단 | `local/study-review` |
| 반복 적용 규칙 | `Docs/06_Policies` |
| 도구와 템플릿 | `Docs/98_Tools` |
| 과거 구조와 import 기록 | `Docs/99_Legacy` |

## Part1 Pilot 재검수 기준

초기 Part1 pilot 문서는 산출물 축 구조를 검증하기 위한 초안으로 본다. 정식 Work Unit 완료로 보려면 대표 예제별로 source comment inventory, current/raw/origin 비교, 직접 검증 상태를 다시 확인한다. 기존 pilot 문서를 그대로 확장하지 않고, 이 정책의 작성 순서를 따라 필요한 문서만 보강한다.

## Docs/01_Examples 폐기 기준

- Docs/01_Examples는 폐기된 예전 경로이며 예제 설명 정본 위치가 아니다.
- 기존 Docs/01_Examples 문서는 코드 폴더 README로 이관했거나 폐기 기록으로만 남긴다.
- 새 redirect 또는 링크 허브를 추가하지 않는다.
- status.md는 코드 폴더로 옮기지 않고 Docs/02_Verification으로 흡수한다.
- Docs/01_Examples는 제거된 경로로 취급한다.

## 금지사항

- 새 예제 설명을 `Docs/99_Legacy/PartDocs`나 `Docs/01_Examples` 본문으로 추가하지 않는다.
- 검증 상세를 예제 문서에 길게 복사하지 않는다.
- demo 파일 원본을 검토 없이 tracked Docs에 추가하지 않는다.
- GitHub draft 원문을 tracked Docs에 두지 않는다.
- tracked Docs에서 `local/` 파일로 직접 링크하지 않는다.
- 정책 원문을 각 산출물 폴더 README에 반복하지 않는다.
- existing Docs만 근거로 새 정본 문서를 확정하지 않는다.
- raw/reference 또는 origin 문서 표현을 tracked Docs에 그대로 옮기지 않는다.
- source 주석을 전수조사 없이 일괄 삭제하지 않는다.
