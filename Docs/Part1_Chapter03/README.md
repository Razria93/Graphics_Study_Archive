# Part1 Chapter03 Docs

CPU ray tracing 예제를 step 단위로 정리하는 문서 공간입니다.

Part1 Chapter03은 ray generation, ray-object intersection, shading, shadow, texturing, supersampling, reflection/environment로 이어지는 단계형 구현입니다. 전체 구조는 Chapter03 기준으로 관리하되, 실제 import와 검증은 step별로 진행합니다.

## 작업 원칙

- raw `Part1_Chapter03` 폴더를 통째로 복사하지 않습니다.
- Step별로 code/project files만 선별 반영합니다.
- source의 장문 학습 주석은 제거하고, 필요한 구조 주석만 새로 작성합니다.
- raw result/capture는 가져오지 않습니다.
- 강의용으로 제공된 open-source 성격의 입력 asset은 private archive 실행에 필요한 경우 포함할 수 있습니다.
- public 공개 전에는 asset 출처/라이선스 표기 가능 여부를 다시 확인합니다.
- 촬영은 현재 보류 상태로 기록합니다.

## Step 상태

| Step | 주제 | Import | Build/run | Diff review | Refactor | Capture |
| --- | --- | --- | --- | --- | --- | --- |
| Step1 Vector(GLM) | vector basics | 예정 | 미확인 | 미확인 | 미확인 | 보류 |
| Step2 CircleScreenSpace | screen-space circle | 예정 | 미확인 | 미확인 | 미확인 | 보류 |
| Step3 CircleWorldSpace | world-space circle | 예정 | 미확인 | 미확인 | 미확인 | 보류 |
| Step4 DrawingSphere | ray-sphere intersection | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step5 PhongShading | Phong shading | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step6 PerspectiveView | perspective camera rays | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step7 Triangle | ray-triangle intersection | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step8 Shadow | shadow ray | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step8 Shadow Square | square primitive wrapper | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step9 BarycentricCordinates | barycentric coordinate | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step10 Texturing | texture mapping | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step11 Supersampling | anti-aliasing | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step12 Reflection | reflection | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step13 Transparency | transparency/refraction | 완료 | 성공 | 완료 | 완료 | 보류 |
| Step14 CubeEnvironment | cube environment sampling | 완료 | 성공 | 완료 | 완료 | 보류 |

## 현재 진행 순서

1. `03_Raytracing_Step4_DrawingSphere`
2. `03_Raytracing_Step5_PhongShading`
3. `03_Raytracing_Step6_PerspectiveView`
4. `03_Raytracing_Step7_Triangle`
5. `03_Raytracing_Step8_Shadow`
6. `03_Raytracing_Step8_Shadow_Square`
7. `03_Raytracing_Step9_BarycentricCordinates`
8. `03_Raytracing_Step10_Texturing`
9. `03_Raytracing_Step11_Supersampling`
10. `03_Raytracing_Step12_Reflection`
11. `03_Raytracing_Step13_Transparency`
12. `03_Raytracing_Step14_CubeEnvironment`

## 관련 운영 문서

- [Part1 Chapter03 import manifest](../_repo/manifests/Part1_Chapter03.md)
- [Chapter Start Checklist](../_repo/workflow/chapter-start-checklist.md)
- [Migration Workflow](../_repo/workflow/migration-workflow.md)
- [Migration Board](../_repo/tracking/migration-board.md)
