# Repo Internals

이 폴더는 repo 내부 agent 진입점과 최소 운영 안내만 둔다.

## 책임

- 새 세션이 먼저 읽을 내부 기준을 안내한다.
- 하위 `AGENTS.md` override 기준을 안내한다.
- 정책 원문, 도구 문서, import 기록을 직접 소유하지 않는다.

## 정본 위치

| 성격 | 위치 |
| --- | --- |
| 문서화와 공개 정책 | `Docs/07_Policies/` |
| validator, templates, troubleshooting | `Docs/98_Tools/` |
| import 기록과 이전 workflow | `Docs/99_Legacy/` |
| 실제 문서 산출물 | `Docs/00_Index`부터 `Docs/06_Publication` |

## 운영 기준

`_repo`에 새 정책 문서를 추가하지 않는다. 새 정책은 `Docs/07_Policies`, 새 도구 문서는 `Docs/98_Tools`, 과거 기록은 `Docs/99_Legacy`에 둔다.