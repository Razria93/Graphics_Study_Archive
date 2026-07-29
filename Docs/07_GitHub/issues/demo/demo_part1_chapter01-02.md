# Part1 Chapter01-02 CPU Bloom Demo

## 요약

`02_Bloom`은 CPU에서 bright-pass와 Gaussian blur를 수행하고 원본 이미지에 합성한 결과를 DirectX11 dynamic texture로 표시한다. Original input과 bloom result를 통해 처리 전후의 glow 차이와 CPU 결과가 rendering pipeline으로 이어지는 흐름을 보여준다.

## 결과

### Original Input

밝은 구체와 어두운 배경의 대비가 bloom 처리 전 기준을 제공한다.

![Original Input](https://github.com/Razria93/Graphics_Study_Archive/blob/af3103cd06ea10d90ce6b1332336ce79eb4eb591/Docs/_assets/captures/part1_chapter01-02_02_bloom_input.jpg?raw=true)

### Bloom Result

밝은 영역을 분리하고 blur한 뒤 원본에 합성한 glow 결과다.

![Bloom Result](https://github.com/Razria93/Graphics_Study_Archive/blob/af3103cd06ea10d90ce6b1332336ce79eb4eb591/Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png?raw=true)

## 핵심 구현

### 밝은 영역 분리

`Image::Bloom()`은 원본 픽셀을 보존하고 RGB 상대 휘도를 계산한다. Threshold보다 어두운 픽셀을 제거해 glow를 만들 밝은 영역만 남기므로 어두운 배경까지 번지는 과도한 blur를 줄인다.

- [원본 보존과 bright-pass 구현](https://github.com/Razria93/Graphics_Study_Archive/blob/af3103cd06ea10d90ce6b1332336ce79eb4eb591/Part1_Chapter01-02/02_Bloom/Example.cpp#L212-L235)

### Blur와 원본 합성

Bright-pass 결과에 `GaussianBlur5()`를 반복 적용한 뒤 `weight`를 곱해 원본에 더한다. 이 선택이 밝은 구체의 형태는 유지하면서 주변으로 퍼지는 glow를 만든다.

- [반복 blur와 original composite 구현](https://github.com/Razria93/Graphics_Study_Archive/blob/af3103cd06ea10d90ce6b1332336ce79eb4eb591/Part1_Chapter01-02/02_Bloom/Example.cpp#L237-L249)

### CPU 결과의 DirectX11 표시

CPU에서 완성한 pixel buffer를 `D3D11_MAP_WRITE_DISCARD`로 연 dynamic texture에 행 단위로 복사한다. `RowPitch`를 반영해 source와 destination의 행 간격이 달라도 결과를 올바르게 업로드하고, shader가 texture를 full-screen quad에 표시한다.

- [Map/Unmap과 RowPitch 기반 upload 구현](https://github.com/Razria93/Graphics_Study_Archive/blob/af3103cd06ea10d90ce6b1332336ce79eb4eb591/Part1_Chapter01-02/02_Bloom/Example.h#L258-L275)
- [full-screen vertex 전달 shader](https://github.com/Razria93/Graphics_Study_Archive/blob/af3103cd06ea10d90ce6b1332336ce79eb4eb591/Part1_Chapter01-02/02_Bloom/VS.hlsl#L13-L20)
- [result texture sampling shader](https://github.com/Razria93/Graphics_Study_Archive/blob/af3103cd06ea10d90ce6b1332336ce79eb4eb591/Part1_Chapter01-02/02_Bloom/PS.hlsl#L10-L13)

전체 처리 흐름과 의사코드는 [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)에서 확인한다.

## 처리 흐름

1. 입력 이미지를 읽고 CPU에서 bright-pass, blur, 원본 합성을 수행한다.
2. 완성한 pixel buffer를 DirectX11 dynamic texture로 업로드한다.
3. Shader가 texture를 샘플링해 full-screen quad에 표시한다.

## 구현 범위와 한계

- CPU image processing 결과를 DirectX11 texture로 표시하는 학습 예제다.
- GPU multi-pass bloom과 실시간 고해상도 성능을 대표하지 않는다.
- HDR render target, tone mapping, emissive material 기반 bloom은 포함하지 않는다.

## 검증

- `02_Bloom` Debug/Release x64 build/run 성공
- `02_Bloom` runtime result 생성과 tracked input/result visual 확보

## 더 자세히 보기

- [상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)
- [Example README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/README.md)
- [PostProcessingAndBloom Topic](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- [Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/02_Verification/Part1_Chapter01-02/verification-index.md)
- [PR #8](https://github.com/Razria93/Graphics_Study_Archive/pull/8)
