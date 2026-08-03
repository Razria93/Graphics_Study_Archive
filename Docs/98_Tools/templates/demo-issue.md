# Demo Title

## 요약

결과와 핵심 구현을 2~4문장으로 설명한다.

## 결과

### Representative Result Or Storyboard

대표 결과 또는 storyboard의 제목을 적고 왼쪽→오른쪽이나 위→아래처럼 읽는 방향을 설명한다.

![Representative Result](https://github.com/<owner>/<repo>/blob/<branch>/Docs/_assets/captures/<result>.png?raw=true)

- 입력 또는 상태 변화:
- 관찰 결과:
- 구현 목적:

### Supporting Or Comparison Result

Chapter·Bundle 범위에서 대표 결과와 다른 구현 선택이나 비교 축을 보여주는 경우에만 사용한다. 필요하지 않으면 이 소제목을 제거한다.

![Supporting Or Comparison Result](https://github.com/<owner>/<repo>/blob/<branch>/Docs/_assets/captures/<comparison>.png?raw=true)

## 핵심 구현

### Implementation Step

어떤 구현을 선택했는지 설명하고 대표 visual이나 실행 결과에 미치는 영향을 함께 연결한다.

- [확인할 구현 역할](https://github.com/<owner>/<repo>/blob/<commit-sha>/<source-path>#L<start>-L<end>)

## 처리 흐름

1. 입력 준비
2. 핵심 처리
3. 결과 출력

## 구현 범위와 한계

- 포함:
- 한계:

## 검증

- Build/Run:
- Capture/Result:

## 더 자세히 보기

### Chapter 안내

- Chapter README:
- Demo Index:
- Verification:
- 관련 PR:

### 대표 구현

- Example name: [Example README](...) · [상세 Demo](...)

### 선택 Demo

- [Example name 상세 Demo](...)

### 관련 개념

- Topic:

### 동적 자료

- [<Interaction video comment>](https://github.com/<owner>/<repo>/issues/<number>#issuecomment-<comment-id>)

## 작성 기준

- 일반 문단과 하나의 목록 항목은 각각 하나의 물리적 줄로 작성한다. 상세 기준은 [Docs Authoring Flow Policy](../../06_Policies/docs-authoring-flow-policy.md)를 따른다.
- 상세 Demo 전체를 복제하지 않는다.
- 대표 visual 1~3개와 핵심 구현 요약을 자체 포함한다.
- 단일 Example은 대표 결과를 우선하고 Chapter·Bundle은 서로 다른 설명 축을 보여주는 visual만 선별한다.
- Supporting/Comparison Result를 사용하지 않으면 해당 소제목과 placeholder를 제거한다.
- Screenshot 또는 storyboard를 최소 1개 유지하고 동적 변화도 본문만으로 이해할 수 있게 설명한다.
- Selected video는 본문에 직접 삽입하지 않고 [Demo Video Comment](demo-video-comment.md) 양식으로 전용 댓글에 한 번 첨부한다.
- PR에서 video가 필요하면 attachment 대신 전용 댓글 permalink를 연결한다.
- 실제 video comment permalink가 없으면 `### 동적 자료`와 placeholder를 제거한다.
- 게시되지 않은 video placeholder와 `local/` 경로를 남기지 않는다.
- 핵심 구현은 단계별 설명, 결과 영향, 인접한 코드 증거 순서로 구성한다.
- 파일명만 있는 link label보다 확인할 구현 역할이 드러나는 label을 사용한다.
- 게시 시점 코드 증거는 commit permalink와 line anchor를 사용한다.
- 의사코드는 필요한 경우에만 사용하고 원본 코드 링크를 함께 둔다.
- 의사코드를 사용하면 함수와 제어문에 Allman brace style을 적용한다.
- 상세 Demo에 같은 의사코드가 있으면 Demo Issue에 그대로 복제하지 않는다.
- 실제 GitHub absolute URL과 Markdown 링크를 사용한다.
- 출처 또는 재배포 조건이 불완전한 runtime asset 원본을 첨부하거나 직접 링크하지 않는다. 승인된 Bundle 예외에서는 구현 결과 visual만 사용한다.
