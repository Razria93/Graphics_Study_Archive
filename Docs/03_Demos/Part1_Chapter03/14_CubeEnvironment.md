# Step14 CubeEnvironment Demo

## 목적

Screen ray direction을 cubemap face와 UV로 변환하고, 여섯 environment image를 CPU에서 sampling해 full-screen environment view를 만드는 흐름을 확인한다.

## 책임 범위

- Dominant axis 기반 face 선택, face-local UV 변환과 bilinear sampling을 실제 코드 근거에 연결한다.
- Step13 다음 순서에 놓이지만 geometry·refraction의 누적 확장으로 표현하지 않는다.
- 일반적인 cubemap과 environment mapping은 [Cubemap And Environment Mapping](../../01_Topics/TexturingAndMapping/CubemapAndEnvironmentMapping.md)으로 위임한다.
- build/run/capture 사실은 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)로 위임한다.

## 결과 미리보기

![Step14 CubeEnvironment result](../../_assets/captures/part1_chapter03_14_cube_environment.png)

## 입력과 출력

- 입력: CC BY 3.0 `SaintPetersBasilica` cubemap JPEG 6면
- Camera: `(0, 0, -1.5)` eye와 z=0 image plane
- Sampling: dominant axis face selection과 face-local bilinear interpolation
- 출력: direction별 RGB environment color
- 표시 경로: CPU RGBA32F 결과를 DirectX11 dynamic texture와 full-screen quad로 표시

## Step13과의 관계

Step13은 geometry hit, reflection/refraction과 textured Square를 재귀 추적한다. Step14는 geometry intersection 없이 camera ray direction을 곧바로 cubemap에 조회한다. 순차 학습 흐름의 마지막 단계이지만 Step13 scene에 environment lighting을 추가한 누적판은 아니다.

## 구현 흐름

```cpp
// Pseudo C++: cubemap environment 렌더 흐름
RenderEnvironment()
{
    for each pixel in 1280x720
    {
        position = TransformScreenToWorld(pixel);
        direction = Normalize(position - eye);
        color = SampleCubemap(direction);
        output[pixel] = Clamp(color);
    }

    UploadRowsUsingMappedRowPitch(output);
    DrawFullscreenQuad();
}
```

- [Environment scene render](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Raytracer.h#L45-L58)

## 핵심 구현

### Camera ray와 face 선택

```cpp
// Pseudo C++: 실제 Step14의 direction-to-face lookup
Color SampleCubemap(Vector direction)
{
    Vector major = Abs(direction);
    Axis axis = SelectDominantAxis(major);
    Face face = SelectSignedFace(axis, direction);
    Vector2 local = ProjectToFace(direction, axis);
    Vector2 uv = local * 0.5 + 0.5;

    return faces[face].SampleLinear(uv);
}
```

Screen point는 aspect ratio를 반영한 z=0 plane 좌표로 변환한다. Eye에서 이 점으로 향하는 normalized direction을 만들고 절댓값이 가장 큰 axis와 부호로 face를 고른다. 동률일 때는 X, Y, Z 순으로 선택한다.

- [Camera ray 생성](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Raytracer.h#L45-L58)
- [Dominant axis와 face-local UV 변환](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Raytracer.h#L83-L138)
- [Aspect-correct screen plane](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Raytracer.h#L140-L146)

### CPU bilinear sampling

```cpp
// Pseudo C++: 선택한 face 내부의 2x2 texel 보간
Color SampleFaceLinear(Vector2 uv)
{
    Vector2 texel = Clamp(uv) * size - 0.5;
    FourSamples samples = FetchClamped2x2(texel);
    return Bilinear(samples, Fraction(texel));
}
```

UV를 선택한 face 내부로 clamp하고 2×2 texel을 bilinear interpolation한다. 인접 face를 함께 filtering하지 않으므로 경계 seam을 완전히 제거하는 방식은 아니다.

- [Face-local bilinear sampling](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Texture.h#L22-L45)

### CPU 결과 표시

Ray lookup은 CPU에서 최초 frame에 한 번 수행한다. Mapped texture의 `RowPitch`를 사용해 row별로 복사하며, HLSL은 CPU 결과 texture를 full-screen quad에 표시한다.

- [CPU render와 RowPitch upload](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Example.h#L55-L87)
- [Runtime shader path fallback](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Example.h#L137-L154)
- [Full-screen presentation](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Example.h#L340-L363)

## 시각 결과

- PosZ face 중심의 basilica interior가 image 중앙에 나타난다.
- 좌우 가장자리에서 PosX와 NegX face로 전환되는 environment view를 확인한다.
- Debug project CWD와 Release repository-root CWD에서 같은 장면이 나타난다.
- 검은 누락 영역, 잘못된 face 회전과 명확한 edge discontinuity는 현재 capture에서 관찰되지 않는다.

## 입력 asset

- 파일: `SaintPetersBasilica/posx.jpg`, `negx.jpg`, `posy.jpg`, `negy.jpg`, `posz.jpg`, `negz.jpg`
- 저자: Emil Persson, aka Humus
- 출처: [Humus](http://www.humus.name)
- 라이선스: [CC BY 3.0 Unported](https://creativecommons.org/licenses/by/3.0/)
- 규격: 각 2048×2048 RGB JPEG
- Attribution 원문: [readme.txt](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/SaintPetersBasilica/readme.txt)
- Capture 파일: `part1_chapter03_14_cube_environment.png`
- Capture SHA-256: `EB7FDD5BC40B78734312E0311A6D0E5846EAA373408675ADC8A2BA4C6E8756F2`

Runtime에서 참조하지 않는 blurred face 6개와 별도 `skybox` asset 18개는 공개·유지 범위를 줄이기 위해 제거했다.

## 구현 범위와 한계

- Camera와 direction을 조작하는 UI가 없다.
- 현재 정적 view는 PosZ 중심과 X face 경계만 보여주며 PosY, NegY와 NegZ orientation을 직접 검증하지 않는다.
- Face 경계에서 cross-face filtering을 수행하지 않는다.
- Mipmap, HDR, gamma correction과 tone mapping을 포함하지 않는다.
- Geometry, reflection, refraction과 environment lighting을 포함하지 않는다.
- OpenMP pragma는 project 설정에서 활성화하지 않아 병렬 실행을 보장하지 않는다.
- Runtime path fallback은 project 폴더와 repository root 기준으로 제한된다.

## 검증

- Debug x64 build/run 성공
- Release x64 build/run 성공
- Project 폴더와 repository root working directory에서 shader와 cubemap 6면 load 확인
- `ComputerGraphics - Step14 CubeEnvironment` application title 확인
- Release x64 전체 application window capture 확인
- 실행용 JPEG 6면의 EXIF, GPS, author, software와 date metadata 부재 확인
- Capture PNG의 text, EXIF와 XMP metadata 및 개인 식별자 부재 확인
- 자세한 상태는 [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)에서 관리한다.

## 관련 코드

- [Cubemap 6면 load](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Raytracer.h#L34-L43)
- [Camera ray 생성](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Raytracer.h#L45-L58)
- [Runtime asset path fallback](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Raytracer.h#L62-L81)
- [Face와 UV 선택](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Raytracer.h#L83-L138)
- [Bilinear sampling](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Texture.h#L22-L45)
- [CPU texture upload](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/Example.h#L55-L87)
- [Application title](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/main.cpp#L38-L49)

## 관련 문서

- [Step14 Example README](../../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/README.md)
- [Cubemap And Environment Mapping](../../01_Topics/TexturingAndMapping/CubemapAndEnvironmentMapping.md)
- [Texture Sampling](../../01_Topics/TexturingAndMapping/TextureSampling.md)
- [Verification Index](../../02_Verification/Part1_Chapter03/verification-index.md)
- [Demo Index](demo-index.md)
