# Portfolio Archive 작업 가이드

이 저장소는 Graphics Study Portfolio 작업을 정리하는 private portfolio archive입니다.

## 목표

- DirectX11 graphics study examples와 개인 확장 작업을 제한 공유 가능한 portfolio archive 형태로 정리합니다.
- 빌드 가능한 예제, demo captures, notes, graphics concepts를 중심에 둡니다.
- `Portfolio_RayTracer`는 Part1 study work 기반의 software ray tracing 대표 작업물로 다룹니다.

## 작업 규칙

- 변경 전 `git status`를 확인합니다.
- 사용자가 명시적으로 요청하기 전에는 commit 또는 push를 하지 않습니다.
- 비공개 원본 자료와 planning folders를 archive에 통째로 복사하지 않습니다.
- 강의 원본 영상, 슬라이드, 퀴즈, 정답은 포함하지 않습니다.
- 강의 기반 학습 코드는 재배포나 교육 목적으로 사용하지 않습니다.
- 외부 공개 가능한 산출물은 별도 public repo로 분리합니다.
- `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `.suo`, `imgui.ini`는 추가하지 않습니다.
- 예제 import 마무리에는 `Docs/_repo/workflow/import-integrity-checklist.md`를 기준으로 XML namespace, HLSL/HLSLI BOM, binary asset hash, raw/project diff를 확인합니다.
- 새 기능 작업보다 documentation, verification records, reproducible demo links를 우선합니다.
- build/run을 직접 확인하지 않았다면 `미확인`으로 기록합니다.

## 문서 언어 규칙

- Portfolio documentation은 한국어를 기본 언어로 사용합니다.
- example names, folder names, API names, graphics concepts, common technical keywords는 영어가 더 명확하면 영어로 유지합니다.
- `README.md`, `BUILD.md`, `DEMOS.md`, `TOPICS.md` 같은 root docs는 한국어 중심으로 작성합니다.
- commit summary는 아래 type prefix와 함께 한국어로 작성합니다.
- PR title은 한국어 의도와 식별하기 쉬운 영어 technical keywords를 조합합니다.
- 해외 제출이 필요해지면 root `README.md`에 English summary section을 먼저 추가합니다.

## 커밋 메시지

가벼운 Conventional Commit 변형을 사용하고, 요약은 한국어로 작성합니다. 필요한 경우 영어 technical terms를 함께 씁니다.

형식:

```text
<type>: <Korean summary>
```

허용 type:

- `docs`: README, notes, DEMOS, TOPICS, portfolio documentation
- `build`: build guides, build verification results, toolchain notes
- `demo`: capture/video links, demo index updates
- `chore`: repository settings, templates, `.gitignore`, maintenance
- `fix`: incorrect links, status labels, wording, broken docs

예시:

```text
docs: 포트폴리오 문서 scaffold 추가
demo: Part1 ray tracing 캡처 항목 추가
build: Part1 빌드 검증 결과 기록
chore: GitHub 이슈 및 PR 템플릿 추가
fix: 불필요한 캡처 이름 규칙 제거
```

## 구조

- Root docs: `README.md`, `BUILD.md`, `DEMOS.md`, `TOPICS.md`
- Detailed docs: `Docs/`
- Example folders는 `Part3_Chapter10-13`, `Part4_Chapter14-20`처럼 chapter-range names를 사용합니다.
- 원본 비교 자료는 제한 공유 범위를 검토한 뒤 포함 여부를 결정합니다.
