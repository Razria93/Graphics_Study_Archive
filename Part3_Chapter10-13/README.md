# Part3 Chapter10-13

Advanced rendering 예제를 정리하는 폴더입니다.

## 상태

- 학습 코드 정리: private 검토 후 결정
- Build/run: Step1-Step5, 11-Step1-Step5, 12-Step1-Step2, 13-Step1, 13-Step2 PipelineStateObject, 13-Step2 Shadow, 13-Step3, 13-Step4, 13-Step5, 13-Step6, 13-Step7, and 13-Step8 성공
- 캡처: 보류

## Archive/Public 검토

| 항목 | 상태 |
| --- | --- |
| Source provenance | [`SRC-P3-C10-13`](../Docs/99_Legacy/source-registry.md) |
| Import status | Step1-Step5, 11-Step1-Step5, 12-Step1-Step2, 13-Step1, 13-Step2 PipelineStateObject, 13-Step2 Shadow, 13-Step3, 13-Step4, 13-Step5, 13-Step6, 13-Step7, and 13-Step8 imported |
| Public readiness | 검토 필요 |
| Build/run status | Step1-Step5, 11-Step1-Step5, 12-Step1-Step2, 13-Step1, 13-Step2 PipelineStateObject, 13-Step2 Shadow, 13-Step3, 13-Step4, 13-Step5, 13-Step6, 13-Step7, and 13-Step8 성공 |
| Next action | Part3 Ch10-13 import 마무리 상태 확인 및 브랜치 정리 |

## Source 기준

- primary와 reference source의 관계는
  [`SRC-P3-C10-13`](../Docs/99_Legacy/source-registry.md)으로 추적한다.
- reference-only snapshot은 build/run 실패나 기능 누락 의심 시에만 비교한다.
- `_Solution` variant는 private archive 비교용 후보이며, 사용자 작업본과 섞지 않습니다.
- 실행에 필요한 asset만 선별하고, raw result/capture/build output은 포함하지 않습니다.

## 예정 주제

- Geometry shader and billboards
- Normal mapping and HDR pipeline
- PBR materials
- Shadow mapping, PCF, and PCSS
