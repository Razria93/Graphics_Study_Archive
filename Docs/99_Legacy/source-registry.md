# Source Registry

이 문서는 archive로 가져온 코드 범위의 추적 가능한 provenance를 기록한다.
로컬 raw/reference 경로는 기록하지 않으며 최신 build/run 상태는
`Docs/02_Verification`에 위임한다.

## Tracked Source

| Source ID | Archive 범위 | 관계 | Start commit | Completion commit | 관련 branch |
| --- | --- | --- | --- | --- | --- |
| `SRC-P1-C03` | `Part1_Chapter03` | top-level 1:1 | [`141fb4e`](https://github.com/Razria93/Graphics_Study_Archive/commit/141fb4ee8da6f866913beaddeba37e2d87b9ed4b) | [`846cee1`](https://github.com/Razria93/Graphics_Study_Archive/commit/846cee1c1982f31ce13309df02a59a7d8b08b0f7) | `archive/part1` |
| `SRC-P2-C04` | `Part2_Chapter04` | top-level 1:1 | [`c5f08cd`](https://github.com/Razria93/Graphics_Study_Archive/commit/c5f08cd77be56d9805d1a331e51473235e4ece89) | [`98e7930`](https://github.com/Razria93/Graphics_Study_Archive/commit/98e7930e65e56dc33488f94fb85fec8007f486e9) | `archive/part2` |
| `SRC-P2-C05-08` | `Part2_Chapter05-08` | top-level 1:1, 내부 variant 포함 | [`44233c1`](https://github.com/Razria93/Graphics_Study_Archive/commit/44233c1bdf9b4d6606ace7f5d873093607a19dfc) | [`f90467d`](https://github.com/Razria93/Graphics_Study_Archive/commit/f90467d6820fba4e037190fe17c4c0358804b8eb) | `archive/part2` |
| `SRC-P3-C09` | `Part3_Chapter09` | top-level 1:1 | [`73b2bd8`](https://github.com/Razria93/Graphics_Study_Archive/commit/73b2bd848c2a17e852ff5a81137b680be47acc6e) | [`71efd50`](https://github.com/Razria93/Graphics_Study_Archive/commit/71efd50219fccca0c8c33295a81d071ddbae0440) | `archive/part3` |
| `SRC-P3-C10-13` | `Part3_Chapter10-13` | N:1 (primary 1 + reference N) | [`5703b7c`](https://github.com/Razria93/Graphics_Study_Archive/commit/5703b7cf173c2d34222b3c60cbe8fd5393415e8a) | [`512bf76`](https://github.com/Razria93/Graphics_Study_Archive/commit/512bf7601983646a747af6a8a1acd15dd11380bf) | `archive/part3` |
| `SRC-P4-C14-20` | `Part4_Chapter14-20` | N:1 (primary 1 + reference 2) | [`2bead38`](https://github.com/Razria93/Graphics_Study_Archive/commit/2bead3861396dd8b67dc6821a56736bef606c6e9) | [`6cc237c`](https://github.com/Razria93/Graphics_Study_Archive/commit/6cc237c4e691312446a5980fb86c0fea2d9e63e9) | `archive/part4` |
| `SRC-PORTFOLIO-RAYTRACER` | `Portfolio_RayTracer` | 미확인 | 미확인 | 미확인 | 미확인 |

`Start commit`과 `Completion commit`은 해당 범위를 가져온 작업의 시작점과
마감점을 각각 가리킨다. Git revision range 표현이 아니며 두 commit 사이의
모든 변경이 동일 source에 속한다는 뜻이 아니다.

## Local Raw Mapping

추적되지 않는 raw/reference repo는 같은 Source ID를 사용해 local-only 문서에서
실제 경로와 대응시킨다. 권장 형식은 다음과 같다.

| Source ID | Local path | 확인 상태 | 비고 |
| --- | --- | --- | --- |
| `SRC-*` | 절대 경로 | 확인 / 미확인 | tracked 문서에 복사하지 않을 메모 |

tracked 문서에서는 Source ID와 import Git history만 사용한다. 로컬 절대 경로,
유료 자료 위치, 개인 환경 정보는 이 registry에 추가하지 않는다.

## 사용 기준

- 현재 Chapter README는 로컬 raw 경로 대신 Source ID와 이 registry를 연결한다.
- source provenance는 import와 비교 기준을 설명하며 코드 내용의 정본을
  대체하지 않는다.
- 최신 코드 설명은 코드 폴더 README, 최신 검증 결과는
  `Docs/02_Verification`을 기준으로 한다.
- `Portfolio_RayTracer`는 code import 근거가 확인될 때까지 commit과 관계를
  `미확인`으로 유지한다.
