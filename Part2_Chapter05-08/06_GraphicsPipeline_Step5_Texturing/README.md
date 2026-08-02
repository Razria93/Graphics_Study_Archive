# Chapter06 Step5 Texturing

이 예제는 Step4의 UV와 pixel shader constant buffer 흐름에 두 개의 GPU texture와 sampler를 추가한다. Pixel shader는 `xSplit`을 기준으로 석재와 목재 texture를 선택하고 같은 UV로 sampling한다.

## 실행 진입점

- Solution: `06_GraphicsPipeline_Step5_Texturing.sln`
- Application entry: `main.cpp`
- 주요 source: `AppBase.cpp`, `ExampleApp.cpp`, `ExampleApp.h`
- Shader: `ColorVertexShader.hlsl`, `ColorPixelShader.hlsl`
- Runtime input: `generated_stone_tiles.png`, `generated_dark_wood.png`
- Runtime working directory: project 폴더
- Application title: `ComputerGraphics - Chapter06 Step5 Texturing`

## Code Map

| 범위 | 책임 |
| --- | --- |
| [Square vertex와 UV](ExampleApp.cpp#L10-L52) | Position·color·UV를 가진 indexed square 구성 |
| [Texture와 sampler 초기화](ExampleApp.cpp#L166-L203) | Generated input 2개를 SRV로 만들고 linear wrap sampler 생성 |
| [Input layout](ExampleApp.cpp#L244-L250) | `POSITION`, `COLOR`, `TEXCOORD`를 vertex shader contract와 연결 |
| [Resource binding과 draw](ExampleApp.cpp#L298-L347) | SRV `t0`·`t1`, sampler `s0`, pixel constant buffer `b0` 연결 |
| [Split UI](ExampleApp.cpp#L350-L354) | `xSplit`을 `0.0`부터 `1.0`까지 조정 |
| [Texture 생성](AppBase.cpp#L520-L571) | Image decode, immutable RGBA texture와 SRV 생성 및 실패 전파 |
| [Vertex shader contract](ColorVertexShader.hlsl#L10-L48) | MVP transform 뒤 color와 UV 전달 |
| [Pixel shader sampling](ColorPixelShader.hlsl#L1-L21) | UV X와 `xSplit` 비교 후 두 texture 중 하나를 sampling |

## 구현 요약

Square의 UV는 왼쪽 위 `(0,0)`에서 오른쪽 아래 `(1,1)`까지 배치된다. CPU는 공개 검수를 마친 generated 석재·목재 PNG를 RGBA8 immutable texture와 shader resource view로 만들고 pixel shader slot `t0`·`t1`에 연결한다. Linear sampler는 slot `s0`, `xSplit` constant buffer는 slot `b0`을 사용한다.

Pixel shader는 `uv.x > xSplit`이면 목재를, 나머지 영역에서는 석재를 같은 UV로 sampling한다. 기본값 `0.5`는 두 재질을 같은 폭으로 보여주고 조정값 `0.25`는 경계 이동과 UI-to-buffer 반영을 확인하게 한다. 일반 sampling 원리는 [Texture Sampling](../../Docs/01_Topics/TexturingAndMapping/TextureSampling.md), 구현 선택과 결과 비교는 [Step5 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_Texturing.md)로 위임한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD, 정상 종료 |
| Release x64 build/run | 성공 | 2026-08-02 현재 확인, project 폴더 CWD, 정상 종료 |
| Texture·UI 반영 | 성공 | Generated input 2개 load, `t0`·`t1`·`s0`·`b0` binding과 `xSplit` 반영 확인 |
| 실패 경로 | 성공 | 잘못된 CWD에서 texture load 실패를 보고하고 exit code `-1`로 종료 |
| Capture/Result | 확보 | 기본 `0.5`와 조정 `0.25` 전체 창 screenshot, 사용자 승인 완료 |

Build 뒤의 `pwsh.exe` 환경 경고는 MSBuild 성공과 분리해 관찰했으며 실행 결과에는 영향을 주지 않았다.

## Capture/Result

기본값 `0.5`에서는 석재와 목재가 square 폭을 절반씩 차지한다.

![Chapter06 Step5 Texturing 기본 split](../../Docs/_assets/captures/part2_chapter06_05_texturing_default.png)

조정값 `0.25`에서는 석재 영역이 약 1/4로 줄고 목재 영역이 약 3/4로 늘어난다.

![Chapter06 Step5 Texturing 조정 split](../../Docs/_assets/captures/part2_chapter06_05_texturing_split_adjusted.png)

두 screenshot이 texture 선택 경계와 UI 값을 충분히 보여주므로 video는 제외한다.

## 구현 범위와 한계

- 실제 draw geometry는 `MakeSquare()`이며 파일에 남은 `MakeBox()`는 사용하지 않는다.
- Vertex color는 stage contract를 따라 전달되지만 현재 pixel shader 결과에는 사용하지 않는다.
- Texture는 mip level 하나만 생성하므로 mipmap·anisotropic filtering을 검증하지 않는다.
- Linear wrap sampler는 UV 경계에서 반대쪽 edge를 참조할 수 있다.
- Generated input은 public-safe Demo용이며 원본 prompt와 생성 작업 메모는 tracked 문서에 복제하지 않는다.
- Runtime shader와 texture load는 project 폴더 CWD에 의존한다.
- Debug/Release x64만 현재 검증하며 Win32 configuration은 범위에서 제외한다.

## 관련 문서

- [Part2 Chapter05-08 README](../README.md)
- [이전 단계: Chapter06 Step4 Shaders](../06_GraphicsPipeline_Step4_Shaders/README.md)
- [다음 단계: Chapter06 Step5A Texturing LightingSelf](../06_GraphicsPipeline_Step5_Texturing_LightingSelf/README.md)
- [Texture Sampling Topic](../../Docs/01_Topics/TexturingAndMapping/TextureSampling.md)
- [Shader Stage Topic](../../Docs/01_Topics/DirectX11Pipeline/ShaderStage.md)
- [Step5 Texturing 상세 Demo](../../Docs/03_Demos/Part2_Chapter05-08/06_Texturing.md)
- [Verification Index](../../Docs/02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](../../Docs/03_Demos/Part2_Chapter05-08/demo-index.md)
