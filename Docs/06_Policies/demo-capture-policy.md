# Demo Capture Policy

이 문서는 screenshot과 video evidence 관리 기준을 정의한다.

## 정본 위치

Demo 계획과 evidence 설명의 정본은 `Docs/03_Demos`에 둔다. 검토된 evidence 파일은 `Docs/_assets`에 둔다.

`Docs/_assets`는 raw capture 저장소가 아니다. `Docs/03_Demos` 또는 `Docs/02_Verification`에서 실제로 참조할 검증 완료 evidence만 둔다.

## 운영 기준

- raw capture 후보, 실패한 capture, 중복 capture, 선별 전 영상은 먼저 `local/`에 둔다.
- 검토된 capture 또는 video reference만 tracked Docs에 연결한다.
- 강의 화면, 유료 자료, 문제/해설 캡처, 출처 불명 asset은 public 후보로 두지 않는다.
- capture가 어떤 예제와 Topic을 보여주는지 함께 기록한다.
- 실행을 직접 확인하지 않은 demo는 `미확인`으로 둔다.
- build/run 상태가 `성공` 또는 `부분 성공`일 때만 evidence를 `확보` 상태로 둔다.
- screenshot evidence는 `Docs/_assets/captures`에 둔다.
- video evidence는 `Docs/_assets/videos`에 둔다.
- diagram 또는 설명용 그림은 `Docs/_assets/diagrams`에 둔다.

## Evidence 승격 기준

`local/`의 capture 후보는 다음 조건을 만족할 때만 `Docs/_assets`로 승격한다.

- build/run 상태가 `성공` 또는 `부분 성공`으로 기록되어 있다.
- 화면이 보여줄 graphics 개념, 예제 상태, 비교 결과를 명확히 설명한다.
- `Docs/03_Demos/*/demo-index.md` 또는 `Docs/03_Demos/capture-plan.md`에서 참조할 계획이 있다.
- `Docs/02_Verification/capture-matrix.md`에 capture 상태를 기록할 수 있다.
- public 후보 여부 또는 private-only 사유를 `Docs/05_Publication`에서 판단할 수 있다.
- 강의 화면, 유료 자료, 문제/해설, 출처 불명 asset이 포함되어 있지 않다.

승격하지 않는 항목:

- 실패한 실행 화면
- 같은 의미의 중복 capture
- 화면 품질이 낮아 개념을 설명하기 어려운 capture
- 권리 검토가 필요한 외부 asset 중심 capture
- 문서에서 참조하지 않을 보관용 이미지

## 파일 기준

파일명은 Part, Chapter, example 또는 concept가 드러나게 작성한다.

권장 형식:

```text
part##_chapter##_example-or-topic.png
part##_chapter##_example-or-topic_before.png
part##_chapter##_example-or-topic_after.png
portfolio_raytracer_topic.png
```

예시:

```text
part02_chapter04_depth-buffer.png
part03_chapter13_shadow-mapping-pcf.png
part04_chapter16_stable-fluids.png
portfolio_raytracer_reflection.png
```

브랜치 기준 `Screenshots/<branch-name>/` 구조는 채택하지 않는다. Graphics Study Archive는 PR branch보다 Part/Chapter/Portfolio 기준으로 evidence를 찾는 것이 더 안정적이다.

## 연결 기준

screenshot 또는 video evidence를 추가하면 다음 문서를 함께 확인한다.

- `Docs/03_Demos/capture-plan.md`
- 해당 Part/Portfolio의 `Docs/03_Demos/*/demo-index.md`
- `Docs/02_Verification/capture-matrix.md`
- 관련 코드 폴더 README와 `Docs/01_Topics`
- `Docs/05_Publication`의 public 후보 또는 제외 판단

## 갱신 기준

- screenshot을 추가하면 `Docs/03_Demos`, `Docs/02_Verification/capture-matrix.md`, `Docs/05_Publication`을 함께 확인한다.
- video evidence를 추가하면 파일 크기, 저장 위치, 공개 가능성을 먼저 확인한다.
- GitHub Issue/PR body에는 검증 완료 evidence만 연결한다.
