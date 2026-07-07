# Portfolio Ray Tracer

`Portfolio_RayTracer`는 Part1 ray tracing 학습을 바탕으로 확장/재구성한 software ray tracer 대표 작업물입니다.

이 문서는 새 엔진 소개가 아니라, ray generation, intersection, shading, shadow, texture sampling, sampling 흐름을 설명하기 위한 대표 작업물 문서입니다.

## 포지셔닝

- Part1 CPU ray tracing study examples를 기반으로 합니다.
- 대표 최종 대상은 `Portfolio_RayTracer/16-01_Sampling`입니다.
- 이전 단계는 development history 또는 concept reference로만 연결합니다.

## 핵심 개념

| 개념 | 예상 위치 | 상태 |
| --- | --- | --- |
| Ray generation | `16-01_Sampling` | 미확인 |
| Sphere/triangle intersection | `12-06_Raytracing_Refactoring_Complete`, `16-01_Sampling` | 미확인 |
| Phong-style shading | `16-01_Sampling` | 미확인 |
| Shadow ray | `11_Raytracing_Shadow`, `16-01_Sampling` | 미확인 |
| Texture sampling | `15-01_Texturing`, `16-01_Sampling` | 미확인 |
| Sampling/anti-aliasing | `16-01_Sampling` | 미확인 |

## 데모 자산

| 자산 | 목적 | 상태 |
| --- | --- | --- |
| `captures/Portfolio_RayTracer/portfolio_raytracer_final.png` | 대표 final render | 예정 |
| `captures/Portfolio_RayTracer/portfolio_raytracer_wireframe.png` | intersection/debug view | 예정 |
| `videos/Portfolio_RayTracer/portfolio_raytracer_overview.mp4` | 짧은 overview | 예정 |

## 후속 작업

- private archive에 포함할 코드 범위를 검토합니다.
- `16-01_Sampling` build/run을 확인합니다.
- 대표 final image를 캡처합니다.
- `notes/Portfolio_RayTracer/` 아래 architecture note를 추가합니다.
