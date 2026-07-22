# Documentation Workflow Policy

이 문서는 산출물 축 구조에서 문서 작성 순서를 정의한다. 전체 Work Unit 흐름은 `work-unit-workflow-policy.md`를 기준으로 한다.

## 작성 순서

1. root 코드 폴더를 확인한다.
2. `Docs/99_Legacy/PartDocs`의 기존 문서를 참고 자료로 읽는다.
3. raw/reference mapping은 필요한 범위만 읽는다.
4. 예제 설명은 `Docs/01_Examples`에 작성한다.
5. 연결 개념은 `Docs/02_Topics`에 작성하거나 갱신한다.
6. build/run/capture 상태는 `Docs/03_Verification`에 기록한다.
7. demo evidence와 시연 포인트는 `Docs/04_Demos`에 기록한다.
8. Issue/PR 작업 과정과 마감 기록은 `Docs/05_WorkLogs`에 기록한다.
9. public subset 판단은 `Docs/06_Publication`에 기록한다.
10. 전체 map은 `Docs/00_Index`에서 갱신한다.

## 작성 위치 결정 규칙

| 내용 | 작성 위치 |
| --- | --- |
| 예제 하나가 무엇을 보여주는지 | `Docs/01_Examples` |
| 여러 예제를 관통하는 개념 | `Docs/02_Topics` |
| 빌드와 실행 상태 | `Docs/03_Verification` |
| 캡처와 영상 evidence | `Docs/04_Demos` |
| 작업 과정과 리뷰 대응 | `Docs/05_WorkLogs` |
| 공개 가능성 판단 | `Docs/06_Publication` |
| 반복 적용되는 규칙 | `Docs/07_Policies` |
| 도구와 템플릿 | `Docs/98_Tools` |
| 과거 구조와 import 기록 | `Docs/99_Legacy` |

## 금지사항

- 새 예제 설명을 `Docs/99_Legacy/PartDocs`에 추가하지 않는다.
- 검증 상세를 예제 문서에 길게 복사하지 않는다.
- demo 파일 원본을 검토 없이 tracked Docs에 추가하지 않는다.
- GitHub draft 원문을 tracked Docs에 두지 않는다.
- 정책 원문을 각 산출물 폴더 README에 반복하지 않는다.
