# Captures

이 폴더는 검토된 screenshot evidence를 둔다.

## 기준

- build/run 상태가 `성공` 또는 `부분 성공`인 예제의 capture만 둔다.
- 파일명은 Part/Chapter/Portfolio, 예제 또는 Topic을 드러낸다.
- 강의 화면 캡처와 출처 불명 asset은 제외한다.
- `Docs/03_Demos` 또는 `Docs/02_Verification`에서 실제로 참조할 capture만 둔다.
- raw 후보, 실패한 capture, 중복 capture는 `local/`에 둔다.

## 파일명 기준

```text
part##_chapter##_example-or-topic.png
part##_chapter##_example-or-topic_before.png
part##_chapter##_example-or-topic_after.png
portfolio_raytracer_topic.png
```

파일명에는 branch 이름이나 PR 번호보다 Part/Chapter/Portfolio와 graphics 개념을 우선 반영한다.

## 승격 체크

| 항목 | 기준 |
| --- | --- |
| 실행 상태 | build/run 상태가 `성공` 또는 `부분 성공`임 |
| 문서 연결 | demo-index, capture-plan, capture-matrix 중 하나 이상에서 참조함 |
| 설명 가능성 | capture가 보여주는 graphics 개념을 설명할 수 있음 |
| 중복 여부 | 같은 의미의 capture가 이미 승격되어 있지 않음 |
| 공개 가능성 | 강의 화면, 유료 자료, 출처 불명 asset이 아님 |

## 연결 문서

- Demo 계획: `Docs/03_Demos`
- Capture 상태: `Docs/02_Verification/capture-matrix.md`
- 공개 판단: `Docs/05_Publication`

## 제외 기준

- 실패 화면만 담긴 capture
- 화질이나 구도가 낮아 개념을 설명하기 어려운 capture
- 동일한 의미의 중복 capture
- 강의 화면 또는 유료 자료가 포함된 capture
- 문서에서 참조하지 않는 보관용 capture
