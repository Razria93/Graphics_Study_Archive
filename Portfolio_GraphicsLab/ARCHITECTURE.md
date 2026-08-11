# GraphicsLab Architecture

## 목적

이 문서는 WU-A0에서 `Portfolio_GraphicsLab`의 초기 architecture와 Part1 reconstruction 순서를 고정한다. 목표는 CPU ray tracing으로 GPU의 암묵적 처리 단계를 관찰하면서, 이후 CPU rasterization과 D3D11 graphics pipeline이 들어와도 application, asset과 scene 책임을 기능별로 교체할 수 있게 하는 것이다.

## Architecture 원칙

- **Lifecycle과 rendering 분리:** Application은 프로그램 시작·종료, window event, frame loop와 renderer 호출을 관리한다. 이미지 생성 알고리즘은 Rendering module에 두어 application lifecycle을 바꾸지 않고 rendering 방식을 교체할 수 있게 한다.
- **Domain data와 backend resource 분리:** Mesh, Material, Camera와 Light는 graphics API에 의존하지 않는 data로 유지한다. D3D11 resource는 backend가 별도로 소유해 같은 Scene을 CPU RayTracing과 이후 renderer가 함께 사용할 수 있게 한다.
- **실행 위치와 무관한 asset 경로:** Asset은 executable 옆 `Assets`를 기준으로 한 relative path 또는 stable ID로 참조한다. CWD와 사용자별 absolute path에는 의존하지 않는다.
- **명확한 단일 ownership:** Value와 `std::unique_ptr`를 기본 ownership으로 사용하고, non-owning 관계는 reference, pointer 또는 stable ID로 표현한다. 실제 shared lifetime이 필요한 경우에만 `std::shared_ptr`를 사용한다.
- **검증된 공통점만 추상화:** Module 책임은 처음부터 분리하지만 공통 renderer interface, factory와 RHI는 미리 만들지 않는다. 두 번째 실제 renderer에서 반복 책임이 확인된 뒤 최소 abstraction을 추출한다.
- **미래 기능은 constraint로만 사용:** Part2부터 Part4까지의 기능은 현재 구조가 미래 확장을 막지 않는지 판단하는 기준으로 사용한다. 관련 module은 해당 Work Unit이 시작될 때 구현한다.

## Module 경계

| Module | 책임 | 의존 가능 대상 | 금지 대상 |
| --- | --- | --- | --- |
| `Application` | composition root, lifecycle, frame orchestration | 모든 concrete module의 public contract | domain object 내부 로직 소유 |
| `Core` | 공통 오류·진단과 작은 범용 utility | C++ standard library | graphics backend와 domain type |
| `Math` | vector, matrix, ray와 transform contract | C++ standard library, 선택한 math dependency | D3D11 resource와 application state |
| `Platform/Windows` | `wWinMain`, window, message loop와 OS boundary | `Application`, Win32 | renderer algorithm과 scene ownership |
| `Asset` | executable 기준 asset root, 파일 읽기와 decoded data | `Core` | process CWD, D3D11 device ownership |
| `Scene` | camera, geometry instance, material과 light domain data | `Math`, asset ID | backend resource와 application settings back-pointer |
| `Rendering/Common` | framebuffer, color와 backend 독립 render input/output | `Math`, `Scene` | Win32와 D3D11 concrete resource |
| `Rendering/Presentation/D3D11` | window surface, dynamic texture upload와 presentation | `Rendering/Common`, Win32, D3D11 | ray tracing algorithm 소유 |
| `Rendering/RayTracing/CPU` | ray generation, intersection, shading와 sampling | `Math`, `Scene`, `Rendering/Common` | Win32 message와 D3D11 resource |
| `Rendering/Rasterization/CPU` | 미래 CPU pipeline 구현 축 | 공통 domain과 framebuffer | RayTracing 내부 type 재사용 |
| `Rendering/GraphicsPipeline/D3D11` | 미래 GPU pipeline 구현 축 | Scene, Asset와 D3D11 boundary | CPU algorithm 내부 type 재사용 |

의존 방향은 application composition root에서 concrete module을 조립하고, rendering module이 platform lifecycle을 호출하지 않는 방향으로 유지한다. `Scene -> Application`, `Asset -> Presentation`과 renderer 사이의 상호 참조는 허용하지 않는다.

## Data와 ownership 계약

- `Application`이 window, selected renderer, presentation backend와 long-lived service의 lifetime을 조립한다.
- `Scene`은 geometry, material, light와 instance를 value 또는 stable ID 중심으로 소유한다. renderer settings를 가리키는 back-pointer를 두지 않는다.
- decoded image와 model data는 backend 독립 CPU data다. D3D11 resource 생성과 해제는 D3D11 module이 소유한다.
- CPU renderer는 output size와 pixel storage를 가진 `Framebuffer`를 반환하거나 갱신한다. presentation module은 그 결과를 읽어 GPU texture에 전달한다.
- `shared_ptr`는 실제 shared lifetime이 입증된 경우에만 사용한다. 단일 lifetime에는 value 또는 `unique_ptr`, 관찰에는 reference·pointer·ID를 사용한다.
- cache와 registry는 첫 중복 consumer가 확인된 Work Unit에서 도입한다.

## 좌표와 transform 계약

| 항목 | Canonical contract |
| --- | --- |
| World/View handedness | left-handed, `+X` right, `+Y` up, `+Z` forward |
| Screen | origin top-left, `+X` right, `+Y` down |
| NDC | `+X` right, `+Y` up |
| Matrix/vector | column vector, `world = model * local`, composition은 오른쪽에서 왼쪽 순서 |
| Length | world unit 사용 |
| Public ray | world-space direction을 normalized 상태로 생성 |
| Front face | `dot(ray.direction, outwardNormal) < 0`으로 판정하며 rasterizer winding과 분리 |
| Normal transform | model matrix의 inverse-transpose 사용 후 normalize |
| Hit ordering | world-space ray distance로 비교 |

object-space intersection은 world ray를 inverse model matrix로 변환하되 local direction을 임의로 normalize해 parameter 의미를 바꾸지 않는다. local hit point를 world로 되돌린 뒤 world-space distance와 inverse-transpose normal을 계산한다. translation, non-uniform scale과 rotation을 numeric test로 확인하기 전에는 완료로 판정하지 않는다.

D3D11 rasterizer의 front-face winding과 HLSL matrix layout은 API boundary에서 명시적으로 변환한다. CPU intersection의 front-face 정의를 API 기본 winding에 종속시키지 않는다.

## 오류와 진단 계약

- programmer contract 위반은 `assert` 또는 `std::invalid_argument`로 빠르게 드러낸다.
- startup, platform과 resource 생성 실패는 구체적 context를 포함한 exception으로 전달하고 application boundary에서 종료 상태로 변환한다.
- 정상적으로 발생 가능한 asset 부재를 silent fallback으로 숨기지 않는다. caller가 대체 asset을 선택하거나 실패를 보고한다.
- C++17에는 범용 `Result` type을 선행 도입하지 않는다. 반복되는 recoverable error 흐름이 확인되면 별도 decision으로 추가한다.
- renderer 내부 진단은 pixel 결과와 분리된 debug output으로 제공하며 release 동작을 바꾸지 않는다.

## Threading 계약

Win32 message loop와 D3D11 immediate context는 main thread에서 소유한다. CPU renderer는 우선 단일 thread에서 deterministic correctness를 검증한다. row 또는 tile 작업이 독립적이고 동일 입력에서 결과 재현성이 확인된 뒤에만 병렬화를 별도 Work Unit으로 추가한다.

## 검증 계약

- Math, ray, transform과 intersection은 작은 numeric test로 경계값을 확인한다.
- asset path는 repository root와 executable output directory를 각각 CWD로 둔 smoke run에서 같은 asset root를 선택해야 한다.
- 각 rendering 기능은 Debug/Release x64 build/run과 최소 scene 결과를 확인한다.
- visual 변경은 같은 scene, camera, resolution과 parameter를 고정한 A/B로 비교한다.
- 직접 확인하지 않은 결과는 `미확인`으로 기록한다.
- 성능 측정은 correctness 완료 이후 별도 baseline과 입력을 고정해 수행한다.

## Part1 Reconstruction Roadmap

| Work Unit | 기능 | 선행 조건 | 완료 기준 |
| --- | --- | --- | --- |
| WU-R1 | Win32 window와 D3D11 presentation | WU-R0 scaffold | resize 가능한 window, 빈 CPU framebuffer upload, 두 CWD smoke |
| WU-R2 | Math·coordinate·transform contract | WU-R1 | camera basis와 translation·rotation·non-uniform scale numeric test |
| WU-R3 | Framebuffer와 primary camera ray | WU-R2 | pixel center ray와 screen/NDC 변환 test, diagnostic gradient capture |
| WU-R4 | Sphere·triangle과 `HitRecord` | WU-R3 | hit/miss, inside/outside, front-face와 epsilon test |
| WU-R5 | Scene instance와 closest-hit traversal | WU-R4 | 여러 instance와 transformed object의 world-space closest hit test |
| WU-R6 | Normal·vertex color diagnostic | WU-R5 | normal과 barycentric color 결과를 고정 scene에서 확인 |
| WU-R7 | Material과 local lighting | WU-R6 | ambient·diffuse·specular 항을 분리 검증하고 합성 결과 확인 |
| WU-R8 | Shadow visibility | WU-R7 | bias, self-shadow와 occluder 유무 A/B 확인 |
| WU-R9 | Triangle attribute interpolation | WU-R8 | barycentric UV·normal interpolation과 edge seam test |
| WU-R10 | Texture decode와 CPU sampling | WU-R9 | 권리 확인 asset, address mode와 point/bilinear sampling test |
| WU-R11 | Anti-aliasing sampling | WU-R10 | deterministic sample pattern과 1 spp 대비 동일 scene A/B |
| WU-R12 | Recursive reflection | WU-R11 | depth limit, energy weight와 reflection on/off 확인 |
| WU-R13 | Transmission과 refraction | WU-R12 | enter/exit IOR, total internal reflection과 recursion termination test |
| WU-R14 | Environment와 Part1 closeout | WU-R13 | direction mapping test, replacement environment, final scene와 limitation 기록 |

각 Work Unit은 original intent와 observed evidence를 먼저 기록하지만 source를 복사하는 단계는 두지 않는다. original final snapshot에 없거나 미완성인 기능도 canonical roadmap에서는 Part1 목표와 별도 검증을 근거로 구현한다.

## Part2부터 Part4까지의 constraint

- Part2의 CPU rasterization과 D3D11 pipeline은 같은 Scene·Asset data를 소비할 수 있어야 하지만 RayTracing 내부 hit type에 의존하지 않는다.
- Part3의 camera interaction, model/material, PBR, multipass와 shadow는 input, asset과 render-pass 책임을 renderer 밖의 전역 state로 밀어 넣지 않아야 한다.
- Part4의 compute, simulation, animation과 physics는 update와 render를 분리하고 GPU resource ownership을 backend에 유지해야 한다.
- 실제 기능이 시작되기 전에는 render graph, ECS, job system, plugin system과 cross-API RHI를 만들지 않는다.

## WU-R1 시작 판정

WU-R0 build contract는 완료됐다. WU-R1은 이 architecture를 사용자 검수하고 coordinate·ownership contract를 승인한 뒤 시작한다. WU-R1에서는 window, resize, CPU framebuffer upload와 presentation까지만 구현하고 camera ray와 ray tracing 기능은 WU-R3 이후로 유지한다.

## 관련 문서

- [Project README](README.md)
- [BUILD](BUILD.md)
- [Reconstruction Strategy](../Docs/04_WorkLogs/decisions/graphics-lab-reconstruction-strategy.md)
- [Original Evidence Review](../Docs/04_WorkLogs/reviews/graphics-lab-original-evidence.md)
