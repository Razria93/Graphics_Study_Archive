# Import Plan: Part4 Chapter14-20

## Source / Target

- Primary raw source:
  - `C:\ComputerGraphics\Part4_HongLabGraphics`
- Reference-only raw source:
  - `C:\ComputerGraphics\Part4_HongLabGraphics_2`
  - `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics`
- Archive target:
  - `Part4_Chapter14-20`
- Docs target:
  - `Docs/Part4_Chapter14-20`
- Branch: `archive/part4`
- Import status: planning
- Build/run status: 미확인
- Public readiness: 검토 필요

## Part4 Working Goal

Part4는 `Examples` 단일 Visual Studio project 안에 `Ex1401`부터 `Ex2001`까지의 예제가 모여 있습니다. Part1-Part3처럼 예제별 solution을 그대로 옮기는 방식이 아니라, archive에서는 실행 단위와 문서 단위를 예제별로 분리하되 source/project 기준은 단일 project 구조를 유지할지 먼저 확인합니다.

1차 목표는 code import, asset selection, build/run 확인입니다. 소스 내부 장문 학습 메모 정리와 최종 portfolio 문서 품질 개선은 전체 code import 이후 2차 문서 정리 단계에서 진행합니다.

## Raw Folder Decision

| Raw folder | Import decision | Note |
| --- | --- | --- |
| `C:\ComputerGraphics\Part4_HongLabGraphics` | primary source | 대부분 예제 파일이 `_2`/`OriginalExamples`보다 확장되어 있고, 2025-11-15 이후 수정 흔적이 있음 |
| `C:\ComputerGraphics\Part4_HongLabGraphics_2` | reference-only snapshot | `OriginalExamples`와 거의 동일한 기준본. 일부 VS/project 관련 파일만 다름 |
| `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics` | original/reference baseline | 강의 기준 baseline 확인용. 직접 import 기준 아님 |

`Part4_HongLabGraphics`를 primary로 보는 이유:

- `Ex1401_Basic`부터 `Ex2001_GamePlay`까지 대부분의 핵심 예제 파일이 `_2` 대비 다른 hash를 가집니다.
- main raw 쪽 파일은 compute shader, fluid/smoke, foliage, PhysX, gameplay 예제에서 더 큰 구현량 또는 더 늦은 수정일을 보입니다.
- `_2`와 `OriginalExamples`는 매우 가까운 baseline/snapshot 성격입니다. 두 폴더 사이의 차이는 `AnimationClip.h`, `BasicVS.hlsl`, `DepthOnlyVS.hlsl`, `Ex1901_Physx.h`, `Ex2001_GamePlay.h`, `FluidSimulationCPU.h`, `Examples.vcxproj` 정도로 제한적입니다.

따라서 archive import는 `Part4_HongLabGraphics`를 기준으로 시작하고, build/run 실패 또는 의도 확인이 필요할 때 `_2`와 `OriginalExamples`를 비교합니다.

## Source Layout

Part4 raw source는 아래처럼 단일 project에 모여 있습니다.

```text
Part4_HongLabGraphics/
  Assets/
    Characters/
    Foliage/
    Textures/
    x/
  Examples/
    Examples.sln
    Examples.vcxproj
    Examples.vcxproj.filters
    Ex1401_Basic.cpp
    Ex1401_Basic.h
    Ex1401_CS.hlsl
    ...
    Ex2001_GamePlay.cpp
    Ex2001_GamePlay.h
```

`Examples/Examples/`, `.vs/`, `x64/` 같은 폴더는 Visual Studio/build output 성격이므로 archive import 대상이 아닙니다.

## Chapter / Example Inventory

| Range | Raw examples | Import decision | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- | --- |
| Ch14 | `Ex1401_Basic`-`Ex1408_BitonicSort` | archive 후보 | 미확인 | 검토 필요 | compute shader basics, blur, matrix/vector, structured buffer, indirect args, sort |
| Ch15 | `Ex1501_ParticleSystem`-`Ex1503_SphWater` | archive 후보 | 미확인 | 검토 필요 | particles, sprite fire, SPH water |
| Ch16 | `Ex1601_StableFluids`-`Ex1606_HybridWater` | archive 후보 | 미확인 | 검토 필요 | stable fluids, curl noise, cloud, smoke, hybrid water |
| Ch17 | `Ex1701_SkeletalAnimation` | archive 후보 | 미확인 | 검토 필요 | skeletal animation |
| Ch18 | `Ex1801_Tree`-`Ex1803_Landscape` | archive 후보 | 미확인 | 검토 필요 | tree, grass, landscape/ocean |
| Ch19 | `Ex1901_Physx` | archive 후보 | 미확인 | 검토 필요 | PhysX integration |
| Ch20 | `Ex2001_GamePlay` | archive 후보 | 미확인 | 검토 필요 | gameplay integration |

## Include Candidates

- `Examples.sln`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`
- `*.cpp`, `*.h`, `*.hlsl`, `*.hlsli`
- 실행에 필요한 selected asset
- `copy_dlls.py`는 실행 재현에 필요할 때만 검토합니다.

## Exclude / Defer

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `Examples/Examples/x64/`
- `*.user`
- `*.suo`
- `imgui.ini`
- `.clang-format`
- raw result/capture/video
- zip/archive asset 원본
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료

## Asset Policy

- `Assets/Characters`, `Assets/Foliage`, `Assets/Textures`, `Assets/x`는 통째로 복사하지 않습니다.
- 각 예제 source에서 실제로 읽는 runtime asset만 선별합니다.
- `.dds`, `.exr`, `.fbx`, `.hdr`는 repository LFS 규칙을 따릅니다.
- public repo로 옮기기 전에는 외부 asset source/license/attribution을 별도 검토합니다.

## Import Order

1. `Docs/Part4_Chapter14-20` scaffold 생성
2. `Ex1401_Basic` 기준으로 최소 project import 방식 확정
3. 단일 solution 유지 vs 예제별 project 분리 여부를 build 결과 기준으로 판단
4. Ch14 compute shader 예제부터 순차 import
5. 각 예제마다 source/project/shader/asset 최소 반영
6. build/run은 사용자가 확인하기 전까지 `미확인`으로 기록

## Project Import Decision

현재 판단은 `Examples` 단일 solution/project 구조를 유지하는 것입니다.

이유:

- raw `main.cpp`가 `Ex1401`부터 `Ex2001`까지 모든 예제 header를 include하고, command-line argument로 실행 예제를 선택합니다.
- raw `.vcxproj`가 모든 example source와 shared source를 하나의 executable로 빌드합니다.
- `Ex1401_Basic`만 분리하려면 `main.cpp`, `.vcxproj`, `.filters`에서 다른 예제 참조를 제거해야 하므로 raw와 archive 차이가 커집니다.
- Part4는 후속 예제들이 shared infrastructure를 많이 재사용하므로, 초기에 project를 잘라내면 이후 예제 import마다 project를 다시 크게 수정할 가능성이 높습니다.

따라서 1차 code import에서는 단일 project를 유지하고, 실행은 raw와 동일하게 command-line argument로 예제를 선택합니다. 예제별 문서와 status는 `Docs/Part4_Chapter14-20/<ExampleName>/` 아래에 분리합니다.

Part4 실행 확인 규칙:

- 예제 이름의 `Ex` 뒤 4자리 숫자를 command argument로 넘깁니다.
- Visual Studio에서는 project properties의 `Debugging > Command Arguments`에 값을 입력합니다.
- 예: `Ex1401_Basic`은 `1401`, `Ex1402_Blur`는 `1402`, `Ex2001_GamePlay`는 `2001`.
- Debug/Release를 확인할 때도 같은 command argument를 각각 설정하거나 유지했는지 확인합니다.

## Ex1401 Dependency Review

`Ex1401_Basic`은 compute shader가 back buffer UAV에 직접 쓰는 첫 compute shader 예제입니다.

핵심 파일:

- `Ex1401_Basic.cpp`
- `Ex1401_Basic.h`
- `Ex1401_CS.hlsl`
- `main.cpp`
- `Examples.sln`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

직접 include:

- `Ex1401_Basic.cpp`
  - `Ex1401_Basic.h`
  - `GeometryGenerator.h`
  - `GraphicsCommon.h`
- `Ex1401_Basic.h`
  - `AppBase.h`
  - `Model.h`

핵심 shared dependency:

- `AppBase.*`
- `D3D11Utils.*`
- `GraphicsCommon.*`
- `GraphicsPSO.*`
- `GeometryGenerator.*`
- `Model.*`, `ModelLoader.*`, `Mesh*.h`
- `Camera.*`
- `PostProcess.*`, `ImageFilter.*`
- `ConstantBuffers.h`, `Buffers.h`, `Vertex.h`

Shader/project 설정:

- `Ex1401_CS.hlsl`은 `FxCompile` 대상이며 Debug/Release x64 모두 `Compute`, shader model `5.0`으로 설정되어 있습니다.
- raw의 `Ex1401_Basic.cpp`, `Ex1401_Basic.h`, `main.cpp`, `.vcxproj`, `.filters`는 UTF-8 BOM이 있습니다.
- raw의 `Ex1401_CS.hlsl`은 UTF-8/UTF-16 BOM이 없습니다. HLSL/HLSLI BOM 없음 규칙을 유지합니다.
- raw `.vcxproj`의 personal vcpkg include path는 archive에서 제거하고, `VCPKG_ROOT`가 설정된 경우에만 `$(VCPKG_ROOT)\installed\x64-windows\include`를 참조하도록 보정했습니다.
- 단일 project 전체를 빌드하므로 `Ex1901_PhysX`, `Ex2001_GamePlay`, `ModelLoader`의 PhysX/Assimp header dependency가 `Ex1401` build 확인에도 영향을 줄 수 있습니다.

Raw comparison:

- `Ex1401_Basic.cpp`, `Ex1401_Basic.h`, `Ex1401_CS.hlsl`은 `Part4_HongLabGraphics`와 `_2`/`OriginalExamples` 사이 hash가 다릅니다.
- `_2`와 `OriginalExamples`의 `Ex1401` 관련 파일 hash는 같습니다.
- 따라서 `Ex1401`도 main raw 작업본을 archive 기준으로 사용합니다.

## Ex1402 Dependency Review

`Ex1402_Blur`는 separable blur를 compute shader로 수행하는 예제입니다.

핵심 파일:

- `Ex1402_Blur.cpp`
- `Ex1402_Blur.h`
- `Ex1402_BlurXCS.hlsl`
- `Ex1402_BlurYCS.hlsl`
- `Ex1402_BlurXGroupCacheCS.hlsl`
- `Ex1402_BlurYGroupCacheCS.hlsl`
- `Ex1402_BlurXPS.hlsl`
- `Ex1402_BlurYPS.hlsl`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1402`를 `Ex1402_Blur`로 매핑합니다.
- `Ex1402`는 별도 runtime asset을 요구하지 않고, blur 입력용 staging texture를 코드에서 생성합니다.
- `Ex1402_BlurXCS.hlsl`, `Ex1402_BlurYCS.hlsl`, `Ex1402_BlurXGroupCacheCS.hlsl`, `Ex1402_BlurYGroupCacheCS.hlsl`은 Debug/Release x64 모두 Compute, shader model `5.0`입니다.
- `Ex1402_BlurXPS.hlsl`, `Ex1402_BlurYPS.hlsl`은 Debug/Release x64 모두 Pixel, shader model `5.0`입니다.
- archive의 `Ex1402` core files는 primary raw hash와 일치합니다.
- 일부 `Ex1402` 파일은 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Ex1403 Dependency Review

`Ex1403_MatVecMult`는 matrix-vector multiplication을 compute shader로 수행하고 CPU 결과와 비교하는 예제입니다.

핵심 파일:

- `Ex1403_MatVecMult.cpp`
- `Ex1403_MatVecMult.h`
- `Ex1403_MatVecMultCS.hlsl`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1403`을 `Ex1403_MatVecMult`로 매핑합니다.
- `Ex1403`은 별도 runtime asset을 요구하지 않고, matrix/vector 데이터를 코드에서 생성합니다.
- `Ex1403_MatVecMultCS.hlsl`은 Debug/Release x64 모두 Compute, shader model `5.0`입니다.
- archive의 `Ex1403` core files는 primary raw hash와 일치합니다.
- `Ex1403_MatVecMult.cpp`와 `Ex1403_MatVecMultCS.hlsl`은 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.
- Debug/Release 모두 `Error GPU 0`, CPU/GPU result checksum 일치, exit code `0`으로 확인되었습니다.

## Ex1404 Dependency Review

`Ex1404_StructuredBuffer`는 compute shader가 structured buffer의 particle position을 갱신하고, vertex shader가 같은 buffer를 읽어 point list를 렌더링하는 예제입니다.

핵심 파일:

- `Ex1404_StructuredBuffer.cpp`
- `Ex1404_StructuredBuffer.h`
- `Ex1404_StructuredBufferCS.hlsl`
- `Ex1404_StructuredBufferVS.hlsl`
- `Ex1404_StructuredBufferPS.hlsl`
- `StructuredBuffer.h`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1404`를 `Ex1404_StructuredBuffer`로 매핑합니다.
- `Ex1404`는 별도 runtime asset을 요구하지 않고, particle 데이터를 코드에서 생성합니다.
- `Ex1404_StructuredBufferCS.hlsl`은 Debug/Release x64 모두 Compute, shader model `5.0`입니다.
- `Ex1404_StructuredBufferVS.hlsl`은 Debug/Release x64 모두 Vertex, shader model `5.0`입니다.
- `Ex1404_StructuredBufferPS.hlsl`은 Debug/Release x64 모두 Pixel, shader model `5.0`입니다.
- archive의 `Ex1404` core files는 primary raw hash와 일치합니다.
- 대부분의 `Ex1404` core files는 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Ex1405 Dependency Review

`Ex1405_ConsumeAppendBuffer`는 consume/append structured buffer의 counter 기반 particle update를 확인하는 예제입니다.

핵심 파일:

- `Ex1405_ConsumeAppendBuffer.cpp`
- `Ex1405_ConsumeAppendBuffer.h`
- `Ex1405_ConsumeAppendCS.hlsl`
- `StructuredBuffer.h`
- `Buffers.h`
- `Ex1404_StructuredBufferVS.hlsl`
- `Ex1404_StructuredBufferPS.hlsl`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1405`를 `Ex1405_ConsumeAppendBuffer`로 매핑합니다.
- `Ex1405`는 별도 runtime asset을 요구하지 않고, particle 데이터를 코드에서 생성합니다.
- `Ex1405_ConsumeAppendCS.hlsl`은 Debug/Release x64 모두 Compute, shader model `5.0`입니다.
- `Ex1404_StructuredBufferVS.hlsl`은 Debug/Release x64 모두 Vertex, shader model `5.0`입니다.
- `Ex1404_StructuredBufferPS.hlsl`은 Debug/Release x64 모두 Pixel, shader model `5.0`입니다.
- archive의 `Ex1405` core files는 primary raw hash와 일치합니다.
- 대부분의 `Ex1405` core files는 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Ex1406 Dependency Review

`Ex1406_DensityField`는 compute shader로 density texture를 감쇠시키고, structured buffer particle을 geometry shader sprite로 렌더링해 density field를 누적하는 예제입니다.

핵심 파일:

- `Ex1406_DensityField.cpp`
- `Ex1406_DensityField.h`
- `Ex1406_DensitySourcingCS.hlsl`
- `Ex1406_DensityDissipationCS.hlsl`
- `Ex1406_SpriteGS.hlsl`
- `Ex1406_SpritePS.hlsl`
- `Ex1404_StructuredBufferVS.hlsl`
- `StructuredBuffer.h`
- `Texture2D.h`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1406`을 `Ex1406_DensityField`로 매핑합니다.
- `Ex1406`은 별도 runtime asset을 요구하지 않고, particle/density 데이터를 코드에서 생성합니다.
- `Ex1406_DensitySourcingCS.hlsl`은 Debug/Release x64 모두 Compute, shader model `5.0`입니다.
- `Ex1406_DensityDissipationCS.hlsl`은 Debug/Release x64 모두 Compute, shader model `5.0`입니다.
- `Ex1406_SpriteGS.hlsl`은 Debug/Release x64 모두 Geometry, shader model `5.0`입니다.
- `Ex1406_SpritePS.hlsl`은 Debug/Release x64 모두 Pixel, shader model `5.0`입니다.
- archive의 `Ex1406` core files는 primary raw hash와 일치합니다.
- `Ex1406_DensityField.cpp`, `Ex1406_DensitySourcingCS.hlsl`은 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Ex1407 Dependency Review

`Ex1407_IndirectArguments`는 `DrawInstancedIndirect()`와 indirect argument buffer를 확인하는 예제입니다. 시각 출력은 `Ex1406`의 density/sprite rendering 흐름을 재사용하고, draw call 인자를 GPU buffer에서 읽는 부분이 핵심입니다.

핵심 파일:

- `Ex1407_IndirectArguments.cpp`
- `Ex1407_IndirectArguments.h`
- `D3D11Utils.cpp`
- `D3D11Utils.h`
- `Ex1406_DensitySourcingCS.hlsl`
- `Ex1406_DensityDissipationCS.hlsl`
- `Ex1406_SpriteGS.hlsl`
- `Ex1406_SpritePS.hlsl`
- `Ex1404_StructuredBufferVS.hlsl`
- `StructuredBuffer.h`
- `Texture2D.h`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1407`을 `Ex1407_IndirectArguments`로 매핑합니다.
- `Ex1407`은 별도 runtime asset을 요구하지 않고, particle/density 데이터를 코드에서 생성합니다.
- `Ex1407`은 `Ex1406`의 density/sprite shader를 재사용합니다.
- `CreateIndirectArgsBuffer()`는 `D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS` misc flag로 indirect argument buffer를 생성합니다.
- archive의 `Ex1407_IndirectArguments.cpp`/`.h`는 primary raw hash와 일치합니다.
- `Ex1407_IndirectArguments.cpp`/`.h`는 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Ex1408 Dependency Review

`Ex1408_BitonicSort`는 CPU/GPU bitonic sort 결과를 비교하는 console test 예제입니다. 화면 렌더링보다는 `Initialize()`에서 element count별 정렬 테스트를 수행하고 `OK` 결과를 확인하는 것이 핵심입니다.

핵심 파일:

- `Ex1408_BitonicSort.cpp`
- `Ex1408_BitonicSort.h`
- `Ex1408_BitonicSortCS.hlsl`
- `BitonicSort.cpp`
- `BitonicSort.h`
- `BitonicSortCS.hlsl`
- `StructuredBuffer.h`
- `Timer.h`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1408`을 `Ex1408_BitonicSort`로 매핑합니다.
- `Ex1408`은 별도 runtime asset을 요구하지 않고, sort input 데이터를 코드에서 생성합니다.
- `Ex1408_BitonicSortCS.hlsl`은 Debug/Release x64 모두 Compute로 설정되어 있습니다.
- `BitonicSortCS.hlsl`은 Debug/Release x64 모두 Compute, shader model `5.0`입니다.
- archive의 `Ex1408`/`BitonicSort` core files는 primary raw hash와 일치합니다.
- `Ex1408_BitonicSort.cpp`, `BitonicSort.cpp`는 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Ex1501 Dependency Review

`Ex1501_ParticleSystem`은 CPU에서 particle simulation을 수행하고, structured buffer와 geometry shader sprite rendering으로 particle을 출력하는 예제입니다.

핵심 파일:

- `Ex1501_ParticleSystem.cpp`
- `Ex1501_ParticleSystem.h`
- `Ex1501_ParticleSystemVS.hlsl`
- `Ex1501_ParticleSystemGS.hlsl`
- `Ex1501_ParticleSystemPS.hlsl`
- `GraphicsCommon.*`
- `D3D11Utils.*`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1501`을 `Ex1501_ParticleSystem`으로 매핑합니다.
- `Ex1501`은 별도 runtime asset을 요구하지 않고, particle 데이터를 코드에서 생성합니다.
- `Ex1501_ParticleSystemVS.hlsl`은 Debug/Release x64 모두 Vertex, shader model `5.0`입니다.
- `Ex1501_ParticleSystemGS.hlsl`은 Debug/Release x64 모두 Geometry, shader model `5.0`입니다.
- `Ex1501_ParticleSystemPS.hlsl`은 Debug/Release x64 모두 Pixel, shader model `5.0`입니다.
- archive의 `Ex1501` core files는 primary raw hash와 일치합니다.
- `Ex1501_ParticleSystem.cpp`, `Ex1501_ParticleSystemVS.hlsl`은 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Ex1502 Dependency Review

`Ex1502_SpriteFireEffect`는 CPU particle update와 textured sprite rendering으로 fire-like particle effect를 출력하는 예제입니다.

핵심 파일:

- `Ex1502_SpriteFireEffect.cpp`
- `Ex1502_SpriteFireEffect.h`
- `Ex1502_SpriteFireEffectVS.hlsl`
- `Ex1502_SpriteFireEffectPS.hlsl`
- `Ex1501_ParticleSystemGS.hlsl`
- `Assets/Textures/flare0.dds`
- `GraphicsCommon.*`
- `D3D11Utils.*`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1502`를 `Ex1502_SpriteFireEffect`로 매핑합니다.
- `Ex1502`는 runtime asset으로 `../Assets/Textures/flare0.dds`를 읽습니다.
- `Ex1502_SpriteFireEffectVS.hlsl`은 Debug/Release x64 모두 Vertex, shader model `5.0`입니다.
- `Ex1501_ParticleSystemGS.hlsl`은 Debug/Release x64 모두 Geometry, shader model `5.0`입니다.
- `Ex1502_SpriteFireEffectPS.hlsl`은 Debug/Release x64 모두 Pixel, shader model `5.0`입니다.
- archive의 `Ex1502` core files는 primary raw hash와 일치합니다.
- archive의 `flare0.dds`는 primary raw asset hash와 일치하며 repository LFS attributes 대상입니다.
- `Ex1502_SpriteFireEffect.cpp`, `Ex1502_SpriteFireEffectVS.hlsl`은 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Ex1503 Dependency Review

`Ex1503_SphWater`는 CPU SPH simulation과 sprite particle rendering으로 물 입자 움직임을 확인하는 예제입니다.

핵심 파일:

- `Ex1503_SphWater.cpp`
- `Ex1503_SphWater.h`
- `Ex1503_SphWaterVS.hlsl`
- `Ex1503_SphWaterPS.hlsl`
- `Ex1501_ParticleSystemGS.hlsl`
- `SphSimulation.cpp`
- `SphSimulation.h`
- `SphKernels.h`
- `GraphicsCommon.*`
- `D3D11Utils.*`
- `main.cpp`
- `Examples.vcxproj`
- `Examples.vcxproj.filters`

확인 내용:

- `main.cpp`는 command argument `1503`을 `Ex1503_SphWater`로 매핑합니다.
- `Ex1503`은 별도 runtime asset을 요구하지 않고, SPH particle 데이터를 코드에서 생성합니다.
- `Ex1503_SphWaterVS.hlsl`은 Debug/Release x64 모두 Vertex, shader model `5.0`입니다.
- `Ex1501_ParticleSystemGS.hlsl`은 Debug/Release x64 모두 Geometry, shader model `5.0`입니다.
- `Ex1503_SphWaterPS.hlsl`은 Debug/Release x64 모두 Pixel, shader model `5.0`입니다.
- archive의 `Ex1503`/`SphSimulation` core files는 primary raw hash와 일치합니다.
- `Ex1503_SphWater.cpp`, `SphSimulation.cpp`는 `_2`/`OriginalExamples`와 hash가 다르므로, archive 기준은 `Part4_HongLabGraphics` primary raw입니다.

## Per-example Finish Check

- raw result/capture/build output 미포함
- `.vcxproj` XML namespace 정상
- HLSL/HLSLI BOM 없음
- shader include 파일이 build 대상이 아닌 include/document file로 남아 있는지 확인
- selected asset hash raw와 일치
- LFS 대상 asset은 pointer로 stage되는지 확인
- raw와 다르게 바꾼 project/source 설정은 `status.md`에 이유 기록
- Debug/Release build/run은 사용자가 확인하기 전까지 `미확인`으로 기록

## Current Next Action

1. 다음 확인 대상은 `Ex1503_SphWater`입니다.
2. Visual Studio `Debugging > Command Arguments`에 `1503`을 설정합니다.
3. 사용자 Debug x64 build/run 확인을 요청합니다.
4. 사용자 Release x64 build/run 확인을 요청합니다.
5. build 실패 시 `VCPKG_ROOT`, Assimp, PhysX include/dependency 설정을 먼저 확인합니다.
