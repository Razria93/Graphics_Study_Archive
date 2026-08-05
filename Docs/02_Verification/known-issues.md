# Known Issues

이 문서는 build/run/capture 검증 중 발견한 실패, 보류, 미확인 사유를 모은다.

## 현재 상태

현재 build/run 결과와 provenance는 `build-run-matrix.md`를 기준으로 한다. 이 문서에는 실패, 보류, 미확인 사유처럼 후속 조치가 필요한 항목만 둔다.

## Issue 목록

| ID | 범위 | 상태 | 내용 | 다음 조치 |
| --- | --- | --- | --- | --- |
| VI-001 | Part4_Chapter14-20 | 문서화 필요 | 과거 build/run 성공과 별개로 `Examples.sln`의 sample 선택 및 실행 argument 절차가 아직 정리되지 않음 | Part4 문서화 시 실행 절차 기록 |
| VI-002 | Portfolio_RayTracer | 미확인 | solution 또는 실행 진입점 확인 필요 | 프로젝트 구조 확인 시 갱신 |
| VI-004 | Part1_Chapter01-02/02_Bloom | 해소 | 기존 입력 이미지의 강의/출처 표기 문제는 ChatGPT 생성 입력 이미지로 교체해 해소함 | result image를 `Docs/_assets/captures`에 승격함. public 판단은 `Docs/05_Publication`에서 처리 |
| VI-005 | Part4_Chapter14-20 | 확인 필요 | Debug x64 build 후 ignored output의 runtime DLL이 정리되어 terminal 실행에서 `PhysXCommon_64.dll` loader error가 발생함 | build output DLL copy 방식 또는 실행 전 runtime DLL 복구 절차를 Part4 build/run 기준에 반영 |
| VI-006 | Part4_Chapter14-20/Ex1402_Blur | 조건부 해소 | 2026-08-06 Debug x64 파일럿 screenshot 후보가 white frame에 가까웠으나, delay sweep에서 5000ms capture가 RGB blur 결과를 확인함 | Ex1402 capture는 5000ms 안정화 대기 기준으로 사용하고 tracked 승격 전 metadata와 visual을 재검수 |

## 기록 기준

- 실패 또는 부분 성공 상태는 삭제하지 않고 원인과 follow-up을 남긴다.
- 해결된 항목은 제거하지 않고 해결 상태와 관련 WorkLog를 연결한다.
- 개인 환경 문제는 필요한 범위만 요약하고 민감 정보는 local에 둔다.
