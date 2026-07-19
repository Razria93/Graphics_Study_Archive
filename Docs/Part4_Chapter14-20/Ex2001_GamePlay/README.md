# Ex2001 GamePlay

## 목적

`Ex2001_GamePlay`는 Part4의 gameplay integration 예제로, 앞선 장에서 만든 character animation, PhysX rigid body simulation, billboard fire effect, PBR material, HDRI lighting, post processing을 하나의 scene에서 함께 확인합니다.

핵심은 그래픽스 기능을 따로 보여주는 데서 끝내지 않고, 캐릭터 애니메이션과 물리 객체, 이펙트 렌더링을 한 update/render loop 안에서 동기화하는 것입니다.

## 실행 정보

| 항목 | 값 |
| --- | --- |
| Solution | `Part4_Chapter14-20/Examples.sln` |
| Project | `Examples` |
| Command argument | `2001` |
| Primary source | `C:\ComputerGraphics\Part4_HongLabGraphics\Examples` |
| Reference source | `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics_v03\Examples` |
| Runtime asset | Mixamo character/animation, PBR ground textures, HDRI cubemap, fire shader resources |

Part4는 단일 `Examples.exe`에서 command argument로 예제를 선택합니다. Debug/Release x64 모두 command argument `2001`로 확인합니다.

## 핵심 구성

| 파일 | 역할 |
| --- | --- |
| `Ex2001_GamePlay.cpp/.h` | gameplay scene setup, character animation update, PhysX stack simulation, fireball input/spawn setup |
| `main.cpp` | command argument `2001` mapping |
| `SkinnedMeshModel.*`, `AnimationClip.h` | character mesh와 animation clip 재생 |
| `BillboardModel.*`, `GameExplosionPS.hlsl` | fireball billboard/effect path |
| `Model.*`, `GeometryGenerator.*` | ground mesh와 PhysX box render model 생성 |
| `AppBase.*` | 공통 camera, GUI, render/post-process loop |

## 구현 포인트

- `ReadAnimationFromFile()`로 `character.fbx`, `FightingIdleOnMichelle2.fbx`, `Fireball.fbx`를 읽어 character animation data를 구성합니다.
- `SkinnedMeshModel::UpdateAnimation()`으로 매 프레임 캐릭터 애니메이션을 갱신합니다.
- `CreateStack()`에서 PhysX dynamic body와 렌더링용 box `Model`을 함께 생성합니다.
- PhysX actor pose를 읽어 `m_objects`의 world transform에 반영합니다.
- `G` 입력 시 Fireball animation clip으로 전환하고, GUI에서 지정한 notify frame에 `BillboardModel`과 `Graphics::volumetricFirePS`를 사용하는 PhysX dynamic fireball을 생성합니다.
- `Fireball` GUI에서 캐릭터 기준 spawn offset, projectile velocity, notify frame을 조절할 수 있습니다.
- PhysX actor 수와 렌더링 object 수가 어긋난 경우에는 동기화 loop에서 범위를 벗어나지 않도록 guard를 둡니다.
- material, skybox, post effects, camera GUI는 기존 Part4 공통 UI를 재사용합니다.

## Runtime Asset

Ex2001은 기존 `character.fbx` 외에 `FightingIdleOnMichelle2.fbx`, `Fireball.fbx` animation clip을 추가로 요구합니다.

- `Assets/Characters/Mixamo/character.fbx`
- `Assets/Characters/Mixamo/FightingIdleOnMichelle2.fbx`
- `Assets/Characters/Mixamo/Fireball.fbx`
- `Assets/Characters/Mixamo/Ch03_1001_Diffuse.png`
- `Assets/Characters/Mixamo/Ch03_1001_Normal.png`

Release 실행 중 두 animation FBX가 누락되어 asset load failure가 발생했고, primary raw에서 필요한 두 FBX만 선별 반영했습니다. raw result/capture/build output은 포함하지 않습니다.

## 비교 메모

- archive의 `Ex2001_GamePlay.cpp/.h`는 primary raw를 기준으로 가져온 뒤, 강의 TODO였던 fireball gameplay input, notify-frame spawn, actor/object 직접 동기화를 최소 범위로 보강했습니다.
- 최신 자료실본 `Part4_HongLabGraphics_v03`의 Ex2001은 주석/포맷 정리와 `PX_RELEASE` 매크로 정의, PhysX include path 차이가 있습니다.
- 현재 archive는 vcpkg include 구조에 맞춰 `physx/PxPhysicsAPI.h`를 유지합니다.
- 최신 v03 차이는 실행 문제가 있을 때만 최소 범위로 검토합니다.

## 확인 포인트

- Debug/Release x64에서 build/run 되는지 확인합니다.
- command argument가 `2001`로 설정되어 있는지 확인합니다.
- 캐릭터가 정상 형태로 표시되고 애니메이션이 재생되는지 확인합니다.
- `G` 키 입력 시 fireball animation으로 전환되고, `Fireball > Notify Frame`에 도달했을 때 projectile이 생성되는지 확인합니다.
- `Fireball > Spawn Offset`과 `Velocity` 조절이 발사 위치/방향에 반영되는지 확인합니다.
- PhysX box stack이 중력과 충돌에 따라 움직이는지 확인합니다.
- PBR ground, HDRI lighting, post processing GUI가 기존 Part4 예제 흐름을 깨지 않는지 확인합니다.
- PhysX/Assimp/runtime DLL 오류가 발생하면 vcpkg runtime DLL, working directory, project dependency 설정을 먼저 확인합니다.
