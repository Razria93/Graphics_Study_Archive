# Status: 03_Raytracing_Step8_Shadow_Square

| Item | Status | Note |
| --- | --- | --- |
| Raw reference | 확인 | `C:\ComputerGraphics\Part1_Chapter03\03_Raytracing_Step8_Shadow_Square` |
| Related raw note | 확인 | `Chapter03_Raytracing_Step8_Shadow.md` |
| Code import | 완료 | selected project/source/HLSL files only |
| Raw result/capture import | 제외 | raw result/capture/output files copied 없음 |
| Source comment cleanup | 완료 | source에는 실행 흐름에 필요한 최소 구조만 유지 |
| Debug x64 build | 성공 | MSBuild, warning 0 / error 0 |
| Release x64 build | 성공 | MSBuild, warning 0 / error 0 |
| Run verification | 성공 | 사용자가 Debug/Release 실행 정상 확인 |
| Capture | 보류 | 사용자 촬영 단계에서 진행 |
| Public readiness | 검토 필요 | private archive 기준 반영, public 공개 전 별도 검토 |

## Build command used

```powershell
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' .\Part1_Chapter03\03_Raytracing_Step8_Shadow_Square\03_Raytracing_Step8_Shadow.sln /p:Configuration=Debug /p:Platform=x64 /m
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe' .\Part1_Chapter03\03_Raytracing_Step8_Shadow_Square\03_Raytracing_Step8_Shadow.sln /p:Configuration=Release /p:Platform=x64 /m
```

## Verification notes

- First sandboxed build failed because MSBuild could not create output directories under the workspace.
- Escalated MSBuild runs completed successfully.
- vcpkg applocal first attempted `pwsh.exe`, then fell back to Windows PowerShell and completed.
- Generated build folders remain ignored by `.gitignore`.
