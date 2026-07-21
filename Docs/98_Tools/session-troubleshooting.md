# Session Troubleshooting

이 문서는 archive 작업 중 반복되는 세션 문제와 확인 절차를 둔다.

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

## Visual Studio 실행 문제

증상:

- Debug와 Release 실행 대상이 다르다.
- Part4 예제가 다른 번호로 실행된다.
- runtime asset이 없어 실행 중 실패한다.

처리:

- 열린 solution 경로를 확인한다.
- startup project와 command argument를 확인한다.
- shader, texture, model 경로를 확인한다.
- 실패는 `Docs/03_Verification/known-issues.md`에 기록한다.

## 작업 분리 문제

증상:

- 예제 설명, 검증, demo, WorkLog가 한 문서에 섞인다.
- 정책 문서와 실제 산출물이 같은 위치에 들어간다.

처리:

- 예제 설명은 `Docs/01_Examples`에 둔다.
- 검증은 `Docs/03_Verification`에 둔다.
- demo evidence는 `Docs/04_Demos`에 둔다.
- 작업 기록은 `Docs/05_WorkLogs`에 둔다.
- 정책은 `Docs/07_Policies`에 둔다.