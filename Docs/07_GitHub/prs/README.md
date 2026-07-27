# PR Bodies

이 폴더는 GitHub PR body 후보를 둔다.

## 단위

- 기본 PR 단위는 Chapter 또는 Chapter 묶음이다.
- Part 단위 PR은 예제가 적고 변경 범위가 작을 때만 예외로 허용한다.
- Part 전체 진행은 Progress Issue, WorkLog, milestone 성격으로 추적한다.

## 권장 본문 흐름

PR body는 파일 변경 목록보다 이 PR이 설명 가능하게 만든 그래픽스 내용을 먼저 보여준다.

```md
## 요약
## 범위
## 핵심 개념
## 대표 예제
## 검증
## 스크린샷
## 미확인 / 제한
## 문서
## 관련 이슈
## 다음 단계
```

`핵심 개념`과 `대표 예제`는 표보다 문단과 짧은 리스트를 기본으로 한다. 표는 검증, 링크, 상태처럼 짧은 값을 비교할 때만 사용한다.

PR body는 README를 복제하지 않는다. Chapter README와 Example README를 기반으로 작성하되, GitHub reviewer가 볼 요약과 링크만 둔다.

PR body 후보는 첫 H1을 title source로 유지한다. 실제 `gh pr create`에서는 title을 H1에서 사용하고 body는 tracked 정본을 그대로 게시한다.

구조 정리 PR처럼 파일 이동 자체가 핵심인 경우에만 `주요 변경` 중심 구성을 예외로 사용할 수 있다. 일반 Chapter/Chapter 묶음 PR은 핵심 개념, 대표 예제, 검증, demo 링크를 기본 흐름으로 둔다.
