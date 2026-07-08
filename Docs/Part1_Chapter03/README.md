# Part1 Chapter03 Docs

CPU ray tracing 예제를 Step 단위로 정리하는 문서 공간입니다.

Part1 Chapter03은 ray generation, ray-object intersection, shading, shadow, texturing, supersampling, reflection/environment로 이어지는 단계형 구현입니다. 전체 구조는 Chapter03 기준으로 관리하되, 실제 import와 검증은 Step별로 진행합니다.

## 작업 원칙

- raw `Part1_Chapter03` 폴더를 통째로 복사하지 않습니다.
- Step별로 code/project files만 선별 반영합니다.
- source의 장문 학습 주석은 `local/Part1_Chapter03/<Step>/`로 분리합니다.
- raw result/capture와 출처/라이선스 미확인 asset은 기본 제외합니다.
- Step10 이후 texture/skybox 관련 asset은 별도 검토 후 반영합니다.
- 촬영은 현재 보류 상태로 기록합니다.

## Step 상태

| Step | 주제 | Import | Build/run | Diff review | Refactor | Capture |
| --- | --- | --- | --- | --- | --- | --- |
| Step1 Vector(GLM) | vector basics | 예정 | 미확인 | 미확인 | 미확인 | 보류 |
| Step2 CircleScreenSpace | screen-space circle | 예정 | 미확인 | 미확인 | 미확인 | 보류 |
| Step3 CircleWorldSpace | world-space circle | 예정 | 미확인 | 미확인 | 미확인 | 보류 |
| Step4 DrawingSphere | ray-sphere intersection | 완료 | 성공 | 진행 중 | 완료 | 보류 |
| Step5 PhongShading | Phong shading | 완료 | 성공 | 진행 중 | 완료 | 보류 |
| Step6 PerspectiveView | perspective camera rays | 완료 | 성공 | 진행 중 | 완료 | 보류 |
| Step7 Triangle | ray-triangle intersection | 완료 | build 성공 / run 미확인 | 진행 중 | 완료 | 보류 |
| Step8 Shadow | shadow ray | 2차 후보 | 미확인 | 미확인 | 미확인 | 보류 |
| Step8 Shadow Square | shadow scene variation | 2차 후보 | 미확인 | 미확인 | 미확인 | 보류 |
| Step9 BarycentricCordinates | barycentric coordinate | 2차 후보 | 미확인 | 미확인 | 미확인 | 보류 |
| Step10 Texturing | texture mapping | asset 검토 필요 | 미확인 | 미확인 | 미확인 | 보류 |
| Step11 Supersampling | anti-aliasing | 2차 후보 | 미확인 | 미확인 | 미확인 | 보류 |
| Step12 Reflection | reflection | asset 검토 필요 | 미확인 | 미확인 | 미확인 | 보류 |
| Step13 Transparency | transparency/refraction | asset 검토 필요 | 미확인 | 미확인 | 미확인 | 보류 |
| Step14 CubeEnvironment | cube environment | 별도 검토 | 미확인 | 미확인 | 미확인 | 보류 |

## 1차 작업 순서

1. `03_Raytracing_Step4_DrawingSphere`
2. `03_Raytracing_Step5_PhongShading`
3. `03_Raytracing_Step6_PerspectiveView`

## 관련 운영 문서

- [Part1 Chapter03 import manifest](../_repo/manifests/Part1_Chapter03.md)
- [Chapter Start Checklist](../_repo/workflow/chapter-start-checklist.md)
- [Migration Workflow](../_repo/workflow/migration-workflow.md)
- [Migration Board](../_repo/tracking/migration-board.md)
