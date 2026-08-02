# Chapter08 Step6 BloomEffect Demo

## 목적

Scene render 결과를 GPU post-processing pass에 연결하고 밝은 영역 분리, 반복 blur와 원본 합성으로 bloom을 만드는 과정을 보여준다.

## 책임 범위

- Step5 scene에서 Step6 post-processing chain으로 확장되는 구현을 설명한다.
- 일반 bloom 이론은 [Post Processing And Bloom](../../01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)으로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

![Chapter08 Step6 BloomEffect](../../_assets/captures/part2_chapter08_06_bloom_effect.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Environment-lit scene, bloom threshold, bloom strength |
| 처리 | Back-buffer copy, threshold, downsample, separable blur, original composite |
| 출력 | 밝은 highlight가 주변으로 확산된 bloom scene |

## 구현 흐름

```text
Scene render
→ back buffer copy
→ bright threshold
→ downsample chain
→ horizontal/vertical blur
→ strength 적용
→ original composite
```

## 핵심 구현

### Scene 결과 복사

Back buffer를 shader-readable 임시 texture로 복사해 첫 post-process pass의 입력으로 사용한다.

- [Back buffer 복사와 filter chain 실행](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L153-L160)

### Threshold와 반복 blur

Threshold pass로 밝은 픽셀만 남기고 해상도를 단계적으로 줄인 뒤 horizontal·vertical blur를 적용한다.

```cpp
// Pseudo C++: bloom filter chain
BuildBloom(source, threshold, strength)
{
    bright = Threshold(source, threshold);
    blurred = DownsampleAndBlur(bright);
    return source + blurred * strength;
}
```

- [Threshold·downsample·blur filter 구성](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L168-L241)
- [초기화된 horizontal blur accumulator](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/BlurXPixelShader.hlsl#L23-L30)
- [초기화된 vertical blur accumulator](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/BlurYPixelShader.hlsl#L23-L30)

### 원본 합성과 resize

마지막 pass가 blur 결과와 원본을 합성한다. Window resize 시 back buffer와 크기에 의존하는 filter chain을 다시 만든다.

- [Bloom과 원본 합성](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L255-L258)
- [Resize 후 filter chain 재생성](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L262-L265)

## 시각 결과

밝은 skybox와 sphere highlight 주변으로 glow가 퍼진다. UI의 threshold와 strength가 bloom 참여 범위와 합성 강도를 제어한다.

## 구현 범위와 한계

- 최대 5단계 sampling chain과 5-tap separable blur를 사용한다.
- HDR tone mapping과 exposure adaptation은 구현하지 않는다.
- Active asset 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 유지한다.
- Video는 정적 frame에서 bloom 결과와 핵심 parameter를 확인할 수 있어 제외한다.

## 검증

- Debug/Release x64 Clean/Rebuild와 run 성공
- Wide·compact resize, minimize/restore와 filter chain 재생성 성공
- Blur accumulator 초기화와 작은 window dimension clamp 확인
- 1282×992 전체 창 PNG 확보
- PNG decode, metadata와 공개 안전성 확인

## 관련 코드

- [Bloom parameter 갱신](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp#L96-L104)
- [Threshold shader](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ThresholdPixelShader.hlsl#L20-L26)
- [Combine shader](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/CombinePixelShader.hlsl#L20-L23)

## 관련 문서

- [Chapter08 Step6 BloomEffect Example](../../../Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/README.md)
- [이전 단계: Chapter08 Step5 FresnelEffect Demo](08_05_FresnelEffect.md)
- [다음 단계: Chapter08 Step7 Shadertoy](08_07_Shadertoy.md)
- [Post Processing And Bloom](../../01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
