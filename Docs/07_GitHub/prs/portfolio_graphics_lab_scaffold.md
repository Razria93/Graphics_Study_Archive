# Portfolio GraphicsLab canonical scaffold와 build contract

## 요약

이 PR은 개인 graphics 구현을 장기적으로 확장할 루트 코드 폴더를 `Portfolio_GraphicsLab`으로 정의하고, 첫 reconstruction 작업 전에 필요한 canonical solution, dependency와 asset path contract를 구성한다.

기존 `Portfolio_RayTracer`는 전체 project명이 아니라 앞으로 추가할 `Rendering/RayTracing` 구현 축으로 재정의한다. 2025년 raw source와 media는 original development evidence로 보존하고 이 PR에는 bulk import하지 않는다.

## 범위

- `Portfolio_GraphicsLab/GraphicsLab.sln`과 C++17 x64 Debug/Release project 추가
- 최소 `wWinMain` application lifecycle과 executable-relative asset resolver 추가
- `glm`, `imgui`, `stb`를 선언하는 vcpkg manifest와 baseline 추가
- tracked `Assets`를 executable 옆으로 복사하는 MSBuild target 구성
- `Portfolio_RayTracer` current 문서 연결을 `Portfolio_GraphicsLab`으로 전환
- WU-R0 build/run 결과를 Verification 정본과 matrix에 반영
- renderer, DirectX11 presentation, RayTracing source와 capture/result는 후속 범위로 유지

## 주요 변경

- Solution, project와 executable identity를 `GraphicsLab`으로 통일한다.
- 초기 지원 범위를 C++17과 `x64-windows` Debug/Release로 제한한다.
- project-local `vcpkg_installed`에 manifest dependency를 복원하고 generated tree는 Git에서 제외한다.
- `GetModuleFileNameW`로 executable directory를 확인하고 그 아래 `Assets`를 runtime asset root로 사용한다.
- current working directory가 달라도 같은 asset root를 찾도록 repository root와 output directory에서 각각 smoke run한다.
- 현재 dependency가 static 또는 header-only이므로 불필요한 app-local DLL 수집을 `VcpkgApplocalDeps=false`로 비활성화한다.
- 역사적 PR, 감사와 closeout 기록의 `Portfolio_RayTracer` 명칭은 당시 snapshot으로 유지하고 current index, policy, Verification, Demo와 Work Unit 연결만 전환한다.

## 검증

- vcpkg manifest restore 성공
  - `glm 1.0.2`
  - `imgui 1.91.9` + `dx11-binding`, `win32-binding`
  - `stb 2024-07-29#1`
- Debug x64 rebuild 성공
- Release x64 rebuild 성공
- Debug/Release executable을 repository root CWD에서 실행해 exit code 0 확인
- Debug/Release executable을 각 output directory CWD에서 실행해 exit code 0 확인
- 두 configuration에서 executable 옆 `Assets/README.md` 복사 확인
- Markdown render, table, wrap validator 전체 통과
- Demo index, GitHub body와 Topic validator 통과
- 변경 파일 strict UTF-8, 상대 링크와 source Korean text 검사 통과
- user-specific absolute path와 stale `Portfolio_RayTracer` Markdown link 없음 확인
- generated build output과 `vcpkg_installed` ignore 확인
- `git diff --check origin/main...HEAD` 통과

## 미확인 / 제한

- Win32 window 생성과 DirectX11 device, swap chain, presentation은 포함하지 않는다.
- renderer, shader, texture와 `Rendering/RayTracing` source는 포함하지 않는다.
- WU-R0 executable은 asset contract를 검증한 뒤 화면 출력 없이 종료한다.
- renderer output이 없으므로 capture/result는 이 PR에서 제외한다.
- 기존 raw texture는 출처와 재배포 조건이 확인되지 않아 포함하지 않는다.
- runtime DLL dependency를 추가하면 vcpkg app-local deployment를 다시 활성화하고 검증해야 한다.
- original Git history가 없는 raw source를 과거 commit history처럼 표현하지 않는다.

## 문서

- 전체 진입점: [README](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-scaffold/README.md)
- GraphicsLab 안내: [Portfolio GraphicsLab README](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-scaffold/Portfolio_GraphicsLab/README.md)
- Build 기준: [GraphicsLab Build Guide](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-scaffold/Portfolio_GraphicsLab/BUILD.md)
- Project manifest: [vcpkg.json](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-scaffold/Portfolio_GraphicsLab/vcpkg.json)
- Asset resolver: [AssetPath.cpp](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-scaffold/Portfolio_GraphicsLab/Source/Asset/AssetPath.cpp)
- 검증 기록: [WU-R0 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-scaffold/Docs/02_Verification/Portfolio_GraphicsLab/wu-r0-canonical-scaffold.md)
- Demo 상태: [GraphicsLab Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-scaffold/Docs/03_Demos/Portfolio_GraphicsLab/demo-index.md)
- 전체 진행 상태: [Plan Progress](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-scaffold/Docs/07_GitHub/plan/plan-progress.md)

## 관련 이슈

- [Progress Issue #7](https://github.com/Razria93/Graphics_Study_Archive/issues/7)
- [Part1 Chapter03 Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12)
- [Closeout PR #39](https://github.com/Razria93/Graphics_Study_Archive/pull/39)

## 다음 단계

- WU-R1에서 Win32 window와 DirectX11 device, swap chain, render target을 구성한다.
- CPU framebuffer를 dynamic texture와 full-screen quad로 표시하는 presentation path를 구현한다.
- ImGui Win32/DX11 lifecycle과 executable-relative shader load를 검증한다.
- Window/presentation 기반을 먼저 마감한 뒤 `Rendering/RayTracing` reconstruction을 별도 milestone로 시작한다.
