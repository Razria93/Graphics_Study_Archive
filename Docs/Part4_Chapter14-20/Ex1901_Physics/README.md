# Ex1901 Physics

## 목적

`Ex1901_PhysX`는 Chapter 19 physics integration 예제로, PhysX rigid body simulation 결과를 DirectX 렌더링 객체의 world transform에 반영하는 흐름을 확인합니다.

핵심은 렌더링용 `Model`과 물리 시뮬레이션용 `PxRigidDynamic`을 따로 만들고, 매 프레임 PhysX scene을 simulate/fetch한 뒤 actor의 global pose를 렌더링 객체에 동기화하는 것입니다.

## 실행 정보

| 항목 | 값 |
| --- | --- |
| Solution | `Part4_Chapter14-20/Examples.sln` |
| Project | `Examples` |
| Command argument | `1901` |
| Primary source | `C:\ComputerGraphics\Part4_HongLabGraphics\Examples` |
| Reference source | `C:\ComputerGraphics\OriginalExamples\Part4_HongLabGraphics_v03\Examples` |
| Runtime asset | 기존 PBR/HDRI asset 재사용 |

Part4는 단일 `Examples.exe`에서 command argument로 예제를 선택합니다. Debug/Release x64 모두 command argument `1901`로 확인합니다.

## 핵심 구성

| 파일 | 역할 |
| --- | --- |
| `Ex1901_Physx.cpp/.h` | PhysX foundation/scene/material 생성, rigid body stack 생성, simulation 결과를 render model에 동기화 |
| `main.cpp` | command argument `1901` mapping |
| `AppBase.*` | 공통 render loop, camera, GUI, cubemap/post-processing |
| `Model.*` | PhysX actor와 대응되는 렌더링 객체 |
| `GeometryGenerator.*` | box mesh 생성 |

## 구현 포인트

- `PxCreateFoundation`, `PxCreatePhysics`, `createScene`으로 PhysX runtime을 초기화합니다.
- `PxCreatePlane`으로 ground plane을 만들고, `PxRigidDynamic` box stack을 생성합니다.
- 각 dynamic actor와 대응되는 `Model`을 `m_objects`에 저장합니다.
- 매 프레임 `gScene->simulate()`와 `gScene->fetchResults()`를 호출합니다.
- `PxShapeExt::getGlobalPose()`로 물리 actor의 transform을 읽고 `Model::UpdateWorldRow()`에 반영합니다.

## 비교 메모

- archive의 `Ex1901_Physx.cpp/.h`는 primary raw와 동일합니다.
- 최신 자료실본 `Part4_HongLabGraphics_v03`의 Ex1901은 주석/포맷 정리와 `PX_RELEASE` 매크로 정의, PhysX include path 차이가 있습니다.
- 현재 archive는 vcpkg include 구조에 맞춰 `physx/PxPhysicsAPI.h`를 유지합니다.
- 최신 v03 차이는 실행 문제가 있을 때만 최소 범위로 검토합니다.

## 확인 포인트

- Debug/Release x64에서 build/run 되는지 확인합니다.
- command argument가 `1901`로 설정되어 있는지 확인합니다.
- 박스 stack이 중력에 따라 떨어지고 충돌하는지 확인합니다.
- 카메라 조작과 기본 GUI가 기존 Part4 예제 흐름을 깨지 않는지 확인합니다.
- PhysX DLL 또는 include/link 문제가 발생하면 vcpkg/PhysX runtime DLL, working directory, project dependency 설정을 먼저 확인합니다.
