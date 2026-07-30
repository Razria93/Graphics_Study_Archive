# Step8 Shadow

## Overview

이 예제는 Step7의 perspective primary ray, primitive 교차와 Phong shading 흐름에 point light visibility 판정을 추가한다. CPU는 surface hit에서 light를 향한 shadow ray를 추적하고 light보다 가까운 blocker가 있으면 ambient만 유지하며, DirectX11은 계산된 RGBA32F texture를 full-screen quad로 표시한다.

일반적인 shadow ray와 visibility 판정은 [Shadow Ray](../../Docs/01_Topics/Shadows/ShadowRay.md)로 위임한다. 이 문서는 Step8 코드와 실행 진입점을 설명한다.

## 실행 진입점

- Solution: `03_Raytracing_Step8_Shadow.sln`
- Application entry: `main.cpp`
- CPU ray tracing과 shadow 판정: `Raytracer.h`
- Primitive intersection: `Object.h`, `Sphere.h`, `Triangle.h`
- Hit와 Light data: `Hit.h`, `Light.h`
- DirectX11 upload/render: `Example.h`
- Shader: `VS.hlsl`, `PS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| `main.cpp` | Win32 window, DirectX11·ImGui 초기화와 실행 loop |
| `Raytracer.h` | sphere와 바닥 scene, closest-hit, shadow ray와 Phong lighting 계산 |
| `Object.h` | material field와 polymorphic intersection interface |
| `Sphere.h` | ray-sphere intersection과 곡면 normal 계산 |
| `Triangle.h` | 바닥 triangle의 ray-plane intersection과 내부 판정 |
| `Hit.h` | hit distance, point, normal과 hit object |
| `Light.h` | point light position |
| `Example.h` | CPU buffer 생성, dynamic texture upload와 full-screen draw |
| `VS.hlsl` | full-screen quad position과 UV 전달 |
| `PS.hlsl` | CPU 결과 texture sampling |

## 구현 요약

Step8은 red sphere와 두 triangle으로 만든 바닥을 배치한다. Primary ray가 가장 가까운 surface를 찾으면 hit point를 normal 방향으로 `1e-4`만큼 이동한 뒤 point light 방향으로 shadow ray를 보낸다. Shadow ray의 가장 가까운 hit가 light까지의 거리보다 짧으면 blocker가 있다고 판단한다.

가려진 surface는 ambient만 반환하고, visible surface는 기존 diffuse와 specular 계산을 이어간다. 실제 visibility 흐름과 코드 증거는 [Step8 상세 Demo](../../Docs/03_Demos/Part1_Chapter03/08_Shadow.md)에서 확인한다.

## Build And Run

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Solution | 존재 | `03_Raytracing_Step8_Shadow.sln` |
| Debug x64 build/run | 성공 | project 폴더를 working directory로 사용 |
| Release x64 build/run | 성공 | project 폴더를 working directory로 사용 |
| Capture/Result | 확보 | sphere가 바닥에 만드는 cast shadow 확인 |

## Capture/Result

![Step8 Shadow result](../../Docs/_assets/captures/part1_chapter03_08_shadow.png)

화면 중앙의 red sphere는 point light를 직접 받아 highlight를 만들고, 바닥에는 sphere가 light를 가리는 타원형 shadow가 나타난다. Shadow 영역은 ambient만 남아 주변의 직접광 영역보다 어둡다.

## Limitations

- Point light 하나와 hard shadow만 사용하며 area light와 soft shadow를 포함하지 않는다.
- Shadow ray origin offset은 scene scale에 고정된 `1e-4`를 사용한다.
- Shadow 판정은 가려진 surface에서 ambient만 반환하고 diffuse와 specular를 함께 생략한다.
- Triangle 교차의 parallel 판정은 고정 epsilon `1e-2`를 사용한다.
- CPU 결과는 최초 frame에 한 번만 계산하고 업로드하므로 초기 표시까지 시간이 걸린다.
- Shader는 project working directory의 `VS.hlsl`, `PS.hlsl`에 의존한다.
- Dynamic texture upload는 mapped `RowPitch`를 별도로 처리하지 않는다.
- `Square.h`는 project에 포함되어 있지만 현재 Step8 scene에서는 사용하지 않는다.

## Related Docs

- [Shadow Ray Topic](../../Docs/01_Topics/Shadows/ShadowRay.md)
- [Ray Topic](../../Docs/01_Topics/RayTracing/Ray.md)
- [Intersection Topic](../../Docs/01_Topics/RayTracing/Intersection.md)
- [Phong Shading Topic](../../Docs/01_Topics/LightingAndShading/PhongShading.md)
- [Verification](../../Docs/02_Verification/Part1_Chapter03/verification-index.md)
- [Detailed Demo](../../Docs/03_Demos/Part1_Chapter03/08_Shadow.md)
- [Demo Index](../../Docs/03_Demos/Part1_Chapter03/demo-index.md)
