# GraphicsLab Build Guide

이 문서는 WU-R0 canonical scaffold의 Windows x64 build와 smoke run 기준을 기록한다.

## 지원 범위

| 항목 | 기준 |
| --- | --- |
| Visual Studio | Visual Studio 2022와 MSVC v143 |
| Windows SDK | 설치된 Windows 10/11 SDK의 `10.0` 계열 |
| C++ standard | C++17 |
| Platform | x64 |
| Configuration | Debug, Release |
| Dependency | `vcpkg.json` manifest mode |

Win32 configuration은 지원하지 않는다. C++ language upgrade와 다른 platform 지원은 reconstruction과 분리한다.

## vcpkg 준비

vcpkg tool 자체는 repository 밖에 준비한다. project dependency와 registry 기준점은 [`vcpkg.json`](vcpkg.json)에 기록한다.

Visual Studio/MSBuild integration은 개발 환경에서 한 번 설정한다.

```powershell
vcpkg integrate install
```

manifest restore 결과는 `Portfolio_GraphicsLab/vcpkg_installed`에 생성되며 Git에 포함하지 않는다. user-wide classic installed tree는 dependency 목록이나 version 기준으로 사용하지 않는다.

## Build

Visual Studio Developer environment에서 다음 명령을 사용한다.

```powershell
msbuild Portfolio_GraphicsLab/GraphicsLab.sln /m /t:Build /p:Configuration=Debug /p:Platform=x64
msbuild Portfolio_GraphicsLab/GraphicsLab.sln /m /t:Build /p:Configuration=Release /p:Platform=x64
```

`msbuild`가 `PATH`에 없으면 Visual Studio Installer의 `vswhere.exe`로 `MSBuild.exe`를 찾는다. 개인 PC의 절대 설치 경로는 project file이나 tracked command에 고정하지 않는다.

build output은 다음 위치에 생성된다.

```text
Portfolio_GraphicsLab/x64/Debug/GraphicsLab.exe
Portfolio_GraphicsLab/x64/Release/GraphicsLab.exe
```

## Asset contract

tracked asset은 `Portfolio_GraphicsLab/Assets` 아래에 둔다. MSBuild는 build 뒤 이 구조를 executable 옆 `Assets`로 복사한다.

runtime code는 current working directory를 사용하지 않는다. `GetModuleFileNameW`로 executable directory를 구하고 그 아래 `Assets`를 asset root로 사용한다.

## Smoke run

WU-R0 executable은 asset root directory가 존재하면 `0`, 없으면 non-zero로 종료한다. repository root와 output directory를 각각 CWD로 사용해 같은 executable을 실행한다.

```powershell
$process = Start-Process `
    -FilePath Portfolio_GraphicsLab/x64/Debug/GraphicsLab.exe `
    -WorkingDirectory . `
    -Wait `
    -PassThru
$process.ExitCode

$process = Start-Process `
    -FilePath ./GraphicsLab.exe `
    -WorkingDirectory Portfolio_GraphicsLab/x64/Debug `
    -Wait `
    -PassThru
$process.ExitCode
```

Release도 같은 방식으로 확인한다. renderer가 추가되기 전까지 capture/result는 검증 대상이 아니다.

## Optional verification

repository validator는 compile/link와 별도 command로 실행한다. validator 또는 shell availability 문제를 build failure로 기록하지 않는다.

- compile/link와 vcpkg manifest restore 결과를 먼저 기록한다.
- WU-R0 dependency는 static 또는 header-only이므로 `VcpkgApplocalDeps=false`를 사용한다. runtime DLL dependency를 추가하는 milestone에서 app-local deployment를 다시 활성화하고 검증한다.
- source/Docs validator는 build 뒤 별도로 실행한다.
