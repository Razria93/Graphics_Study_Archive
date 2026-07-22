# Verification Map

이 문서는 build/run/capture/known issue 기록의 정본 위치를 안내한다.

## 정본 위치

| 항목 | 위치 | 책임 |
| --- | --- | --- |
| 전체 build/run matrix | `Docs/03_Verification/build-run-matrix.md` | Part/Chapter별 Debug x64, Release x64, 실행 상태 |
| 예제별 검증 기록 | `Docs/03_Verification/<Part*>/` | 예제 단위 실행 조건, asset path, known issue |
| capture 상태 | `Docs/04_Demos` | demo evidence와 연결 |
| Work Unit 검증 요약 | `Docs/05_WorkLogs` | 이번 작업에서 확인한 검증 결과 요약 |

## 상태값

| 상태 | 의미 |
| --- | --- |
| `미확인` | 아직 직접 빌드/실행하지 않음 |
| `성공` | 직접 빌드 또는 실행 확인 완료 |
| `실패` | 실패를 직접 확인했고 원인을 기록함 |
| `부분 성공` | 실행은 가능하나 known issue가 남음 |
| `제외` | 검증 대상에서 의도적으로 제외함 |

## 기록 기준

- Debug x64를 기본 검증 기준으로 둔다.
- 대표 예제는 필요하면 Release x64도 확인한다.
- 실패 상태는 숨기지 않고 known issue로 남긴다.
- 문서만 작성한 경우 검증 상태를 성공으로 바꾸지 않는다.
