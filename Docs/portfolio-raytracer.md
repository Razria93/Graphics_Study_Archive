# Portfolio Ray Tracer

`Portfolio_RayTracer`는 Part1 ray tracing 학습을 바탕으로 확장/재구성한 software ray tracer 대표 작업물입니다.

이 문서는 새 엔진 소개가 아니라, ray generation, intersection, shading, shadow, texture sampling, sampling 흐름을 설명하기 위한 대표 작업물 문서입니다.

## 포지셔닝

- Part1 CPU ray tracing study examples를 기반으로 합니다.
- 대표 최종 대상은 `Portfolio_RayTracer/16-01_Sampling`입니다.
- 이전 단계는 development history 또는 concept reference로만 연결합니다.

## Raw reference 확인

| 항목 | 값 |
| --- | --- |
| Raw root | `C:\ComputerGraphics\_00_Graphics_Portfolio` |
| 대표 후보 | `C:\ComputerGraphics\_00_Graphics_Portfolio\16-01_Sampling` |
| Solution 후보 | `12_Raytracing_Refactoring.sln` |
| Project 후보 | `12_Raytracing_Refactoring.vcxproj` |
| Import status | 검토 필요 |
| Public readiness | 검토 필요 |
| Build/run status | 미확인 |

`16-01_Sampling`은 대표 후보로 우선 검토합니다. 다만 raw 폴더 안에 `.vs/`, `x64/`, `.user`, `imgui.ini`, texture 파일이 함께 있으므로 archive로 옮기기 전 제외 파일, asset 출처, 프로젝트 경로 의존성을 확인해야 합니다.

## 후보 분류

| 후보 | 용도 | Import status | Public readiness | 비고 |
| --- | --- | --- | --- | --- |
| `16-01_Sampling` | 대표 final ray tracer 후보 | 검토 필요 | 검토 필요 | build path, texture license, 강의 기반 코드 범위 확인 필요 |
| `12-06_Raytracing_Refactoring_Complete` | refactoring complete reference | 검토 필요 | 검토 필요 | 대표 후보의 비교/설명용 reference로만 우선 검토 |
| `15-01_Texturing` | texture sampling reference | 검토 필요 | 검토 필요 | texture asset 출처 확인 필요 |
| `_TextureRaw` | raw texture reference | 검토 필요 | 검토 필요 | raw asset로 취급하고 통째 이동하지 않음 |
| `_old` | old/development history | 제외 | 제외 | archive/public 후보 아님 |

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
- `16-01_Sampling`의 `.sln`, `.vcxproj`, shader path, asset path를 확인합니다.
- texture 파일과 `_TextureRaw`의 출처/라이선스를 확인합니다.
- `16-01_Sampling` build/run을 확인합니다.
- archive 기준으로 대표 final image를 새로 캡처합니다.
- `notes/Portfolio_RayTracer/` 아래 architecture note를 추가합니다.
