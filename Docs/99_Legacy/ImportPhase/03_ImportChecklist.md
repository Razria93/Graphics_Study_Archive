# Import Checklist

이 문서는 각 Part/Chapter/Example import 작업을 시작하기 전과 끝난 뒤 확인할 체크리스트입니다.

## 역할

- 작업자가 빠뜨리기 쉬운 확인 항목을 모읍니다.
- 정책 문장은 반복하지 않고 [Import Policy](01_ImportPolicy.md)를 참조합니다.
- 검증 세부 절차는 [Import Verification](04_ImportVerification.md)를 참조합니다.

## 착수 전 확인

| 항목             | 확인 내용                                      |
| -------------- | ------------------------------------------ |
| Branch         | 현재 브랜치가 작업 대상에 맞는지 확인                      |
| Working tree   | `git status --short`로 이전 작업 변경분이 섞여 있는지 확인 |
| Latest commit  | 직전 commit이 어떤 단위였는지 확인                     |
| Raw access     | raw/reference 경로를 읽을 수 있는지 확인              |
| Archive target | archive에 만들거나 수정할 target folder 확인         |
| Existing docs  | `Docs/Part*_Chapter*/...` 문서가 이미 있는지 확인    |
| Local docs     | `local/Part*_Chapter*/...` 작업 재료 위치 확인     |
| Build tools    | Visual Studio 또는 MSBuild 실행 가능 여부 확인       |

## Raw 조사

파일을 반영하기 전에 raw 구조만 먼저 읽습니다.

| 항목                        | 판단                                            |
| ------------------------- | --------------------------------------------- |
| `.sln`, `.vcxproj`        | archive에 필요한 project files인지 확인               |
| source/header/shader      | 실행에 필요한 코드 파일인지 확인                            |
| image/texture/model asset | 출처/라이선스 확인 전까지 기본은 `검토 필요`                    |
| result/capture/video      | raw 결과물은 기본적으로 복사하지 않음                        |
| local/build output        | [Import Policy](01_ImportPolicy.md)의 제외 기준 확인 |
| source comments           | local-only 문서로 분리할 메모가 있는지 확인                 |
| raw markdown docs         | 관련 문서 위치만 먼저 기록                               |


## Variant / Snapshot 판단

비슷한 예제 폴더가 여러 개 있을 때는 먼저 기준 source를 정합니다.

| 패턴 | 기본 판단 | 기록 위치 |
| --- | --- | --- |
| `_Debug` | 제외 / reference-only | 해당 Part manifest |
| `_Backup`, temporary experiment | 제외 / reference-only | 필요 시 local review note |
| `_Solution` | 직접 import하지 않고 비교 후보로 검토 | 해당 예제 manifest |
| duplicate snapshot folder | primary source와 비교 후 reference-only 유지 | 해당 Part/Chapter manifest |
| zip/raw asset archive | tracked archive 기준 아님 | asset note 또는 manifest |

기준 source를 선택한 이유는 manifest에 남기고, 최신 build/run/capture 상태는 `Docs/_repo/BuildRunVerificationMatrix.md`에서 관리합니다.

## 작업 전 결정

작업을 시작하기 전에 사용자에게 짧게 보고합니다.

```text
이번 예제에서 반영할 것:
- code/project files:
- tracked docs:
- local-only docs:

이번 예제에서 제외할 것:
- raw assets:
- raw result/capture:
- private-only notes:

주의할 점:
- build/run status:
- raw/original diff:
- refactor risk:
```

## 파일 반영 전 확인

- import manifest를 작성했는가
- 포함/제외 기준을 [Import Policy](01_ImportPolicy.md)에 맞춰 확인했는가
- raw 폴더를 통째로 복사하지 않았는가
- 출처/라이선스가 불명확한 asset을 `검토 필요`로 표시했는가
- source comment 정리 범위를 `.cpp`, `.h` 중심으로 제한했는가
- project/shader/binary 파일을 text rewrite 대상으로 삼지 않았는가

## 작업 후 확인

| 항목                  | 명령 또는 확인                                                  |
| ------------------- | --------------------------------------------------------- |
| 파일 목록               | `rg --files <target>`                                     |
| raw asset 유입        | image/result/capture/video가 들어왔는지 확인                      |
| source comments     | 장문 메모가 남아 있는지 확인                                          |
| local-only docs     | `git status --short --ignored local/...`                  |
| whitespace          | `git diff --check`                                        |
| working tree        | `git status --short`                                      |
| build/run           | 가능하면 `Debug x64` 확인, 불가하면 `미확인` 기록                        |
| import verification | [Import Verification](04_ImportVerification.md)의 필수 체크 확인 |

## Commit 안내 기준

commit은 사용자가 명시적으로 요청할 때만 수행합니다. 단, 아래 단위가 끝나면 commit 타이밍으로 안내할 수 있습니다.

- 예제 1개의 code split + tracked docs/status 갱신
- 예제 1개의 build/run 확인 기록
- Part 하나의 import manifest 갱신
- 공통 workflow/template 변경
