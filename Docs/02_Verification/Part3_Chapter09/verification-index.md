# Part3 Chapter09 Verification Index

이 문서는 `Part3_Chapter09` Step1~6의 build/run/capture 사실을 기록한다.

## Provenance

- 과거 확인: 문서화 이전 Step1~6 build/run 성공
- 현재 재검증: 2026-08-03 Debug/Release x64 Clean/Rebuild와 Release run 완료
- Runtime working directory: 각 project 폴더
- Capture: exact application title을 포함한 1282×752 전체 창 PNG 확보

| Example | Debug build/run | Release build/run | Capture | 비고 |
| --- | --- | --- | --- | --- |
| `09_UserInteraction_Step1_FirstPersonView` | 성공 | 성공 | 완료 | cursor camera view와 WASD 경로 확인 |
| `09_UserInteraction_Step2_MousePicking` | 성공 | 성공 | 완료 | ID color MRT와 readback 경로 확인 |
| `09_UserInteraction_Step3_MousePickingRayCollision` | 성공 | 성공 | 완료 | CPU ray와 bounding sphere 경로 확인 |
| `09_UserInteraction_Step4_QuaternianRotation` | 성공 | 성공 | 완료 | zero axis fallback과 quaternion 변환 확인 |
| `09_UserInteraction_Step5_VirtualTrackball` | 성공 | 성공 | 완료 | drag capture와 sphere-surface rotation 경로 확인 |
| `09_UserInteraction_Step6_MouseDragMove` | 성공 | 성공 | 완료 | drag capture와 bounding sphere center 동기화 확인 |

## 공통 확인

- Step1~6은 cubemap 또는 texture를 상대 경로로 읽으므로 project 폴더 CWD를 사용한다.
- Step2의 `NormalVertexShader.hlsl`은 출력 초기화 warning을 남기지만 shader object와 executable 생성, run은 성공한다.
- Step4~6은 mouse capture를 사용해 drag 중 cursor가 client 밖으로 나간 뒤 release되는 상태를 복구한다.
- 기본 창 실행과 clean exit를 확인했다. Resize resource 수명 정규화는 후속 공통 portability 작업으로 분리한다.

## Capture 검증

- PNG 6장 full decode 성공
- 각 capture 1282×752
- application title과 Example 결과 일치
- 외부 application UI, 계정, 로컬 경로와 개인 식별자 없음
- source asset 권리 근거가 부족하므로 Publication은 `검토 필요`

## 관련 문서

- [Chapter README](../../../Part3_Chapter09/README.md)
- [Demo Index](../../03_Demos/Part3_Chapter09/demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
