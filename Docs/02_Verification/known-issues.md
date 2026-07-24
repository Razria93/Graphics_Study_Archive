# Known Issues

이 문서는 build/run/capture 검증 중 발견한 실패, 보류, 미확인 사유를 모은다.

## 현재 상태

`02_Bloom`은 Debug/Release x64 build/run을 확인했다. 그 외 예제는 아직 직접 build/run 검증을 수행하지 않았으므로 `미확인` 상태다.

## Issue 목록

| ID | 범위 | 상태 | 내용 | 다음 조치 |
| --- | --- | --- | --- | --- |
| VI-001 | Part4_Chapter14-20 | 미확인 | `Examples.sln` 단일 solution과 실행 argument 방식 확인 필요 | Part4 구조 확인 시 갱신 |
| VI-002 | Portfolio_RayTracer | 미확인 | solution 또는 실행 진입점 확인 필요 | 프로젝트 구조 확인 시 갱신 |
| VI-003 | Part1_Chapter01-02/02_Bloom | 관찰됨 | Debug/Release x64 build는 성공했지만 MSBuild 출력 끝에 `pwsh.exe`를 찾을 수 없다는 경고가 표시됨. 프로젝트 파일 내부의 명시적 post-build 명령에서는 원인을 찾지 못함 | 반복 발생 여부 확인. build/run 성공 상태는 유지 |
| VI-004 | Part1_Chapter01-02/02_Bloom | 보류 | 실행 결과 `result.png`는 생성됐지만 이미지에 강의/출처 표기가 포함되어 tracked/public evidence 승격은 보류함 | 공개용 evidence는 별도 캡처 또는 재구성 필요 |

## 기록 기준

- 실패 또는 부분 성공 상태는 삭제하지 않고 원인과 follow-up을 남긴다.
- 해결된 항목은 제거하지 않고 해결 상태와 관련 WorkLog를 연결한다.
- 개인 환경 문제는 필요한 범위만 요약하고 민감 정보는 local에 둔다.
