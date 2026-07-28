# PR Title

## 요약

이 PR이 어떤 Chapter 또는 Chapter 묶음을 설명 가능하게 만드는지 2~4문장으로 정리한다. source docs를 읽고 GitHub review용으로 요약/재구성한다.

## 범위

- Chapter:
- 대표 예제:
- 제외 범위:

## 핵심 개념

- Concept name: 이 PR에서 중요한 이유를 한두 문장으로 적고 관련 README 또는 Topic을 연결한다.
- Concept name: 자세한 설명은 정본 문서로 넘긴다.

## 대표 예제

### ExampleName

예제가 보여주는 내용을 짧게 설명한다.

- README:
- Demo:
- Verification:

## 검증

- Debug x64 build/run:
- Release x64 build/run:
- capture/result:
- validator:

## 대표 Visual

대표 visual이 review에 도움이 될 때만 0~1개 사용한다. 상세 visual은 Demo
Issue로 연결한다.

### Example Capture

capture/result가 보여주는 내용을 한 문장으로 설명한다.

![Example Capture](https://github.com/Razria93/Graphics_Study_Archive/blob/<branch-name>/Docs/_assets/captures/example.png?raw=true)

## 구현 범위와 한계

-

## 문서

- Example README:
- Topic:
- Verification:
- Demo:
- WorkLog:
- Publication:

## 관련 이슈

- 없음

## 다음 단계

-

## 작성 기준

- 파일 변경 목록보다 핵심 개념, 대표 예제, 검증, demo를 먼저 보여준다.
- PR body는 README를 복제하지 않고 GitHub review용 요약과 링크 허브로 작성한다.
- source docs 원문을 그대로 복사하지 않고 핵심 요약, 검토 시점의 상태, 링크만 남긴다.
- 핵심 개념과 대표 예제는 표보다 문단과 짧은 리스트를 기본으로 한다.
- 표는 검증, 링크, 상태처럼 짧은 값을 비교할 때만 사용한다.
- 구조 정리 PR처럼 파일 이동 자체가 핵심인 경우에만 변경 목록 중심 구성을 예외로 사용한다.
- 상세 설명은 README, Topic, Verification, Demo 문서로 링크한다.
- 대표 visual은 최대 1개만 사용하고 GitHub absolute URL을 사용한다.
- GitHub 게시 후보는 `Docs/07_GitHub/prs`에 둔다.
