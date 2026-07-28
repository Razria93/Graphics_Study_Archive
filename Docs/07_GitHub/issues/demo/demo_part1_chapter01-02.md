# Demo Issue - Part1 Chapter01-02 Visual And Implementation Guide

## 요약

이 문서는 `Part1_Chapter01-02`의 데모 자료를 모아 보여주는 공개용 Demo Issue 본문이다. PR 본문은 요약만 유지하고, 시각 자료와 구현 하이라이트는 이 문서에서 설명한다.

## 핵심 목표

- Chapter01-02의 시각 결과를 한눈에 확인할 수 있게 한다.
- 각 파일이 무엇을 보여주는지 명확히 설명한다.
- 결과를 만든 구현 하이라이트와 핵심 코드 위치를 빠르게 추적할 수 있게 한다.

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | `Docs/_assets/captures/part1_chapter01-02_02_bloom_input.jpg` | bloom 처리 전 입력 이미지. 밝은 구체와 배경 대비를 보여준다. |
| Result screenshot | `Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png` | bloom 처리 후 결과 이미지. 밝은 영역 확산(glow) 결과를 보여준다. |
| Result image | `Part1_Chapter01-02/02_Bloom/result.png` | 실행 중 생성되는 결과 파일. `_assets` 비교 이미지의 원본 결과다. |
| Video | 없음 | 현재 Chapter01-02는 정적 input/result 비교로 목적을 충족하므로 video를 사용하지 않는다. |

## 시각 정보

### 02_Bloom Original Input

밝은 영역 분리(bright-pass) 이전 입력 상태를 보여준다.

![02_Bloom Original Input](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/_assets/captures/part1_chapter01-02_02_bloom_input.jpg?raw=true)

### 02_Bloom Bloom Result

Gaussian blur 반복 후 원본에 합성된 최종 glow 결과를 보여준다.

![02_Bloom Bloom Result](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png?raw=true)

## 구현 하이라이트

### 구현 목표

- CPU에서 bloom 후처리 결과를 계산한다.
- 계산된 pixel buffer를 DirectX11 dynamic texture로 업로드한다.
- full-screen quad 렌더링으로 input/result 비교 가능한 화면을 제공한다.

### 처리 흐름

1. 입력 이미지 로드(`Image::ReadFromFile`) 또는 fallback 이미지 생성
2. bright-pass로 bloom 대상 픽셀 분리
3. Gaussian blur 반복 적용
4. blur 결과를 원본에 합성해 result 생성
5. `Map/Unmap`으로 GPU texture에 업로드
6. pixel shader sampling으로 화면 표시

### Key Code Map

| 파일                                        | 핵심 역할                                              |
| ----------------------------------------- | -------------------------------------------------- |
| `Part1_Chapter01-02/02_Bloom/Example.cpp` | bloom 계산(분리, blur, 합성), result image 저장            |
| `Part1_Chapter01-02/02_Bloom/Example.h`   | DirectX11 초기화, dynamic texture upload, render loop |
| `Part1_Chapter01-02/02_Bloom/PS.hlsl`     | 최종 texture sampling 출력                             |
| `Part1_Chapter01-02/02_Bloom/VS.hlsl`     | full-screen quad vertex 처리                         |

## 핵심 로직 의사코드

### 1) Bloom 합성 핵심

밝은 영역 추출, blur 반복, 원본 합성의 구조를 C++ 스타일 의사코드로 요약한다.

```cpp
// Pseudo C++: 구조 설명용 요약
void BloomPseudo(float threshold, int repeatCount, float weight)
{
    auto original = currentPixels;

    for (auto& pixel : currentPixels) {
        const float luma = Dot(
            pixel.rgb,
            {0.2126f, 0.7152f, 0.0722f}
        );
        if (luma < threshold) {
            pixel.rgb = {0.0f, 0.0f, 0.0f};
        }
    }

    for (int i = 0; i < repeatCount; ++i) {
        GaussianBlur5(currentPixels);
    }

    for (size_t i = 0; i < currentPixels.size(); ++i) {
        const auto bloom = original[i].rgb + currentPixels[i].rgb * weight;
        currentPixels[i].rgb = Clamp01(bloom);
        currentPixels[i].a = original[i].a;
    }
}
```

원본 코드: [Example.cpp#L212-L255](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/Example.cpp#L212-L255)

### 2) CPU -> GPU 업로드 핵심

Map/Unmap과 RowPitch 보정을 포함한 업로드 절차를 C++ 스타일 의사코드로 요약한다.

```cpp
// Pseudo C++: 구조 설명용 요약
void UploadCanvasTexturePseudo()
{
    auto mapped = MapWriteDiscard(canvasTexture);
    if (!mapped.ok) {
        return;
    }

    const size_t srcRowBytes = canvasWidth * sizeof(Vec4);
    const size_t dstRowBytes = mapped.rowPitch;

    for (int y = 0; y < canvasHeight; ++y) {
        auto* srcRow =
            cpuBufferBase + y * srcRowBytes;
        auto* dstRow =
            mapped.base + y * dstRowBytes;
        CopyBytes(dstRow, srcRow, srcRowBytes);
    }

    Unmap(canvasTexture);
}
```

원본 코드: [Example.h#L258-L275](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/Example.h#L258-L275)

## 검증 상태

- Build/Run: `01_DX11InitAndImGui`, `02_Bloom` Debug/Release x64 성공
- Capture/Result: `02_Bloom` input/result 확보

## 구현 범위와 한계

- `02_Bloom`은 CPU image processing 결과를 DirectX11 dynamic texture로 표시하는 예제다.
- GPU multi-pass bloom, HDR render target, tone mapping, emissive material 기반 bloom은 다루지 않는다.

## 관련 문서

- Progress Issue: #7
- PR: #8 (Draft)
- Example README: `Part1_Chapter01-02/02_Bloom/README.md`
- Topic: `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md`
- Verification: `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`
- Demo Index: `Docs/03_Demos/Part1_Chapter01-02/demo-index.md`
