# Workflow Map

이 문서는 Work Unit 진행 시 각 단계에서 참고할 위치와 저장할 위치를 요약한다. 세부 절차와 승인 규칙의 정본은 `Docs/06_Policies`에 둔다.

## 빠른 흐름

```text
루트 코드 폴더 확인
-> Legacy 문서와 raw/reference repo 확인
-> local review 작성
-> 작업 계획 보고
-> 코드 폴더 README 작성/수정
-> 01_Topics 연결
-> 02_Verification 갱신
-> 03_Demos와 _assets 연결
-> 05_Publication 판단
-> 04_WorkLogs 요약
-> 07_GitHub 게시 후보 작성
-> 00_Index 라우팅 갱신
```

## 단계별 위치

| 단계 | 참고 위치 | 저장 위치 |
| --- | --- | --- |
| 코드 확인 | 루트 코드 폴더 | `local/` review 자료 |
| 기존 문서 확인 | `Docs/99_Legacy/PartDocs`, `Docs/99_Legacy/ImportHistory`, raw/reference repo | `local/` review 자료 |
| 계획 보고 | 코드, legacy, raw/reference 검토 결과 | 대화 또는 Work Unit 초안 |
| 예제 설명 | 코드 폴더, local review | 대상 코드 폴더 `README.md` |
| 개념 설명 | 코드 폴더 README, 관련 코드, reference | `Docs/01_Topics` |
| 검증 | solution, executable, assets | `Docs/02_Verification` |
| 데모 | capture/result 후보, 검증 결과 | `Docs/03_Demos`, `Docs/_assets` |
| 공개 판단 | README, Topic, Demo, assets | `Docs/05_Publication` |
| 작업 기록 | 변경된 산출물 전체 | `Docs/04_WorkLogs` |
| GitHub 게시 후보 | WorkLog, Verification, Demo, Publication | `Docs/07_GitHub` |
| 지도 갱신 | 전체 산출물 | `Docs/00_Index` |

## 관련 정책

- [Work Unit Workflow Policy](../06_Policies/work-unit-workflow-policy.md)
- [Docs Authoring Flow Policy](../06_Policies/docs-authoring-flow-policy.md)
- [Structure Cleanup Roadmap](../06_Policies/structure-cleanup-roadmap.md)
- [Verification Policy](../06_Policies/verification-policy.md)
- [Demo Capture Policy](../06_Policies/demo-capture-policy.md)
- [GitHub Workflow Policy](../06_Policies/github-workflow-policy.md)
- [Publication Policy](../06_Policies/publication-policy.md)
- [Terminology Policy](../06_Policies/terminology-policy.md)
