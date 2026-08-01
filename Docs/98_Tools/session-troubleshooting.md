# Session Troubleshooting

이 문서는 archive 작업 중 반복되는 세션 문제와 확인 절차를 둔다.

## gh 인증과 실행 환경

`gh`가 keyring 또는 token 오류를 보고해도 인증 만료로 바로 단정하지 않는다. 같은 read-only 명령을 승인된 PowerShell 실행 환경에서 다시 확인한다. sandbox 밖에서는 성공하면 keyring 접근 범위 차이로 분류한다.

토큰 값을 출력하거나 환경 변수로 주입해 우회하지 않는다. 승인된 환경에서도 실패하면 remote 작업을 중단하고 `gh auth status` 결과와 필요한 재인증 절차를 보고한다.

## UTF-8 GitHub Body

한글 body는 UTF-8 파일을 `--body-file`로 전달한다. shell 문자열 조합이나 encoding이 불명확한 임시 변환은 사용하지 않는다. 게시 후에는 remote body를 다시 읽어 글자 깨짐과 누락을 확인한다.

Issue와 PR 후보는 첫 H1을 title source로 사용한다. remote body 비교 전 첫 H1과 바로 뒤 빈 줄을 제거해 게시 변환을 정규화한다.

## Remote 변경 부분 실패

여러 remote 객체를 한 번에 수정하지 않는다. 한 객체를 변경한 뒤 실제 상태를 확인하고 다음 객체로 이동한다.

일부 변경만 성공하면 다음 변경을 중단한다. 성공한 대상, 실패한 대상과 아직 실행하지 않은 대상을 구분하고 read-only로 remote 상태를 재확인한다. 확인되지 않은 rollback이나 다른 객체의 보상 수정을 시도하지 않는다.

## Branch Head 불일치

push 전 upstream이 local HEAD의 ancestor인지 확인한다. non-fast-forward 가능성이 있거나 tracking ref와 실제 remote head가 다르면 push와 PR body 수정을 중단한다.

push 후 local HEAD, tracking ref, 실제 remote branch head와 PR head가 모두 일치하는지 확인한다. 불일치를 해소하기 전에는 Ready 전환이나 후속 remote 변경을 진행하지 않는다.

## 기본 확인

- 작업 전 `git status --short --branch`를 확인한다.
- 현재 branch가 의도한 작업 branch인지 확인한다.
- raw repo는 읽기 전용 reference로만 사용한다.
- archive에 복사할 자료는 선별 기준을 먼저 확인한다.

## 권한 문제

증상:

- 파일 쓰기 실패
- read-only 속성으로 인한 수정 실패
- parent directory 생성 실패

처리:

- 대상 경로가 archive 내부인지 확인한다.
- 파일 속성을 확인한다.
- 필요한 경우 사용자 승인 후 대상 범위에 한정해 속성을 조정한다.

## 인코딩 문제

증상:

- PowerShell 출력에서 한글이 깨져 보인다.
- 파일 내용과 콘솔 표시가 다르게 보인다.

처리:

- VSCode 또는 GitHub diff 표시를 기준으로 최종 확인한다.
- 새 tracked Docs는 UTF-8로 작성한다.
- 깨진 기존 문서는 legacy로 보존하고 새 정본 문서로 재작성한다.

### Actions PowerShell host 불일치

`pwsh`로 실행한 fixture가 내부에서 `powershell.exe`를 고정 호출하면 영문 Windows runner의 system code page가 BOM 없는 UTF-8 script를 다르게 해석할 수 있다. 직접 validator는 통과하지만 자식 process에서 parser 오류가 발생하는 형태로 나타난다.

Fixture가 별도 process로 validator의 exit code를 검사해야 하면 현재 process의 executable을 사용한다.

```powershell
$powerShellPath = [Diagnostics.Process]::GetCurrentProcess().MainModule.FileName
& $powerShellPath -NoProfile -ExecutionPolicy Bypass -File $validator
```

이 오류는 `gh` 인증이나 repository 권한 문제로 분류하지 않는다. Actions log에서 실패한 shell, 직접 validator 단계와 fixture의 자식 process 호출을 비교한다.

## Visual Studio 실행 문제

증상:

- Debug와 Release 실행 대상이 다르다.
- Part4 예제가 다른 번호로 실행된다.
- runtime asset이 없어 실행 중 실패한다.

처리:

- 열린 solution 경로를 확인한다.
- startup project와 command argument를 확인한다.
- shader, texture, model 경로를 확인한다.
- 실패는 `Docs/02_Verification/known-issues.md`에 기록한다.

## 작업 분리 문제

증상:

- 예제 설명, 검증, demo, WorkLog가 한 문서에 섞인다.
- 정책 문서와 실제 산출물이 같은 위치에 들어간다.

처리:

- 예제 설명은 대상 코드 폴더 README에 둔다.
- 검증은 `Docs/02_Verification`에 둔다.
- Demo capture/result는 `Docs/03_Demos`에 둔다.
- 작업 기록은 `Docs/04_WorkLogs`에 둔다.
- 정책은 `Docs/06_Policies`에 둔다.
