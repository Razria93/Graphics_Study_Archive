# Part3 Chapter09 Verification Index

이 문서는 `Part3_Chapter09` Step1부터 Step6까지의 build/run/capture 사실을 기록한다.

## Provenance

- 과거 확인: 문서화 이전 Step1부터 Step6까지 build/run 성공
- 현재 재검증: 2026-08-04 Step2 Debug/Release x64 Rebuild와 resize run 완료
- Runtime working directory: 각 project 폴더
- Capture: exact application title을 포함한 1282×752 전체 창 PNG와 selected local video 확보

| Example | Debug build/run | Release build/run | Capture | 비고 |
| --- | --- | --- | --- | --- |
| `09_UserInteraction_Step1_FirstPersonView` | 성공 | 성공 | 완료 | 기본 PNG, WASD·mouse-look selected local video 확인 |
| `09_UserInteraction_Step2_MousePicking` | 성공 | 성공 | 완료 | 기본·hover red PNG, signed cursor readback과 resize resource 재구성 확인 |
| `09_UserInteraction_Step3_MousePickingRayCollision` | 성공 | 성공 | 완료 | release·press PNG, lifecycle video와 mouse capture 복구 확인 |
| `09_UserInteraction_Step4_QuaternianRotation` | 성공 | 성공 | 완료 | 기본 PNG와 X·Y·Z 축별 15초 selected local video 확인 |
| `09_UserInteraction_Step5_VirtualTrackball` | 성공 | 성공 | 완료 | 기본 PNG와 18.6초 trackball selected local video 확인 |
| `09_UserInteraction_Step6_MouseDragMove` | 성공 | 성공 | 완료 | 기본 PNG와 16.07초 drag-move selected local video 확인 |

## 공통 확인

- Step1부터 Step6까지는 cubemap 또는 texture를 상대 경로로 읽으므로 project 폴더 CWD를 사용한다.
- Step2의 `NormalVertexShader.hlsl`은 출력 초기화 warning을 남기지만 shader object와 executable 생성, run은 성공한다.
- Step2는 wide·medium·compact resize, 기본 크기 복원과 minimize/restore에서 resource 재구성과 clean exit를 확인한다.
- Step3부터 Step6까지는 mouse capture를 사용해 drag 중 cursor가 client 밖으로 나간 뒤 release되는 상태를 복구한다.
- Step2는 실제 ID texture 범위 밖 cursor readback을 생략하고 이전 hover 상태를 유지한다.

## Capture 검증

- PNG 8장 full decode 성공
- 각 capture 1282×752
- application title과 Example 결과 일치
- 외부 application UI, 계정, 로컬 경로와 개인 식별자 없음
- Selected local video 8개는 H.264, `yuv420p`, 30 FPS, 1282×752, audio stream 0개와 full decode를 확인했다.
- 검증된 screenshot과 selected local video에서 의미 상태를 선별한 storyboard PNG 7장의 full decode, label 순서와 source sequence 대응을 확인했다.
- QA contact sheet와 중간 frame은 `local/`에 유지하고 최종 storyboard만 tracked capture로 승격했다.
- Step1 mouse-look 31초는 사용자가 지정한 5초 이동 네 구간을 보존한 예외다.
- Step4는 39.77초 통합 take를 선택하지 않고 X·Y·Z 축별 15초 파일 세 개로 분리했다.
- Publication 판정은 [Candidate List](../../05_Publication/candidate-list.md)에 위임한다.

## 관련 문서

- [Chapter README](../../../Part3_Chapter09/README.md)
- [Demo Index](../../03_Demos/Part3_Chapter09/demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
