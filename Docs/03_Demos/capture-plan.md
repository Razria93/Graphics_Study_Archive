# Capture Plan

이 문서는 screenshot evidence 확보 계획을 기록한다.

## 파일 위치

- raw capture 후보: `local/`
- 검토된 screenshot: `Docs/_assets/captures/`
- capture 상태 요약: `Docs/02_Verification/capture-matrix.md`
- demo 설명과 우선순위: `Docs/03_Demos/*/demo-index.md`, `Docs/03_Demos/demo-priority.md`

`Docs/_assets/captures`에는 문서에서 실제로 참조할 검증 완료 evidence만 둔다. 단순 보관, 실패 기록, 중복 후보는 `local/`에 남긴다.

## 파일명 기준

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

기준:

- Part/Chapter/Portfolio 기준을 우선한다.
- example 또는 Topic이 드러나는 짧은 이름을 붙인다.
- before/after 비교가 필요한 경우 접미사로 구분한다.
- branch 이름 또는 PR 번호를 파일명 기준으로 삼지 않는다.

## Capture Checklist

| 항목 | 기준 |
| --- | --- |
| 실행 확인 | build/run 상태가 `성공` 또는 `부분 성공`임 |
| 화면 품질 | 보여줄 개념이 한눈에 보임 |
| 파일명 | Part/Chapter/Portfolio와 예제 또는 Topic이 드러남 |
| 권리 검토 | 강의 화면, 유료 자료, 출처 불명 asset이 아님 |
| 식별자 제거 | 강의명, 강사명, 워터마크, 개인 이름, 계정, 로컬 경로가 보이지 않음 |
| 화면 범위 | window title, overlay, terminal, IDE 주변 정보가 공개 가능 범위임 |
| 연결 문서 | Example, Topic, Verification, Demo 문서와 연결됨 |
| 공개 판단 | public 후보, private 전용, 검토 필요, 제외 중 하나로 판단 가능 |

## demo-index 연결 기준

각 Part/Portfolio의 `demo-index.md`에는 capture 후보를 다음 수준으로 나눈다.

| 구분 | 의미 |
| --- | --- |
| 최소 capture | 해당 Part/Portfolio를 설명하기 위해 반드시 필요한 evidence |
| 대표 capture | 포트폴리오 설명에 우선 사용할 evidence |
| 선택 capture | 시간이 있거나 설명 보강이 필요할 때 사용할 evidence |

각 capture 항목에는 다음을 기록한다.

- 연결 Example
- 연결 Topic
- build/run 상태
- capture 상태
- `_assets` 경로 또는 `local/` 후보 상태
- public 후보 여부

## capture-matrix 연결 기준

`Docs/02_Verification/capture-matrix.md`에는 capture 결과의 상태만 기록한다. 상세 설명은 `Docs/03_Demos`와 Example/Topic 문서에 둔다.

상태값은 다음을 따른다.

- `확보`: 검토된 capture가 `Docs/_assets/captures`에 있고 문서에서 참조된다. 강의명, 강사명, 워터마크, 개인 식별자 검토를 통과해야 한다.
- `미확인`: 아직 capture를 직접 확인하지 않았다.
- `보류`: 촬영 또는 공개 판단을 의도적으로 미룬다.
- `제외`: demo evidence로 사용하지 않는다.

## 갱신 기준

- screenshot을 추가하면 `demo-priority.md`, Part별 `demo-index.md`, `Docs/02_Verification/capture-matrix.md`를 함께 확인한다.
- tracked evidence로 승격하기 전에는 강의명, 강사명, 워터마크, 개인 식별자, 로컬 경로 노출 여부를 확인한다.
- public 후보 여부는 `Docs/05_Publication`에서 별도로 판단한다.
- GitHub 게시 후보를 만들 때는 `local/github/public` 본문이 `_assets`의 검토된 evidence만 참조하는지 확인한다.
