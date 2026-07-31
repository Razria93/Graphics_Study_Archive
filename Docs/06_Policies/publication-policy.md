# Publication Policy

이 문서는 private archive에서 public subset으로 전환할 때 적용할 기준을 정의한다.

## 정본 위치

공개 가능성 판단의 정본은 `Docs/05_Publication`에 둔다. 공개 정책 원문은 이 문서를 기준으로 한다.

## 사용 범위

`Docs/05_Publication`은 공개용 본문을 미리 작성하는 공간이 아니다. 이 폴더는 public subset 후보, private archive 전용 항목, 검토 필요 항목, 제외 대상을 상태로 기록한다.

- 모든 예제마다 Publication 상세 문서를 만들지 않는다.
- 공개 후보가 생긴 항목만 `candidate-list.md`, `private-only.md`, `excluded-material.md`, `redaction-log.md`에 기록한다.
- 공개용 README나 제출 본문은 private archive 문서를 그대로 복사하지 않고, 공개 전 검토가 끝난 뒤 별도 public subset 문장으로 재작성한다.
- Work Unit 초반에는 공개 확정 대신 `검토 필요` 상태를 기본값으로 둔다.

## public 후보

- 직접 작성한 portfolio 설명
- 직접 작성한 학습 회고
- 독자적으로 재구성한 구현 설명
- 일반적인 graphics concept 설명
- 직접 실행해서 만든 capture/result 중 권리 문제가 없는 결과물
- 사용자 직접 생성 또는 직접 촬영으로 출처 상태를 확인한 asset
- metadata에 개인 식별자, 로컬 경로, 강의명, 출처 불명 정보가 남아 있지 않은 screenshot/result image
- 강의명, 강사명, 워터마크, 개인 식별자가 제거된 capture/result
- 출처와 라이선스가 명확한 asset을 사용한 산출물
- 직접 확인한 build/run 검증 요약

## private archive 후보

- raw를 바탕으로 재작성한 학습 정리
- 공개 전 검토가 필요한 demo 후보
- Work Unit 진행 요약
- 공개 여부가 아직 결정되지 않은 설명 문서

## 검토 필요 후보

- 미확인 build/run 상태
- 출처와 라이선스 확인 전의 capture/result
- 생성 주체나 외부 자료 복제 여부를 확인하지 못한 generated asset
- 공개용 문장으로 재작성하기 전의 private archive 설명
- metadata, 개인 식별자, 로컬 경로 확인 전의 screenshot/result image

## 제외 대상

- 강의 원문 코드
- 강의 원본 영상, 슬라이드, 퀴즈, 정답
- 유료 자료
- 강의 화면 캡처
- 강의명, 강사명, 강의 워터마크, 강의 브랜드 표기가 포함된 screenshot/video/result image
- overlay, debug HUD, window title, browser tab, taskbar, notification에 개인 식별자나 로컬 환경 정보가 노출된 capture/result
- 문제/해설 전문
- 강의 고유 구조를 그대로 재현한 문서
- 출처와 라이선스가 불명확한 asset
- 외부 image, texture, model, HDRI 입력 asset의 출처와 라이선스를 확인하지 않은 result image
- 개인 메모, 계정 정보, 로컬 절대 경로, 제출 대상별 기록
- raw/reference 원문 복사본

## 제출 요약 문서 기준

`Docs/05_Publication/submission-summary.md`는 public subset 후보가 확정된 뒤 작성하는 제출용 요약 후보 문서다. private archive의 상세 문서를 대체하지 않고, 공개 가능한 설명과 capture/result 링크만 압축한다.

이 문서는 다음 시점에만 생성한다.

- public 후보와 제외 대상이 `candidate-list.md`, `private-only.md`, `excluded-material.md`에 정리된 뒤
- 대표 verification과 demo capture/result가 연결된 뒤
- redaction과 공개 전 체크리스트 검토가 끝난 뒤

## 작성 기준

- 법률 자문처럼 단정하지 않고 공개 전 점검 기준으로 작성한다.
- 후보 목록과 redaction log는 먼저 local에서 검토한다.
- public repo는 private archive가 안정화된 뒤 별도 subset으로 구성한다.
- public 후보는 private archive 문서를 그대로 복사하지 않고 공개용 문장으로 재작성한다.
- public capture/result 후보는 강의명, 강사명, 워터마크, 개인 식별자 포함 여부를 확인한 뒤 연결한다. 포함된 자료는 public 후보에서 제외하거나 재촬영/재생성한다.
- screenshot/result image는 metadata 확인을 포함한다. 사용자 직접 생성 asset은 최소 출처 기록을 적용하고, 외부 입력 asset을 사용한 result image는 입력 asset의 출처와 라이선스를 확인하기 전까지 검토 필요 또는 제외로 둔다.
