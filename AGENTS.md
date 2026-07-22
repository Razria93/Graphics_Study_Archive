# Repository Guidelines

이 저장소는 DirectX11 graphics study examples와 개인 확장 작업을 private archive 형태로 정리하는 작업 공간이다. 목표는 raw 자료를 그대로 공개하는 것이 아니라, 코드 확인, 문서 재작성, 검증 기록, Demo evidence, GitHub Issue/PR 요약을 통해 설명 가능한 portfolio archive를 만드는 것이다.

## 공통 운영 원칙

- 작업 전 `git status --short --branch`를 확인한다.
- 사용자가 명시적으로 요청하거나 현재 대화에서 커밋까지 승인한 작업 단위가 아니면 commit, push, PR, Issue 생성/수정을 하지 않는다.
- root의 `Part*_Chapter*`와 `Portfolio_RayTracer` 폴더는 코드와 build 기준으로 유지한다.
- 문서 용어는 `Docs/07_Policies/terminology-policy.md`를 따른다.
- 문서 정본은 `Docs/00_Index`부터 `Docs/07_Policies`까지의 산출물 축 구조와 `Docs/98_Tools`, `Docs/99_Legacy` 책임 경계를 기준으로 작성한다.
- 기존 `Docs/Part*` 문서는 정본으로 사용하지 않고 `Docs/99_Legacy/PartDocs`의 전환기 참고 자료로만 사용한다.
- raw/reference repo의 내용은 필요한 부분만 읽고, Git에 추적되는 Docs/AGENTS 문서에는 직접 이해한 설명으로 재작성한다.
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료, 강의 화면 캡처, 문제/해설 전문은 archive/public 후보로 확정하지 않는다.
- `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `.suo`, `imgui.ini`, 임시 캡처, raw result는 추가하지 않는다.
- build/run/capture를 직접 확인하지 않은 항목은 `미확인`으로 기록한다.
- push, pull, merge, rebase, branch delete, history rewrite, LFS import 같은 되돌리기 어려운 작업은 실행 전에 범위와 위험도를 보고한다.

## 문서 위치

- `Docs/00_Index`: 전체 map과 진입점
- `Docs/01_Examples`: 예제 설명 정본
- `Docs/02_Topics`: graphics 개념 정본
- `Docs/03_Verification`: build/run/capture 검증 정본
- `Docs/04_Demos`: demo capture/video evidence 정본
- `Docs/05_WorkLogs`: Issue/PR 작업 기록 정본
- `Docs/06_Publication`: public subset 판단 정본
- `Docs/07_Policies`: 문서화, 검증, demo, GitHub 운영, 공개 정책 정본
- `Docs/98_Tools`: validator, templates, troubleshooting 같은 도구 문서
- `Docs/99_Legacy`: import 기록과 이전 문서 구조
- `local/`: mini plan, raw 검토 메모, GitHub draft/public 사본, 원본 캡처/영상 후보

## AGENTS 계층 규칙

- 상위 공통 안전 규칙은 항상 유지한다.
- 작업 대상 폴더에 하위 `AGENTS.md`가 있으면 해당 폴더 범위의 추가/제한 규칙으로 적용한다.
- 하위 `AGENTS.md`와 상위 규칙이 직접 충돌하면 하위 문서를 우선하되, commit, push, PR, Issue, merge, rebase, 삭제 같은 안전 게이트는 완화하지 않는다.
- 정책 원문은 `Docs/07_Policies`에 둔다.
- import/history 원문은 `Docs/99_Legacy`에 둔다.
- 에이전트는 파일 수정 전 해당 작업 범위의 README와 AGENTS를 먼저 확인한다.

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
- `demo`: capture/video, demo map, Demo evidence
- `chore`: repo 설정, validator, template, 유지보수
- `fix`: 잘못된 링크, 상태값, 문구, 깨진 문서 수정
