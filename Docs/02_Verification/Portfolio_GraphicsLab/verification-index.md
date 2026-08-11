# Portfolio_GraphicsLab Verification Index

이 문서는 `Portfolio_GraphicsLab`의 build/run/capture 상태를 기록한다.

| 예제 또는 단위 | solution | Debug build | Debug run | Release build | Release run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| [WU-R0 canonical scaffold](wu-r0-canonical-scaffold.md) | `GraphicsLab.sln` | 성공 | 성공 | 성공 | 성공 | 제외 | 2026-08-11 manifest restore와 두 CWD smoke run 현재 확인 |
| `Rendering/RayTracing` | WU-R0 이후 연결 | 미확인 | 미확인 | 미확인 | 미확인 | 미확인 | reconstruction milestone에서 구현 |

## 갱신 기준

- WU-R0에서는 x64 Debug/Release build와 두 CWD smoke run을 기록한다.
- RayTracing과 후속 graphics pipeline은 구현 축별로 별도 행을 추가한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
- capture/result는 renderer가 화면 출력을 제공한 뒤 기록한다.
