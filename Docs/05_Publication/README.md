# Publication

이 폴더는 private archive에서 public subset으로 옮길 수 있는 후보와 제외 대상을 판단하는 정본 위치다. public repo 자체를 만들거나 게시하는 위치가 아니다.

## 책임

- public 후보, private-only, 검토 필요, 제외 대상을 구분한다.
- 공개 전 체크리스트와 redaction 확인 항목을 관리한다.
- Example, Topic, Verification, Demo 문서를 public 후보로 그대로 복사하지 않고 재작성 대상으로 분리한다.
- 권리, 출처, 민감 정보, 강의 자료 포함 여부를 공개 전 점검 기준으로 기록한다.
- GitHub 게시 후보 본문은 `Docs/07_GitHub`에서 관리한다. 공개 전 상세 검토 메모는 필요할 때 `local/publication`에 둔다.

## 문서 목록

| 문서 | 책임 |
| --- | --- |
| [Candidate List](candidate-list.md) | public subset 후보 목록 |
| [Private Only](private-only.md) | private archive에만 둘 항목 |
| [Excluded Material](excluded-material.md) | public/archive 이동 제외 대상 |
| [Redaction Log](redaction-log.md) | 공개 전 제거 또는 재작성 필요 항목 |
| [Publication Checklist](publication-checklist.md) | 공개 전 최종 점검표 |


## 제출 요약 예약

`submission-summary.md`는 지금 생성하지 않는다. public 후보와 대표 capture/result가 확정된 뒤, 공개용 repo 또는 포트폴리오 제출 자료를 구성하기 직전에 작성한다.

생성 조건:

- `candidate-list.md`에서 public 후보가 P0 또는 대표 후보로 좁혀져 있다.
- `Docs/02_Verification`에 대표 build/run/capture 확인 기록이 있다.
- `Docs/03_Demos`와 `Docs/_assets`에 연결 가능한 demo capture/result가 있다.
- `redaction-log.md`와 `publication-checklist.md` 기준으로 공개 전 제거/재작성 대상이 정리되어 있다.

문서 책임:

- 3줄 요약
- 이력서 또는 README용 한 문장
- 대표 기능과 설명 포인트
- 연결 capture/result와 build/run 확인 기록
- 공개 시 남길 제한 사항

`submission-summary.md`는 public 제출용 요약 후보이며, private archive의 Example, Topic, Verification, Demo 문서를 그대로 복제하지 않는다.

## 상태값

| 상태 | 의미 |
| --- | --- |
| `public 후보` | 직접 작성했고 공개 전 체크리스트 통과 가능성이 있음 |
| `private archive` | private repo에는 둘 수 있으나 public 후보는 아님 |
| `검토 필요` | 출처, 권리, 민감 정보, 표현 재작성 여부 확인 필요 |
| `제외` | public subset으로 옮기지 않음 |

## 운영 기준

- raw/reference에서 public으로 직접 이동하지 않는다.
- private archive 문서도 public으로 그대로 복사하지 않는다.
- public 후보는 직접 이해한 설명, 직접 만든 capture/result, 라이선스 확인 asset 중심으로 다시 선별한다.
- 법률 자문처럼 단정하지 않고 공개 전 점검 기준으로 기록한다.
