# Verification Guidelines

## 적용 범위

이 규칙은 `Docs/02_Verification/` 아래 문서에 적용한다.

## 책임

- build, run, capture, known issue의 최신 상태를 기록한다.
- 문서 작성 상태와 실제 검증 상태를 섞지 않는다.
- 예제 설명은 대상 코드 폴더 README로 링크한다.
- demo capture/result는 `Docs/03_Demos`와 `Docs/_assets`로 링크한다.
- raw/reference 원문, GitHub draft, 개인 메모는 이 폴더에 두지 않는다.
- 문서화 이전에 직접 확인한 build/run 성공은 결과를 `성공`으로 유지하고
  provenance를 `과거 확인`으로 기록한다.
- 과거 성공 이후 현재 작업에서 다시 실행하지 않은 상태는 `재검증 필요`로
  분리하며 실패나 미확인으로 낮추지 않는다.

## 작성 단위

- 전체 상태는 `build-run-matrix.md`, `capture-matrix.md`, `known-issues.md`에 기록한다.
- Part/Chapter 하위에는 `verification-index.md`를 둔다.
- 예제별 상세 검증 문서는 실제 build/run을 수행한 뒤 추가한다.

## 문체

- 평서형 현재형을 사용한다.
- 존댓말, 대화체, 감상문체를 사용하지 않는다.
- technical keywords, folder names, configuration names는 영어를 유지한다.
