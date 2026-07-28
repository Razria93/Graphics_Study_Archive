# Part4_Chapter14-20 Verification Index

이 문서는 `Part4_Chapter14-20`의 build/run/capture 상태를 기록한다.

## Provenance

- 확인 근거: 과거 확인
- 확인 시점: 문서화 이전(날짜 미기록)
- 현재 재검증: 필요
- 근거: Chapter README에 기록된 Ex1401~Ex2001 Debug/Release build/run 성공

| 예제 또는 단위 | solution | Debug build | Debug run | Release build | Release run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `Part4_Chapter14-20` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요. 실행 argument와 sample 선택 방식 문서화 필요 |

## 갱신 기준

- `Examples.sln`의 startup project와 실행 argument를 확인한다.
- 실제 sample 단위가 확인되면 행을 분리한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
