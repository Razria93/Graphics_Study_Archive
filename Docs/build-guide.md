# 빌드 검증표

이 문서는 예제별 빌드/실행 확인 결과를 기록합니다. 현재 상태는 scaffold 단계이므로 모두 `미확인`입니다.

## 상태 값

| 값 | 의미 |
| --- | --- |
| 미확인 | 아직 빌드/실행하지 않음 |
| 성공 | 해당 항목 확인 완료 |
| 실패 | 실패 원인을 비고에 기록 |
| 보류 | 현재 정리 범위 밖이거나 중복/디버그 성격 |
| 해당 없음 | 해당 검증이 꼭 필요하지 않음 |

## 최소 검증 대상

| Part      | 예제                                                      | Debug x64 | Release x64 | 실행  | 캡처  | 비고                                    |
| --------- | ------------------------------------------------------- | --------- | ----------- | --- | --- | ------------------------------------- |
| Part1     | `Part1_Chapter01-02/01_DX11InitAndImGui`                | 미확인       | 미확인         | 미확인 | 미확인 | DX11/ImGui 기본 화면                      |
| Part1     | `Part1_Chapter03/03_Raytracing_Step4_DrawingSphere`     | 미확인       | 미확인         | 미확인 | 미확인 | ray-sphere intersection               |
| Part1     | `Part1_Chapter03/03_Raytracing_Step5_PhongShading`      | 미확인       | 미확인         | 미확인 | 미확인 | Phong shading                         |
| Part2     | `Part2_Chapter04/04_Rasterization_Step5_DepthBuffer`    | 미확인       | 미확인         | 미확인 | 미확인 | depth buffer                          |
| Part2     | `Part2_Chapter05-08/06_GraphicsPipeline_Step6_Lighting` | 미확인       | 미확인         | 미확인 | 미확인 | MVP and lighting                      |
| Part3     | `Part3_Chapter09/09_UserInteraction_Step2_MousePicking` | 미확인       | 미확인         | 미확인 | 미확인 | picking ray                           |
| Part3     | `Part3_Chapter10-13/12_PBR_Step2_PBRModels`             | 미확인       | 미확인         | 미확인 | 미확인 | PBR models                            |
| Part4     | `Part4_Chapter14-20/Examples/Examples.sln`              | 미확인       | 미확인         | 미확인 | 미확인 | Ex1402_Blur, Ex1501_ParticleSystem 우선 |
| Portfolio | `Portfolio_RayTracer/16-01_Sampling`                    | 미확인       | 미확인         | 미확인 | 미확인 | 대표 ray tracer                         |

## Archive 이름 재검증

Archive에서 chapter-range folder name을 적용한 예제는 정리 후 다시 확인합니다. 이때 `.sln`, `.vcxproj`, shader path, asset path가 기존 폴더 구조에 의존하는지 함께 확인합니다.
