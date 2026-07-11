# 11_TexturingTechniques_Step1_Mipmaps

## Chapter Focus

이 예제는 texture sampling에서 mipmap을 사용하는 흐름을 확인하는 단계입니다.

핵심은 `SampleLevel`을 사용해 diffuse texture의 mipmap LOD를 직접 지정하는 것입니다. 카메라와 pixel 위치 사이의 거리로 `lod`를 계산하고, 그 값을 `g_texture0.SampleLevel(g_sampler, input.texcoord, lod)`에 전달합니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\11_TexturingTechniques_Step1_Mipmaps`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\11_TexturingTechniques_Step1_Mipmaps`
- Reference snapshot과는 `BasicPixelShader.hlsl`, `D3D11Utils.cpp`, `ExampleApp.cpp`가 다릅니다.
- Archive에는 mipmap 단계의 사용자 작업 흐름이 포함된 primary raw 기준 파일을 반영했습니다.
- Primary raw의 `BasicPixelShader.hlsl`에는 LOD 계산식의 괄호 오류가 있어 archive에서 문법 오류만 최소 수정했습니다.
- 장문 학습 메모와 source comment 정리는 2차 문서 정리 단계에서 분리합니다.

## Runtime Assets

새로 추가한 asset은 없습니다. 이전 Step에서 반영한 공용 texture/cubemap asset을 사용합니다.

## Verification

- Static verification: 완료
- Debug x64 run: 성공
- Release x64 run: 성공
