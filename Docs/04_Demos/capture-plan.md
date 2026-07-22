# Capture Plan

이 문서는 screenshot evidence 확보 계획을 기록한다.

## 파일 위치

- 검토된 screenshot: `Docs/_assets/captures/`
- raw capture 후보: `local/`
- capture 상태 요약: `Docs/03_Verification/capture-matrix.md`

## 파일명 기준

```text
part##_chapter##_example_or_topic_short-name.png
portfolio_raytracer_short-name.png
```

예시:

```text
part02_chapter04_depth-buffer.png
part03_chapter13_shadow-mapping-pcf.png
portfolio_raytracer_reflection.png
```

## Capture Checklist

| 항목 | 기준 |
| --- | --- |
| 실행 확인 | build/run 상태가 `성공` 또는 `부분 성공`임 |
| 화면 품질 | 보여줄 개념이 한눈에 보임 |
| 파일명 | Part/Chapter, 예제 또는 Topic이 드러남 |
| 권리 검토 | 강의 화면, 유료 자료, 출처 불명 asset이 아님 |
| 연결 문서 | Example, Topic, Verification 문서와 연결됨 |

## 갱신 기준

- screenshot을 추가하면 `demo-priority.md`, Part별 `demo-index.md`, `Docs/03_Verification/capture-matrix.md`를 함께 확인한다.
- public 후보 여부는 `Docs/06_Publication`에서 별도로 판단한다.
