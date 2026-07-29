# Review Feedback Log

이 문서는 PR review에서 발견된 actionable feedback 중 이후 작업의 회귀 검사에 재사용할 항목만 기록한다. review 원문은 복제하지 않고 GitHub source와 대응 결과를 연결한다.

## 상태

- `open`: 대응 또는 검증이 남아 있다.
- `resolved`: 수정과 검증을 완료했다.
- `accepted`: 검토 결과 현재 상태를 유지한다.

## 기록

### RF-001 — 정책 이동 후 stale link

- Source: [PR #8 review comment](https://github.com/Razria93/Graphics_Study_Archive/pull/8#discussion_r3675769532)
- Category: `link`
- Affected: `Docs/99_Legacy/PartDocs/Part1_Chapter01-02`의 Chapter 및 Example README 3개
- Finding: 정책 디렉터리 이동 후 삭제된 이전 정책 경로를 가리키는 링크가 남아 404가 발생한다.
- Response: 세 링크를 현재 정본인 `Docs/06_Policies/docs-authoring-flow-policy.md`로 교체하고 동일한 이전 경로를 저장소 전체에서 검색한다.
- Verification: 상대 링크 대상 확인, 이전 경로 재검색, 필수 validator 5종
- Fix: `a35b1f2`
- Status: `resolved`
- Regression check: 파일 또는 정책 경로를 이동·삭제한 PR은 이전 경로 문자열과 해당 대상을 가리키는 inbound Markdown link를 검색한다.
