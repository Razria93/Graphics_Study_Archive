# Validation Tools

이 문서는 문서 검증 도구의 의도와 운영 위치를 정의한다.

## 책임

- tracked Docs 문체와 링크 검수 기준을 정리한다.
- GitHub body draft 검수 기준을 정리한다.
- 실제 validator script가 있으면 이 문서에서 실행법을 연결한다.

## 현재 상태

이 구조 변경 브랜치에서는 validator script를 새로 추가하지 않는다. 기존 도구가 필요하면 백업 브랜치의 `tools/validate-docs.ps1`와 `local/tools/validate-github-body.ps1`를 검토한 뒤 별도 commit으로 승격한다.

## 최소 검증

- `git diff --check`
- 문체 금지 표현 검색
- 오래된 `_repo/workflow`, `_repo/ImportPhase`, `Docs/Part*` 정본 경로 검색
- README와 AGENTS의 정본 위치 일치 확인