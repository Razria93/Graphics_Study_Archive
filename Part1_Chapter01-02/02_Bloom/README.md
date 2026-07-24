# 02_Bloom

## Overview

`02_Bloom`은 CPU에서 이미지 기반 bloom 후처리를 계산하고, 계산된 픽셀 데이터를 DirectX11 dynamic texture로 업로드해 화면에 표시하는 예제다. 밝은 영역을 threshold로 분리하고 blur를 반복 적용한 뒤 원본 이미지와 합성하는 기본 bloom 흐름을 확인한다.

이 예제는 GPU multi-pass bloom pipeline이 아니라 CPU image processing 결과를 DirectX11 렌더링 파이프라인에 연결하는 구조다. 따라서 bloom 개념과 dynamic texture upload 흐름을 함께 설명하는 데 초점을 둔다.

## Key Concepts

| 개념 | 설명 |
| --- | --- |
| Bloom | 밝은 영역을 blur한 뒤 원본에 더해 빛 번짐을 만드는 후처리 효과다. |
| Bright-pass | threshold를 기준으로 bloom에 참여할 밝은 픽셀만 분리한다. |
| Gaussian blur | 밝은 영역을 주변 픽셀로 확산시켜 부드러운 glow를 만든다. |
| Dynamic texture | CPU에서 계산한 픽셀 배열을 GPU shader resource로 업로드한다. |
| Full-screen quad | 처리된 texture를 화면 전체에 표시하는 렌더링 단위다. |

## Code Map

| 파일 | 역할 |
| --- | --- |
| `Example.cpp` | 이미지 로드, blur, bloom 합성, PNG 저장 로직 |
| `Example.h` | DirectX11 초기화, dynamic texture 생성, update/render 흐름 |
| `main.cpp` | Win32 window와 render loop 구성 |
| `VS.hlsl` | full-screen quad vertex shader |
| `PS.hlsl` | texture sampling pixel shader |
| `image_1_360.JPG` | 입력 이미지 |

## Processing Flow

1. `Image::ReadFromFile()`이 입력 이미지를 float RGBA 픽셀 배열로 읽는다.
2. 이미지 로드에 실패하면 fallback image를 만든다.
3. `Image::Bloom()`이 threshold 기준으로 밝은 영역을 분리한다.
4. `GaussianBlur5()`를 반복 적용해 밝은 영역을 확산시킨다.
5. blur 결과를 원본 이미지에 weight로 더해 최종 bloom 결과를 만든다.
6. `WritePNG()`가 결과 이미지를 `result.png`로 저장한다.
7. `Example::Initialize()`가 swap chain, shader, dynamic texture, SRV를 구성한다.
8. `Example::Update()`가 `Map/Unmap`으로 CPU 픽셀 데이터를 GPU texture에 업로드한다.
9. `Example::Render()`가 full-screen quad로 texture를 화면에 표시한다.

## Build And Run

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| Solution | 확인 | `02_Bloom.sln` |
| Debug x64 build | 확인 | MSBuild 17.14로 `x64/Debug/02_Bloom.exe` 생성 확인 |
| Debug x64 run | 확인 | 실행 후 5초 이상 유지, `result.png` 생성, 종료 코드 0 |
| Release x64 build/run | 확인 | `x64/Release/02_Bloom.exe` 생성과 실행 확인 |
| Capture | 보류 | `result.png`는 생성됐지만 워터마크/권리 검토 전까지 tracked capture/result로 승격하지 않음 |

## Demo Points

- 원본 이미지와 bloom 결과의 밝은 영역 확산 차이를 보여준다.
- threshold와 blur 반복 횟수가 bloom 강도에 미치는 영향을 설명한다.
- CPU에서 계산한 결과가 DirectX11 texture로 업로드되어 화면에 표시되는 흐름을 보여준다.

## Limitations

- GPU shader 기반 multi-pass bloom pipeline은 아니다.
- HDR render target, tone mapping, emissive material 기반 bloom은 다루지 않는다.
- Debug/Release x64 build와 run은 확인했다. 다만 `result.png`에는 강의/출처 표기가 포함되어 public capture/result 승격은 보류한다.

## Related Docs

- Topic: `../../Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md`
- Verification: `../../Docs/02_Verification/Part1_Chapter01-02/verification-index.md`
- Demo: `../../Docs/03_Demos/Part1_Chapter01-02/demo-index.md`
