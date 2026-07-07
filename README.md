# Graphics Study Portfolio

Graphics Study Portfolio는 DirectX11 기반 그래픽스 학습 예제와 개인 확장 작업을 Part 단위로 실행, 분석, 문서화한 private portfolio archive입니다.

이 저장소의 목적은 새 엔진을 만드는 것이 아니라, 이미 구현한 예제를 빌드하고 시연하며 그래픽스 개념을 설명 가능한 형태로 정리하는 것입니다.

## 빠른 링크

- [Build Guide](BUILD.md)
- [Demo Index](DEMOS.md)
- [Topic Index](TOPICS.md)
- [Docs](Docs/README.md)
- [Portfolio Ray Tracer](Docs/portfolio-raytracer.md)
- [Notice](NOTICE.md)

## 저장소 구성

| 폴더 | 주요 내용 | 상태 |
| --- | --- | --- |
| `Part1_Chapter01-02` | DirectX11 setup, ImGui, bloom | private 정리 예정 |
| `Part1_Chapter03` | CPU ray tracing fundamentals | private 정리 예정 |
| `Part2_Chapter04` | Software rasterization | private 정리 예정 |
| `Part2_Chapter05-08` | D3D11 pipeline, modeling, shader toys | private 정리 예정 |
| `Part3_Chapter09` | User interaction and picking | private 정리 예정 |
| `Part3_Chapter10-13` | Geometry pipeline, texturing, PBR, shadows | private 정리 예정 |
| `Part4_Chapter14-20` | Compute shader, particles, fluids, smoke, cloud | private 정리 예정 |
| `Portfolio_RayTracer` | Part1 ray tracing study extension | private 정리 예정 |

## 대표 데모 후보

| 데모 | 개념 | 자산 |
| --- | --- | --- |
| Portfolio Ray Tracer final render | Ray tracing extension | `Docs/captures/Portfolio_RayTracer/portfolio_raytracer_final.png` 예정 |
| Part1 ray sphere | Ray-sphere intersection | `Docs/captures/Part1/part1_ray_sphere.png` 예정 |
| Part2 depth buffer | Rasterization and depth test | `Docs/captures/Part2/part2_depth_buffer.png` 예정 |
| Part3 PBR models | PBR material workflow | `Docs/captures/Part3/part3_pbr_models.png` 예정 |
| Part4 particle system | Compute/simulation demo | `Docs/videos/Part4/part4_particle_system.mp4` 예정 |

## 저장소 운영 기준

- 각 예제는 독립적인 Visual Studio solution 기준으로 확인합니다.
- Part1~Part4를 하나의 master solution 또는 하나의 실행 파일로 통합하지 않습니다.
- 이 저장소는 private portfolio archive로 관리합니다.
- 외부 공개 가능한 자료는 별도 public repo로 분리합니다.
- 강의 원본 영상, 슬라이드, 퀴즈, 정답은 포함하지 않습니다.
- 강의 기반 학습 코드는 재배포나 교육 목적으로 사용하지 않습니다.
- 빌드 또는 실행을 직접 확인하지 않은 항목은 `미확인`으로 남깁니다.
