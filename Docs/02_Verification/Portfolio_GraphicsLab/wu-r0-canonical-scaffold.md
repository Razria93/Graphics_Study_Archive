# GraphicsLab WU-R0 Canonical Scaffold Verification

## 검증 범위

- 확인일: 2026-08-11
- Solution: `Portfolio_GraphicsLab/GraphicsLab.sln`
- Project: `GraphicsLab.vcxproj`
- Platform: x64
- Configuration: Debug, Release
- Toolset: MSVC v143
- C++ standard: C++17
- Windows SDK selector: `10.0`

renderer, window creation, DirectX11 presentation, RayTracing과 capture/result는 WU-R0 범위에 포함하지 않는다.

## Dependency restore

`vcpkg.json` manifest와 `x64-windows` triplet으로 다음 dependency를 project-local `vcpkg_installed`에 복원했다.

| Package | Version과 feature | 결과 |
| --- | --- | --- |
| `glm` | `1.0.2` | 성공 |
| `imgui` | `1.91.9`, `dx11-binding`, `win32-binding` | 성공 |
| `stb` | `2024-07-29#1` | 성공 |

manifest `builtin-baseline`은 local vcpkg registry의 `d1ff36c6520ee43f1a656c03cd6425c2974a449e`를 사용한다. user-wide classic installed package는 dependency version 기준으로 사용하지 않는다.

## Build 결과

| Configuration | Target | 결과 | Output |
| --- | --- | --- | --- |
| Debug x64 | Rebuild | 성공 | `x64/Debug/GraphicsLab.exe` |
| Release x64 | Rebuild | 성공 | `x64/Release/GraphicsLab.exe` |

source는 warning level 4와 warning-as-error로 compile한다. build log에서 compile/link warning은 발생하지 않았다.

## `pwsh.exe`와 app-local 처리

최초 manifest build는 link 뒤 vcpkg app-local target에서 `pwsh.exe`를 먼저 시도하고 Windows PowerShell fallback으로 완료해 최종 exit code 0을 반환했다.

현재 `glm`, `imgui`, `stb`는 static 또는 header-only dependency라 runtime DLL 수집이 필요하지 않다. project에 `VcpkgApplocalDeps=false`를 명시하고 Debug/Release를 다시 build했다. 이후 build에는 `pwsh.exe` 시도나 app-local warning이 없다.

runtime DLL dependency를 추가하면 app-local deployment를 다시 활성화하고 별도로 검증한다.

## Smoke run

| Configuration | CWD | Exit code | executable 옆 `Assets/README.md` |
| --- | --- | ---: | --- |
| Debug | repository root | 0 | 확인 |
| Debug | `x64/Debug` | 0 | 확인 |
| Release | repository root | 0 | 확인 |
| Release | `x64/Release` | 0 | 확인 |

application은 `GetModuleFileNameW`로 executable directory를 구하고 그 아래 `Assets`를 asset root로 사용한다. CWD가 달라도 동일한 asset root를 찾는 최소 계약을 확인했다.

## 남은 범위

- WU-R1에서 Win32 window와 DirectX11 presentation을 구현한다.
- shader를 추가할 때 executable-relative asset resolver를 실제 load path에 연결한다.
- `Rendering/RayTracing`은 이후 reconstruction milestone에서 추가한다.
- renderer output이 없으므로 capture/result는 제외 상태로 유지한다.
