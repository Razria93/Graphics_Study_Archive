# GraphicsLab Architecture Evolution Decision

## 목적

이 문서는 `Portfolio_GraphicsLab`이 Unreal Engine에서 지향하는 책임 분리 방향을 어떤 범위에서 참고하고, 어떤 구조를 현재 채택하거나 미래로 보류하는지 기록한다. 현재 architecture의 상세 책임은 `Portfolio_GraphicsLab/ARCHITECTURE.md`를 정본으로 사용하며 이 문서는 선택 당시의 의도와 도입 조건을 보존한다.

## 결정 배경

GraphicsLab은 Part1 CPU RayTracing에서 시작해 CPU Rasterization, D3D11 graphics pipeline, interaction, PBR, compute, simulation, animation과 physics까지 확장할 계획이다. 초기 구현 하나에 맞춘 class 구조를 고정하면 이후 graphics implementation을 추가할 때 Application, Scene과 Asset까지 다시 작성할 가능성이 크다.

반대로 Unreal Engine의 전체 class hierarchy, module system과 rendering infrastructure를 초기부터 복제하면 현재 consumer가 없는 abstraction과 lifetime 관리 비용이 생긴다. 따라서 Unreal의 구체 type보다 다음 책임 원칙을 참고한다.

- Runtime 기능을 독립 module로 캡슐화하고 dependency 방향을 제한한다.
- Subsystem은 자신을 소유하는 상위 객체의 lifetime에 맞춰 초기화하고 종료한다.
- Asset reference, loaded object와 rendering resource를 구분한다.
- World/domain state와 renderer/backend resource를 분리한다.
- High-level rendering과 low-level API resource 실행을 서로 다른 책임으로 본다.

## 채택한 구조

| 결정 | 현재 적용 방식 | 의도 |
| --- | --- | --- |
| Composition root | `Application`이 concrete module과 lifetime을 조립 | 전역 접근과 순환 ownership을 피함 |
| Platform boundary | `Platform/Windows`가 native window와 event를 담당 | OS 변경이 renderer algorithm에 전파되지 않게 함 |
| Backend 독립 domain | `Scene`이 camera, geometry, material과 light를 표현 | 여러 renderer가 같은 장면을 소비하게 함 |
| Asset/resource 분리 | Asset은 reference·decode, D3D11 backend는 API resource를 소유 | CPU와 GPU implementation이 source data를 공유하게 함 |
| Rendering 축 분리 | CPU RayTracing, CPU Rasterization, D3D11 pipeline을 별도 축으로 둠 | Algorithm 고유 state와 검증 목적을 보존함 |
| Lifetime 기반 ownership | Value와 단일 owner를 기본으로 하고 observer는 reference·pointer·ID를 사용 | 생성·해제 책임과 유효 기간을 명확히 함 |
| Evidence-based abstraction | 두 번째 concrete consumer에서 반복 책임을 확인한 뒤 공통화 | 추측에 기반한 interface와 migration 비용을 줄임 |

## 현재 보류한 구조

| 구조 | 보류 이유 | 다시 검토할 조건 |
| --- | --- | --- |
| Unreal식 `UObject`·Actor·Component 복제 | Reflection, editor, serialization과 gameplay composition 요구가 아직 없음 | Object 책임 조합과 serialization 요구가 실제로 생김 |
| 독립 `World` | 현재 Scene은 rendering domain data만으로 충분함 | Update, animation, physics와 object lifetime을 함께 관리해야 함 |
| 자동 생성 subsystem framework | Application이 소수 service의 lifetime을 명확히 조립할 수 있음 | 서로 다른 Application·World·Window lifetime service가 반복됨 |
| 범용 renderer interface와 factory | CPU RayTracing 외 실제 renderer contract가 없음 | 두 번째 renderer의 선택·교체 사용 사례가 구현됨 |
| Render Graph | 현재 pass와 temporary resource dependency가 단순함 | Multipass와 compute dependency가 수동 관리 범위를 넘음 |
| Cross-API RHI | 초기 지원 backend가 D3D11 하나임 | 두 번째 graphics API가 roadmap과 검증 대상이 됨 |
| 범용 job system | Correctness 우선의 single-thread 실행으로 시작함 | 여러 module에서 scheduling과 cancellation 요구가 반복됨 |

## Unreal Engine과의 관계

Unreal Engine module은 runtime 기능과 library를 독립 단위로 캡슐화하고 dependency graph와 load/unload 경계를 제공한다. GraphicsLab은 현재 단일 Visual Studio project를 유지하지만 source responsibility와 public dependency를 같은 방향으로 제한한다.

Unreal Engine subsystem은 Engine, GameInstance, World와 LocalPlayer 같은 상위 객체의 lifetime에 맞춰 생성·해제된다. GraphicsLab은 별도 subsystem framework를 만들지 않고 Application, Window, Scene과 frame lifetime을 먼저 명시하며 반복되는 service가 생길 때 해당 원칙을 적용한다.

Unreal Engine Asset Manager는 asset ID, discovery, loading과 memory lifetime을 관리한다. GraphicsLab은 executable-relative path로 시작하고 cache, unload와 streaming consumer가 생길 때 stable ID와 registry로 확장한다.

Unreal Engine Render Dependency Graph는 pass와 resource dependency를 기록해 scheduling, temporary resource lifetime과 validation을 관리한다. GraphicsLab은 multipass와 compute dependency가 실제로 복잡해지기 전에는 명시적인 pass 순서와 concrete D3D11 resource ownership을 유지한다.

## 공식 참고 자료

- [Unreal Engine Modules](https://dev.epicgames.com/documentation/en-us/unreal-engine/unreal-engine-modules)
- [Programming Subsystems](https://dev.epicgames.com/documentation/unreal-engine/programming-subsystems-in-unreal-engine)
- [Gameplay Framework](https://dev.epicgames.com/documentation/en-us/unreal-engine/gameplay-framework-in-unreal-engine)
- [Asset Management](https://dev.epicgames.com/documentation/en-us/unreal-engine/asset-management-in-unreal-engine)
- [Render Dependency Graph](https://dev.epicgames.com/documentation/en-us/unreal-engine/render-dependency-graph-in-unreal-engine)

공식 자료는 책임 분리 원칙을 이해하기 위한 참고이며 GraphicsLab의 구현 완료 증거가 아니다. Unreal Engine과 동일한 type, lifetime, reflection, editor, serialization, RHI와 rendering feature parity를 주장하지 않는다.

## 변경 기준

- 보류 구조의 도입 조건을 충족하면 concrete 사용 사례와 dependency 영향을 먼저 기록한다.
- 현재 구조가 기능 구현을 막는다는 이유만으로 즉시 범용 abstraction을 추가하지 않고 가장 작은 변경안을 비교한다.
- 채택 또는 보류 판정이 바뀌면 이 decision과 Architecture 정본을 함께 갱신한다.
- Unreal Engine version과 내부 구현 변화에 관계없이 GraphicsLab이 채택한 책임 원칙은 이 repository의 검증 결과로 판단한다.

## 관련 문서

- [GraphicsLab Architecture](../../../Portfolio_GraphicsLab/ARCHITECTURE.md)
- [Reconstruction Strategy](graphics-lab-reconstruction-strategy.md)
- [WU-GraphicsLab-Architecture](../work-units/WU-GraphicsLab-Architecture.md)
