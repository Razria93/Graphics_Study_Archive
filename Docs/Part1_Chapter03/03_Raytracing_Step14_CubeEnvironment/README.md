# 03 Raytracing Step14 CubeEnvironment

## Chapter purpose

Step14는 cube environment / skybox asset을 다루기 위한 scaffold 단계입니다. 현재 raw source의 `Raytracer.h`는 실제 cube map sampling 구현 전 상태이며, archive에서는 build/run 가능한 빈 environment scaffold로 정리합니다.

## Core keywords

| Keyword | Summary |
| --- | --- |
| Cube environment | 6장의 방향별 texture로 주변 환경을 표현하는 방식 |
| Skybox | camera 주변을 감싸는 background environment |
| Environment lookup | ray direction을 cube face와 UV로 변환해 environment color를 읽는 과정 |
| IBL | image based lighting. environment image에서 diffuse/specular lighting 정보를 얻는 방식 |
| Asset license | environment map은 public 공개 전 author/license/attribution 확인이 필요한 asset |

## Current implementation

현재 archive 코드는 `Raytracer::Render()`에서 고정 background color를 채우는 buildable scaffold입니다.

```cpp
std::fill(pixels.begin(), pixels.end(), glm::vec4(0.02f, 0.03f, 0.05f, 1.0f));
```

raw Step14의 `skybox/`와 `SaintPetersBasilica/` asset 묶음은 현재 source에서 직접 참조되지 않습니다. 따라서 이번 이관에서는 대용량 environment assets를 복사하지 않고, asset review 대상으로 기록합니다.

## Asset handling

| Asset group | Archive status | Note |
| --- | --- | --- |
| `skybox/*.jpg` | 미포함 | raw에 포함되어 있으나 현재 Step14 source에서 직접 사용하지 않음 |
| `skybox/*_diffuseIBL.dds` | 미포함 | IBL 후보 asset, public 공개 전 license 확인 필요 |
| `skybox/*_specularIBL.dds` | 미포함 | IBL 후보 asset, public 공개 전 license 확인 필요 |
| `SaintPetersBasilica/*.jpg` | 미포함 | Humus / CC BY 3.0 attribution 필요 |
| `SaintPetersBasilica/*_blurred.jpg` | 미포함 | 생성/가공 asset으로 별도 검토 필요 |
| `SaintPetersBasilica/image_blurring.py` | 미포함 | helper script, 현재 build에 불필요 |

`SaintPetersBasilica/readme.txt`는 Humus author와 Creative Commons Attribution 3.0 Unported license를 명시합니다. asset을 archive/public에 포함할 때는 attribution 문서와 함께 별도 반영합니다.

## Current status

| Item | Status |
| --- | --- |
| Code split | 완료 |
| Source comment cleanup | 완료 |
| Required texture asset | 없음 |
| Environment asset import | 보류 |
| Debug x64 build | 성공 |
| Release x64 build | 성공 |
| Run verification | 미확인 |
| Capture | 보류 |
| Public readiness | 검토 필요 |

## Follow-up

- 사용자가 Debug/Release 실행을 확인하면 status와 tracking 문서를 갱신합니다.
- 실제 cube environment 구현을 진행할 경우 asset subset과 attribution 문서를 먼저 확정합니다.
