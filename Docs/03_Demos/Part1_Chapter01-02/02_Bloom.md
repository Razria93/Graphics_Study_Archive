# 02_Bloom Demo

## 목적

`02_Bloom`은 CPU에서 bright-pass, Gaussian blur, 원본 합성을 수행한 뒤 결과
픽셀을 DirectX11 dynamic texture로 업로드하는 흐름을 보여준다. 입력과 결과를
함께 제시해 기본 bloom 효과와 CPU 결과의 GPU 표시 경로를 연결한다.

## 책임 범위

- CPU bloom 구현 선택과 DirectX11 표시 흐름을 설명한다.
- 입력과 결과 visual이 보여주는 차이를 설명한다.
- 일반적인 bloom 이론은 [PostProcessingAndBloom](../../01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part1_Chapter01-02/verification-index.md)로 위임한다.

## 결과 미리보기

### Original Input

밝은 구체와 어두운 배경의 대비가 bloom 처리 전 기준을 제공한다.

![Original input](../../_assets/captures/part1_chapter01-02_02_bloom_input.jpg)

### Bloom Result

밝은 영역을 분리하고 blur한 뒤 원본에 합성한 glow 결과다.

![Bloom result](../../_assets/captures/part1_chapter01-02_02_bloom_result.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | `image_1_360.JPG`의 float RGBA pixel buffer |
| 중간 결과 | threshold를 통과한 밝은 영역과 반복 blur 결과 |
| runtime 출력 | ignored `result.png`와 CPU pixel buffer |
| 공개 결과 | `Docs/_assets/captures`에 승격한 input/result 비교 asset |

## 구현 흐름

1. `Image::ReadFromFile()`로 입력 이미지를 읽고 실패하면 fallback을 만든다.
2. luminance threshold보다 어두운 픽셀을 제거해 bright-pass 결과를 만든다.
3. `GaussianBlur5()`를 반복해 밝은 영역을 주변으로 확산한다.
4. blur 결과에 weight를 적용하고 원본 픽셀과 합성한다.
5. 합성 결과를 `result.png`로 기록하고 CPU pixel buffer로 유지한다.
6. `Map/Unmap`과 `RowPitch`를 사용해 dynamic texture에 픽셀을 업로드한다.
7. pixel shader가 texture를 샘플링하고 full-screen quad로 표시한다.

## 핵심 구현

### CPU Bloom

`Example.cpp`는 원본 pixel buffer를 보존한 뒤 bright-pass와 blur를 적용한다.
마지막 합성에서 원본과 blur 결과를 더하고 출력 범위로 제한한다. 개념과 수학적
배경은 Topic에 위임하고 여기서는 실제 예제의 처리 연결을 기준으로 설명한다.

#### Bloom 합성 의사코드

```cpp
// Pseudo C++: bright-pass, blur, composite 구조 요약
auto original = currentPixels;

for (auto& pixel : currentPixels)
{
    if (Luminance(pixel.rgb) < threshold)
    {
        pixel.rgb = 0.0f;
    }
}

for (int i = 0; i < repeatCount; ++i)
{
    GaussianBlur5(currentPixels);
}

for (size_t i = 0; i < currentPixels.size(); ++i)
{
    currentPixels[i].rgb = Clamp01(
        original[i].rgb + currentPixels[i].rgb * weight
    );
    currentPixels[i].a = original[i].a;
}
```

- [원본 보존과 bright-pass 구현](../../../Part1_Chapter01-02/02_Bloom/Example.cpp#L212-L235)
- [반복 blur와 original composite 구현](../../../Part1_Chapter01-02/02_Bloom/Example.cpp#L237-L249)

### Dynamic Texture Upload

`Example.h`는 `D3D11_USAGE_DYNAMIC` texture를 `D3D11_MAP_WRITE_DISCARD`로
갱신한다. Source row 크기와 mapped `RowPitch`가 다를 수 있으므로 각 행을
분리해 복사한 뒤 texture를 pixel shader resource로 사용한다.

#### CPU에서 GPU로 업로드하는 의사코드

```cpp
// Pseudo C++: Map/Unmap과 RowPitch를 고려한 행 단위 업로드
auto mapped = MapWriteDiscard(canvasTexture);
if (!mapped.ok)
{
    return;
}

const size_t sourceRowBytes = canvasWidth * sizeof(Vec4);
auto sourceBytes = ByteView(cpuPixels);

for (int y = 0; y < canvasHeight; ++y)
{
    auto* sourceRow = sourceBytes.data + y * sourceRowBytes;
    auto* destinationRow = mapped.base + y * mapped.rowPitch;
    CopyBytes(destinationRow, sourceRow, sourceRowBytes);
}

Unmap(canvasTexture);
```

- [Map/Unmap과 RowPitch 기반 upload 구현](../../../Part1_Chapter01-02/02_Bloom/Example.h#L258-L275)

### Full-screen Presentation

Vertex shader는 full-screen quad를 만들고 pixel shader는 업로드된 texture를
샘플링한다. CPU image processing 결과가 DirectX11 rendering pipeline의 최종
화면으로 이어지는 경계를 담당한다.

- [Vertex shader](../../../Part1_Chapter01-02/02_Bloom/VS.hlsl)
- [Pixel shader](../../../Part1_Chapter01-02/02_Bloom/PS.hlsl)

## 시각 결과

입력에서는 밝은 구체의 경계가 비교적 선명하다. 결과에서는 threshold를 통과한
밝은 영역이 blur를 통해 주변으로 확산되고 원본에 다시 합성되어 glow가 나타난다.
이 비교는 GPU multi-pass 구현이 아니어도 bloom의 핵심 단계가 최종 이미지에
어떤 차이를 만드는지 보여준다.

## 구현 범위와 한계

- CPU image processing 결과를 DirectX11 dynamic texture로 표시한다.
- 구현 단계의 이해와 input/result 비교를 우선한다.
- GPU multi-pass bloom pipeline은 다루지 않는다.
- HDR render target, tone mapping, emissive material 기반 bloom은 포함하지 않는다.
- CPU 처리 구조이므로 실시간 고해상도 post-processing 성능을 대표하지 않는다.

## 검증

- Debug/Release x64 build와 run을 직접 확인했다.
- 두 configuration에서 runtime `result.png` 생성을 확인했다.
- 공개 visual은 runtime output을 직접 연결하지 않고 검토 후 승격한 tracked
  input/result asset을 사용한다.
- 상세 근거는 [Verification Index](../../02_Verification/Part1_Chapter01-02/verification-index.md)와 [Capture Registry](../../_assets/captures/README.md)를 기준으로 확인한다.

## 관련 코드

- [02_Bloom Example README](../../../Part1_Chapter01-02/02_Bloom/README.md)
- [Example.cpp](../../../Part1_Chapter01-02/02_Bloom/Example.cpp)
- [Example.h](../../../Part1_Chapter01-02/02_Bloom/Example.h)

## 관련 문서

- [PostProcessingAndBloom Topic](../../01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- [Verification Index](../../02_Verification/Part1_Chapter01-02/verification-index.md)
- [Demo Index](demo-index.md)
- [PR #8](https://github.com/Razria93/Graphics_Study_Archive/pull/8)
