---
description: "Run an evidence-based read-only audit of the repository document system."
mode: ask
tools:
  - codebase
  - runCommands
---

# Audit Document System at High Quality

이 prompt는
[Document System Audit Policy](../../Docs/06_Policies/document-system-audit-policy.md)에
따라 문서 체계를 감사한다.

## 입력

- 감사 범위: `Single` / `Impact` / `Chapter` / `Full`
- 대상 경로:
- 감사 모드: `ReadOnly`
- remote 확인: `None` / `ReadOnly`
- 목표 모드: `Auto` / `On` / `Off`
- 에이전트: `Auto` / `None` / 최대 수
- 필수 validator:
- 추가 stale path:

## Full 기본값

- 감사 범위: `Full`
- 감사 모드: `ReadOnly`
- remote 확인: `ReadOnly`
- 목표 모드: `On`
- 에이전트: `Auto`, 하위 최대 3개

## 실행 규칙

1. 메인 에이전트가 root와 관련 하위 `AGENTS.md`를 직접 확인한다.
2. [Audit Guide](../../Docs/98_Tools/document-system-audit-guide.md)의 시작 절차를
   수행한다.
3. 하위 에이전트는 read-only 조사만 수행한다.
4. 메인 에이전트가 모든 최종 근거와 오탐을 재검증한다.
5. Legacy 역사 기록과 현재 정본의 잘못된 연결을 구분한다.
6. validator 결과와 수동 감사 결과를 별도로 비교한다.
7. 같은 root cause의 증상은 하나의 발견 항목으로 통합한다.
8. 파일 수정, stage, commit, remote 변경을 수행하지 않는다.
9. 감사 결과 수정은 별도 `감사 결과 반영 시작` 요청으로 분리한다.
10. 목표 모드나 하위 에이전트를 지원하지 않으면 같은 완료 조건과 조사 관점을
    메인 에이전트가 순차 유지한다.

## 완료 형식

[Document System Audit Report](../../Docs/98_Tools/templates/document-system-audit-report.md)의
구조와 발견 항목 필드를 사용한다. 초기·최종 validator, 변경 여부, commit
readiness를 포함한다.
