# 02_Bloom

## Overview

`02_Bloom`은 CPU에서 이미지 기반 bloom 후처리를 계산하고, 계산된 픽셀 데이터를 DirectX11 dynamic texture로 업로드해 화면에 표시하는 예제다. 밝은 영역을 threshold로 분리하고 blur를 반복 적용한 뒤 원본 이미지와 합성하는 기본 bloom 흐름을 확인한다.

이 예제는 GPU multi-pass bloom pipeline이 아니라 CPU image processing 결과를 DirectX11 렌더링 파이프라인에 연결하는 구조다. 따라서 bloom 개념과 dynamic texture upload 흐름을 함께 설명하는 데 초점을 둔다.

## 실행 진입점

- Solution: `02_Bloom.sln`
- Application entry: `main.cpp`
- CPU bloom: `Example.cpp`
- DirectX11 upload/render: `Example.h`
- Shader: `VS.hlsl`, `PS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| `Example.cpp` | 이미지 로드, blur, bloom 합성, PNG 저장 로직 |
| `Example.h` | DirectX11 초기화, dynamic texture 생성, update/render 흐름 |
| `main.cpp` | Win32 window와 render loop 구성 |
| `VS.hlsl` | full-screen quad vertex shader |
| `PS.hlsl` | texture sampling pixel shader |
| `image_1_360.JPG` | ChatGPT 생성 이미지 기반 입력 이미지 |

## 구현 요약

입력 이미지를 CPU에서 처리한 뒤 dynamic texture로 업로드하고 full-screen quad로
표시한다. Bright-pass, blur, 합성, `RowPitch`를 고려한 upload의 전체 연결은
[02_Bloom 상세 Demo](../../Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)를
기준으로 확인한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Solution | 존재 | `02_Bloom.sln` |
| Debug x64 build/run | 성공 | 상세 근거는 Verification으로 위임 |
| Release x64 build/run | 성공 | 상세 근거는 Verification으로 위임 |
| Capture/Result | 확보 | original input과 bloom result 비교 이미지 연결 |

## Capture/Result

### Bloom Result

![Bloom result](../../Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png)

Input/result 비교와 결과 해석은 상세 Demo로 연결한다.

## Limitations

- GPU shader 기반 multi-pass bloom pipeline은 아니다.
- HDR render target, tone mapping, emissive material 기반 bloom은 다루지 않는다.
- CPU 처리 구조이므로 실시간 고해상도 post-processing 성능을 대표하지 않는다.

## Related Docs

- [Topic](../../Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- [Verification](../../Docs/02_Verification/Part1_Chapter01-02/verification-index.md)
- [Detailed Demo](../../Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)
- [Demo Index](../../Docs/03_Demos/Part1_Chapter01-02/demo-index.md)
