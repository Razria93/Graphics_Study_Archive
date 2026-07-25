# Verification Map

이 문서는 build/run/capture/known issue 기록의 정본 위치를 안내한다. 상태값의 의미와 검증 작성 기준은 `Docs/06_Policies/verification-policy.md`를 따른다.

## 정본 위치

| 항목 | 위치 | 책임 |
| --- | --- | --- |
| 전체 build/run matrix | `Docs/02_Verification/build-run-matrix.md` | Part/Chapter별 Debug x64, Release x64, 실행 상태 |
| capture matrix | `Docs/02_Verification/capture-matrix.md` | build/run과 연결된 capture/result 상태 요약 |
| known issue | `Docs/02_Verification/known-issues.md` | 실패, 보류, 미확인 사유 기록 |
| 예제별 검증 기록 | `Docs/02_Verification/<Part*>/` | 예제 단위 실행 조건, asset path, known issue |
| Demo capture/result | `Docs/03_Demos` | capture/result의 정리와 우선순위 |
| Work Unit 검증 요약 | `Docs/04_WorkLogs` | 이번 작업에서 확인한 검증 결과 요약 |

## 운영 기준

- 이 문서는 검증 상태판이 아니라 검증 정본 위치를 안내하는 map이다.
- build/run 상태값은 `Docs/06_Policies/verification-policy.md`를 따른다.
- capture/result 상태값은 `Docs/06_Policies/demo-capture-policy.md`와 `Docs/02_Verification/capture-matrix.md`를 기준으로 확인한다.
- Debug x64를 기본 검증 기준으로 둔다.
- 대표 예제는 필요하면 Release x64도 확인한다.
- 실패 상태는 숨기지 않고 known issue로 남긴다.
- 문서만 작성한 경우 검증 상태를 성공으로 바꾸지 않는다.
