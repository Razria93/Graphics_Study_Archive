# Chapter Start Checklist

이 문서는 각 챕터/예제 작업을 시작하기 전에 확인할 항목과, 작업 중 생긴 시행착오를 기록하는 운영 체크리스트입니다.

목표는 바로 파일을 옮기기 전에 작업 범위, 권한, raw asset 위험, 문서 위치, commit 단위를 먼저 확인하는 것입니다.

## 착수 전 확인

작업을 시작하기 전에 아래 항목을 먼저 확인합니다.

| 항목 | 확인 내용 |
| --- | --- |
| Branch | 현재 브랜치가 작업 대상에 맞는지 확인 |
| Working tree | `git status --short`로 이전 작업 변경분이 섞여 있는지 확인 |
| Latest commit | 직전 commit이 어떤 단위였는지 확인 |
| Raw access | raw/reference 경로를 읽을 수 있는지 확인 |
| Archive target | archive에 만들거나 수정할 target folder 확인 |
| Existing docs | `Docs/Part*_Chapter*/...` 문서가 이미 있는지 확인 |
| Local docs | `local/Part*_Chapter*/...` 작업 재료 위치 확인 |
| Build tools | `MSBuild.exe`, Visual Studio 실행 가능 여부 확인 |

## Raw 조사

파일을 복사하기 전에 raw 구조만 먼저 읽습니다.

| 항목 | 판단 |
| --- | --- |
| `.sln`, `.vcxproj` | archive에 필요한 project files인지 확인 |
| source/header/shader | 실행에 필요한 코드 파일인지 확인 |
| image/texture/model asset | 출처/라이선스 확인 전까지 기본은 `검토 필요` |
| result/capture/video | raw 결과물은 기본적으로 복사하지 않음 |
| `.vs`, `x64`, `Debug`, `Release`, `.user` | 제외 |
| source comments | local-only 문서로 분리할 메모가 있는지 확인 |
| raw markdown docs | 관련 문서 위치만 먼저 기록 |

## 작업 전 결정

작업을 시작하기 전에 사용자에게 짧게 보고할 내용입니다.

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

## 파일 반영 원칙

- raw 폴더를 통째로 복사하지 않습니다.
- source/header/shader/project files만 먼저 선별합니다.
- raw asset은 출처/라이선스 확인 전까지 복사하지 않습니다.
- 실행에 asset이 꼭 필요하면 먼저 fallback 전략을 제안합니다.
- 기존 장문 학습 주석은 source에서 제거하고 `local/`에 분리합니다.
- source에는 섹션 구분, 구현 의도, lifetime/path 주의 정도만 남깁니다.
- 코드 동작을 바꾸는 리팩터링은 반드시 status 문서에 기록합니다.

## 작업 후 확인

작업이 끝나면 아래를 확인합니다.

| 항목 | 명령 또는 확인 |
| --- | --- |
| 파일 목록 | `rg --files <target>` |
| raw asset 유입 | image/result/capture/video가 들어왔는지 확인 |
| source comments | 장문 메모가 남아 있는지 확인 |
| local-only docs | `git status --short --ignored local/...` |
| whitespace | `git diff --check` |
| working tree | `git status --short` |
| build/run | 가능하면 `Debug x64` 확인, 불가하면 `미확인` 기록 |

## 시행착오 로그

### 2026-07-08: `02_Bloom` 폴더 생성 권한과 patch 흐름

상황:
- `Part1_Chapter01-02/02_Bloom` 및 `Docs/Part1_Chapter01-02/02_Bloom` 하위 폴더 생성이 sandbox에서 거부되었습니다.
- 승인 실행으로 폴더와 raw 파일을 선별 복사했습니다.
- 이후 일부 source file은 `apply_patch`에서 delete 후 add 형태로 재작성되며 중간 상태가 잠시 생겼습니다.

배운 점:
- 새 예제 폴더를 만들기 전에 target parent directory에 하위 폴더 생성이 가능한지 먼저 테스트합니다.
- 권한 문제로 승인 실행을 쓰는 경우, 복사 직후 `rg --files`와 `git status --short`로 실제 반영 파일을 확인합니다.
- raw 파일을 먼저 복사한 뒤 크게 재작성해야 한다면, 작업 전 사용자에게 “원본 대비 변경이 큰 refactor”라고 명시합니다.
- asset fallback 같은 동작 변경은 status 문서에 `Raw/original diff review 필요`로 기록합니다.

다음 대응:
- 각 예제 착수 전 이 문서를 먼저 확인합니다.
- 작업 전 plan에서 “복사만 할지, 정리/리팩터링까지 할지”를 분리합니다.
- build/run 확인 전에는 `Capture ready`를 `아니오`로 유지합니다.
