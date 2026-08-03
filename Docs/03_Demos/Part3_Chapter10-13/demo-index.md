# Part3_Chapter10-13 Demo Index

이 문서는 Chapter10→13의 순차 Demo와 capture 연결 상태를 기록한다.

## 범위

- 주요 demo 후보: Chapter10 Geometry Pipeline, Chapter11 HDR, Chapter12 PBR, Chapter13 shadow quality
- 비고: 각 Example은 독립 상세 Demo를 사용하고 Chapter 대표 선정은 Publication에서 별도로 수행한다.

## Demo 목록

| Demo 후보 | 상세 Demo | 연결 Example | 연결 Topic | Verification | Capture/Result | GitHub Demo Issue | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 최소 capture | [Step1 Demo](10_01_GeometryShader.md) | [Step1 README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step1_GeometryShader/README.md) | [Geometry Shader](../../01_Topics/ModelingAndGeometry/GeometryShaderAndBillboards.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Docs/_assets PNG](../../_assets/captures/part3_chapter10_01_geometry_shader.png) | 미게시 | 확보 | Geometry shader 기준선 |
| 대표 capture | [Step5 Demo](10_05_Tessellation.md) | [Step5 README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step5_Tessellation/README.md) | [Tessellation](../../01_Topics/ModelingAndGeometry/TessellationPipeline.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | [Docs/_assets PNG](../../_assets/captures/part3_chapter10_05_tessellation.png) | 미게시 | 후보 | Chapter10 대표 후보 |
| video | [Step4 Demo](10_04_Fireball.md) | [Step4 README](../../../Part3_Chapter10-13/10_GeometryPipeline_Step4_Fireball/README.md) | [Runtime Inputs](../../01_Topics/DirectX11Pipeline/ShadertoyRuntimeInputs.md) | [Docs/02_Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md) | 없음 | 미게시 | 제외 | 정지 image로 형태와 phase 차이 확인 가능 |

## Chapter10 Geometry Pipeline

| 단계 | 상세 Demo | Capture | 상태 |
| --- | --- | --- | --- |
| Step1 GeometryShader | [Demo](10_01_GeometryShader.md) | [PNG](../../_assets/captures/part3_chapter10_01_geometry_shader.png) | 완료 |
| Step2 Billboards | [Demo](10_02_Billboards.md) | [PNG](../../_assets/captures/part3_chapter10_02_billboards.png) | 완료 |
| Step3 NormalLines | [Demo](10_03_NormalLines.md) | [PNG](../../_assets/captures/part3_chapter10_03_normal_lines.png) | 완료 |
| Step4 Fireball | [Demo](10_04_Fireball.md) | [PNG](../../_assets/captures/part3_chapter10_04_fireball.png) | 완료 |
| Step5 Tessellation | [Demo](10_05_Tessellation.md) | [PNG](../../_assets/captures/part3_chapter10_05_tessellation.png) | 완료 |

Chapter10의 순차 흐름은 point primitive 확장, billboard, diagnostic normal, procedural animation과 tessellation으로 이어진다. Step5는 원래 Manual 경로와 사용자 확장 Distance Adaptive 경로를 하나의 상세 Demo에서 명확히 분리한다.

## 이후 Chapter 후보

| Chapter | 순차 범위 | 상태 | 대표 후보 |
| --- | --- | --- | --- |
| Chapter11 | Mipmaps → HDR Pipeline | 현재 재검증 예정 | HDR Pipeline |
| Chapter12 | Unreal PBR → PBR Models | 현재 재검증 예정 | Unreal PBR material matrix |
| Chapter13 | Mirror → Unreal Sphere Light | 현재 재검증 예정 | ShadowMapping·PCF·PCSS 비교 |

## Video 판정

- Step4 Fireball animation은 정지 image로 형태와 phase 차이를 확인할 수 있어 video를 필수로 두지 않는다.
- UI 조작이나 시간 변화가 구현 이해에 실질적인 정보를 더할 때만 local selected video를 만든다.
- Tracked 상세 Demo는 안정적인 정적 visual을 유지한다.

## 갱신 기준

- 현재 build/run/capture가 확인된 Example만 `완료`로 기록한다.
- 원본 runtime asset과 rendered evidence의 공개 책임을 구분한다.
- GitHub 게시 상태는 실제 Issue URL을 확보한 뒤 갱신한다.

## 관련 문서

- [Chapter README](../../../Part3_Chapter10-13/README.md)
- [Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
- [Publication](../../05_Publication/candidate-list.md)
