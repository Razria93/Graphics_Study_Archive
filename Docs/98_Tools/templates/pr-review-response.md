# PR Review Response

이 템플릿은 GitHub PR review comment에 대응할 때 사용하는 짧은 답변 형식이다. 리뷰 대응 댓글은 문제 해결 여부, 검증, 남은 제한만 남긴다.

```md
반영함.

- 대응: <무엇을 어떻게 수정했는지>
- 검증: <실행한 검증 또는 확인한 근거>
- 비고: <남은 제한 또는 추가 제한 없음>
```

여러 리뷰 코멘트를 한 번에 처리할 때는 대응 항목을 묶어서 작성한다.

```md
반영함.

- 대응: validator multiline heading 검사와 legacy publication 링크를 수정함.
- 검증: `validate-github-body.ps1`, `git diff --check`, 임시 `## Metadata` 회귀 케이스를 확인함.
- 비고: 두 리뷰 코멘트 모두 같은 커밋에서 처리함.
```

## 작성 기준

- 존댓말과 대화체를 쓰지 않는다.
- 원인 분석을 길게 반복하지 않는다.
- 수정하지 않은 항목은 반영했다고 쓰지 않는다.
- 검증하지 않은 항목은 `미확인`으로 적는다.
- 원격 댓글 게시 전에는 `github-workflow-policy.md`의 승인 게이트를 따른다.
