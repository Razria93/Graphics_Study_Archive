# Demo Capture Policy

이 문서는 demo capture/result 관리 기준을 정의한다.

## 정본 위치

Demo registry와 상세 기술 구현·시각 결과의 정본은 `Docs/03_Demos`에 둔다. 검토된 capture/result 파일은 `Docs/_assets`에 둔다.

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
- raw, attempt와 selected video는 `local/`에 둔다. 게시한 video의 reference와 운영 안내는 `Docs/_assets/videos`에서 관리한다.
- result image는 성격에 따라 `Docs/_assets/captures` 또는 별도 정한 result image 경로에 둔다.
- diagram 또는 설명용 그림은 `Docs/_assets/diagrams`에 둔다.

## 최소 Demo 의무 기준

- graphics 예제 문서화에서는 Chapter 또는 Chapter 묶음 단위 demo에 screenshot을 최소 1개 이상 필수로 둔다.
- screenshot 추가본은 해당 Chapter 작업을 설명하는 데 필수적인 장면만 선별해 구성한다.
- video가 필요하다고 판단한 경우 작업자는 사용자에게 video 요청 조건을 제시한다.
- 사용자가 demo 구성을 요청한 경우 작업자는 해당 범위의 demo를 구성한다.

Demo Issue 본문의 `visual unit`은 독자가 하나의 결과나 변화를 독립적으로 이해할 수 있는 screenshot 또는 storyboard 하나를 뜻한다. 여러 screenshot을 하나의 비교 image로 합쳤더라도 같은 비교 목적을 설명하면 visual unit 하나로 센다. Video는 본문 visual unit으로 세지 않고 전용 댓글에서 별도 관리한다.

- 단일 Example Demo Issue는 해당 Example의 대표 결과를 가장 직접적으로 보여주는 visual을 우선한다.
- Chapter 또는 Bundle Demo Issue는 대표 기술 결과, 비교 가능한 구현 차이, 사용자 확장이나 시간 변화처럼 서로 다른 설명 축을 먼저 정하고 각 축에 필요한 visual만 선별한다.
- 각 visual은 다른 visual이 설명하지 않는 구현 선택이나 결과 변화를 추가해야 한다. 같은 상태를 반복하거나 설명 가치가 겹치면 제외한다.
- Chapter 또는 Bundle Demo Issue도 대표 visual 1~3개 범위와 screenshot 최소 1개를 유지한다.
- PR은 상세 showcase가 아니라 review 요약이므로 Chapter 또는 Bundle 범위여도 대표 visual 0~1개를 유지한다.

## Video 필요성 판정

Video 필요성은 `필수`, `선택`, `생략`으로 구분한다. 이 판정은 예제 의미와 정지 이미지 대비 추가 설명 가치를 수동으로 검토해 결정하며 validator가 추측하지 않는다.

- `필수`: UI parameter의 연속 변화, animation, camera 이동, 실시간 interaction, 단계 전환이나 시간에 따라 나타나는 artifact처럼 정지 이미지로 핵심 결과를 설명하기 어려운 경우다.
- `선택`: 정지 이미지로 결과를 이해할 수 있지만 조명·재질 parameter 비교, render mode 전환, object movement나 before/after 사이 과정이 설명력을 높이는 경우다.
- `생략`: 고정 결과 한 장으로 충분하거나 단순 build/run 성공, 같은 상태의 반복처럼 video가 추가 정보를 제공하지 않는 경우다.

필수 또는 선택 video가 있는 Demo도 핵심 상태 screenshot과 텍스트 설명만으로 주요 구현과 결과를 이해할 수 있게 작성한다.

## 동적 결과 Storyboard 기준

Storyboard는 검증된 screenshot 또는 selected video에서 의미 있는 상태 2~5개를 선별해 하나의 읽기 순서로 구성한 comparison image다. 시간 간격대로 자동 추출한 QA contact sheet와 구분하며, 독자가 입력과 결과 변화를 정지 화면만으로 따라갈 수 있을 때 사용한다.

- 입력·상태 전환이 핵심이면 storyboard를 사용하고 속도·연속성 자체가 핵심이면 video를 함께 유지한다.
- 각 frame에는 순번과 짧은 상태 label을 두고 같은 crop, scale과 application bounds를 유지한다.
- 상세 Demo는 시트 제목, 읽는 순서, 입력 변화, 관찰 지점과 구현 결과를 함께 설명한다.
- Demo Issue 본문도 storyboard 제목, 읽는 방향, 입력 또는 상태 변화, 관찰 결과와 구현 목적을 함께 설명한다.
- Storyboard 하나는 같은 변화 축을 설명하는 visual unit 하나로 센다.
- 원본 frame, QA contact sheet와 조합 중간 파일은 `local/`에 두고 검수한 최종 storyboard만 `Docs/_assets/captures`에 둔다.
- Storyboard는 selected video를 대체하지 않는다. Video의 게시 여부와 lifecycle은 별도로 관리한다.

## Video lifecycle과 위치

Video 상태와 위치는 다음과 같이 구분한다.

| 상태 | 위치 | 책임 |
| --- | --- | --- |
| raw | `local/` | 녹화 원본과 선별 전 자료 |
| attempt | `local/` | 정상 종료와 자동 검증을 통과한 take |
| selected | `local/` | 사용자 시각 검수를 포함해 게시 후보로 선택한 master |
| published | GitHub Demo Issue 전용 댓글 attachment | selected video를 한 번 업로드한 게시본 |

- selected video는 일반 Git history에 추가하지 않는 것을 기본값으로 한다.
- published video의 기본 게시 위치는 독립 공개 가치가 있는 Demo Issue의 전용 댓글이다.
- 전용 댓글 하나는 하나의 독립 설명 축만 다루고 제목, 조작 순서, 관찰 결과, 대응 Demo와 attachment를 포함한다.
- PR에서 video가 Chapter 대표 자료로 선택되면 attachment를 직접 삽입하지 않고 Demo Issue의 전용 댓글 permalink를 연결한다.
- 같은 video를 Demo Issue와 PR에 각각 중복 업로드하지 않는다.
- tracked 상세 Demo는 핵심 screenshot과 변화 설명을 유지하고 published video는 실제 Demo Issue로 연결한다.
- Git tracked video와 Git LFS는 `assets-policy.md`의 예외 기준과 사용자 승인을 따른다.

Video 댓글은 게시 목적에 따라 다음과 같이 갱신한다.

- 같은 목적과 같은 설명 축의 video를 개선하면 기존 댓글을 수정하고 attachment와 설명을 교체한다.
- 다른 조작, 비교 기준 또는 구현 결과를 설명하면 새 댓글을 추가한다.
- 잘못된 게시, 중복 게시 또는 공개 위험이 확인된 경우에만 댓글이나 attachment 삭제를 검토한다.
- 댓글 수정, 추가와 삭제는 각각 원격 변경으로 보고 별도 승인 범위를 확인한다.
- 게시 registry에는 Demo Issue URL, video comment permalink와 attachment URL을 구분해 기록한다.

## Video 촬영과 검수 기준

- 기본 게시 후보는 MP4, H.264, `yuv420p`, CFR 30 FPS와 audio stream 0개를 사용한다.
- application 전체 창과 공개 가능한 title bar를 포함하고 Chapter와 Step을 식별할 수 있는 title을 사용한다.
- 한 video에는 하나의 변화 또는 interaction을 설명하고 권장 길이는 5~20초로 둔다.
- 시작과 종료에 결과를 확인할 수 있는 안정 구간을 두고 불필요한 마우스 이동과 대기를 줄인다.
- 녹화 중 대상 창을 이동하거나 resize하지 않는다.
- 자동 검수는 container, codec, pixel format, dimensions, CFR, duration, stream 수, 민감 metadata, SHA-256과 전체 frame decode를 확인한다.
- MP4 brand, `handler_name`, encoder library처럼 개인 정보가 아닌 기술 container metadata는 허용한다.
- 사용자 시각 검수는 조작과 결과의 대응, 시작·종료 frame, 잘림과 black frame, 다른 window·notification·계정·경로 노출, 속도와 길이, 정지 이미지 대비 추가 설명 가치를 확인한다.
- 자동 검수는 사용자 시각 검수를 대신하지 않는다.

## 자동 UI 조작 안전 기준

- 자동 UI 조작 시작 전에 사용자가 mouse와 keyboard를 조작하지 않도록 안내하고 countdown을 실행한다.
- countdown 종료 후에 도구가 시작한 process ID, exact window title, foreground window와 DWM bounds를 다시 확인한다.
- 대상 process, title, foreground 또는 bounds가 예상과 다르면 현재 screenshot 또는 video attempt를 폐기한다.
- 자동 조작은 저장소 범위의 example application에만 적용하며 browser, terminal, system UI와 다른 application을 조작하지 않는다.
- Windows 전체 input lock, global mouse hook과 system-wide keyboard hook은 사용하지 않는다.
- 범용 도구는 application 실행, foreground, window bounds, capture, 검증과 cleanup을 담당하고 slider, checkbox, parameter, 상대 좌표와 조작 sequence는 example별 local driver에 둔다.

## Window 배치와 bounds 기준

- application window의 DWM extended frame bounds 전체가 monitor working area 안에 들어오도록 한다.
- 화면 중앙 배치는 잘림과 taskbar 침범을 피하기 위한 선택적 권장 기본값으로 사용한다.
- 중앙 배치는 기존 window size를 유지하며 window가 working area보다 크면 강제 resize 대신 실패로 처리한다.
- 같은 비교 묶음의 capture는 동일한 window size, position과 capture 방식을 유지한다.
- title bar와 window border를 포함하며 녹화 중 window 이동과 resize가 확인되면 현재 attempt를 실패로 처리한다.

## Screenshot 조작 lifecycle

```text
초기 상태 확인
→ 목표 parameter 설정
→ rendering 안정화
→ cursor 대피
→ screenshot
→ 초기 상태 복구 또는 application 재시작
```

- screenshot마다 초기 상태, 목표 parameter, capture 시점과 reset 방식을 local operation plan에 기록한다.
- before/after 비교는 application restart를 기본 reset 방식으로 사용한다.
- parameter를 역조작해 복구하면 실제 기본값과 rendering 상태가 복구됐는지 확인한다.

## Video 조작 lifecycle

```text
핵심 변화 결정
→ 초기 상태와 조작 sequence 확정
→ 시작 안정 구간
→ 조작
→ 결과 안정 구간
→ 저장·검증
→ selected 판정
→ 초기 상태 복구
```

- 촬영 전에 초기값, 목표값, 조작 순서, 동작별 대기 시간, cursor 대피 위치, 종료 상태와 재촬영 조건을 local operation plan에 기록한다.
- 한 video에는 하나의 변화나 interaction을 두고 불필요한 parameter 왕복, 반복 click, mouse movement와 대기를 제거한다.
- 조작 전후에 결과를 확인할 수 있는 안정 구간을 둔다.
- 재촬영하더라도 기존의 정상 attempt는 보존하고 selected 교체는 명시적 옵션으로만 허용한다.

## 기존 visual 유지 판정

각 Example은 새 capture 수량을 채우기보다 기존 visual이 학습 목표를 충분히 설명하는지 먼저 판단한다.

- 기존 visual이 핵심 결과를 명확히 보여주고 동적 변화, 조작, mode 또는 parameter 비교가 새 정보를 추가하지 않으면 재촬영 없이 유지할 수 있다.
- 재촬영 불필요 판정도 visual 검수 결과이며 검토 생략으로 취급하지 않는다.
- 기존 visual 유지는 사용자 시각 검수를 거쳐 `retained`로 확정한다.
- 새 후보는 사용자 승인 전까지 기존 tracked capture를 교체하거나 삭제하지 않는다.
- 기존 visual을 그대로 유지하고 정본 상태도 정확하면 불필요한 파일 변경이나 빈 commit을 만들지 않는다.
- 촬영자가 달라도 자동 기술 검수, 사용자 시각 검수와 tracked asset 승격 기준은 동일하게 적용한다.

## Capture/Result 승격 기준

`local/`의 capture 후보나 ignored output의 result image는 다음 조건을 만족할 때만 `Docs/_assets`로 승격한다.

- build/run 상태가 `성공` 또는 `부분 성공`으로 기록되어 있다.
- 화면 또는 결과 파일이 보여줄 graphics 개념, 예제 상태, 비교 결과를 명확히 설명한다.
- `Docs/03_Demos/*/demo-index.md`, 상세 Demo 문서 또는 `Docs/03_Demos/capture-plan.md`에서 참조할 계획이 있다.
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

전체 application window를 촬영하면 공개 가능한 application title과 window border는 포함할 수 있다. 이 경우 실행 결과 규격은 client 해상도를 기준으로 기록하며 OS theme, border와 DPI에 따른 전체 image dimensions 차이는 허용한다. 같은 Demo의 비교 capture는 가능한 한 동일한 window 크기, 위치와 capture 방식을 유지한다.

예제 유형별 기본 요청 기준은 다음과 같다.

| 예제 유형 | 우선 요청 | 기준 |
| --- | --- | --- |
| post-processing | input image와 result image | 처리 전후 비교는 상세 Demo에 두고 Example README에는 대표 visual을 최대 1개 둔다. |
| static rendering | screenshot | 최종 화면 한 장으로 핵심 개념을 설명할 수 있어야 한다. |
| interaction, camera, control | video | 움직임이나 입력 반응이 설명의 핵심이면 video를 우선한다. |
| simulation, animation, physics | video와 대표 screenshot | 시간 변화는 video로, 대표 상태는 screenshot으로 남긴다. |
| file output 기반 예제 | result image | 프로그램이 출력한 파일을 우선 연결한다. |

예제 단위에서 capture/result가 필요 없거나 시각적 설명 가치가 낮으면 `제외`로 기록하고 사유를 남긴다. 단, Chapter 또는 Chapter 묶음 demo-index 기준으로는 최소 1개 screenshot을 유지한다.

## README 표시 기준

capture/result가 확보된 예제는 코드 폴더 README의 `Capture/Result` 섹션에 대표 자료를 최대 1개 연결한다. 여러 시각 자료의 비교는 상세 Demo에서 별도 소제목을 둔 세로 배치를 기본으로 한다.

README와 일반 Docs 문서는 repo 안에서 렌더링되므로 repo-relative path를 사용한다. GitHub Issue, PR, comment body는 GitHub remote 페이지에서 렌더링되므로 `Docs/07_GitHub` 후보 문서에 capture/result를 연결할 때는 GitHub absolute URL을 사용한다.

권장 형식:

```md
## Capture/Result

### Input

![Input](../../Docs/_assets/captures/example_input.png)

### Result

![Result](../../Docs/_assets/captures/example_result.png)
```

input/result, before/after처럼 비교가 필요한 경우에도 한 줄 표보다 별도 소제목을 둔 세로 배치를 우선한다. tracked 상세 Demo는 video attachment를 직접 정본으로 삼지 않고 실제 Demo Issue 링크와 관찰할 변화의 짧은 설명을 둔다.

## GitHub body 이미지 URL 기준

GitHub Issue, PR, comment body에 들어가는 screenshot/result image는 repo-relative path를 사용하지 않는다. 게시 후보 문서인 `Docs/07_GitHub` 안에서는 다음 형식을 사용한다.

```md
![Description](https://github.com/Razria93/Graphics_Study_Archive/blob/<branch-name>/Docs/_assets/captures/example.png?raw=true)
```

기준:

- 게시 전 branch 검토 중에는 후보 branch URL을 임시로 사용할 수 있다.
- 계속 갱신되는 문서 이동 링크는 확인된 default branch URL을 사용한다.
- 게시 시점의 image와 code 증거는 commit permalink를 사용한다.
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


## Generated Input workflow

이미지 입력이 필요한 예제는 외부 wallpaper나 출처 불명 이미지를 우선 사용하지 않는다. Generated input의 출처 기록과 강화 검수 조건은 [Assets Policy](assets-policy.md)를 따른다.

1. 예제 목적에 맞는 입력 이미지를 직접 생성하거나 출처가 확인된 자료를 선택한다.
2. 출처 상태와 외부 자료 복제 여부를 확인한다.
3. 예제 실행용 입력으로 테스트하고 result image를 생성한다.
4. 실행 입력과 tracked input의 hash 또는 재인코딩 관계를 확인한다.
5. metadata, 워터마크, 텍스트, 개인 식별자를 검수한다.
6. tracked 입력 asset 교체, `Docs/_assets` 승격, public subset 후보 여부를 별도로 판단한다.

권장 프롬프트 조건:

```text
No text, no logo, no watermark, no people
16:9 aspect ratio
Clear visual features for the target graphics concept
```

Prompt 원문, 생성 화면, 생성 날짜와 작업용 원본은 기본 승격 필수가 아니다. 출처가 불명확하거나 외부 자료가 섞인 경우에만 강화 검수 자료로 요청한다.

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
- 연결된 상세 Demo 문서
- `Docs/02_Verification/capture-matrix.md`
- 관련 코드 폴더 README와 `Docs/01_Topics`
- capture/result가 있는 예제의 코드 폴더 README
- `Docs/05_Publication`의 public 후보 또는 제외 판단
- Root/Chapter/Example README의 대표 visual 노출 필요 여부
- `Docs/07_GitHub` Demo Issue와 PR 게시 후보의 연결 필요 여부

## 갱신 기준

- screenshot/video/result image를 추가하면 `Docs/03_Demos`, `Docs/02_Verification/capture-matrix.md`, `Docs/05_Publication`을 함께 확인한다. Video는 필요성 판정과 raw, attempt, selected, published 상태도 함께 기록한다.
- screenshot/result image를 추가하면 이미지 metadata를 확인하고, video를 추가하면 파일 크기, 저장 위치, 공개 가능성을 먼저 확인한다.
- GitHub Issue/PR body에는 승격 검수를 통과한 capture/result만 연결한다.
- 상세 Demo에서 구현·결과·limitation이 크게 바뀌면 Demo Issue 동기화 필요 여부를 확인한다.
- 같은 tracked asset은 여러 public surface에서 재사용할 수 있지만 설명 본문은 각 surface 목적에 맞게 작성한다.
- capture/result 승격 전에는 화면 안의 title, watermark, overlay, account, path를 수동으로 확인한다.

## Bundle 단위 rendered evidence 승격

강의 제공 runtime asset이 포함된 capture/result는 기본적으로 출처와 권리 검토 기준을 따른다. 다만 `publication-policy.md`의 Bundle 단위 rendered evidence 예외가 승인된 범위에서는 원본 asset을 공개하지 않고 구현 결과만 보여주는 screenshot, storyboard와 video를 별도로 승격할 수 있다.

- 시각 자료는 asset 자체가 아니라 구현 동작과 graphics 결과를 설명해야 한다.
- 원본 asset과 직접 다운로드 링크는 tracked Demo와 GitHub body에 넣지 않는다.
- 강의 화면, 워터마크, 개인정보, 계정, 로컬 경로와 외부 application UI가 없어야 한다.
- 예외 승인 범위와 원본 asset 교체 backlog는 `Docs/05_Publication`에 기록한다.
