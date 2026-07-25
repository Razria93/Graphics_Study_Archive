# Post Processing And Bloom

## 목적

이 문서는 `02_Bloom` 예제를 기준으로 bloom 후처리의 개념과 DirectX11 texture 표시 흐름을 정리한다. `02_Bloom`은 GPU shader pass로 bloom을 계산하는 구조가 아니라, CPU에서 bloom 결과 이미지를 만든 뒤 DirectX11 texture로 업로드해 표시하는 구조다.

## Bloom 처리 단계

| 단계 | 설명 |
| --- | --- |
| 입력 이미지 로드 | 이미지 파일을 읽어 CPU 메모리의 float RGBA 픽셀 배열로 변환한다. |
| 밝은 영역 분리 | threshold보다 밝은 픽셀만 남기고 나머지는 검정에 가깝게 만든다. |
| Blur | 밝은 영역에 blur를 반복 적용해 주변으로 빛이 번지는 형태를 만든다. |
| 합성 | blur 결과를 원본 이미지에 weight로 더해 최종 bloom 이미지를 만든다. |
| 표시 | CPU 결과 픽셀을 DirectX11 dynamic texture에 업로드하고 full-screen quad로 렌더링한다. |

## 핵심 개념

### Bright-pass

Bloom은 모든 픽셀을 blur하지 않는다. 먼저 luminance 또는 RGB 평균 밝기 기준으로 bloom에 참여할 픽셀을 고른다. 이 과정이 없으면 이미지 전체가 흐려지고, 빛 번짐 효과가 아니라 단순 blur처럼 보인다.

### Gaussian blur

Gaussian blur는 중심 픽셀에 더 큰 가중치를 두고 주변 픽셀을 섞는 방식이다. `02_Bloom`에서는 밝은 영역을 여러 번 blur해 빛이 주변으로 퍼지는 형태를 만든다. 이 예제는 bloom의 원리를 확인하기 위한 CPU 처리라 성능 최적화보다는 처리 단계 이해에 초점을 둔다.

### Original + blurred highlights

Bloom의 최종 결과는 blur된 밝은 영역만 보여주는 것이 아니라 원본 이미지에 다시 더한 결과다. 이때 weight 값이 커지면 bloom이 강해지고, 너무 크면 이미지가 쉽게 과노출처럼 보일 수 있다.

### Dynamic texture upload

CPU에서 계산한 픽셀은 `D3D11_USAGE_DYNAMIC` texture에 `Map/Unmap`으로 전달된다. 이후 pixel shader는 이 texture를 shader resource로 샘플링해 화면에 표시한다. 이 흐름은 CPU image processing 결과를 DirectX11 pipeline에 연결하는 기본 패턴으로 볼 수 있다.

## 02_Bloom에서 확인할 코드

| 코드 | 역할 |
| --- | --- |
| `Image::ReadFromFile()` | 입력 이미지를 CPU 픽셀 배열로 읽는다. |
| `Image::Bloom()` | bright-pass, blur 반복, 원본 합성을 수행한다. |
| `Image::GaussianBlur5()` | bloom 확산에 쓰는 blur 처리를 수행한다. |
| `Example::Initialize()` | swap chain, shader, dynamic texture, SRV를 만든다. |
| `Example::Update()` | CPU 픽셀 배열을 GPU texture로 업로드한다. |
| `Example::Render()` | full-screen quad로 texture를 화면에 표시한다. |

## 시연 포인트

- 원본 이미지와 bloom 결과의 차이를 비교한다.
- threshold와 blur 반복 횟수가 bloom 강도에 미치는 영향을 설명한다.
- CPU에서 계산한 결과가 DirectX11 texture로 표시되는 과정을 설명한다.

## 한계

- 현재 예제는 GPU multi-pass post-processing pipeline이 아니다.
- HDR render target, tone mapping, emissive material 기반 bloom까지 다루지는 않는다.
- build/run과 capture/result 검증 결과는 `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`를 기준으로 확인한다.

## 연결 예제

- `../../../Part1_Chapter01-02/02_Bloom/README.md`
