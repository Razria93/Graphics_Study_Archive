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
| VI-005 | Part4_Chapter14-20 | 조건부 해소 | Debug와 Release x64 build 후 ignored output의 runtime DLL이 정리된다. 2026-08-07에는 vcpkg `x64-windows/debug/bin`과 `x64-windows/bin` DLL을 각각 23개씩 `x64/Debug`, `x64/Release`에 복구한 뒤 Chapter16부터 Chapter20까지 smoke를 수행함 | build output DLL copy 방식이 생기기 전까지 configuration에 맞는 vcpkg runtime DLL 복구 절차를 Part4 build/run 기준으로 유지 |
| VI-008 | Part4_Chapter14-20/Chapter16 | 조건부 해소 | `Examples.exe`를 `x64/Debug`에서 실행하면 relative shader를 찾지 못해 `File not found.`를 출력하고 main window를 만들지 못함 | `Part4_Chapter14-20` source root를 working directory로 사용하고 command argument별 smoke를 수행 |
| VI-006 | Part4_Chapter14-20/Ex1402_Blur | 조건부 해소 | 2026-08-06 Debug x64 파일럿 screenshot 후보가 white frame에 가까웠으나, delay sweep에서 5000ms capture가 RGB blur 결과를 확인함. 5000ms 안정화, collapsed UI, centered client-visible capture를 tracked 후보로 승격함 | Ex1402 capture는 5000ms 안정화 대기 기준을 유지한다. video 또는 timing 재검증은 별도 범위로 둔다 |
| VI-007 | Part4_Chapter14-20 | 조건부 해소 | 노트북 환경의 Part4 local screenshot 후보 일부에 taskbar 또는 ImGui control panel이 크게 포함됨. `HLAB_CAPTURE_UI=collapsed` 실행에서는 `Scene Control` titlebar를 좌측 상단 margin에 고정하고 접힌 상태로 유지함. visible client area capture는 taskbar를 제외하며, 큰 모니터에서 중앙 배치 후 `Ex1404`부터 `Ex1407`까지 전체 client capture를 확인함 | tracked capture 승격 전 capture UI mode, centered window, visible client area capture를 사용한다. video는 데스크탑 별도 목표로 분리 |

## 기록 기준

- 실패 또는 부분 성공 상태는 삭제하지 않고 원인과 follow-up을 남긴다.
- 해결된 항목은 제거하지 않고 해결 상태와 관련 WorkLog를 연결한다.
- 개인 환경 문제는 필요한 범위만 요약하고 민감 정보는 local에 둔다.
