# Import Manifest: Part1_Chapter01-02

> 이 문서는 import 당시 포함/제외 판단 기록입니다.
> 최신 build/run/capture 상태의 기준 문서가 아닙니다.


이 문서는 `C:\ComputerGraphics\Part1_Chapter01-02` raw/reference 자료를 `C:\Graphics_Study_Archive\Part1_Chapter01-02` archive 폴더로 선별 정리하기 위한 manifest입니다.

`01_DX11InitAndImGui`와 `02_Bloom`은 manifest 기준으로 code/project files를 선별 반영했습니다. `02_Bloom`의 기본 입력 이미지 1개는 private archive 실행 확인용으로 반영했고, raw 결과 이미지는 생성 경로 확인 전까지 복사하지 않습니다.

## Source / Target

| 항목 | 값 |
| --- | --- |
| Source | `C:\ComputerGraphics\Part1_Chapter01-02` |
| Target | `Part1_Chapter01-02` |
| Import status | 01/02 부분 반영 |
| Public readiness | 검토 필요 |
| Build/run status | 미확인 |
| 우선 예제 | `01_DX11InitAndImGui`, `02_Bloom` |

## Raw 구조 요약

| Raw path | 성격 | 판단 |
| --- | --- | --- |
| `01_DX11InitAndImGui/` | DX11 window, ImGui setup 예제 | 부분 반영 |
| `02_Bloom/` | image processing/bloom 예제 | 부분 반영 |
| `Convolutions_00.png` | convolution 설명/참고 이미지 후보 | 검토 필요 |
| `Convolutions_01.gif` | convolution 설명/참고 GIF 후보 | 검토 필요 |
| `Convolutions_02.gif` | convolution 설명/참고 GIF 후보 | 검토 필요 |
| `Convolutions_03.gif` | convolution 설명/참고 GIF 후보 | 검토 필요 |
| `Kernel.png` | kernel 설명/참고 이미지 후보 | 검토 필요 |

## Include candidates

### `01_DX11InitAndImGui`

| 후보 | 이유 | 상태 |
| --- | --- | --- |
| `01_DX11InitAndImGui.sln` | Visual Studio solution | 반영 완료 |
| `01_DX11InitAndImGui.vcxproj` | Visual Studio project | 반영 완료 |
| `01_DX11InitAndImGui.vcxproj.filters` | project filters | 반영 완료 |
| `Example.cpp` | 예제 source | 반영 완료 |
| `Example.h` | 예제 header | 반영 완료 |
| `main.cpp` | application entry/window setup | 반영 완료 |
| `PS.hlsl` | pixel shader | 반영 완료 |
| `VS.hlsl` | vertex shader | 반영 완료 |

### `02_Bloom`

| 후보 | 이유 | 상태 |
| --- | --- | --- |
| `02_Bloom.sln` | Visual Studio solution | 반영 완료 |
| `02_Bloom.vcxproj` | Visual Studio project | 반영 완료 |
| `02_Bloom.vcxproj.filters` | project filters | 반영 완료 |
| `Example.cpp` | bloom/image processing source | 반영 완료 |
| `Example.h` | bloom/image processing header | 반영 완료 |
| `main.cpp` | application entry/window setup | 반영 완료 |
| `PS.hlsl` | pixel shader | 반영 완료 |
| `VS.hlsl` | vertex shader | 반영 완료 |
| `image_1.JPG` | project image item | 제외 |
| `image_1_360.JPG` | code에서 기본 입력으로 사용하는 image 후보 | private archive 반영 / public 검토 필요 |
| `image_2.JPG` | project image item | 검토 필요 |
| `image_2_360.JPG` | project image item | 검토 필요 |
| `image_3.JPG` | project image item | 검토 필요 |

## Exclude patterns

다음 항목은 archive로 복사하지 않습니다.

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`
- `01_DX11I.068b66ab/`
- `02_Bloom/02_Bloom/`
- `02_Bloom/result/`
- `02_Bloom/result.png`
- `02_Bloom/raytraced.png`
- `02_Bloom/image_1_bloom.png`
- `Convolutions_*.gif`
- `Convolutions_*.png`
- `Kernel.png`

## 확인한 경로/의존성

- `01_DX11InitAndImGui.vcxproj`는 `Example.cpp`, `main.cpp`, `Example.h`, `PS.hlsl`, `VS.hlsl`를 project item으로 참조합니다.
- archive로 복사한 `01_DX11InitAndImGui.vcxproj`와 `.sln`에서 raw 절대 경로 참조는 발견되지 않았습니다.
- raw `02_Bloom.vcxproj`는 `Example.cpp`, `main.cpp`, `Example.h`, `PS.hlsl`, `VS.hlsl`, `image_1.JPG`, `image_1_360.JPG`, `image_2.JPG`, `image_2_360.JPG`, `image_3.JPG`를 project item으로 참조했습니다.
- archive `02_Bloom.vcxproj`에서는 기본 입력 이미지 `image_1_360.JPG`만 project item으로 유지했습니다.
- archive `02_Bloom/Example.h`는 `image_1_360.JPG`를 기본 입력으로 시도하되, 파일이 없으면 synthetic fallback image를 생성합니다.
- `02_Bloom/Example.cpp`에서 `stbi_load`와 `stbi_write_png`를 사용합니다.
- build/run은 아직 직접 확인하지 않았습니다.

## Unresolved risks

| 항목 | 내용 | 상태 |
| --- | --- | --- |
| 강의 기반 코드 범위 | 학습 코드 성격이므로 archive 포함은 private 기준으로만 검토 | 검토 필요 |
| 입력 이미지 출처 | `image_1_360.JPG`는 private archive 실행 확인용으로 포함. public 공개 전 출처/라이선스 검토 필요 | 검토 필요 |
| 생성 결과물 | `result/`, `result.png`, `raytraced.png`, `image_1_bloom.png`는 raw 결과물로 보이며 새 capture 기준과 분리 필요 | 제외 |
| root 설명 이미지/GIF | `Convolutions_*`, `Kernel.png`는 출처/재배포 가능성 확인 전까지 제외 | 제외 |
| build output/local state | `.vs/`, `x64/`, `.user`, `imgui.ini` 존재 | 제외 |
| 경로 의존성 | `01_DX11InitAndImGui`, `02_Bloom` project item은 상대 경로 기준으로 확인됨. 실제 build는 미확인 | 부분 확인 |

## Next action

1. `01_DX11InitAndImGui`와 `02_Bloom`을 Visual Studio에서 `Debug x64`로 빌드할 수 있는지 확인합니다.
2. 빌드/실행 결과를 `Docs/03_Verification/build-run-matrix.md`에 기록한다.
3. `02_Bloom` raw image assets은 출처/라이선스 확인 전까지 `검토 필요`로 둡니다.
4. 직접 build/run 전까지 `Docs/03_Verification/build-run-matrix.md`의 상태는 `미확인`으로 유지한다.
