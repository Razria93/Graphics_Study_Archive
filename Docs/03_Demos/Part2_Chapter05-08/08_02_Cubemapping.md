# Chapter08 Step2 Cubemapping Demo

## 목적

DDS cubemap의 6면을 camera 주변 skybox로 표시하고 방향 벡터가 cube face의 texel로 대응되는 흐름을 설명한다.

## 책임 범위

- 실제 DDS load, 내부 면 cube와 shader binding을 설명한다.
- 일반 이론은 [Cubemap And Environment Mapping](../../01_Topics/TexturingAndMapping/CubemapAndEnvironmentMapping.md)으로 위임한다.
- Build/run/capture 사실은 [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)로 위임한다.

## 결과 미리보기

![Chapter08 Step2 Cubemapping](../../_assets/captures/part2_chapter08_02_cubemapping.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | DDS cubemap 6면, skybox cube, camera rotation |
| 중간값 | Cube 내부 면의 world direction |
| 출력 | Camera 주변의 연속된 skybox와 전경 Zelda mesh |

## 구현 흐름

1. DDS loader가 texture-cube SRV를 생성한다.
2. Box index 순서를 뒤집어 내부 면을 전면으로 만든다.
3. Camera translation을 제거한 rotation-only view를 skybox constant buffer에 기록한다.
4. Pixel shader가 world direction으로 cube texture를 sampling한다.
5. 같은 frame에 일반 mesh를 별도 pipeline state로 그린다.

## 핵심 구현

### 내부 면 skybox와 방향 sampling

```cpp
// Pseudo C++: camera 주변 cubemap
DrawSkybox(camera, cubemap)
{
    cube = MakeInsideFacingBox();
    view = RemoveTranslation(camera.View);
    direction = TransformToWorld(cube.Position);
    color = cubemap.Sample(direction);
    Draw(cube, view, color);
}
```

- [DDS load와 내부 면 cube](../../../Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/ExampleApp.cpp#L29-L70)
- [Rotation-only skybox view](../../../Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/ExampleApp.cpp#L336-L342)
- [TextureCube 방향 sampling](../../../Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/CubeMappingPixelShader.hlsl#L3-L9)

## 시각 결과

수평선과 산맥이 camera 주변을 감싸며 Zelda mesh는 별도의 전경 geometry로 남는다. Skybox가 camera translation을 따르지 않아 배경의 무한 거리 인상을 유지한다.

## 구현 범위와 한계

- Skybox 표시가 대상이며 reflection과 refraction은 아직 적용하지 않는다.
- Zelda FBX와 skybox DDS의 공개 재배포 권리 근거가 충분하지 않아 공개 후보로 확정하지 않는다.
- 정적 결과로 방향 sampling과 배경 구성이 충분히 보이므로 video를 제외한다.

## 검증

- Debug/Release x64 Clean/Rebuild와 실행 성공, 2026-08-03 현재 확인
- Assimp·DirectXTK runtime DLL과 project 폴더 CWD 확인
- Wide·compact·minimize/restore resource 재생성 확인
- 1282×992 전체 창 screenshot과 exact title 확인

## 관련 코드

- [Cubemap 초기화](../../../Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/ExampleApp.cpp#L18-L115)
- [Skybox draw](../../../Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/ExampleApp.cpp#L361-L393)
- [Cubemap pixel shader](../../../Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/CubeMappingPixelShader.hlsl#L1-L13)

## 관련 문서

- [Chapter08 Step2 Cubemapping Example](../../../Part2_Chapter05-08/08_ShaderToys_Step2_Cubemapping/README.md)
- [이전 단계: Chapter08 Step1 RimLighting Demo](08_01_RimLighting.md)
- 다음 단계: Chapter08 Step3 EnvironmentMapping
- [Cubemap And Environment Mapping](../../01_Topics/TexturingAndMapping/CubemapAndEnvironmentMapping.md)
- [Verification Index](../../02_Verification/Part2_Chapter05-08/verification-index.md)
- [Demo Index](demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
