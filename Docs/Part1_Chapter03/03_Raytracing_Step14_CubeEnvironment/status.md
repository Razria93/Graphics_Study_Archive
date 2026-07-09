# Status: 03_Raytracing_Step14_CubeEnvironment

| Item | Status | Note |
| --- | --- | --- |
| Raw reference | 확인 | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step14_CubeEnvironment` |
| Related raw note | 미확인 | cube environment 관련 raw note는 별도 확인 필요 |
| Code import | 완료 | selected project/source/HLSL files only |
| Environment asset import | 보류 | `skybox/`, `SaintPetersBasilica/`는 현재 source에서 직접 사용하지 않음 |
| Raw result/capture import | 제외 | raw result/capture/output files copied 없음 |
| Source comment cleanup | 완료 | source에는 실행 흐름에 필요한 최소 구조만 유지 |
| Debug x64 build | 성공 | MSBuild, warning 0 / error 0 |
| Release x64 build | 성공 | MSBuild, warning 0 / error 0 |
| Run verification | 미확인 | 사용자 실행 확인 전 |
| Capture | 보류 | 사용자 촬영 단계에서 진행 |
| Public readiness | 검토 필요 | environment asset 공개 전 attribution/license 확인 |

## Planned build command

```powershell
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' .\Part1_Chapter03\03_Raytracing_Step14_CubeEnvironment\03_Raytracing_Step14_CubeEnvironment.sln /p:Configuration=Debug /p:Platform=x64 /m
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' .\Part1_Chapter03\03_Raytracing_Step14_CubeEnvironment\03_Raytracing_Step14_CubeEnvironment.sln /p:Configuration=Release /p:Platform=x64 /m
```

## Verification notes

- Current archive import is a buildable scaffold, not a full cube environment renderer.
- `SaintPetersBasilica/readme.txt` records Humus author and CC BY 3.0 license.
- sandboxed build는 output directory 생성 권한 문제로 실패했으며, escalated MSBuild에서 Debug x64가 성공했습니다.
- Release x64는 raw project 설정에 `d3d11.lib`, `d3dcompiler.lib`, `dxgi.lib` 링크 의존성이 빠져 있어 처음 실패했고, project 설정 보정 후 성공했습니다.
- vcpkg applocal은 `pwsh.exe` 시도 후 Windows PowerShell fallback으로 완료되었습니다.
- run 확인 전까지 tracking 문서의 실행 상태는 `미확인`으로 유지합니다.
