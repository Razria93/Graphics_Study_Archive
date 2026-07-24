# Demo Map

이 문서는 capture와 video evidence의 계획, 위치, 공개 판단 연결을 안내한다.

## 정본 위치

| 항목 | 위치 | 책임 |
| --- | --- | --- |
| demo 우선순위 | `Docs/03_Demos/demo-priority.md` | Part별 최소/대표/선택 demo 후보 |
| screenshot 계획 | `Docs/03_Demos/capture-plan.md` | screenshot evidence 확보 기준 |
| video 계획 | `Docs/03_Demos/video-plan.md` | video evidence 확보 기준 |
| Part별 demo index | `Docs/03_Demos/<Part*>/demo-index.md` | Part/Chapter별 demo 후보와 evidence 연결 |
| capture 파일 | `Docs/_assets/captures` | 검토된 screenshot evidence |
| video 파일 또는 링크 | `Docs/_assets/videos` | 검토된 video evidence 또는 reference |
| diagram 파일 | `Docs/_assets/diagrams` | 직접 만든 설명용 이미지 |
| 공개 판단 | `Docs/05_Publication` | public 후보 여부와 제외 사유 |

## Demo 등급

| 등급 | 기준 | 처리 |
| --- | --- | --- |
| 최소 capture | 예제 실행 여부를 보여주는 기본 evidence | 주요 Work Unit에 최소 1개 확보 |
| 대표 capture | 포트폴리오에서 시각적 임팩트가 있는 evidence | README, Issue, PR 후보로 연결 |
| 선택 capture | 보조 설명용 evidence | 시간이 남을 때 정리 |
| video | 조작, animation, simulation처럼 정지 화면만으로 부족한 evidence | 필요 항목만 선별 |
| 제외 | 권리, 출처, 품질 문제가 있는 evidence | public 후보에서 제외 |

## 운영 기준

- capture는 검증 문서의 실행 상태와 연결한다.
- 강의 화면 캡처, 유료 자료, 출처 불명 asset은 public 후보로 두지 않는다.
- 게시 전 파일명, 출처, 라이선스, 민감 정보 포함 여부를 확인한다.
- raw capture 후보는 tracked Docs가 아니라 `local/`에 둔다.
