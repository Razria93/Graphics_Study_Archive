# Capture Matrix

이 문서는 build/run 검증과 연결되는 capture/result 상태를 요약한다. 실제 demo 계획과 capture/result 설명은 `Docs/03_Demos`를 정본으로 둔다.

## 상태 기준

- 정책 검수 PASS는 capture/result `확보`가 아니다.
- capture/result 후보는 후보 검수와 승격 검수를 별도로 통과해야 한다.
- 강의명, 강사명, 워터마크, 개인 식별자, 계정, 로컬 경로가 보이면 `확보`가 아니라 `보류` 또는 `제외`로 기록한다.

| 범위 | 최소 capture/result | 대표 capture/result | video | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- |
| Part1_Chapter01-02 | 보류 | 보류 | 미확인 | 보류 | `02_Bloom` runtime result 생성 확인. 워터마크/권리 검토 전까지 `Docs/_assets` 승격 보류 |
| Part1_Chapter03 | 미확인 | 미확인 | 미확인 | 미확인 | ray tracing 단계별 결과 후보 |
| Part2_Chapter04 | 미확인 | 미확인 | 미확인 | 미확인 | rasterization, depth buffer 후보 |
| Part2_Chapter05-08 | 미확인 | 미확인 | 미확인 | 미확인 | modeling, IBL, bloom 후보 |
| Part3_Chapter09 | 미확인 | 미확인 | 미확인 | 미확인 | interaction 영상 후보 |
| Part3_Chapter10-13 | 미확인 | 미확인 | 미확인 | 미확인 | PBR, shadow 후보 |
| Part4_Chapter14-20 | 미확인 | 미확인 | 미확인 | 미확인 | 구조 확인 후 후보 확정 |
| Portfolio_RayTracer | 미확인 | 미확인 | 미확인 | 미확인 | 대표 포트폴리오 후보 |

## 갱신 기준

- capture/result는 build/run 성공 또는 부분 성공 상태와 연결한다.
- 강의 화면 캡처와 출처 불명 asset은 capture/result 후보로 두지 않는다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
