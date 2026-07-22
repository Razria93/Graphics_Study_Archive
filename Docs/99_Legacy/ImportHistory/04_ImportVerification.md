# Import Verification

이 문서는 raw 예제를 archive로 반영한 뒤 수행할 파일, project, shader, asset 무결성 검증 기준입니다.

## 역할

- import 후 정적 검증과 무결성 검증의 기준 문서입니다.
- 포함/제외 정책은 [Import Policy](01_ImportPolicy.md)를 따릅니다.
- 작업 순서는 [Import Workflow](02_ImportWorkflow.md)를 따릅니다.
- 작업 전후 체크 항목은 [Import Checklist](03_ImportChecklist.md)를 따릅니다.

## 적용 시점

- 예제 source/project/shader/asset을 archive에 반영한 직후
- build/run 확인을 사용자에게 요청하기 전
- commit guide를 제안하기 전

## 원칙

- `.sln`, `.vcxproj`, `.vcxproj.filters`, `.hlsl`, `.hlsli`, image/binary asset은 일괄 문자열 치환이나 주석 제거 대상에서 제외합니다.
- source comment 정리는 `.cpp`, `.h` 중심으로만 수행하고, project/XML/shader/binary 파일은 raw 구조를 우선 유지합니다.
- 실행 편의를 위한 project 설정 변경은 먼저 raw와 비교하고, 필요성이 명확할 때만 status 문서에 이유를 남깁니다.

## 필수 체크

| 항목                   | 확인 방법                                                                                    | 실패 시 조치                                   |
| -------------------- | ---------------------------------------------------------------------------------------- | ----------------------------------------- |
| XML namespace        | `.vcxproj`, `.filters`의 `xmlns="http://schemas.microsoft.com/developer/msbuild/2003"` 확인 | raw에서 project 파일의 namespace를 다시 대조하고 복구   |
| HLSL BOM             | `.hlsl`, `.hlsli` 첫 3 bytes가 `EF BB BF`가 아닌지 확인                                          | UTF-8 no BOM으로 저장                         |
| HLSL 첫 문자            | shader 파일 첫 non-empty 문자가 `#`, `struct`, `cbuffer`, `Texture2D` 등 정상 코드인지 확인             | 파일 앞쪽의 깨진 문자, 잘못 들어간 binary/text 변환 흔적 제거 |
| Binary asset         | image/texture/model 파일 크기와 hash를 raw와 비교                                                 | raw에서 binary copy로 다시 복구                  |
| Project item type    | asset/shader 항목이 raw와 불필요하게 달라졌는지 확인                                                     | raw 구조로 되돌리거나 변경 이유를 status에 기록           |
| LFS pointer          | LFS 대상 binary가 pointer로 stage되는지 확인                                                      | `.gitattributes`와 `git lfs ls-files` 확인   |
| Excluded local files | `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `.suo`, `imgui.ini` 제외 확인                 | tracked 대상에서 제거                           |
| Static diff          | `git diff --check`                                                                       | whitespace/error 수정                       |

## PowerShell 확인 예시

```powershell
# XML namespace check
rg -n 'xmlns="http://schemas\.microsoft\.com/developer/msbuild/2003"' `
  Part2_Chapter05-08/07_Modeling_Step4_Cylinder/*.vcxproj `
  Part2_Chapter05-08/07_Modeling_Step4_Cylinder/*.filters

# HLSL/HLSLI BOM check
$shaderFiles = Get-ChildItem Part2_Chapter05-08/07_Modeling_Step4_Cylinder -Include *.hlsl,*.hlsli -File
foreach ($file in $shaderFiles) {
  $bytes = [System.IO.File]::ReadAllBytes($file.FullName)
  $first3 = (($bytes[0..2] | ForEach-Object { $_.ToString('X2') }) -join ' ')
  if ($first3 -eq 'EF BB BF') { "BOM FOUND: $($file.FullName)" }
}

# Raw/archive texture hash comparison example
Get-FileHash C:\ComputerGraphics\Part2_Chapter05-08\07_Modeling_Step4_Cylinder\crate2_diffuse.png
Get-FileHash C:\Graphics_Study_Archive\Part2_Chapter05-08\07_Modeling_Step4_Cylinder\crate2_diffuse.png

# Final static checks
git diff --check
git status --short --branch
```

## Known Failure Case: Step4 Cylinder

발생한 문제:

- `.vcxproj`, `.filters`의 XML namespace가 `xmlns="http:`처럼 잘려 Visual Studio project load가 실패했습니다.
- HLSL 파일에 BOM 또는 잘못된 선행 byte가 들어가 `error X3000: Illegal character in shader file`가 발생했습니다.
- texture asset이 text encoding 변환을 거치며 binary가 손상되어 `stbi_load()`가 실패했습니다.
- 실행 편의를 위해 `Image` item을 `Content + CopyToOutputDirectory`로 바꿨지만, raw project 구조를 우선하도록 되돌렸습니다.

원인:

- `http://` 안의 `//`를 주석 시작처럼 다룬 문자열 처리 실수
- shader/binary 파일을 text file처럼 다룬 처리 실수
- raw project와 archive project의 차이를 충분히 좁히기 전에 편의성 보정을 먼저 적용한 판단

재발 방지:

- XML/project/shader/binary 파일은 일괄 주석 제거 대상에서 제외합니다.
- 예제 작업 종료 전 이 문서의 필수 체크를 수행합니다.
- raw와 다르게 바꾼 project 설정은 반드시 status 문서에 이유와 검증 상태를 남깁니다.
