# Demo Capture Policy

이 문서는 demo capture/result 관리 기준을 정의한다.

## 정본 위치

Demo 계획과 capture/result 설명의 정본은 `Docs/03_Demos`에 둔다. 검토된 capture/result 파일은 `Docs/_assets`에 둔다.

`Docs/_assets`는 raw capture 저장소가 아니다. `Docs/03_Demos` 또는 `Docs/02_Verification`에서 실제로 참조할 검토 완료 capture/result만 둔다.

## 용어 기준

`capture/result`는 demo나 문서에서 보여줄 화면 기록과 프로그램 출력 결과 전체를 뜻한다.

```text
capture/result
├─ screenshot: 실행 화면을 이미지로 캡처한 파일
├─ video: 실행 화면을 영상으로 녹화한 파일
└─ result image: 프로그램이 파일로 출력한 결과 이미지
```

- `capture`는 screenshot과 video처럼 화면을 기록한 자료를 뜻한다.
- `result image`는 화면 캡처가 아니라 프로그램 출력물이다.
- `검증 근거`라는 표현은 build/run 확인 근거를 뜻할 때만 제한적으로 사용한다.

## 검수 단계 구분

- 정책 검수: 정책, 계획, 템플릿이 capture/result 승격 기준을 충분히 설명하는지 확인한다.
- 후보 검수: `local/` 또는 ignored output에 있는 screenshot, video, result image 후보가 승격 가능한지 분류한다.
- 승격 검수: 검토된 capture/result를 `Docs/_assets` 또는 GitHub body에 연결해도 되는지 최종 확인한다.

정책 검수 PASS는 실제 capture/result 승격 PASS가 아니다. 실제 파일은 후보 검수와 승격 검수를 별도로 통과해야 한다.

## 운영 기준

- raw capture 후보, 실패한 capture, 중복 capture, 선별 전 video/result image는 먼저 `local/` 또는 ignored output에 둔다.
- 검토된 capture/result만 tracked Docs에 연결한다.
- 강의 화면, 유료 자료, 문제/해설 캡처, 출처 불명 asset은 public 후보로 두지 않는다.
- 강의명, 강사명, 워터마크, 개인 이름, 계정, 로컬 경로가 보이는 capture/result는 승격하지 않는다.
- capture/result가 어떤 예제와 Topic을 보여주는지 함께 기록한다.
- 실행을 직접 확인하지 않은 demo는 `미확인`으로 둔다.
- build/run 상태가 `성공` 또는 `부분 성공`일 때만 capture/result를 `확보` 상태로 둔다.
- screenshot은 `Docs/_assets/captures`에 둔다.
- video는 `Docs/_assets/videos`에 둔다.
- result image는 성격에 따라 `Docs/_assets/captures` 또는 별도 정한 result image 경로에 둔다.
- diagram 또는 설명용 그림은 `Docs/_assets/diagrams`에 둔다.

## Capture/Result 승격 기준

`local/`의 capture 후보나 ignored output의 result image는 다음 조건을 만족할 때만 `Docs/_assets`로 승격한다.

- build/run 상태가 `성공` 또는 `부분 성공`으로 기록되어 있다.
- 화면 또는 결과 파일이 보여줄 graphics 개념, 예제 상태, 비교 결과를 명확히 설명한다.
- `Docs/03_Demos/*/demo-index.md` 또는 `Docs/03_Demos/capture-plan.md`에서 참조할 계획이 있다.
- `Docs/02_Verification/capture-matrix.md`에 capture/result 상태를 기록할 수 있다.
- public 후보 여부 또는 private-only 사유를 `Docs/05_Publication`에서 판단할 수 있다.
- 강의 화면, 유료 자료, 문제/해설, 출처 불명 asset이 포함되어 있지 않다.
- 강의명, 강사명, 워터마크, 개인 식별자, 계정 정보, 로컬 절대 경로가 포함되어 있지 않다.
- window title, overlay text, image watermark, terminal/IDE 주변 정보까지 확인했다.
- video는 화면뿐 아니라 audio, subtitle/caption, 파일 metadata에 강의명, 계정, 로컬 경로, 개인 식별자가 남아 있지 않은지 확인했다.

승격하지 않는 항목:

- 실패한 실행 화면
- 같은 의미의 중복 capture/result
- 화면 품질이 낮아 개념을 설명하기 어려운 capture/result
- 권리 검토가 필요한 외부 asset 중심 capture/result
- 강의명, 강사명, 워터마크, 개인 식별자가 포함된 capture/result
- 문서에서 참조하지 않을 보관용 이미지

## 식별자 검수 방법

승격 검수에서는 다음 위치를 직접 확인한다.

- 실행 창 title과 app overlay text
- screenshot/video/result image 내부의 watermark, caption, debug HUD
- terminal, IDE, browser tab, taskbar, notification 등 주변 UI
- 파일명과 저장 경로에 포함된 개인 이름, 계정, 로컬 절대 경로
- video의 audio, subtitle/caption, metadata

하나라도 공개 불가 식별자가 보이면 `확보`가 아니라 `보류` 또는 `제외`로 기록한다.

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

브랜치 기준 `Screenshots/<branch-name>/` 구조는 채택하지 않는다. Graphics Study Archive는 PR branch보다 Part/Chapter/Portfolio 기준으로 capture/result를 찾는 것이 더 안정적이다.

## 연결 기준

screenshot, video, result image를 추가하면 다음 문서를 함께 확인한다.

- `Docs/03_Demos/capture-plan.md`
- 해당 Part/Portfolio의 `Docs/03_Demos/*/demo-index.md`
- `Docs/02_Verification/capture-matrix.md`
- 관련 코드 폴더 README와 `Docs/01_Topics`
- `Docs/05_Publication`의 public 후보 또는 제외 판단

## 갱신 기준

- screenshot/video/result image를 추가하면 `Docs/03_Demos`, `Docs/02_Verification/capture-matrix.md`, `Docs/05_Publication`을 함께 확인한다.
- video를 추가하면 파일 크기, 저장 위치, 공개 가능성을 먼저 확인한다.
- GitHub Issue/PR body에는 승격 검수를 통과한 capture/result만 연결한다.
- capture/result 승격 전에는 화면 안의 title, watermark, overlay, account, path를 수동으로 확인한다.
