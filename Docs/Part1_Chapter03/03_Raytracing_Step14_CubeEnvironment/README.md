# 03 Raytracing Step14 CubeEnvironment

## Chapter purpose

Step14는 cube environment / skybox asset을 다루는 단계입니다. raw source의 `Raytracer.h`는 실제 cube map sampling 구현 전 상태였기 때문에, archive에서는 `SaintPetersBasilica` 6면 이미지를 ray direction 기준으로 샘플링하는 최소 environment renderer로 정리했습니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Cube environment | 6장의 방향별 texture로 주변 환경을 표현하는 방식 |
| Skybox | camera 주변을 감싸는 background environment |
| Environment lookup | ray direction을 cube face와 UV로 변환해 environment color를 읽는 과정 |
| IBL | image based lighting. environment image에서 diffuse/specular lighting 정보를 얻는 방식 |
| Asset license | environment map은 public 공개 전 author/license/attribution 확인이 필요한 asset |

## Current implementation

현재 archive 코드는 `Raytracer::Render()`에서 camera ray direction을 만들고, 해당 direction이 향하는 cube face를 선택해 environment texture를 샘플링합니다.

```cpp
const glm::vec3 rayDir = glm::normalize(pixelPosWorld - eyePos);
const glm::vec3 color = SampleEnvironment(rayDir);
```

raw Step14의 `skybox/`와 `SaintPetersBasilica/` asset 묶음은 실행 확인을 위해 private archive에 포함했습니다. 다만 public 공개 전에는 attribution/license를 별도로 확인해야 하며, 현재 archive source가 어떤 asset을 실제로 읽는지는 코드 경로 기준으로 다시 확인합니다.

`Example.h`는 실행 위치에 따라 `VS.hlsl`, `PS.hlsl`을 못 찾는 문제를 줄이기 위해 project folder와 repo root 기준 fallback 경로를 확인합니다. `Raytracer.h`도 `SaintPetersBasilica` texture를 같은 방식으로 찾습니다.

## Asset handling

| Asset group | Archive status | Note |
| --- | --- | --- |
| `skybox/*.jpg` | 포함 | private archive 실행 확인용, public 공개 전 출처/라이선스 확인 |
| `skybox/*_diffuseIBL.dds` | 포함 | IBL 후보 asset, public 공개 전 license 확인 필요 |
| `skybox/*_specularIBL.dds` | 포함 | IBL 후보 asset, public 공개 전 license 확인 필요 |
| `SaintPetersBasilica/*.jpg` | 포함 | Humus / CC BY 3.0 attribution 필요 |
| `SaintPetersBasilica/*_blurred.jpg` | 포함 | 생성/가공 asset, public 공개 전 attribution/license 확인 필요 |
| `SaintPetersBasilica/image_blurring.py` | 미포함 | helper script, 현재 build에 불필요 |

`SaintPetersBasilica/readme.txt`는 Humus author와 Creative Commons Attribution 3.0 Unported license를 명시합니다. public 공개 후보로 넘길 때는 attribution 문서와 함께 별도 반영합니다.

## Current status

| Item | Status |
| --- | --- |
| Code split | 완료 |
| Source comment cleanup | 완료 |
| Required texture asset | `skybox/`, `SaintPetersBasilica/` 포함 |
| Environment asset import | 완료(private archive), public 검토 필요 |
| Environment sampling | 구현 |
| Debug x64 build | 성공 |
| Release x64 build | 성공 |
| Run verification | 성공 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Known issue record

초기 archive 이관본은 raw `Raytracer::Render()`가 비어 있는 scaffold를 기준으로 정리되어 화면에 의미 있는 environment image를 출력하지 못했습니다. 이후 리소스를 추가했지만 출력이 바뀌지 않았고, 원인은 리소스 누락만이 아니라 texture loading과 cube environment sampling 코드가 `pixels` write path에 연결되어 있지 않았기 때문입니다.

현재 archive는 실행 확인을 위해 `SaintPetersBasilica` 6면 이미지를 직접 샘플링하는 최소 구현을 추가했습니다. raw Step14가 비어 있던 정확한 의도와 강의 맥락은 추후 별도 확인합니다.

## Follow-up

- capture는 사용자 촬영 단계에서 진행합니다.
- raw Step14의 빈 `Render()` 상태와 강의 맥락은 추후 확인합니다.
