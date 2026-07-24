# Study Map

이 문서는 코드 기준 폴더와 문서 산출물 축의 연결을 요약한다. 예제별 README 정본은 코드 폴더 아래에 둔다.

## 코드 기준 폴더

| 코드 폴더 | 문서화 상태 | 예제 README 위치 | 비고 |
| --- | --- | --- | --- |
| `Part1_Chapter01-02` | pilot 진행 중 | 코드 폴더 README | `02_Bloom` README 이관 pilot |
| `Part1_Chapter03` | pilot 진행 중 | 코드 폴더 README 예정 | `Step14_CubeEnvironment` 후속 후보 |
| `Part2_Chapter04` | 예정 | 코드 폴더 README 예정 | rasterization 단계 |
| `Part2_Chapter05-08` | 예정 | 코드 폴더 README 예정 | mesh, texture, lighting 기초 |
| `Part3_Chapter09` | 예정 | 코드 폴더 README 예정 | user interaction, camera, scene interaction |
| `Part3_Chapter10-13` | 예정 | 코드 폴더 README 예정 | shadow, normal mapping, PBR/IBL 후보 |
| `Part4_Chapter14-20` | 예정 | 코드 폴더 README 예정 | compute, simulation, advanced graphics 후보 |
| `Portfolio_RayTracer` | 예정 | 코드 폴더 README 예정 | Part1 ray tracing 확장 대표 작업물 |

## 산출물 연결 기준

| 산출물 축 | 위치 | 연결 방식 |
| --- | --- | --- |
| 예제 README | 코드 폴더 | 예제 목적, 핵심 개념, 코드 위치, 실행 요약 작성 |
| 개념 설명 | `Docs/01_Topics` | 여러 예제를 관통하는 graphics topic 작성 |
| 검증 | `Docs/02_Verification` | build/run/capture/known issue 상태 기록 |
| Demo | `Docs/03_Demos` | 대표 capture와 영상 evidence 연결 |
| 작업 기록 | `Docs/04_WorkLogs` | Work Unit 종료 요약 기록 |
| 공개 판단 | `Docs/05_Publication` | public subset 후보와 제외 사유 기록 |

## 운영 기준

- 예제별 README는 코드 폴더 아래에 둔다.
- 모든 예제는 최소 README와 verification 상태를 갖도록 한다.
- 대표 예제만 Topic, Demo, Publication 문서를 깊게 연결한다.
- legacy PartDocs는 참고 자료이며 현재 정본으로 보지 않는다.
