# 02_Bloom

> 문서 상태: migration draft입니다. build/run, raw/original diff review, refactor check 전까지 최종 제출 문서로 보지 않습니다.

## 목적

이미지를 CPU 메모리로 읽어온 뒤 밝은 영역을 추출하고, separable Gaussian blur를 반복 적용한 결과를 원본 이미지에 더해 bloom 효과를 만드는 예제입니다. 처리된 이미지는 DirectX11 dynamic texture로 업로드하여 full-screen quad에 표시합니다.

## 핵심 키워드

- Image loading
- Texture upload
- Shader Resource View
- Box blur
- Gaussian blur
- Separable convolution
- Relative luminance
- Bloom threshold
- OpenMP

## 관련 이론 / 원리

Bloom은 밝은 픽셀만 분리한 뒤 주변으로 퍼뜨려 원본 이미지에 다시 합성하는 후처리 효과입니다. 이 예제에서는 GPU post-process pass가 아니라 CPU에서 픽셀 배열을 직접 조작한 뒤, 결과 이미지를 DX11 texture로 업로드합니다.

핵심 단계는 다음과 같습니다.

1. 이미지를 `Vec4` float pixel buffer로 변환합니다.
2. relative luminance 기준으로 threshold보다 어두운 픽셀을 제거합니다.
3. 5-tap Gaussian blur를 x/y 방향으로 나누어 반복합니다.
4. blurred highlight를 원본 이미지에 더합니다.
5. 처리된 buffer를 `Map`/`memcpy`/`Unmap`으로 dynamic texture에 복사합니다.

## 핵심 코드 흐름

밝은 영역 분리:

```cpp
const float relativeLuminance =
    c.v[0] * 0.2126f +
    c.v[1] * 0.7152f +
    c.v[2] * 0.0722f;

if (relativeLuminance < threshold)
{
    c.v[0] = 0.0f;
    c.v[1] = 0.0f;
    c.v[2] = 0.0f;
}
```

Separable Gaussian blur:

```cpp
neighborColorSum.v[0] += GetPixel(i + (k - 2), j).v[0] * weights[k];
```

Texture upload:

```cpp
deviceContext->Map(canvasTexture, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
memcpy(ms.pData, image.pixels.data(), image.pixels.size() * sizeof(Vec4));
deviceContext->Unmap(canvasTexture, NULL);
```

## 구현 순서

1. `stb_image`로 private archive 입력 이미지 `image_1_360.JPG`를 읽어 `Vec4` buffer에 저장합니다.
2. 입력 이미지가 누락되면 실행 확인용 synthetic fallback image를 생성합니다.
3. `Bloom(threshold, repeatCount, weight)`에서 bright-pass, blur, additive combine을 수행합니다.
4. 처리 결과를 `result.png`로 저장합니다.
5. 같은 pixel buffer를 DX11 dynamic texture에 업로드해 화면에 표시합니다.

## 실행 결과

- Build/run status: Debug/Release 실행 성공
- Capture: 보류
- Raw/original diff review: 완료
- Refactor check: 완료

## 공개 가능성

- 상태: 검토 필요
- 코드: 학습 기반 구현이므로 public subset 이동 전 핵심 구현 범위와 원문 코드 포함 여부를 재검토합니다.
- 입력 이미지: `image_1_360.JPG` 1개는 private archive 실행 확인용으로 포함했습니다. public 공개 전에는 출처/라이선스 검토가 필요합니다.
- 결과 이미지: raw 결과물은 복사하지 않고, archive에서 직접 실행/촬영한 산출물만 후보로 둡니다.

## Local-only 작업 재료

다음 파일은 `local/` 아래에 있으며 git에 포함하지 않습니다.

- `local/Part1_Chapter01-02/02_Bloom/source-comments.md`
- `local/Part1_Chapter01-02/02_Bloom/raw-md-notes.md`
- `local/Part1_Chapter01-02/02_Bloom/memo-review.md`
- `local/Part1_Chapter01-02/02_Bloom/final-doc-plan.md`

## 관련 문서

- [Example status](status.md)
- [Part1 import manifest](../../../ImportHistory/Manifests/Part1_Chapter01-02.md)
- [Chapter Study 정리 방식](../../../../06_Policies/docs-authoring-flow-policy.md)
