# Study Map

이 문서는 코드 기준 폴더와 문서 산출물 축의 연결 방식을 안내한다. 예제별 README 정본은 코드 폴더 아래에 두며, 단일 project Part4는 `ExampleDocs`를 예외 경로로 사용한다. 최신 build/run, capture/result, publication 상태는 이 문서에 복제하지 않는다.

## 코드 기준 폴더

| 코드 폴더 | README 기준 | 연결할 정본 문서 |
| --- | --- | --- |
| `Part1_Chapter01-02` | 예제 폴더별 README | `Docs/01_Topics`, `Docs/02_Verification`, `Docs/03_Demos`, `Docs/05_Publication` |
| `Part1_Chapter03` | 예제 폴더별 README | `Docs/01_Topics`, `Docs/02_Verification`, `Docs/03_Demos` |
| `Part2_Chapter04` | 예제 폴더별 README | `Docs/01_Topics`, `Docs/02_Verification`, `Docs/03_Demos` |
| `Part2_Chapter05-08` | 예제 폴더별 README | `Docs/01_Topics`, `Docs/02_Verification`, `Docs/03_Demos`, `Docs/05_Publication` |
| `Part3_Chapter09` | 예제 폴더별 README | `Docs/01_Topics`, `Docs/02_Verification`, `Docs/03_Demos` |
| `Part3_Chapter10-13` | 예제 폴더별 README | `Docs/01_Topics`, `Docs/02_Verification`, `Docs/03_Demos` |
| `Part4_Chapter14-20` | `ExampleDocs` 예제별 문서 | `Docs/01_Topics`, `Docs/02_Verification`, `Docs/03_Demos` |
| `Portfolio_GraphicsLab` | 프로젝트 README | `Docs/01_Topics`, `Docs/02_Verification`, `Docs/03_Demos`, `Docs/05_Publication` |

## 산출물 축

| 산출물 축 | 위치 | 정본 책임 |
| --- | --- | --- |
| 예제 README | 코드 폴더 또는 Part4 `ExampleDocs` | 예제 목적, 핵심 개념, 코드 위치, 실행 요약 |
| Topic | `Docs/01_Topics` | 여러 예제를 관통하는 graphics concept 설명 |
| Verification | `Docs/02_Verification` | build/run/capture/known issue 최신 상태 |
| Demo | `Docs/03_Demos` | capture/result 계획, demo 후보, visual result 연결 |
| WorkLog | `Docs/04_WorkLogs` | 작업 종료 시점 요약과 결정 기록 |
| Publication | `Docs/05_Publication` | public subset 후보와 제외 사유 |
| GitHub | `Docs/07_GitHub` | Issue/PR/comment 게시 후보 본문 |

## 운영 기준

- 이 문서는 상태판이 아니라 라우팅 map이다.
- 예제별 README는 코드 폴더 아래에 둔다. `Part4_Chapter14-20`은 단일 project 예외로 `ExampleDocs`를 사용한다.
- 모든 예제의 최신 검증 상태는 `Docs/02_Verification`에서 확인한다.
- capture/result 확보 상태는 `Docs/03_Demos`와 `Docs/02_Verification/capture-matrix.md`에서 확인한다.
- legacy PartDocs는 참고 자료이며 현재 정본으로 보지 않는다.
