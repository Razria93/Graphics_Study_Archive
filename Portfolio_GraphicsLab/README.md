# Portfolio GraphicsLab

`Portfolio_GraphicsLab`은 RayTracing부터 graphics pipeline과 후속 rendering 기능까지 단계적으로 확장하는 개인 graphics 구현의 루트 코드 폴더다.

첫 구현 축은 사용자가 2025년에 바닥부터 구현한 software ray tracer다. 당시 Git history는 남아 있지 않지만 단계별 raw/reference code, 실행 영상과 refactoring 전후 자료를 original development evidence로 보존한다. 이 저장소의 Git history는 해당 자료를 검증하며 canonical source로 재구성하는 과정이다.

## Project Identity

| 항목 | 값 |
| --- | --- |
| Solution | `GraphicsLab.sln` |
| Project | `GraphicsLab.vcxproj` |
| Executable | `GraphicsLab.exe` |
| MSBuild RootNamespace | `GraphicsLab` |
| C++ standard | C++17 |
| 초기 platform | `x64-windows` Debug/Release |
| Dependency | vcpkg manifest mode |

## Architecture 진입점

프로젝트의 module, ownership, coordinate와 Part1 reconstruction 순서는 [ARCHITECTURE.md](ARCHITECTURE.md)를 정본으로 사용한다. original implementation은 직접 import하지 않고 [Reconstruction Strategy](../Docs/04_WorkLogs/decisions/graphics-lab-reconstruction-strategy.md)에 따라 기능 단위로 검증하며 재구성한다.

## 계획한 구현 축

```text
GraphicsLab
├── Assets
└── Source
    ├── Application
    ├── Asset
    ├── Core
    ├── Platform
    └── Rendering
        └── RayTracing
```

WU-R0에서는 renderer 구현 전 canonical project, dependency와 asset path contract를 구성했다. `Rendering/RayTracing`은 WU-R1부터 WU-R14까지 presentation, math, primary ray, intersection, shading, sampling과 recursive effect 순서로 재구성한다. graphics pipeline과 다른 rendering 기능은 실제 두 번째 consumer가 생길 때 같은 project의 별도 구현 축으로 추가한다.

## 상태

- Canonical scaffold: WU-R0 구성 완료
- Debug/Release x64 build/run: 2026-08-11 현재 확인
- Architecture와 Part1 roadmap: WU-A0 사용자 검수 전
- RayTracing reconstruction: WU-R1부터 순차 진행 예정
- Renderer capture/result: WU-R0 제외, rendering milestone부터 확인

## Asset와 공개 범위

- 기존 raw texture는 출처와 재배포 조건이 확인되지 않아 canonical/public tree에 포함하지 않는다.
- renderer milestone에서는 직접 제작하거나 재배포 가능한 replacement asset을 사용한다.
- raw/reference code, historical output과 local development media는 직접 import하지 않는다.
- `.vs`, build output, `.user`, `imgui.ini`와 vcpkg generated tree는 Git에 포함하지 않는다.

## 관련 문서

- [Verification](../Docs/02_Verification/Portfolio_GraphicsLab/verification-index.md)
- [Demo Index](../Docs/03_Demos/Portfolio_GraphicsLab/demo-index.md)
- [Ray Tracing Topics](../Docs/01_Topics/RayTracing/README.md)
- [Reconstruction Strategy](../Docs/04_WorkLogs/decisions/graphics-lab-reconstruction-strategy.md)
- [Original Evidence Review](../Docs/04_WorkLogs/reviews/graphics-lab-original-evidence.md)
- [Architecture WorkLog](../Docs/04_WorkLogs/work-units/WU-GraphicsLab-Architecture.md)
- [Source Registry](../Docs/99_Legacy/source-registry.md)
