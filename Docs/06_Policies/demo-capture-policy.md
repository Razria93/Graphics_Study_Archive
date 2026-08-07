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
- `build/run 확인 기록`이라는 표현은 build/run 확인 결과를 보조하는 기록을 뜻할 때만 제한적으로 사용한다.

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

## 최소 Demo 의무 기준

- graphics 예제 문서화에서는 Chapter 또는 Chapter 묶음 단위 demo에 screenshot을 최소 1개 이상 필수로 둔다.
- screenshot 추가본은 해당 Chapter 작업을 설명하는 데 필수적인 장면만 선별해 구성한다.
- video가 필요하다고 판단한 경우 작업자는 사용자에게 video 요청 조건을 제시한다.
- 사용자가 demo 구성을 요청한 경우 작업자는 해당 범위의 demo를 구성한다.

## Capture/Result 승격 기준

`local/`의 capture 후보나 ignored output의 result image는 다음 조건을 만족할 때만 `Docs/_assets`로 승격한다.

- build/run 상태가 `성공` 또는 `부분 성공`으로 기록되어 있다.
- 화면 또는 결과 파일이 보여줄 graphics 개념, 예제 상태, 비교 결과를 명확히 설명한다.
- `Docs/03_Demos/*/demo-index.md` 또는 `Docs/03_Demos/capture-plan.md`에서 참조할 계획이 있다.
- capture/result가 있는 예제는 코드 폴더 README에도 연결한다.
- `Docs/02_Verification/capture-matrix.md`에 capture/result 상태를 기록할 수 있다.
- public 후보 여부 또는 private-only 사유를 `Docs/05_Publication`에서 판단할 수 있다.
- 강의 화면, 유료 자료, 문제/해설, 출처 불명 asset이 포함되어 있지 않다.
- 강의명, 강사명, 워터마크, 개인 식별자, 계정 정보, 로컬 절대 경로가 포함되어 있지 않다.
- window title, overlay text, image watermark, terminal/IDE 주변 정보까지 확인했다.
- video는 화면뿐 아니라 audio, subtitle/caption, 파일 metadata에 강의명, 계정, 로컬 경로, 개인 식별자가 남아 있지 않은지 확인했다.
- screenshot과 result image는 EXIF, PNG text chunk, 파일 속성 등 이미지 metadata에 개인 식별자, 로컬 경로, 강의명, 출처 불명 정보가 남아 있지 않은지 확인했다.
- result image가 외부 image, texture, model, HDRI를 입력으로 사용했다면 입력 asset의 출처와 라이선스를 확인하기 전까지 보류로 둔다.

## 검증 단계 요청 기준

build/run 검증 단계에서 screenshot, video, result image가 필요한 예제라고 판단되면 작업자는 사용자에게 capture/result 요청 조건을 구체적으로 제시한다.

Chapter 또는 Chapter 묶음 단위 demo에서는 screenshot 최소 1개를 기본 요청으로 둔다.

요청에는 다음 항목을 포함한다.

- 필요한 유형: screenshot, video, result image 중 무엇인지
- 찍어야 할 화면이나 프로그램 출력물
- before/after 또는 input/result 비교가 필요한지
- README에 연결할 대표 capture/result인지, local 검토 후보인지
- 피해야 할 노출 요소: 강의명, 강사명, 워터마크, 개인 식별자, 계정, 로컬 경로, 불필요한 IDE/terminal/browser UI
- 권장 비율과 구도: 가능하면 16:9, 예제 결과가 중심에 보이는 화면
- 파일명 기준: Part/Chapter/Example과 개념이 드러나는 이름

예제 유형별 기본 요청 기준은 다음과 같다.

| 예제 유형 | 우선 요청 | 기준 |
| --- | --- | --- |
| post-processing | input image와 result image | 처리 전후 차이를 README에서 세로로 비교한다. |
| static rendering | screenshot | 최종 화면 한 장으로 핵심 개념을 설명할 수 있어야 한다. |
| interaction, camera, control | video | 움직임이나 입력 반응이 설명의 핵심이면 video를 우선한다. |
| simulation, animation, physics | video와 대표 screenshot | 시간 변화는 video로, 대표 상태는 screenshot으로 남긴다. |
| file output 기반 예제 | result image | 프로그램이 출력한 파일을 우선 연결한다. |

예제 단위에서 capture/result가 필요 없거나 시각적 설명 가치가 낮으면 `제외`로 기록하고 사유를 남긴다. 단, Chapter 또는 Chapter 묶음 demo-index 기준으로는 최소 1개 screenshot을 유지한다.

## README 표시 기준

capture/result가 확보된 예제는 코드 폴더 README의 `Capture/Result` 섹션에 대표 자료를 연결한다. screenshot이나 result image는 너무 작게 보이지 않도록 세로 배치를 기본으로 한다.

README와 일반 Docs 문서는 repo 안에서 렌더링되므로 repo-relative path를 사용한다. GitHub Issue, PR, comment body는 GitHub remote 페이지에서 렌더링되므로 `Docs/07_GitHub` 후보 문서에 capture/result를 연결할 때는 GitHub absolute URL을 사용한다.

권장 형식:

```md
## Capture/Result

### Input

![Input](../../Docs/_assets/captures/example_input.png)

### Result

![Result](../../Docs/_assets/captures/example_result.png)
```

input/result, before/after처럼 비교가 필요한 경우에도 한 줄 표보다 별도 소제목을 둔 세로 배치를 우선한다. video는 직접 embed보다 링크와 짧은 설명을 둔다.

## GitHub body 이미지 URL 기준

GitHub Issue, PR, comment body에 들어가는 screenshot/result image는 repo-relative path를 사용하지 않는다. 게시 후보 문서인 `Docs/07_GitHub` 안에서는 다음 형식을 사용한다.

```md
![Description](https://github.com/Razria93/Graphics_Study_Archive/blob/<branch-name>/Docs/_assets/captures/example.png?raw=true)
```

기준:

- draft PR 또는 branch 검토 중에는 현재 작업 branch 기준 `blob/<branch-name>/...?...raw=true` URL을 사용한다.
- merge 후 main 기준 snapshot이나 제출용 body가 필요하면 `blob/main/...?...raw=true` 또는 raw.githubusercontent URL로 정리한다.
- 코드 폴더 README, Topic, Demo, Verification 문서에는 repo-relative path를 유지한다.
- GitHub body에 연결하는 파일은 승격 검수를 통과한 `Docs/_assets/captures` 또는 정해진 `Docs/_assets` 파일만 사용한다.

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
- screenshot/result image의 metadata, video의 audio, subtitle/caption, metadata

하나라도 공개 불가 식별자가 보이면 `확보`가 아니라 `보류` 또는 `제외`로 기록한다.


## ChatGPT 생성 이미지 workflow

이미지 입력이 필요한 예제는 외부 wallpaper나 출처 불명 이미지를 우선 사용하지 않는다. 기본 흐름은 ChatGPT 생성 이미지와 local-only provenance 기록을 사용하는 방식으로 통일한다.

1. 에이전트가 예제 목적에 맞는 영어 이미지 생성 프롬프트를 제안한다.
2. 사용자가 ChatGPT 앱에서 이미지를 생성한다.
3. 작업용 원본 이미지는 `local/<work-unit>/image.png`에 저장한다.
4. 생성 화면 스크린샷은 `local/<work-unit>/provenance-chatgpt-generation.png`에 저장한다.
5. provenance screenshot은 생성 증빙용 local-only 자료로만 사용하고 public 문서에 게시하지 않는다.
6. 에이전트는 local-only 입력 테스트를 수행하고 result image를 생성한다.
7. screenshot/result image metadata, 워터마크, 텍스트, 개인 식별자를 검수한다.
8. tracked 입력 asset 교체, `Docs/_assets` 승격, public subset 후보 여부는 별도로 판단한다.

권장 프롬프트 조건:

```text
No text, no logo, no watermark, no people
16:9 aspect ratio
Clear visual features for the target graphics concept
```

ChatGPT 생성 이미지라도 곧바로 public 후보로 확정하지 않는다. 생성 도구, 프롬프트, 생성 날짜, 원본 파일 hash, 변환 파일 hash, 테스트 결과를 local review에 기록한 뒤 승격 검수를 수행한다.

## 파일 기준

파일명은 Part, Chapter, example 또는 concept가 드러나게 작성한다. 실제 코드 폴더 표기와 맞추기 위해 Part 번호는 `part1`처럼 쓰고, Chapter는 `chapter01` 또는 `chapter01-02`처럼 쓴다.

권장 형식:

```text
part#_chapter##_example-or-topic.png
part#_chapter##-##_example-or-topic_input.png
part#_chapter##-##_example-or-topic_result.png
portfolio_raytracer_topic.png
```

예시:

```text
part1_chapter01-02_02_bloom_input.jpg
part1_chapter01-02_02_bloom_result.png
part2_chapter04_depth-buffer.png
part3_chapter10-13_shadow-mapping-pcf.png
part4_chapter14-20_stable-fluids.png
portfolio_raytracer_reflection.png
```

기준:

- Part 번호는 실제 폴더명과 맞춰 `part1`, `part2`처럼 쓴다.
- Chapter 번호는 두 자리로 쓰고, 범위는 `chapter01-02`처럼 하이픈으로 연결한다.
- example 번호가 있으면 `02_bloom`처럼 유지한다.
- before/after보다 input/result 관계가 명확한 예제는 `_input`, `_result` 접미사를 우선한다.
- 브랜치 기준 `Screenshots/<branch-name>/` 구조는 채택하지 않는다. Graphics Study Archive는 PR branch보다 Part/Chapter/Portfolio 기준으로 capture/result를 찾는 것이 더 안정적이다.

## 연결 기준

screenshot, video, result image를 추가하면 다음 문서를 함께 확인한다.

- `Docs/03_Demos/capture-plan.md`
- 해당 Part/Portfolio의 `Docs/03_Demos/*/demo-index.md`
- `Docs/02_Verification/capture-matrix.md`
- 관련 코드 폴더 README와 `Docs/01_Topics`
- capture/result가 있는 예제의 코드 폴더 README
- `Docs/05_Publication`의 public 후보 또는 제외 판단

## 갱신 기준

- screenshot/video/result image를 추가하면 `Docs/03_Demos`, `Docs/02_Verification/capture-matrix.md`, `Docs/05_Publication`을 함께 확인한다.
- screenshot/result image를 추가하면 이미지 metadata를 확인하고, video를 추가하면 파일 크기, 저장 위치, 공개 가능성을 먼저 확인한다.
- GitHub Issue/PR body에는 승격 검수를 통과한 capture/result만 연결한다.
- capture/result 승격 전에는 화면 안의 title, watermark, overlay, account, path를 수동으로 확인한다.
