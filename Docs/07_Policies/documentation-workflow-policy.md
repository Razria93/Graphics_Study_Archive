# Documentation Workflow Policy

이 문서는 Part 또는 Chapter를 방식 1 구조로 정리하는 순서를 정의한다.

## 작업 순서

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

## 금지사항

- 새 예제 설명을 `Docs/99_Legacy/PartDocs`에 추가하지 않는다.
- 검증 상세를 예제 문서에 길게 복사하지 않는다.
- demo 파일 원본을 검토 없이 tracked Docs에 추가하지 않는다.
- GitHub draft 원문을 tracked Docs에 두지 않는다.