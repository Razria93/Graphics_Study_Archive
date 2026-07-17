# Ex1701 SkeletalAnimation

## 목적

`Ex1701_SkeletalAnimation`은 skinned mesh와 skeletal animation clip을 로드해서 character animation을 재생하는 예제입니다. Part4의 compute/simulation 예제 흐름에서 animation chapter로 넘어가는 첫 예제이며, mesh bone hierarchy, animation clip sampling, skinned vertex rendering, simple state transition을 한 화면에서 확인합니다.

## 실행 기준

| 항목 | 값 |
| --- | --- |
| Executable | `Part4_Chapter14-20/x64/<Config>/Examples.exe` |
| Command argument | `1701` |
| Working directory | `Part4_Chapter14-20` |
| Runtime asset | Mixamo FBX/textures, PBR ground textures, HDRI cubemap |
| Build/run status | 미확인 |
| Public readiness | 검토 필요 |

확인할 동작:

- Mixamo character가 화면에 표시되고 skeletal animation이 재생되는지 확인합니다.
- idle/walk/dance 계열 animation clip이 로드되어 state 변화나 loop 동작이 깨지지 않는지 확인합니다.
- ground plane, mirror/reflection, skybox/IBL 조명이 함께 렌더링되는지 확인합니다.
- GUI의 material, mirror, post processing, env map 항목이 표시되는지 확인합니다.
- Debug/Release x64 모두 command argument `1701`로 확인합니다.

## 핵심 흐름

1. `main.cpp`가 command argument `1701`을 `Ex1701_SkeletalAnimation`으로 매핑합니다.
2. `Ex1701_SkeletalAnimation::Initialize()`에서 HDRI cubemap, ground PBR material, Mixamo character model과 animation clips를 준비합니다.
3. `SkinnedMeshModel`과 `SkeletalMeshActor`가 skeleton, bone transforms, animation clip sampling, draw call을 관리합니다.
4. `Update()`에서 animation state와 actor transform을 갱신합니다.
5. `Render()`에서 skybox, ground, mirror/reflection, animated character를 렌더링합니다.

## 주요 파일

| 파일 | 역할 |
| --- | --- |
| `Ex1701_SkeletalAnimation.cpp/.h` | 예제 entry, scene setup, animation state, GUI |
| `AnimationClip.h` | animation clip sampling data |
| `SkinnedMeshModel.h` | skinned model loading/rendering wrapper |
| `SkeletalMeshActor.h` | animated actor transform/state wrapper |
| `BasicVS/PS` 계열 shared shader path | skinned mesh, PBR, mirror, skybox rendering |
| `main.cpp` | command argument `1701` mapping |
| `Examples.vcxproj` | source/header registration |

## Runtime Asset

이번 예제는 실행을 위해 아래 asset만 선별 반영합니다. raw result, capture, intermediate output은 포함하지 않습니다.

| 경로 | 용도 |
| --- | --- |
| `Assets/Characters/Mixamo/character.fbx` | base skinned character model |
| `Assets/Characters/Mixamo/CatwalkIdle.fbx` | idle animation clip |
| `Assets/Characters/Mixamo/CatwalkIdleToWalkForward.fbx` | transition animation clip |
| `Assets/Characters/Mixamo/CatwalkWalkForward.fbx` | walk animation clip |
| `Assets/Characters/Mixamo/CatwalkWalkStop.fbx` | stop animation clip |
| `Assets/Characters/Mixamo/BreakdanceFreezeVar2.fbx` | dance/free pose animation clip |
| `Assets/Characters/Mixamo/Ch03_1001_Diffuse.png` | character diffuse texture |
| `Assets/Characters/Mixamo/Ch03_1001_Normal.png` | character normal texture |
| `Assets/Textures/PBR/stringy-marble-ue/*.png` | ground PBR textures |
| `Assets/Textures/Cubemaps/HDRI/clear_puresky*.dds` | skybox/IBL cubemap textures |

`.fbx`와 `.dds`는 repo LFS 추적 대상입니다. `.png` texture는 현재 LFS 대상이 아니므로, public 공개 전 asset license/source와 repo 용량을 별도로 검토합니다.

## Import 메모

- `Ex1701_SkeletalAnimation.cpp/.h`, `AnimationClip.h`, `SkinnedMeshModel.h`, `SkeletalMeshActor.h`, `main.cpp`는 primary raw와 hash가 일치합니다.
- `Examples.vcxproj`와 `Examples.vcxproj.filters`에는 Ex1701 source/header 항목이 등록되어 있습니다.
- Ex1701은 별도 Ex1701 전용 HLSL 파일을 추가하지 않고, shared skinned/PBR shader path를 사용합니다.
- public 공개 전 Mixamo character/animation, PBR texture, HDRI cubemap의 license/source 검토가 필요합니다.
