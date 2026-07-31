# Post Processing And Bloom

## 목적

이 문서는 `02_Bloom` 예제를 기준으로 bloom 후처리의 개념과 DirectX11 texture 표시 흐름을 정리한다. `02_Bloom`은 GPU shader pass로 bloom을 계산하는 구조가 아니라, CPU에서 bloom 결과 이미지를 만든 뒤 DirectX11 texture로 업로드해 표시하는 구조다.

## 책임 범위

이 Topic 문서는 bloom과 dynamic texture upload의 개념, pipeline 위치, 여러 예제로 확장 가능한 설명을 맡는다. `02_Bloom`의 build/run 상태, capture/result, 파일별 구현 요약은 코드 폴더 README와 Verification/Demo 문서를 기준으로 확인한다.

## 개념 흐름

| 단계 | 설명 |
| --- | --- |
| 입력 | 원본 scene color 또는 image에서 bloom 처리 기준이 되는 색상 정보를 얻는다. |
| 밝은 영역 분리 | threshold보다 밝은 픽셀만 남겨 bloom에 참여할 영역을 제한한다. |
| Blur | 밝은 영역을 주변으로 확산해 부드러운 glow 분포를 만든다. |
| 합성 | blur 결과를 원본에 더해 밝은 영역이 번져 보이는 최종 색상을 만든다. |
| 표시 | 합성 결과를 rendering pipeline의 최종 출력으로 전달한다. |

## 핵심 개념

### Bright-pass

Bloom은 모든 픽셀을 blur하지 않는다. 먼저 luminance 또는 RGB 평균 밝기 기준으로 bloom에 참여할 픽셀을 고른다. 이 과정이 없으면 이미지 전체가 흐려지고, 빛 번짐 효과가 아니라 단순 blur처럼 보인다.

### Gaussian blur

Gaussian blur는 중심 픽셀에 더 큰 가중치를 두고 주변 픽셀을 섞는 방식이다. `02_Bloom`에서는 밝은 영역을 여러 번 blur해 빛이 주변으로 퍼지는 형태를 만든다. 이 예제는 bloom의 원리를 확인하기 위한 CPU 처리라 성능 최적화보다는 처리 단계 이해에 초점을 둔다.

### Original + blurred highlights

Bloom의 최종 결과는 blur된 밝은 영역만 보여주는 것이 아니라 원본 이미지에 다시 더한 결과다. 이때 weight 값이 커지면 bloom이 강해지고, 너무 크면 이미지가 쉽게 과노출처럼 보일 수 있다.

### Dynamic texture upload

CPU에서 계산한 픽셀은 `D3D11_USAGE_DYNAMIC` texture에 `Map/Unmap`으로 전달된다. 이후 pixel shader는 이 texture를 shader resource로 샘플링해 화면에 표시한다. 이 흐름은 CPU image processing 결과를 DirectX11 pipeline에 연결하는 기본 패턴으로 볼 수 있다.

## 데모 연결

`02_Bloom`은 original input과 bloom result를 비교해 bright-pass, blur, 합성의 시각적 차이를 보여준다. 코드 탐색은 Example README로 연결하고, 함수별 구현 흐름과 dynamic texture upload, capture/result는 상세 Demo에서 설명한다.

## 한계

- 현재 예제는 GPU multi-pass post-processing pipeline이 아니다.
- HDR render target, tone mapping, emissive material 기반 bloom까지 다루지는 않는다.

## 관련 문서

- Example: [`Part1_Chapter01-02/02_Bloom/README.md`](../../../Part1_Chapter01-02/02_Bloom/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter01-02/verification-index.md`](../../02_Verification/Part1_Chapter01-02/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md`](../../03_Demos/Part1_Chapter01-02/02_Bloom.md)
