# 11_TexturingTechniques_Step1_Mipmaps

## Chapter Focus

이 예제는 texture sampling에서 mipmap LOD를 직접 선택하는 흐름을 확인하는 단계입니다.

핵심은 `SampleLevel`을 사용해 diffuse texture의 mipmap level을 명시하는 것입니다. GUI의 `Mipmaps Level` slider가 `mipmapLevel` constant buffer 값을 바꾸고, pixel shader가 그 값을 `g_texture0.SampleLevel(g_sampler, input.texcoord, mipmapLevel)`에 전달합니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step1_Mipmaps`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\11_TexturingTechniques_Step1_Mipmaps`
- Intent reference: `C:\ComputerGraphics\OriginalExamples\Part3_Chapter10_13\11_TexturingTechniques_Step1_Mipmaps`
- Primary raw had a distance-based LOD experiment and the `Mipmaps Level` GUI slider was disabled.
- Archive restored `ExampleApp.cpp` and `BasicPixelShader.hlsl` to the OriginalExamples intent for this step.
- The distance-based LOD experiment is treated as a later/user experiment rather than the Step1 baseline.
- 장문 학습 메모와 source comment 정리는 2차 문서 정리 단계에서 분리합니다.

## Runtime Assets

새로 추가한 asset은 없습니다. 이전 Step에서 반영한 공용 texture/cubemap asset을 사용합니다.

## Verification

- Static verification: 통과
- Debug x64 run: 성공
- Release x64 run: 성공
