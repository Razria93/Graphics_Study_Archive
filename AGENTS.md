# Repository Guidelines

이 저장소는 DirectX11 graphics study examples와 개인 확장 작업을 private archive 형태로 정리하는 작업 공간이다. 목표는 raw 자료를 그대로 공개하는 것이 아니라, 코드 확인, 문서 재작성, 검증 기록, Demo capture/result, GitHub Issue/PR 요약을 통해 설명 가능한 portfolio archive를 만드는 것이다.

## 공통 운영 원칙

- 작업 전 `git status --short --branch`를 확인한다.
- 사용자가 명시적으로 요청하거나 현재 대화에서 커밋까지 승인한 작업 단위가 아니면 commit, push, PR, Issue 생성/수정을 하지 않는다.
- root의 `Part*_Chapter*`와 `Portfolio_GraphicsLab` 폴더는 코드와 build 기준으로 유지한다.
- 문서 용어는 `Docs/06_Policies/terminology-policy.md`를 따른다.
- 문서 정본은 코드 폴더 README와 `Docs/00_Index`부터 `Docs/07_GitHub`까지의 산출물 축 구조, `Docs/98_Tools`, `Docs/99_Legacy` 책임 경계를 기준으로 작성한다.
- 기존 `Docs/Part*` 문서는 정본으로 사용하지 않고 `Docs/99_Legacy/PartDocs`의 전환기 참고 자료로만 사용한다.
- raw/reference repo의 내용은 필요한 부분만 읽고, Git에 추적되는 Docs/AGENTS 문서에는 직접 이해한 설명으로 재작성한다.
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료, 강의 화면 캡처, 문제/해설 전문은 archive/public 후보로 확정하지 않는다.
- `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `.suo`, `imgui.ini`, 임시 캡처, raw result는 추가하지 않는다.
- build/run/capture를 직접 확인하지 않은 항목은 `미확인`으로 기록한다.
- push, pull, merge, rebase, branch delete, history rewrite, LFS import 같은 되돌리기 어려운 작업은 실행 전에 범위와 위험도를 보고하고 승인받는다.
- 포트폴리오 증빙용 브랜치는 보존 대상일 수 있으므로 로컬/원격 브랜치를 임의로 삭제하지 않는다.
- PR merge는 사용자가 다르게 명시하지 않는 한 일반 merge commit 방식만 사용하고 squash merge, rebase merge, history rewrite를 사용하지 않는다.
- 작업 종료 시에는 commit readiness를 보고하고, 커밋 가능 상태라면 Git Bash 기준 `git add` 대상과 권장 commit 메시지를 제안한다.

## 문서 위치

- `Docs/00_Index`: 전체 map과 진입점
- 코드 폴더 README: 예제 설명 정본
- `Docs/01_Topics`: graphics 개념 정본
- `Docs/02_Verification`: build/run/capture 검증 정본
- `Docs/03_Demos`: 구현 선택, 시각 자료, 결과 해석, limitation을 설명하는 상세 Demo 정본
- `Docs/04_WorkLogs`: Issue/PR 작업 기록 정본
- `Docs/05_Publication`: public subset 판단 정본
- `Docs/06_Policies`: 문서화, 검증, demo, GitHub 운영, 공개 정책 정본
- `Docs/07_GitHub`: GitHub Issue/PR/comment 게시 후보 정본
- `Docs/98_Tools`: validator, templates, troubleshooting 같은 도구 문서
- `Docs/99_Legacy`: import 기록과 이전 문서 구조
- `local/`: mini plan, raw 검토 메모, GitHub draft/public 사본, 원본 캡처/영상 후보

## AGENTS 계층 규칙

- 상위 공통 안전 규칙은 항상 유지한다.
- 작업 대상 폴더에 하위 `AGENTS.md`가 있으면 해당 폴더 범위의 추가/제한 규칙으로 적용한다.
- 하위 `AGENTS.md`와 상위 규칙이 직접 충돌하면 하위 문서를 우선하되, commit, push, PR, Issue, merge, rebase, 삭제 같은 안전 게이트는 완화하지 않는다.
- 정책 원문은 `Docs/06_Policies`에 둔다.
- import/history 원문은 `Docs/99_Legacy`에 둔다.
- 에이전트는 파일 수정 전 해당 작업 범위의 README와 AGENTS를 먼저 확인한다.

## 작업 profile 진입점

- 모든 작업은 `Docs/98_Tools/work-session-quickstart.md`에서 `Graphics Work` 또는 `Maintenance Work`로 먼저 분류한다.
- 유형별 필수 산출물, 고정 작업 순서, 검증과 종료 조건은 `Docs/06_Policies/work-profile-policy.md`를 따른다.
- Work Unit 상태와 마감은 `Docs/06_Policies/work-unit-workflow-policy.md`, GitHub 승인과 remote 실행은 `Docs/06_Policies/github-workflow-policy.md`를 따른다.

## 문서 감사 진입점

- `문서 단일검수 시작`, `문서 영향감사 시작`, `문서 전수감사 시작`, `감사 결과 반영 시작`, `감사 결과 게시 시작`을 문서 감사 workflow keyword로 사용한다.
- keyword의 범위, 목표 모드, 에이전트 구성, 권한은 `Docs/06_Policies/document-system-audit-policy.md`를 따른다.
- 실행 절차와 보고 형식은 `Docs/98_Tools/document-system-audit-guide.md`를 따른다.
- root에는 상세 감사 규칙을 복제하지 않는다.

## 사용자 주의 알림

- 목표 모드 완료·중단, 장시간 도구 작업 완료, 사용자 승인·결정 대기와 진행 불가처럼 사용자가 확인해야 하는 terminal point에서 알림을 한 번 실행한다.
- 후속 작업에 바로 사용하는 완성형 작업 프롬프트를 최종 산출물로 제공한 경우에는 60초 지연 알림을 예약한다.
- 단순 설명, 짧은 질의응답, 중간 commentary와 status update에는 실행하지 않는다.
- 한 assistant turn에서는 terminal point가 겹쳐도 알림을 최대 한 번만 실행한다.
- blocker와 사용자 결정 대기는 즉시 알림을 우선하고, 목표 완료와 완성형 작업 프롬프트 제공이 겹치면 지연 알림을 사용한다.
- 목표 모드를 종료할 때는 목표 상태를 먼저 정리하고 최종 응답 직전에 실행한다.
- 알림 실패는 원래 작업 결과를 변경하지 않는다.
- 실행 조건과 명령은 `Docs/98_Tools/user-attention-notification.md`를 따른다.

## 문체 규칙

Git에 추적되는 Docs와 AGENTS 문서는 한국어 중심의 평서형 현재형으로 작성한다.

- 사용: `정의한다`, `기록한다`, `둔다`, `사용한다`, `확인한다`
- 금지: `합니다`, `해주세요`, `됩니다`, `좋습니다`, 대화체, 감상문체
- GitHub Issue/PR/comment body도 한국어 중심으로 작성한다.
- technical keywords, folder names, API names, graphics concepts, command names는 영어가 더 명확하면 영어를 유지한다.
- GitHub public body는 한국어 명사형 bullet과 짧은 평서형을 사용한다.
- local draft는 자유롭게 작성할 수 있으나, public 변환 시 `Metadata`, draft 문구, 내부 메모, 존댓말을 제거한다.

## 커밋 메시지

가벼운 Conventional Commit 변형을 사용한다.

```text
<type>: <Korean summary>
```

허용 type:

- `docs`: 문서, README, portfolio notes, Issue/PR body 기준
- `build`: build guide, build verification, toolchain notes
- `demo`: capture/result, demo map, Demo capture/result
- `chore`: repo 설정, validator, template, 유지보수
- `fix`: 잘못된 링크, 상태값, 문구, 깨진 문서 수정
