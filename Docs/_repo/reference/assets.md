# Asset Notes

캡처와 영상은 Part/Chapter 문서에서 먼저 기록하고, 실제 파일이 필요할 때 `Docs/_assets/` 아래에 둡니다.

## 권장 위치

- 캡처: `Docs/_assets/captures/{Part_Chapter}/{example_or_topic}.png`
- 영상: `Docs/_assets/videos/{Part_Chapter}/{example_or_topic}.mp4`

## 예시

- `Docs/_assets/captures/Part1_Chapter01-02/01_DX11InitAndImGui.png`
- `Docs/_assets/captures/Part1_Chapter03/ray_sphere.png`
- `Docs/_assets/captures/Part2_Chapter04/depth_buffer.png`
- `Docs/_assets/captures/Part3_Chapter10-13/pbr_models.png`
- `Docs/_assets/captures/Part4_Chapter14-20/compute_blur.png`
- `Docs/_assets/videos/Part4_Chapter14-20/particle_system.mp4`
- `Docs/_assets/captures/Portfolio_RayTracer/portfolio_raytracer_final.png`

## 공개 전 확인

- raw repo의 기존 캡처나 영상을 그대로 archive/public 후보로 사용하지 않습니다.
- archive 기준으로 직접 실행한 결과를 새로 캡처하거나, 권리 문제가 없는 결과물만 기록합니다.
- 강의 화면, 강의 음성, 슬라이드, 유료 자료, 문제/해설 캡처는 포함하지 않습니다.
- 외부 texture/model/image asset이 화면에 포함되는 경우 출처와 라이선스를 확인하기 전까지 `검토 필요`로 둡니다.

## Third-party source headers

- STB image headers는 runtime asset이 아니라 build dependency입니다.
- clean checkout 재현성을 위해 `ThirdParty/stb`에 vendoring합니다.
- STB headers 자체의 public 공개 여부는 파일 header의 public domain 표기를 기준으로 하되, public repo 구성 시 third-party notice를 다시 확인합니다.
