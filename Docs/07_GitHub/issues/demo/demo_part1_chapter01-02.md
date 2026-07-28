# Part1 Chapter01-02 CPU Bloom Demo

## 요약

`02_Bloom`은 CPU에서 bright-pass와 Gaussian blur를 수행하고 원본 이미지에
합성한 결과를 DirectX11 dynamic texture로 표시한다. Original input과 bloom
result를 통해 처리 전후의 glow 차이와 CPU 결과가 rendering pipeline으로
이어지는 흐름을 보여준다.

## 결과

### Original Input

밝은 구체와 어두운 배경의 대비가 bloom 처리 전 기준을 제공한다.

![Original Input](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/_assets/captures/part1_chapter01-02_02_bloom_input.jpg?raw=true)

### Bloom Result

밝은 영역을 분리하고 blur한 뒤 원본에 합성한 glow 결과다.

![Bloom Result](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png?raw=true)

## 핵심 구현

- Bright-pass: luminance threshold를 통과한 픽셀만 bloom 입력으로 사용
- Gaussian blur: 밝은 영역을 반복 확산해 부드러운 glow 생성
- Original composite: blur 결과에 weight를 적용하고 원본과 합성
- Dynamic texture: `Map/Unmap`과 `RowPitch`를 고려해 CPU buffer 업로드
- Full-screen quad: pixel shader에서 결과 texture를 샘플링해 화면에 표시

핵심 코드는
[Example.cpp](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/Example.cpp#L212-L255)와
[Example.h](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Part1_Chapter01-02/02_Bloom/Example.h#L258-L275)에서
확인한다.

## 처리 흐름

1. 입력 이미지를 float RGBA pixel buffer로 읽는다.
2. threshold를 기준으로 밝은 영역을 분리한다.
3. Gaussian blur를 반복 적용한다.
4. blur 결과를 원본에 합성하고 result image를 만든다.
5. CPU pixel buffer를 DirectX11 dynamic texture로 업로드한다.
6. full-screen quad로 최종 결과를 표시한다.

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
