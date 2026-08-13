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

## 전체 책임 구조

이 구조는 폴더 계층을 그대로 표현하는 목록이 아니라 책임과 의존 방향을 보여주는 지도다. `현재`는 WU-R0 또는 가까운 Part1 Work Unit에서 사용하는 경계이고, `미래`는 실제 기능이 시작될 때 추가할 후보 경계다.

```text
Platform/Windows
        │ event, native window
        ▼
Application ──────────────── composition root
   ├── Asset ─────────────── file reference와 decoded CPU data
   ├── Scene ─────────────── camera, geometry, material과 light
   └── Rendering
       ├── Common ────────── framebuffer와 공통 render data
       ├── RayTracing/CPU ── 현재 Part1 image 생성 축
       ├── Presentation/D3D11 ─ CPU 결과의 window 표시
       ├── Rasterization/CPU ─── 미래 Part2 image 생성 축
       └── GraphicsPipeline/D3D11 ─ 미래 Part2·3 GPU rendering 축

Core와 Math는 위 module이 필요한 최소 기반 기능을 제공한다.
```

`Application`은 concrete module을 조립하지만 각 module의 내부 알고리즘을 소유하지 않는다. `Scene`은 무엇을 그릴지 표현하고, Rendering module은 어떻게 이미지를 만들지 결정하며, Presentation은 결과를 어디에 표시할지 담당한다. Platform과 Asset은 각각 OS와 file system 경계를 담당한다.

## 주요 실행 흐름

### Frame 흐름

```text
Windows event 수집
-> Application이 frame 순서 결정
-> Scene 상태 읽기 또는 update
-> 선택한 Rendering algorithm 실행
-> CPU Framebuffer 또는 GPU render target 생성
-> Presentation
-> Window 출력
```

Part1 CPU RayTracing에서는 `Scene -> RayTracing/CPU -> Framebuffer -> Presentation/D3D11` 흐름을 사용한다. 미래 D3D11 graphics pipeline은 GPU render target을 직접 생성할 수 있으므로 CPU Framebuffer를 강제하지 않는다.

### Asset 흐름

```text
Canonical relative path 또는 stable ID
-> Asset이 file 탐색과 decode 수행
-> backend 독립 CPU data
-> Scene domain data 또는 Rendering backend resource 생성
```

Asset reference, loaded CPU data와 D3D11 resource는 서로 다른 lifetime과 책임을 가진다. 이 구분을 유지해야 CPU renderer가 D3D11 resource 없이 같은 source data를 사용할 수 있다.

## Lifetime 구조

| Lifetime | 현재 owner | 소유 대상 | 확장 방향 |
| --- | --- | --- | --- |
| Process/Application | `Application` | 장기 service, 선택한 renderer와 전체 실행 순서 | service가 늘어나면 application-lifetime subsystem을 분리 |
| Window | `Platform/Windows`와 D3D11 presentation | native window, swap chain과 window-size resource | multi-window 요구가 생기면 window context 단위로 분리 |
| Scene | 현재 `Application`이 소유하는 `Scene` | camera, geometry instance, material과 light | update·animation·physics lifetime이 생기면 `World` 경계 검토 |
| Frame | 선택한 renderer와 presentation | render input, temporary result와 command state | multipass dependency가 복잡해지면 render graph 검토 |
| Asset/Resource | Asset service와 concrete backend | decoded CPU data와 API resource | cache·streaming·unload 요구가 생기면 registry와 handle 도입 |

Unreal Engine의 구체 class hierarchy를 복제하지 않는다. 대신 기능을 module로 캡슐화하고 상위 객체의 lifetime에 맞춰 subsystem을 생성·해제하며 domain object와 rendering resource를 분리하는 방향을 참고한다. 세부 채택·보류 근거는 [Architecture Evolution Decision](../Docs/04_WorkLogs/decisions/graphics-lab-architecture-evolution.md)에 기록한다.

## Module 경계

| Module                             | 책임                                                     | 의존 가능 대상                                  | 금지 대상                                               |
| ---------------------------------- | ------------------------------------------------------ | ----------------------------------------- | --------------------------------------------------- |
| `Application`                      | composition root, lifecycle, frame orchestration       | 모든 concrete module의 public contract       | domain object 내부 로직 소유                              |
| `Core`                             | 공통 오류·진단과 작은 범용 utility                                | C++ standard library                      | graphics backend와 domain type                       |
| `Math`                             | vector, matrix, ray와 transform contract                | C++ standard library, 선택한 math dependency | D3D11 resource와 application state                   |
| `Platform/Windows`                 | `wWinMain`, window, message loop와 OS boundary          | `Application`, Win32                      | renderer algorithm과 scene ownership                 |
| `Asset`                            | executable 기준 asset root, 파일 읽기와 decoded data          | `Core`                                    | process CWD, D3D11 device ownership                 |
| `Scene`                            | camera, geometry instance, material과 light domain data | `Math`, asset ID                          | backend resource와 application settings back-pointer |
| `Rendering/Common`                 | framebuffer, color와 backend 독립 render input/output     | `Math`, `Scene`                           | Win32와 D3D11 concrete resource                      |
| `Rendering/Presentation/D3D11`     | window surface, dynamic texture upload와 presentation   | `Rendering/Common`, Win32, D3D11          | ray tracing algorithm 소유                            |
| `Rendering/RayTracing/CPU`         | ray generation, intersection, shading와 sampling        | `Math`, `Scene`, `Rendering/Common`       | Win32 message와 D3D11 resource                       |
| `Rendering/Rasterization/CPU`      | 미래 CPU pipeline 구현 축                                   | 공통 domain과 framebuffer                    | RayTracing 내부 type 재사용                              |
| `Rendering/GraphicsPipeline/D3D11` | 미래 GPU pipeline 구현 축                                   | Scene, Asset와 D3D11 boundary              | CPU algorithm 내부 type 재사용                           |

의존 방향은 application composition root에서 concrete module을 조립하고, rendering module이 platform lifecycle을 호출하지 않는 방향으로 유지한다. `Scene -> Application`, `Asset -> Presentation`과 renderer 사이의 상호 참조는 허용하지 않는다.

## Module별 책임과 확장

### `Application`

**역할:** Process 진입 이후 window, asset service, Scene, 선택한 renderer와 presentation backend를 생성하고 frame 실행 순서와 종료를 조정한다. 최상위 오류를 사용자에게 보고 가능한 종료 상태로 변환한다.

**담당하지 않는 것:** Windows message 처리 세부, geometry intersection, shading, D3D11 resource 생성과 Scene domain logic을 직접 구현하지 않는다.

**구성 근거:** 프로그램 운영과 image 생성 알고리즘을 분리해야 CPU RayTracing을 CPU Rasterization 또는 D3D11 graphics pipeline으로 바꿔도 application lifecycle을 다시 작성하지 않는다. 모든 객체가 Application을 역참조하는 구조도 피한다.

**현재 범위와 확장:** 현재는 하나의 window와 renderer를 직접 조립한다. 장기 service가 늘어나고 독립적인 초기화·종료 순서가 반복될 때 application-lifetime subsystem을 도입한다. renderer가 두 개 이상 실제로 사용되면 선택과 교체에 필요한 최소 contract를 추출한다.

### `Core`

**역할:** 특정 graphics algorithm, Scene 또는 backend에 속하지 않는 오류·진단과 작은 범용 utility를 제공한다.

**담당하지 않는 것:** Mesh, Material, D3D11 device, renderer option과 편의를 위해 모은 miscellaneous helper를 두지 않는다.

**구성 근거:** 공통 기반을 두되 모든 module이 의존하는 거대한 utility 계층으로 변하는 것을 막는다. 기능이 한 module에서만 사용되면 해당 module에 남기는 것이 dependency와 변경 이유를 더 명확하게 만든다.

**현재 범위와 확장:** 반복 사용이 확인된 작은 기능만 추가한다. 두 개 이상의 독립 module이 같은 backend 비종속 기능을 요구할 때 Core 승격을 검토한다.

### `Math`

**역할:** Vector, matrix, Ray, Transform과 좌표 변환을 표현하고 GraphicsLab 전체의 handedness, matrix/vector와 normal transform convention을 고정한다.

**담당하지 않는 것:** Scene ownership, camera input, 전체 intersection algorithm과 D3D11 constant buffer를 소유하지 않는다.

**구성 근거:** RayTracing, Rasterization과 D3D11 pipeline이 서로 다른 좌표 convention을 암묵적으로 사용하면 transform 오류를 검증하기 어렵다. 반대로 renderer 전용 알고리즘까지 Math에 모으면 책임이 흐려진다.

**현재 범위와 확장:** WU-R2에서 camera basis와 object transform을 numeric test로 고정한다. Quaternion, bounding volume과 projection helper는 실제 consumer와 검증 사례가 생길 때 추가한다.

### `Platform/Windows`

**역할:** `wWinMain`, native window 생성·제거, Windows message loop, resize와 input event 수집 같은 OS boundary를 담당한다.

**담당하지 않는 것:** Scene update 규칙, RayTracing, framebuffer pixel 결정과 D3D11 rendering algorithm을 구현하지 않는다.

**구성 근거:** OS event와 rendering code가 섞이면 renderer를 독립적으로 시험하기 어렵고 window lifecycle 변경이 graphics algorithm에 전파된다. Platform은 native event와 handle을 application이 사용할 수 있는 경계까지만 전달한다.

**현재 범위와 확장:** WU-R1에서 단일 window와 resize lifecycle을 구현한다. input 요구가 생기면 raw Windows message를 Scene에 전달하지 않고 application-level input state로 변환한다. 다른 OS를 지원하기 전에는 공통 platform interface를 만들지 않는다.

### `Asset`

**역할:** Executable 기준 `Assets` root, canonical relative path, file 읽기와 image/model 같은 backend 독립 CPU data의 decode를 담당한다.

**담당하지 않는 것:** `ID3D11Texture2D`, shader resource view와 다른 API resource를 생성·소유하지 않으며 process CWD와 사용자별 absolute path를 lookup contract로 사용하지 않는다.

**구성 근거:** File discovery·decode와 GPU resource 생성이 결합되면 CPU RayTracing도 D3D11에 의존한다. Asset reference와 loaded data를 분리하면 같은 source data를 여러 renderer가 사용할 수 있다.

**현재 범위와 확장:** 현재는 executable-relative path와 최소 file contract를 사용한다. 여러 consumer가 같은 asset을 반복 load하고 unload·streaming 요구가 생길 때 stable ID, registry, cache와 handle을 단계적으로 도입한다.

### `Scene`

**역할:** Camera, geometry, instance transform, Material과 Light를 통해 무엇을 렌더링할지 표현하는 backend 독립 domain data를 소유한다.

**담당하지 않는 것:** `HitRecord`, BVH traversal state, rasterizer triangle setup, D3D11 buffer, application settings back-pointer와 Windows input message를 소유하지 않는다.

**구성 근거:** Scene이 RayTracing 또는 D3D11 전용 type을 가지면 다른 renderer가 같은 장면을 소비할 수 없다. Domain state와 renderer의 계산·resource state를 분리해야 한 장면을 여러 graphics 구현 축에서 비교할 수 있다.

**현재 범위와 확장:** Part1에서는 camera, primitive, material과 light부터 시작한다. Scene이 rendering data를 넘어 gameplay object update, animation과 physics lifetime을 관리하기 시작하면 상위 `World` 경계를 도입하고 Scene을 renderable view 또는 spatial data 책임으로 좁히는 방안을 검토한다.

### `Rendering/Common`

**역할:** CPU `Framebuffer`, Color와 같이 두 개 이상의 rendering/presentation 축에서 실제로 공유하는 최소 backend 독립 data contract를 둔다.

**담당하지 않는 것:** RayTracing의 `HitRecord`, Rasterization의 triangle setup, D3D11 resource와 모든 renderer를 하나로 보이게 하는 거대한 interface를 두지 않는다.

**구성 근거:** CPU renderer 결과를 D3D11 presentation에 전달하려면 공통 경계가 필요하지만, renderer 고유 상태까지 공통화하면 잘못된 결합이 생긴다. 확인된 교환 data만 공유하는 것이 변경 범위를 작게 유지한다.

**현재 범위와 확장:** WU-R1에서 CPU Framebuffer contract를 확정한다. CPU Rasterization과 두 번째 consumer가 추가되면 실제로 반복되는 render input/output만 이 module로 승격한다.

### `Rendering/Presentation/D3D11`

**역할:** D3D11 device와 swap chain, window surface, dynamic texture upload, fullscreen presentation과 resize에 종속되는 resource lifetime을 담당한다.

**담당하지 않는 것:** Ray 생성, intersection, shading, Scene traversal과 CPU pixel 값을 결정하지 않는다.

**구성 근거:** Part1 algorithm은 CPU에서 명시적으로 구현하지만 결과를 실제 window에 표시하려면 D3D11이 필요하다. Presentation을 분리하면 CPU renderer는 API resource 없이 Framebuffer만 생성하고 동일한 표시 경로를 계속 사용할 수 있다.

**현재 범위와 확장:** WU-R1에서 diagnostic Framebuffer를 표시한다. 미래 D3D11 graphics pipeline이 device와 resource 생성 책임을 공유하게 되면 두 concrete consumer를 근거로 공통 D3D11 backend 경계를 추출한다.

### `Rendering/RayTracing/CPU`

**역할:** Primary ray, primitive intersection, closest-hit traversal, attribute interpolation, shading, shadow, texture sampling, anti-aliasing, reflection, refraction과 environment sampling으로 CPU Framebuffer를 생성한다.

**담당하지 않는 것:** Window message, swap chain, D3D11 resource, process CWD asset lookup과 Scene object lifetime을 관리하지 않는다.

**구성 근거:** Part1은 GPU가 제공하는 좌표 변환, visibility, interpolation과 shading을 CPU에서 관찰 가능한 단계로 구현하는 학습 축이다. Presentation과 분리해야 algorithm correctness와 시각 출력을 독립적으로 검증할 수 있다.

**현재 범위와 확장:** WU-R3부터 WU-R14까지 기능을 순차적으로 추가한다. Deterministic correctness 이후에만 tile/row 병렬화와 acceleration structure를 별도 Work Unit으로 검토한다.

### `Rendering/Rasterization/CPU`

**역할:** 미래 Part2 축으로 vertex transform, primitive assembly, clipping, viewport transform, triangle coverage, interpolation, depth test와 CPU shader에 해당하는 처리를 수행한다.

**담당하지 않는 것:** Ray, `HitRecord`와 RayTracing traversal state를 재사용하지 않으며 D3D11 resource에 의존하지 않는다.

**구성 근거:** RayTracing과 Rasterization은 같은 Scene을 소비할 수 있지만 image 생성 알고리즘과 중간 상태가 다르다. Scene, Math와 검증된 output contract만 공유해야 두 방식의 차이를 분명히 관찰할 수 있다.

**현재 범위와 확장:** 현재는 책임만 예약하며 folder와 type을 만들지 않는다. Part2 Work Unit이 시작될 때 실제 요구로 module을 만들고 RayTracing과 확인된 공통점만 `Rendering/Common`으로 승격한다.

### `Rendering/GraphicsPipeline/D3D11`

**역할:** 미래 Part2·3 축으로 GPU vertex/index buffer, input layout, shader, constant buffer, texture/sampler, pipeline state, draw call, render target와 depth buffer를 담당한다.

**담당하지 않는 것:** CPU RayTracing과 Rasterization의 내부 type을 재사용하지 않으며 Scene domain object에 API resource ownership을 넘기지 않는다.

**구성 근거:** CPU 구현에서 관찰한 graphics 단계를 D3D11 API가 어떻게 제공하는지 연결하려면 같은 Scene을 소비하는 독립 GPU rendering 축이 필요하다. Backend resource를 분리하면 Scene과 Asset을 유지한 채 implementation을 비교할 수 있다.

**현재 범위와 확장:** Part2에서 기본 graphics pipeline, Part3에서 model, PBR, multipass와 shadow로 확장한다. 여러 D3D11 module이 device, context와 resource factory를 실제로 공유하면 공통 backend를 추출하며, 두 번째 graphics API가 목표가 되기 전에는 RHI를 만들지 않는다.

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

## 단계별 구조 확장

| 단계 | 실제 구현 축 | 유지하는 경계 | 새로 검토하는 경계 |
| --- | --- | --- | --- |
| WU-R1부터 WU-R14까지 | Window, D3D11 presentation과 CPU RayTracing | Application, Asset, Scene, Framebuffer와 backend resource 분리 | 두 번째 consumer가 없으므로 renderer interface와 RHI를 만들지 않음 |
| Part2 | CPU Rasterization과 D3D11 graphics pipeline | 같은 Scene·Asset·Math를 소비하고 algorithm state는 분리 | 공통 render input/output, D3D11 device/resource service |
| Part3 | Input, model/material, PBR, multipass와 shadow | Domain state와 render resource 분리 | World/Object 구성, rendering frontend와 pass orchestration |
| Part4 | Compute, simulation, animation과 physics | Update와 render, CPU domain과 GPU execution 분리 | Lifetime subsystem, asynchronous work와 render graph |
| 실제 다중 API 목표 | 두 번째 graphics API backend | High-level scene/render intent와 concrete API resource 분리 | 최소 RHI와 backend selection |

확장은 빈 folder나 interface를 미리 추가하는 방식이 아니다. 해당 단계의 첫 concrete consumer를 구현하고 두 번째 consumer에서 반복되는 책임을 확인한 뒤 공통 경계를 추출한다.

## 미래 구조 도입 조건

| 후보 구조 | 도입 조건 | 도입 전 유지할 방식 |
| --- | --- | --- |
| `World` | Scene이 render data를 넘어 object update, lifetime, animation과 physics 결과를 관리하기 시작할 때 | Application이 backend 독립 Scene을 직접 소유 |
| Object/Component | 하나의 object가 render, animation, physics와 interaction 책임을 선택적으로 조합해야 할 때 | 명시적인 Scene instance와 value data 사용 |
| Lifetime subsystem | Application, World 또는 Window lifetime에 맞춘 service 초기화·종료가 반복될 때 | Application composition root의 직접 ownership |
| Asset Registry | 여러 consumer가 stable ID, cache, reload, unload 또는 streaming을 요구할 때 | Canonical relative path와 명시적 load |
| Rendering frontend | CPU와 GPU renderer가 view 구성과 Scene render-data 추출을 실제로 공유할 때 | 각 concrete renderer가 Scene의 public data를 읽음 |
| Common D3D11 backend | Presentation과 graphics pipeline이 device, context와 resource 생성 책임을 공유할 때 | Presentation이 필요한 D3D11 resource를 직접 소유 |
| Render Graph | Multipass, compute와 temporary resource dependency를 수동 순서로 관리하기 어려워질 때 | 명시적인 pass 호출과 resource lifetime |
| Job system | 독립 작업이 여러 subsystem에서 반복되고 scheduling·shutdown contract가 필요할 때 | Deterministic single-thread 또는 module-local 병렬화 |
| RHI | D3D11 외 두 번째 graphics API 구현이 실제 roadmap과 검증 대상이 될 때 | Concrete D3D11 type을 backend boundary 안에 유지 |

도입 조건을 충족해도 기존 구조를 자동으로 교체하지 않는다. Concrete 사용 사례, 대안, dependency 영향과 migration 단위를 별도 decision record로 검토한다.

## Architecture 변경 기준

- Module 역할, 허용 dependency와 금지 dependency가 바뀌면 이 문서를 먼저 갱신한다.
- 새로운 공통 abstraction은 최소 두 concrete consumer와 반복 책임을 근거로 제안한다.
- 새로운 lifetime owner는 생성 시점, 종료 순서와 non-owning reference의 유효 기간을 함께 기록한다.
- Scene domain type에 backend resource를 추가하거나 backend type에 domain ownership을 넘기는 변경은 별도 architecture decision을 요구한다.
- Render Graph, RHI, ECS 또는 Component model처럼 여러 module에 영향을 주는 구조는 해당 기능 구현 commit에 섞지 않고 decision과 migration 계획을 먼저 검수한다.
- Architecture 정본은 현재 책임을 설명하고, 선택 당시의 대안과 이유는 `Docs/04_WorkLogs/decisions`에 보존한다.

## WU-R1 시작 판정

WU-R0 build contract는 완료됐다. WU-R1은 이 architecture를 사용자 검수하고 coordinate·ownership contract를 승인한 뒤 시작한다. WU-R1에서는 window, resize, CPU framebuffer upload와 presentation까지만 구현하고 camera ray와 ray tracing 기능은 WU-R3 이후로 유지한다.

## 관련 문서

- [Project README](README.md)
- [BUILD](BUILD.md)
- [Reconstruction Strategy](../Docs/04_WorkLogs/decisions/graphics-lab-reconstruction-strategy.md)
- [Architecture Evolution Decision](../Docs/04_WorkLogs/decisions/graphics-lab-architecture-evolution.md)
- [Original Evidence Review](../Docs/04_WorkLogs/reviews/graphics-lab-original-evidence.md)
