# Build Run Matrix

이 문서는 archive 기준 최신 build/run 상태의 정본이다. 직접 확인하지 않은 항목은 `미확인`으로 둔다.

## 기준

- 검증 정책은 `Docs/07_Policies/verification-policy.md`를 따른다.
- Debug x64를 기본 build/run 기준으로 둔다.
- Release x64는 대표 예제 또는 공개 후보에 대해 선택적으로 확인한다.
- import manifest, legacy PartDocs, WorkLog는 최신 검증 정본이 아니다.

## Matrix

| 범위 | solution 기준 | Debug x64 build | Debug x64 run | Release x64 build | Release x64 run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Part1_Chapter01-02 | 예제별 `.sln` | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | `01_DX11InitAndImGui`, `02_Bloom` |
| Part1_Chapter03 | 예제별 `.sln` | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | ray tracing step 예제 |
| Part2_Chapter04 | 예제별 `.sln` | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | rasterization step 예제 |
| Part2_Chapter05-08 | 예제별 `.sln` | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | transform, pipeline, modeling, shader toy |
| Part3_Chapter09 | 예제별 `.sln` | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | user interaction |
| Part3_Chapter10-13 | 예제별 `.sln` | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | geometry, texturing, PBR, shadow |
| Part4_Chapter14-20 | `Part4_Chapter14-20/Examples.sln` | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | 단일 solution과 실행 argument 확인 필요 |
| Portfolio_RayTracer | solution 확인 필요 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | 프로젝트 구조 확인 필요 |

## 갱신 규칙

- 실제 검증을 수행하면 이 matrix를 먼저 갱신한다.
- 예제별 상세 결과는 해당 Part/Chapter의 `verification-index.md` 또는 별도 검증 문서에 기록한다.
- capture evidence는 `capture-matrix.md`와 `Docs/04_Demos`에 연결한다.
- 실패 원인은 `known-issues.md`에 요약한다.
