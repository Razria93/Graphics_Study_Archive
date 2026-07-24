# Agent Safety Policy

이 문서는 agent가 작업 범위와 위험도를 다루는 기준을 정의한다.

## 기본 원칙

- 작업 전 `git status --short --branch`를 확인한다.
- 사용자가 명시적으로 요청하거나 현재 대화에서 커밋까지 승인한 작업 단위가 아니면 commit, push, PR, Issue 생성/수정을 하지 않는다.
- 되돌리기 어려운 작업은 실행 전 범위와 위험도를 보고한다.
- repository 존속에 영향을 줄 수 있는 위험을 발견하면 작업을 멈추고 먼저 보고한다.

## 사전 보고 대상

- push, pull, merge, rebase
- branch 삭제
- history rewrite, reset
- LFS import 또는 대용량 asset 추적 방식 변경
- raw repo에서 archive로 대량 복사
- public 공개 범위에 영향을 주는 파일 이동
- 기존 작업물을 복구하기 어렵게 삭제하는 작업

## 보고 기준

- 현재 branch와 worktree 상태
- 대상 파일 또는 branch
- 되돌리기 어려운 지점
- 권장 진행 방식
- 실행 후 검증 방법
