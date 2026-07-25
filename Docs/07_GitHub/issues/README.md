# Issue Bodies

이 폴더는 GitHub Issue body 후보를 둔다.

## 기본 원칙

Issue는 Work Unit 작업 추적을 중심으로 만든다. Topic, Demo, Verification Issue는 독립 추적 가치가 있을 때만 만든다.

| 유형 | 파일명 | 생성 기준 |
| --- | --- | --- |
| Work Unit Issue | `work-unit_*.md` | Work Unit 범위, 검증 기준, 완료 조건을 GitHub에서 추적해야 할 때 |
| Topic Issue | `topic_*.md` | 여러 Chapter를 관통하는 개념 문서가 독립 작업일 때 |
| Verification Issue | `verification_*.md` | build/run 실패, 환경 문제, 미확인 묶음이 별도 추적 대상일 때 |
| Demo Issue | 필요 시 별도 결정 | screenshot, video, result image 제작이 별도 작업일 때 |

PR 자체를 위한 별도 Issue는 기본으로 만들지 않는다. PR 상태는 `Docs/04_WorkLogs/work-unit-github-index.md`와 Plan Issue 댓글에서 추적한다.

## Work Unit Issue

Work Unit Issue는 작업 범위와 완료 조건을 GitHub에서 추적해야 할 때만 만든다. Docs 정본을 복제하지 않고, 범위와 검증 기준, 완료 조건, 관련 문서 링크만 둔다.

반복 작성용 템플릿은 `../../98_Tools/templates/work-unit-issue.md`를 따른다. 게시 전 검사는 `../../98_Tools/validators/validate-github-body.ps1`를 사용한다.
