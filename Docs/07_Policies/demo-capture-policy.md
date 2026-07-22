# Demo Capture Policy

이 문서는 screenshot과 video evidence 관리 기준을 정의한다.

## 정본 위치

Demo 계획과 evidence 설명의 정본은 `Docs/04_Demos`에 둔다. 검토된 파일은 `Docs/_assets`에 둔다.

## 운영 기준

- raw capture 후보는 먼저 `local/`에 둔다.
- 검토된 capture 또는 video reference만 tracked Docs에 연결한다.
- 강의 화면, 유료 자료, 문제/해설 캡처, 출처 불명 asset은 public 후보로 두지 않는다.
- capture가 어떤 예제와 Topic을 보여주는지 함께 기록한다.
- 실행을 직접 확인하지 않은 demo는 `미확인`으로 둔다.
- build/run 상태가 `성공` 또는 `부분 성공`일 때만 evidence를 `확보` 상태로 둔다.

## 파일 기준

- 파일명은 Part, Chapter, example 또는 concept가 드러나게 작성한다.
- 최종 파일 위치는 `Docs/_assets` 기준을 따른다.
- 큰 영상은 repo에 직접 추가하기 전에 저장 방식과 공개 가능성을 검토한다.

## 갱신 기준

- screenshot을 추가하면 `Docs/04_Demos`, `Docs/03_Verification/capture-matrix.md`, `Docs/06_Publication`을 함께 확인한다.
- video evidence를 추가하면 파일 크기, 저장 위치, 공개 가능성을 먼저 확인한다.
