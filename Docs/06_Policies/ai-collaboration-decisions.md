# AI Collaboration Decisions

이 문서는 AI 협업 구조를 정리하면서 선택한 운영 결정과 이유를 기록한다. 정책 원문은 각 policy 문서에 두고, 이 문서는 선택 배경과 변경 근거만 남긴다.

## 원칙

- 반복 적용 규칙은 `Docs/06_Policies`의 각 policy 문서에 반영한다.
- 이 문서는 추천 선택지와 이유를 기록한다.
- 운영 중 선택이 바뀌면 기존 결정을 지우지 않고 새 결정 기록을 추가한다.
- remote 상태를 바꾸는 작업은 별도 사용자 승인 후 진행한다.

## 결정 목록

| 결정 | 선택 | 이유 | 반영 위치 |
| --- | --- | --- | --- |
| commit 승인 규칙 | 사용자가 명시적으로 요청했거나 현재 대화에서 커밋까지 승인한 작업 단위일 때만 진행 | root/safety 정책과 GitHub workflow 충돌을 막는다. | `AGENTS.md`, `agent-safety-policy.md`, `github-workflow-policy.md` |
| snapshot 저장 방식 | 게시 전 최종 후보는 `local/github/public`, 게시 후 실제 게시본은 `local/github/snapshots`에 전문 저장 | GitHub에 실제 게시한 본문을 로컬에서 재현할 수 있다. | `github-workflow-policy.md`, `work-unit-workflow-policy.md`, `local-review-policy.md` |
| draft to public 전환 | agent가 local-only 전환과 validator 실행까지 진행 가능 | remote 상태를 바꾸지 않으므로 반복 작업 효율이 높다. | `github-workflow-policy.md` |
| WorkLog/Issue Index 갱신 시점 | draft 작성 시 상태를 기록하고, public-ready/post/snapshot 단계에서 갱신 | 작업 추적 누락을 줄인다. | `worklog.md`, `issue-pr-index.md` |
| validator 미지원 파일 처리 | 우선 warning 성격으로 다루고, 지원 범위를 README에 명시 | 너무 강하게 막으면 새 GitHub body 유형 추가가 어려워진다. | `validators/README.md` |
| 상태값 범위 | Verification 상태와 Demo/Evidence 상태를 분리 정의 | build/run 성공과 evidence 확보는 다른 상태다. | `verification-policy.md`, `demo-capture-policy.md` |
| AGENTS override | 상위 공통 안전 규칙은 유지하고 하위 AGENTS는 폴더 범위의 추가/제한 규칙으로 적용 | 하위 규칙이 safety gate를 완화하지 않게 한다. | `AGENTS.md` |
| structure cleanup roadmap | 정책 폴더에 유지하되 완료 축과 남은 브랜치 마감 작업을 분리 표기 | 브랜치 마감 전까지 구조 정리 맥락을 보존한다. | `structure-cleanup-roadmap.md` |
| GitHub body 언어 | 한국어 중심으로 작성 | tracked Docs와 AGENTS의 문체 기준과 맞춘다. | `style-policy.md`, `validators/README.md` |
| snapshot 저장 단위 | Issue/PR/comment 게시 본문은 게시 후 snapshot 저장 | 초기 운용에서는 단순한 규칙이 추적성을 높인다. | `github-workflow-policy.md` |
| local legacy cache 삭제 | Work Unit 완료 전까지 필요한 local legacy cache는 보존 | Part별 pilot 전 참고 자료를 성급히 잃지 않는다. | `local-review-policy.md`, `local-inventory.md` |
