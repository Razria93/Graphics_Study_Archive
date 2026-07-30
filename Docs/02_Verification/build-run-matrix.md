# Build Run Matrix

이 문서는 archive 기준 build/run 결과와 provenance, 현재 재검증 상태의 정본이다. 직접 확인한 근거가 없는 항목은 `미확인`으로 둔다.

## 기준

- 검증 정책은 `Docs/06_Policies/verification-policy.md`를 따른다.
- Debug x64를 기본 build/run 기준으로 둔다.
- Release x64는 대표 예제 또는 공개 후보에 대해 선택적으로 확인한다.
- import manifest, legacy PartDocs, WorkLog는 최신 검증 정본이 아니다.

## Matrix

| 범위 | solution 기준 | Debug x64 build | Debug x64 run | Release x64 build | Release x64 run | Provenance | 현재 재검증 | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Part1_Chapter01-02 | 예제별 `.sln` | 성공 | 성공 | 성공 | 성공 | 현재 확인 | 완료 | 확보 | 두 예제 build/run 성공. `01_DX11InitAndImGui` capture 제외, `02_Bloom` input/result 확보 |
| Part1_Chapter03 | 예제별 `.sln` | 성공 | 성공 | 성공 | 성공 | 혼합 | 부분 완료 | 확보 | Step4~10은 2026-07-30~31 현재 확인, Step11~14는 과거 확인·재검증 필요. Step10 capture는 외부 입력 texture 권리 검토 보류 |
| Part2_Chapter04 | 예제별 `.sln` | 성공 | 성공 | 성공 | 성공 | 과거 확인 | 필요 | 미확인 | 문서화 이전 전체 예제 확인, 날짜 미기록 |
| Part2_Chapter05-08 | 예제별 `.sln` | 성공 | 성공 | 성공 | 성공 | 과거 확인 | 필요 | 미확인 | 문서화 이전 전체 예제 확인, 날짜 미기록 |
| Part3_Chapter09 | 예제별 `.sln` | 성공 | 성공 | 성공 | 성공 | 과거 확인 | 필요 | 미확인 | 문서화 이전 전체 예제 확인, 날짜 미기록 |
| Part3_Chapter10-13 | 예제별 `.sln` | 성공 | 성공 | 성공 | 성공 | 과거 확인 | 필요 | 미확인 | 문서화 이전 현재 index 범위 확인, 날짜 미기록 |
| Part4_Chapter14-20 | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 과거 확인 | 필요 | 미확인 | 문서화 이전 Ex1401~Ex2001 확인, 날짜 미기록 |
| Portfolio_RayTracer | solution 확인 필요 | 미확인 | 미확인 | 미확인 | 미확인 | 없음 | 해당 없음 | 미확인 | 프로젝트 구조와 실행 진입점 확인 필요 |

## 갱신 규칙

- 현재 검증 또는 과거 확인 근거가 생기면 이 matrix를 먼저 갱신한다.
- 과거 성공 이후 현재 작업에서 다시 실행하지 않았으면 결과는 `성공`으로 유지하고 provenance `과거 확인`, 현재 재검증 `필요`를 함께 기록한다.
- 예제별 상세 결과는 해당 Part/Chapter의 `verification-index.md` 또는 별도 검증 문서에 기록한다.
- capture/result는 `capture-matrix.md`와 `Docs/03_Demos`에 연결한다.
- 실패 원인은 `known-issues.md`에 요약한다.
