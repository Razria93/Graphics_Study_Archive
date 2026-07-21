# Build Run Matrix

이 문서는 archive 기준 최신 build/run/capture 상태의 정본이다.

## 기준

- 검증 정책은 `Docs/07_Policies/verification-policy.md`를 따른다.
- 직접 확인하지 않은 항목은 `미확인`으로 기록한다.
- import manifest, legacy PartDocs, WorkLog는 최신 검증 정본이 아니다.

## Matrix

| Part | 대상 | Debug x64 build | Debug x64 run | Release x64 build | Release x64 run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Part1_Chapter01-02 | 전체 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | legacy 기록 분해 필요 |
| Part1_Chapter03 | 전체 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | legacy 기록 분해 필요 |
| Part2_Chapter04 | 전체 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | legacy 기록 분해 필요 |
| Part2_Chapter05-08 | 전체 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | legacy 기록 분해 필요 |
| Part3_Chapter09 | 전체 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | legacy 기록 분해 필요 |
| Part3_Chapter10-13 | 전체 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | legacy 기록 분해 필요 |
| Part4_Chapter14-20 | 전체 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | `Examples.sln` argument 방식 확인 필요 |
| Portfolio_RayTracer | 전체 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | 대표 작업물 기준 별도 검증 필요 |

## Known Notes

- Part4는 `Examples.sln` 단일 solution과 command argument 기반 실행 흐름을 사용한다.
- Part4 일부 예제는 legacy 기록상 Debug/Release 실행 확인 흔적이 있다.
- 이전 기록은 `Docs/99_Legacy/PartDocs`와 `Docs/99_Legacy/ImportPhase`에서 참고한다.
- 새 검증을 수행하면 이 matrix를 먼저 갱신하고, 상세 evidence는 `Docs/04_Demos`와 연결한다.