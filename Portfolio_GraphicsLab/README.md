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

## 구현 축

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

WU-R0에서는 renderer 구현 전 canonical project, dependency와 asset path contract를 구성한다. `Rendering/RayTracing`은 이후 milestone에서 초기 기능부터 단계적으로 재구성한다. graphics pipeline과 다른 rendering 기능은 같은 project의 별도 구현 축으로 추가한다.

## 상태

- Canonical scaffold: WU-R0 구성 완료
- Debug/Release x64 build/run: 2026-08-11 현재 확인
- RayTracing reconstruction: 예정
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
- [Source Registry](../Docs/99_Legacy/source-registry.md)
