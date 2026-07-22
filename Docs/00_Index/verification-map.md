# Verification Map

이 문서는 build/run/capture/known issue 기록의 정본 위치를 안내한다.

## 정본 위치

| 항목 | 위치 | 책임 |
| --- | --- | --- |
| 전체 build/run matrix | `Docs/03_Verification/build-run-matrix.md` | Part/Chapter별 Debug x64, Release x64, 실행 상태 |
| capture matrix | `Docs/03_Verification/capture-matrix.md` | build/run과 연결된 capture 상태 요약 |
| known issue | `Docs/03_Verification/known-issues.md` | 실패, 보류, 미확인 사유 기록 |
| 예제별 검증 기록 | `Docs/03_Verification/<Part*>/` | 예제 단위 실행 조건, asset path, known issue |
| Demo evidence | `Docs/04_Demos` | capture/video evidence의 정리와 우선순위 |
| Work Unit 검증 요약 | `Docs/05_WorkLogs` | 이번 작업에서 확인한 검증 결과 요약 |

## 상태값

| 상태 | 의미 |
| --- | --- |
| `미확인` | 아직 직접 build/run/capture하지 않음 |
| `성공` | 직접 확인한 성공 상태 |
| `실패` | 직접 확인한 실패 상태 |
| `부분 성공` | 실행 가능하지만 known issue가 남음 |
| `보류` | 의도적으로 확인을 미룸 |
| `제외` | 검증 대상에서 제외함 |

## 기록 기준

- Debug x64를 기본 검증 기준으로 둔다.
- 대표 예제는 필요하면 Release x64도 확인한다.
- 실패 상태는 숨기지 않고 known issue로 남긴다.
- 문서만 작성한 경우 검증 상태를 성공으로 바꾸지 않는다.
