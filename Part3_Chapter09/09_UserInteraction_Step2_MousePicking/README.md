# Chapter09 Step2 MousePicking

Object ID color를 별도 render target에 기록하고 cursor의 한 pixel을 staging texture로 읽어 hover object를 식별한다.

## 실행 진입점

- Solution: `09_UserInteraction_Step2_MousePicking.sln`
- 주요 source: `AppBase.cpp`, `ExampleApp.cpp`, `BasicPixelShader.hlsl`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter09 Step2 MousePicking`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [AppBase.cpp](AppBase.cpp#L193-L237) | resize 전 resource 해제와 render target 재구성 |
| [AppBase.cpp](AppBase.cpp#L245-L257) | signed cursor 좌표 저장 |
| [AppBase.cpp](AppBase.cpp#L571-L665) | ID render target와 1×1 staging texture 구성 |
| [ExampleApp.cpp](ExampleApp.cpp#L221-L347) | texture bounds 검사와 cursor pixel readback |
| [ExampleApp.cpp](ExampleApp.cpp#L325-L344) | ID color와 object highlight 상태 연결 |
| [ExampleApp.cpp](ExampleApp.cpp#L425-L433) | resize 전 filter 해제와 재구성 |

## Capture/Result

![Chapter09 Step2 MousePicking](../../Docs/_assets/captures/part3_chapter09_02_mouse_picking.png)

기본 상태와 hover red 상태의 비교는 [상세 Demo](../../Docs/03_Demos/Part3_Chapter09/09_02_MousePicking.md)에서 확인한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | HLSL 출력 초기화 warning 관찰 |
| Release x64 build/run | 성공 | project 폴더 CWD |
| Capture/Result | 완료 | 기본·hover red 전체 창 PNG |

## Limitations

- 매 frame GPU readback을 수행해 동기화 비용이 있다.
- Cursor가 실제 ID texture 범위를 벗어나면 readback을 생략하고 이전 hover 상태를 유지한다.
- MSAA edge resolve와 exact color 비교는 경계 pixel에서 선택을 놓칠 수 있다.
- Scene asset 원본은 비공개 runtime dependency로 유지하고 직접 실행 visual만 공개한다.

## Related Docs

- [Picking And Screen Ray](../../Docs/01_Topics/AnimationAndPhysics/PickingAndScreenRay.md)
- [Verification](../../Docs/02_Verification/Part3_Chapter09/verification-index.md)
- [상세 Demo](../../Docs/03_Demos/Part3_Chapter09/09_02_MousePicking.md)
- [이전 단계](../09_UserInteraction_Step1_FirstPersonView/README.md)
- [다음 단계](../09_UserInteraction_Step3_MousePickingRayCollision/README.md)
