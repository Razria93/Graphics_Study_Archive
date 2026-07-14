# AI Collaboration Safety

이 문서는 archive 작업 중 AI assistant가 작업 범위와 위험도를 어떻게 확인해야 하는지 정리합니다.

## 기본 원칙

- 사용자가 명시한 목표를 우선하되, 되돌리기 어려운 작업은 실행 전에 한 번 멈춰서 확인합니다.
- 긴 요청 안에 여러 작업이 붙어 있으면 작업을 작은 단위로 나누어 제안합니다.
- 사용자가 한 번에 진행하라고 한 경우에도, push/merge/delete/history rewrite처럼 영향이 큰 작업은 사전 스캔 결과와 권장 진행 방식을 먼저 공유합니다.
- 객관적으로 안전한 기본안이 있으면 권장안을 함께 제시합니다.
- repository 또는 project의 존속에 큰 문제가 될 수 있는 사안을 발견하면 작업을 멈추고 먼저 보고합니다.

## 즉시 중단하고 보고할 상황

아래 상황은 사용자의 기존 요청보다 중단 보고를 우선합니다.

- 원격 `main` 또는 주요 branch의 history를 다시 써야 하는 경우
- 대용량 파일, LFS quota, repository size가 repo 사용을 막을 가능성이 있는 경우
- private-only 자료, 유료 자료, 계정/개인정보가 commit 또는 public 공개 범위에 들어갈 가능성이 있는 경우
- build/run 재현성을 크게 깨뜨리는 구조 변경이 필요한 경우
- raw/original 자료를 archive로 대량 복사해야 해서 저작권/라이선스 범위를 판단하기 어려운 경우
- 기존 작업물을 복구하기 어렵게 삭제하거나 덮어써야 하는 경우

## 사전 확인이 필요한 작업

아래 작업은 실행 전에 현재 상태를 확인하고 계획을 짧게 보고합니다.

- `git push`
- PR 생성, PR merge
- `git pull`, `git fetch --prune`
- branch 삭제
- commit history rewrite, rebase, reset
- Git LFS migration 또는 대용량 asset 추적 방식 변경
- raw repo에서 archive로 대량 복사
- public 공개 범위에 영향을 주는 파일 이동

## 권장 진행 방식

1. `git status --short --branch`로 현재 branch와 worktree를 확인합니다.
2. 작업 대상 파일, 브랜치, 원격 상태를 스캔합니다.
3. 되돌리기 어려운 지점을 표시합니다.
4. 여러 작업이 묶여 있으면 다음 중 하나를 제안합니다.
   - 한 번에 진행: 상태가 clean이고 되돌리기 위험이 낮을 때
   - 단계별 진행: push/merge/delete처럼 원격 상태를 바꾸는 작업이 포함될 때
5. 사용자의 확인 후 실행합니다.

## 연속 요청 처리

사용자가 "PR 만들고 push/merge하고 브랜치 제거"처럼 연속 작업을 요청하면 다음 순서로 나눕니다.

1. 작업 범위 스캔
2. PR 생성 전 diff/commit/branch 확인
3. push
4. PR 생성
5. merge 가능 상태 확인
6. merge
7. local main 동기화
8. local/remote branch 정리
9. 최종 상태 확인

기본 권장안은 단계별 진행입니다. 단, 사용자가 명확히 자동 진행을 원하고 상태가 단순하면 각 단계의 결과를 확인하면서 이어서 진행할 수 있습니다.

## 보고 형식

짧게 아래 항목을 포함합니다.

- 현재 branch/worktree 상태
- 대상 branch 또는 파일
- 되돌리기 어려운 작업 여부
- 권장 진행 방식
- 실행 후 검증 방법

## 시행착오 기록

- PR merge와 branch delete는 되돌리기 비용이 크므로, 사용자가 한 문장에 함께 요청하더라도 사전 스캔과 단계 분리를 기본으로 둡니다.
- 대용량 binary asset은 GitHub push 경고가 발생할 수 있습니다. 새 asset import 전에는 LFS 대상 여부를 먼저 확인합니다.
