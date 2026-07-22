# Study Map

이 문서는 코드 기준 폴더와 문서 산출물 축의 연결을 요약한다. 상세 설명은 각 산출물 폴더의 정본 문서에 둔다.

## 코드 기준 폴더

| 코드 폴더 | 문서화 상태 | 주 문서 위치 | 비고 |
| --- | --- | --- | --- |
| `Part1_Chapter01-02` | 골격 작성 | `Docs/01_Examples/Part1_Chapter01-02` | 기초 수학, image/ray 기반 예제 |
| `Part1_Chapter03` | 골격 작성 | `Docs/01_Examples/Part1_Chapter03` | ray tracing 기초 확장 |
| `Part2_Chapter04` | 골격 작성 | `Docs/01_Examples/Part2_Chapter04` | rasterization 단계 |
| `Part2_Chapter05-08` | 골격 작성 | `Docs/01_Examples/Part2_Chapter05-08` | mesh, texture, lighting 기초 |
| `Part3_Chapter09` | 골격 작성 | `Docs/01_Examples/Part3_Chapter09` | user interaction, camera, scene interaction |
| `Part3_Chapter10-13` | 골격 작성 | `Docs/01_Examples/Part3_Chapter10-13` | shadow, normal mapping, PBR/IBL 후보 |
| `Part4_Chapter14-20` | 골격 작성 | `Docs/01_Examples/Part4_Chapter14-20` | compute, simulation, advanced graphics 후보 |
| `Portfolio_RayTracer` | 골격 작성 | `Docs/01_Examples/Portfolio_RayTracer` | Part1 ray tracing 확장 대표 작업물 |

## 산출물 연결 기준

| 산출물 축 | 위치 | 연결 방식 |
| --- | --- | --- |
| 예제 설명 | `Docs/01_Examples` | 모든 예제의 최소 README/status 작성 |
| 개념 설명 | `Docs/02_Topics` | 여러 예제를 관통하는 graphics topic 작성 |
| 검증 | `Docs/03_Verification` | build/run/capture/known issue 상태 기록 |
| Demo | `Docs/04_Demos` | 대표 캡처와 영상 evidence 연결 |
| 작업 기록 | `Docs/05_WorkLogs` | Work Unit 종료 요약 기록 |
| 공개 판단 | `Docs/06_Publication` | public subset 후보와 제외 사유 기록 |

## 운영 기준

- 예제는 제외하지 않는다.
- 모든 예제는 최소 문서화 대상으로 둔다.
- 대표 예제만 Topic, Demo, Publication 문서를 깊게 연결한다.
- legacy PartDocs는 참고 자료이며 현재 정본으로 보지 않는다.
