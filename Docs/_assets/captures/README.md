# Captures

이 폴더는 검토된 screenshot과 result image를 둔다. 검토 전 후보, 실패한 capture, 중복 capture는 이 폴더에 승격하지 않는다.

## 기준

- build/run 상태가 `성공` 또는 `부분 성공`인 예제의 capture/result만 둔다.
- 파일명은 Part/Chapter/Portfolio, 예제 또는 Topic을 드러낸다.
- 강의 화면 캡처, 유료 자료, 출처 불명 asset은 제외한다.
- `Docs/03_Demos` 또는 `Docs/02_Verification`에서 실제로 참조하는 capture/result만 둔다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.

## 파일명 기준

상세 파일명 정책의 정본은 `Docs/06_Policies/demo-capture-policy.md`를 따른다.

```text
part#_chapter##_example-or-topic.png
part#_chapter##-##_example-or-topic_input.png
part#_chapter##-##_example-or-topic_result.png
portfolio_raytracer_topic.png
```

예시:

```text
part1_chapter01-02_02_bloom_input.jpg
part1_chapter01-02_02_bloom_result.png
part2_chapter04_depth-buffer.png
```

파일명에는 branch 이름이나 PR 번호보다 Part/Chapter/Portfolio와 graphics 개념을 우선 반영한다.

## 승격된 파일

| 파일 | 유형 | 연결 예제 | 상태 | 비고 |
| --- | --- | --- | --- | --- |
| `part1_chapter01-02_02_bloom_input.jpg` | input image | `Part1_Chapter01-02/02_Bloom` | 확보 | bloom 전 원본 비교 이미지 |
| `part1_chapter01-02_02_bloom_result.png` | result image | `Part1_Chapter01-02/02_Bloom` | 확보 | ChatGPT 생성 입력 이미지 기반 `result.png`를 승격함 |
| `part1_chapter03_04_drawing-sphere.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step4_DrawingSphere` | 확보 | Debug x64 전체 application window에서 기본 sphere와 조절 UI 확인 |
| `part1_chapter03_04_drawing-sphere_parameter-adjusted.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step4_DrawingSphere` | 확보 | 전체 application window에서 Center, Radius와 RGB 조정 결과 확인 |
| `part1_chapter03_05_phong-shading.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step5_PhongShading` | 확보 | Debug x64 전체 application window에서 기본 Phong lighting과 parameter UI 확인 |
| `part1_chapter03_05_phong-shading_parameter-adjusted.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step5_PhongShading` | 확보 | 전체 application window에서 Light 위치 조정과 highlight 이동 확인 |
| `part1_chapter03_06_perspective-view.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step6_PerspectiveView` | 확보 | Release x64 전체 application window에서 perspective 크기 변화와 sphere overlap 확인 |
| `part1_chapter03_07_triangle.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step7_Triangle` | 확보 | Debug x64 전체 application window에서 triangle 경계, flat normal shading과 sphere closest-hit 확인 |
| `part1_chapter03_08_shadow.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step8_Shadow` | 확보 | Release x64 전체 application window에서 Square 바닥의 연속 면과 cast shadow 확인 |
| `part1_chapter03_09_barycentric_coordinates.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step9_BarycentricCordinates` | 확보 | Release x64 전체 application window에서 RGB vertex color의 연속 보간 확인 |
| `part1_chapter03_10_texturing.png` | screenshot | `Part1_Chapter03/03_Raytracing_Step10_Texturing` | 확보 | Release x64 전체 application window에서 자작 UV 진단 texture의 방향·보간·seam 확인 |

## 승격 체크

| 항목 | 기준 |
| --- | --- |
| 실행 상태 | build/run 상태가 `성공` 또는 `부분 성공`임 |
| 문서 연결 | demo-index, capture-plan, capture-matrix 중 하나 이상에서 참조함 |
| 설명 가능성 | capture/result가 보여주는 graphics 개념을 설명할 수 있음 |
| 중복 여부 | 같은 의미의 capture/result가 이미 승격되어 있지 않음 |
| 공개 가능성 | 강의 화면, 유료 자료, 출처 불명 asset이 아님 |
| 식별자 검수 | 강의명, 강사명, 워터마크, 개인 식별자, 계정, 로컬 경로가 보이지 않음 |

## 연결 문서

- Demo 계획: `Docs/03_Demos`
- Capture 상태: `Docs/02_Verification/capture-matrix.md`
- 공개 판단: `Docs/05_Publication`

## 제외 기준

- 실패 화면만 담긴 capture
- 화질이나 구도가 낮아 개념을 설명하기 어려운 capture/result
- 동일한 의미의 중복 capture/result
- 강의 화면 또는 유료 자료가 포함된 capture/result
- 문서에서 참조하지 않는 보관용 capture/result
