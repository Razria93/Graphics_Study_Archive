# Part1 Pilot Collaboration Environment

이 문서는 Part1 Chapter01-02 파일럿을 통해 확립한 협업 환경과 선택 배경을
요약한 마감 snapshot이다. 반복 적용 규칙의 정본을 대체하지 않으며 최신
운영 기준은 `Docs/06_Policies`와 `Docs/98_Tools`에서 확인한다.

## 검토 범위

- 저장소와 문서 산출물 축
- AGENTS 계층과 작업 안전 gate
- 목표 모드와 read-only 하위 agent 사용
- 계획, 수정, 검증, commit과 remote 게시 흐름
- GitHub body template, validator와 문서 감사
- Part1 Chapter01-02 및 `02_Bloom` 파일럿 적용

## 해결한 운영 문제

- Part 중심 이전 문서 구조를 Example, Topic, Verification, Demo, WorkLog,
  Publication과 GitHub body 책임 축으로 분리했다.
- source docs와 GitHub 게시 후보를 분리해 원문 복제 대신 요약과 링크를
  사용하도록 정렬했다.
- build/run/capture, Demo와 Publication 상태가 서로 다른 정본에서 관리되도록
  상태 책임을 분리했다.
- WorkLog를 최신 상태표가 아니라 작업 당시 결정과 마감 snapshot으로
  정의했다.
- 문서 전수감사를 keyword, 목표 모드, read-only agent와 증거 중심 보고가
  포함된 반복 workflow로 만들었다.

## 협업 방식

명확한 단일 수정은 메인 agent가 직접 수행한다. 여러 정본의 영향 조사와
전수감사는 목표 모드에서 read-only 하위 agent를 병렬로 사용할 수 있다.
하위 결과는 메인 agent가 실제 파일과 상태로 재검증한다.

파일 수정, stage, commit, push와 GitHub remote 변경은 메인 agent가 직렬로
수행한다. commit, push, Issue/PR/comment, Ready와 merge는 각 승인 범위를
구분한다.

## 작업 생명주기

```text
상태와 AGENTS 확인
-> 작업 유형과 권한 결정
-> 책임 정본과 계획 확인
-> 수정
-> validator, test와 수동 검수
-> 독립 commit 분리
-> 승인 후 push
-> remote head 확인
-> 승인 후 Issue/PR/comment 반영
-> 게시 후 영향 정본 동기화
-> Ready 감사와 별도 전환 승인
-> handoff
```

구체적인 실행 순서는
[Work Session Quickstart](../../98_Tools/work-session-quickstart.md)를 따른다.

## Template과 Validator

tracked template은 산출물별 최소 구조를 제공하고 validator는 section, 상태,
링크 형식처럼 결정적으로 검사할 수 있는 항목만 담당한다. 문서 책임, 설명
중복, 탐색 흐름, public narrative와 코드 링크의 의미상 대응은 수동 감사로
확인한다.

GitHub Issue와 PR 후보는 첫 H1을 title source로 유지한다. remote body에서는
첫 H1과 바로 뒤 빈 줄을 제거해 제목 중복을 피한다.

## 파일럿 적용 결과

`01_DX11InitAndImGui`와 `02_Bloom`을 통해 Example README, Topic, Verification,
Demo, Publication, WorkLog와 GitHub body의 연결을 실제로 적용했다.
`02_Bloom`에서는 대표 visual, metadata가 제거된 input/result asset, 상세 Demo,
Demo Issue와 코드 permalink를 연결했다.

파일럿 작업은 예제 문서화뿐 아니라 저장소 구조, 협업 규칙, validator와 GitHub
게시 흐름을 정립하는 기준 작업으로 사용했다.

## 완화하거나 폐기한 운영 부담

- 모든 generated asset에 prompt 원문, 생성 화면과 생성 날짜를 요구하지 않는다.
  외부 자료 복제 여부와 공개 안전성에 맞는 최소 출처 기록을 사용한다.
- 게시 후 snapshot은 모든 객체의 필수 gate가 아니다. 실제 게시본이나 리뷰
  대응 기록을 별도로 보존할 필요가 있을 때만 local에 둔다.
- 일반 Markdown 본문은 80자 제한으로 강제 개행하지 않는다. fenced code의
  가독성만 별도 기준으로 검사한다.
- 완료된 구조 정리 roadmap은 계속 갱신하는 상태 원장으로 유지하지 않는다.

## 남은 한계

- validator는 전체 Markdown 링크와 모든 상태 교차검증을 자동화하지 않는다.
- public narrative와 구현 설명의 의미 품질은 사람 또는 agent의 수동 검수가
  필요하다.
- GitHub remote 변경은 인증, network와 UI 상태에 영향을 받으므로 게시 후
  실제 remote 상태를 다시 확인해야 한다.
