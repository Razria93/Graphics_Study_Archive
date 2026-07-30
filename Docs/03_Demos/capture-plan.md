# Capture Plan

이 문서는 screenshot, video, result image 확보 계획을 기록한다.

## 용어 기준

```text
capture/result
├─ screenshot: 실행 화면을 이미지로 캡처한 파일
├─ video: 실행 화면을 영상으로 녹화한 파일
└─ result image: 프로그램이 파일로 출력한 결과 이미지
```

- `capture`는 screenshot과 video를 묶는 화면 기록 자료다.
- `result image`는 프로그램이 직접 저장한 출력 파일이다.
- 실무 문장에서는 `capture/result`로 줄여 쓸 수 있다.

## 검수 단계

| 단계 | 의미 | 결과 |
| --- | --- | --- |
| 정책 검수 | 기준 문서와 템플릿이 필요한 조건을 설명하는지 확인 | 정책/템플릿 PASS 또는 보완 |
| 후보 검수 | local capture/result 후보가 승격 가능한지 분류 | 미확인, 보류, 제외, 승격 가능 |
| 승격 검수 | `Docs/_assets` 또는 GitHub body에 연결해도 되는지 최종 확인 | 확보 또는 제외 |

정책 검수 PASS는 capture/result 확보가 아니다. 실제 파일은 후보 검수와 승격 검수를 별도로 통과해야 한다.

## 파일 위치

- raw capture 후보: `local/`
- ignored result image 후보: 예제 runtime output 위치
- 검토된 screenshot: `Docs/_assets/captures/`
- 검토된 video: `Docs/_assets/videos/`
- 검토된 result image: `Docs/_assets/captures/` 또는 별도 정한 result image 경로
- capture/result 상태 요약: `Docs/02_Verification/capture-matrix.md`
- demo 설명과 우선순위: `Docs/03_Demos/*/demo-index.md`, `Docs/03_Demos/demo-priority.md`

`Docs/_assets/captures`에는 문서에서 실제로 참조할 검토 완료 screenshot 또는 result image를 둔다. 단순 보관, 실패 기록, 중복 후보는 `local/`에 남긴다.

## 파일명 기준

상세 파일명 정책의 정본은 `Docs/06_Policies/demo-capture-policy.md`를 따른다.

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
- branch 이름 또는 PR 번호를 파일명 기준으로 삼지 않는다.

## Capture/Result Checklist

| 항목 | 기준 |
| --- | --- |
| 실행 확인 | build/run 상태가 `성공` 또는 `부분 성공`임 |
| 화면/결과 품질 | 보여줄 개념이 한눈에 보임 |
| 파일명 | Part/Chapter/Portfolio와 예제 또는 Topic이 드러남 |
| 권리 검토 | 강의 화면, 유료 자료, 출처 불명 asset이 아님 |
| 식별자 제거 | 강의명, 강사명, 워터마크, 개인 이름, 계정, 로컬 경로가 보이지 않음 |
| 화면 범위 | window title, overlay, debug HUD, terminal, IDE, browser tab, taskbar, notification이 공개 가능 범위임 |
| video 검토 | audio, subtitle/caption, metadata에 개인 정보나 강의 정보가 없음 |
| 연결 문서 | Example, Topic, Verification, Demo 문서와 연결됨 |
| 공개 판단 | public 후보, private 전용, 검토 필요, 제외 중 하나로 판단 가능 |

## demo-index 연결 기준

각 Part/Portfolio의 `demo-index.md`에는 capture/result 후보를 다음 수준으로 나눈다.

| 구분 | 의미 |
| --- | --- |
| 최소 capture/result | 해당 Part/Portfolio를 설명하기 위해 반드시 필요한 screenshot/video/result image |
| 대표 capture/result | 포트폴리오 설명에 우선 사용할 screenshot/video/result image |
| 선택 capture/result | 시간이 있거나 설명 보강이 필요할 때 사용할 screenshot/video/result image |

각 항목에는 다음을 기록한다.

- 연결 Example
- 연결 Topic
- build/run 상태
- capture/result 상태
- `_assets` 경로 또는 `local/` 후보 상태
- public 후보 여부

## capture-matrix 연결 기준

`Docs/02_Verification/capture-matrix.md`에는 capture/result 상태만 기록한다. 상세 설명은 `Docs/03_Demos`와 Example/Topic 문서에 둔다.

상태값은 다음을 따른다.

- `확보`: 검토된 capture/result가 `Docs/_assets`에 있고 문서에서 참조된다. 강의명, 강사명, 워터마크, 개인 식별자, 계정, 로컬 경로 검토를 통과해야 한다.
- `미확인`: 아직 capture/result를 직접 확인하지 않았다.
- `보류`: 촬영, result 생성, 권리 검토, 공개 판단을 의도적으로 미룬다.
- `제외`: demo capture/result로 사용하지 않는다.

## 갱신 기준

- screenshot/video/result image를 추가하면 `demo-priority.md`, Part별 `demo-index.md`, `Docs/02_Verification/capture-matrix.md`를 함께 확인한다.
- tracked capture/result로 승격하기 전에는 강의명, 강사명, 워터마크, 개인 식별자, 로컬 경로 노출 여부를 확인한다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
- GitHub 게시 후보를 만들 때는 `Docs/07_GitHub` 본문이 `_assets`의 검토된 capture/result만 참조하는지 확인한다.

## Part1 Chapter03 순차 계획

- Step4 DrawingSphere와 Step5 PhongShading의 기본·파라미터 조정 screenshot, Step6 PerspectiveView부터 Step11 Supersampling까지의 기본 screenshot을 동일한 전체 application window 규격으로 확보했다.
- Step10 Texturing은 사용자 직접 생성 석재 texture를 적용해 자연석 mapping·bilinear sampling·Square seam 부재를 확인했다.
- Step11 Supersampling은 동일 석재 texture를 사용해 160×90 output cell의 64-sample 평균과 8배 point upscale을 확인했다.
- Step12~14는 build/run과 문서화를 같은 순서로 완료한 뒤 capture 필요성을 판단한다.
- 각 Step은 독립 상세 Demo를 기본으로 하며 Chapter 전체를 하나의 Demo로 합치지 않는다.
- 최소·대표·선택 등급은 Step4~14 상세 Demo가 완료된 뒤 확정한다.
