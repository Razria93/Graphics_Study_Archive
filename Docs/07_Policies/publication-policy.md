# Publication Policy

이 문서는 private archive에서 public subset으로 전환할 때 적용할 기준을 정의한다.

## 정본 위치

공개 가능성 판단의 정본은 `Docs/06_Publication`에 둔다. 공개 정책 원문은 이 문서를 기준으로 한다.

## public 후보

- 직접 작성한 portfolio 설명
- 직접 작성한 학습 회고
- 독자적으로 재구성한 구현 설명
- 일반적인 graphics concept 설명
- 직접 실행해서 만든 capture/video 중 권리 문제가 없는 결과물
- 출처와 라이선스가 명확한 asset을 사용한 산출물
- 직접 확인한 build/run 검증 요약

## private archive 후보

- raw를 바탕으로 재작성한 학습 정리
- 공개 전 검토가 필요한 demo 후보
- 미확인 build/run 상태
- Work Unit 진행 요약
- 공개 여부가 아직 결정되지 않은 설명 문서

## 제외 대상

- 강의 원문 코드
- 강의 원본 영상, 슬라이드, 퀴즈, 정답
- 유료 자료
- 강의 화면 캡처
- 문제/해설 전문
- 강의 고유 구조를 그대로 재현한 문서
- 출처와 라이선스가 불명확한 asset
- 개인 메모, 계정 정보, 로컬 절대 경로, 제출 대상별 기록
- raw/reference 원문 복사본


## 제출 요약 문서 기준

`Docs/06_Publication/submission-summary.md`는 public subset 후보가 확정된 뒤 작성하는 제출용 요약 후보 문서다. private archive의 상세 문서를 대체하지 않고, 공개 가능한 설명과 evidence 링크만 압축한다.

이 문서는 다음 시점에만 생성한다.

- public 후보와 제외 대상이 `candidate-list.md`, `private-only.md`, `excluded-material.md`에 정리된 뒤
- 대표 verification과 demo evidence가 연결된 뒤
- redaction과 공개 전 체크리스트 검토가 끝난 뒤

## 작성 기준

- 법률 자문처럼 단정하지 않고 공개 전 점검 기준으로 작성한다.
- 후보 목록과 redaction log는 먼저 local에서 검토한다.
- public repo는 private archive가 안정화된 뒤 별도 subset으로 구성한다.
- public 후보는 private archive 문서를 그대로 복사하지 않고 공개용 문장으로 재작성한다.
