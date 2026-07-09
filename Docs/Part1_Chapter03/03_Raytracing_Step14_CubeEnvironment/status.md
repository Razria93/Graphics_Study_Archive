# Status: 03_Raytracing_Step14_CubeEnvironment

| Item | Status | Note |
| --- | --- | --- |
| Raw reference | 확인 | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step14_CubeEnvironment` |
| Related raw note | 미확인 | cube environment 관련 raw note는 별도 확인 필요 |
| Code import | 완료 | selected project/source/HLSL files only |
| Environment asset import | 완료 | `skybox/`, `SaintPetersBasilica/`를 private archive 실행 확인용으로 포함 |
| Environment sampling | 완료 | `SaintPetersBasilica` 6면 이미지를 ray direction 기준으로 sampling |
| Runtime path fallback | 완료 | shader/resource 파일을 project folder와 repo root 기준에서 찾도록 보정 |
| Raw result/capture import | 제외 | raw result/capture/output files copied 없음 |
| Source comment cleanup | 완료 | source에는 실행 흐름에 필요한 최소 구조만 유지 |
| Debug x64 build | 성공 | MSBuild, warning 0 / error 0 |
| Release x64 build | 성공 | MSBuild, warning 0 / error 0 |
| Run verification | 성공 | 사용자 Debug/Release 실행 확인 |
| Capture | 보류 | 사용자 촬영 단계에서 진행 |
| Public readiness | 검토 필요 | environment asset 공개 전 attribution/license 확인 |

## Planned build command

```powershell
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' .\Part1_Chapter03\03_Raytracing_Step14_CubeEnvironment\03_Raytracing_Step14_CubeEnvironment.sln /p:Configuration=Debug /p:Platform=x64 /m
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' .\Part1_Chapter03\03_Raytracing_Step14_CubeEnvironment\03_Raytracing_Step14_CubeEnvironment.sln /p:Configuration=Release /p:Platform=x64 /m
```

## Verification notes

- Current archive import renders a basic cube environment by sampling `SaintPetersBasilica` cube faces.
- `skybox/` jpg/dds files and `SaintPetersBasilica/` jpg files are included for private archive execution checks.
- `SaintPetersBasilica/readme.txt` records Humus author and CC BY 3.0 license.
- `SaintPetersBasilica/image_blurring.py` helper script is excluded.
- raw Release x64 project has the same `D3D11CreateDeviceAndSwapChain` linker issue when `d3d11.lib` is missing from linker input.
- sandboxed build는 output directory 생성 권한 문제로 실패했으며, escalated MSBuild에서 Debug x64가 성공했습니다.
- Release x64는 raw project 설정에 `d3d11.lib`, `d3dcompiler.lib`, `dxgi.lib` 링크 의존성이 빠져 있어 처음 실패했고, archive project 설정 보정 후 성공했습니다.
- vcpkg applocal은 `pwsh.exe` 시도 후 Windows PowerShell fallback으로 완료되었습니다.
- 사용자 확인 기준으로 Debug/Release 실행이 정상 동작했습니다.

## Issue record

- 초기 archive Step14는 raw `Raytracer::Render()`가 비어 있는 scaffold 상태를 기준으로 이관되어 의미 있는 화면을 출력하지 못했습니다.
- raw에는 `skybox/`, `SaintPetersBasilica/` 리소스와 canvas texture 표시 파이프라인은 있었지만, CPU raytracer에서 environment image를 읽어 `pixels`에 기록하는 구현은 없었습니다.
- 리소스만 archive에 추가해도 출력이 바뀌지 않았던 원인은 `Texture` loading, cube face selection, UV sampling, `pixels` write path가 연결되어 있지 않았기 때문입니다.
- archive에서는 실행 가능한 결과물을 우선하기 위해 `SaintPetersBasilica` 6면 이미지를 sampling하는 최소 구현을 추가했습니다.
- raw Step14가 원래 어느 시점에서 어떤 의도로 비어 있었는지는 추후 사용자가 raw history/강의 맥락을 확인합니다.
