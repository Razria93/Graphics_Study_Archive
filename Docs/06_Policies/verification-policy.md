# Verification Policy

이 문서는 build, run, capture 검증 기록 기준을 정의한다.

## 정본 위치

검증 상태의 정본은 `Docs/02_Verification`에 둔다.

## 기록 항목

- 대상 solution 또는 실행 파일
- configuration
- build 상태
- run 상태
- capture 상태
- 확인 일자
- 확인자
- known issue
- follow-up

과거 확인 기록에는 다음 provenance 항목을 함께 둔다.

- 확인 근거: `현재 확인`, `과거 확인`, `없음`
- 확인 시점: 날짜를 알면 날짜, 알 수 없으면 `문서화 이전(날짜 미기록)`
- 현재 재검증: `완료`, `필요`, `해당 없음`
- 과거 build/run 확인을 명시한 문서 또는 그 기록을 포함한 Git commit

## 상태값

- `성공`: 직접 확인한 성공 상태
- `부분 성공`: 일부 configuration, 실행 단계, capture 조건만 확인한 상태
- `실패`: 직접 확인한 실패 상태
- `미확인`: 아직 직접 확인하지 않은 상태
- `보류`: 확인을 의도적으로 미룬 상태

`과거 확인`은 검증 결과 상태값이 아니라 provenance다. 문서화 이전에 직접
build/run을 확인한 이력이 있으면 결과는 `성공`으로 유지하고 현재 작업에서
다시 실행하지 않았다는 사실은 `현재 재검증: 필요`로 분리한다. 근거가 없는
대상에는 과거 성공을 추론하지 않는다.

## Capture/Result 상태값

Demo와 capture/result 상태는 build/run 상태와 구분한다.

- `확보`: 검토된 capture/result가 있고 연결 위치가 기록된 상태
- `미확인`: 아직 capture/result를 직접 확인하지 않은 상태
- `보류`: 촬영 또는 공개 판단을 의도적으로 미룬 상태
- `제외`: public/archive demo capture/result로 사용하지 않기로 결정한 상태


## 최종 요약 문서 기준

`Docs/02_Verification/final-verification-summary.md`는 모든 검증 기록의 정본이 아니라 제출 직전 요약 문서다. Part/Chapter별 최신 상태는 `build-run-matrix.md`, `capture-matrix.md`, `known-issues.md`, 각 `verification-index.md`를 기준으로 유지한다.

이 문서는 다음 시점에만 생성한다.

- 대표 예제와 public 후보가 좁혀진 뒤
- 직접 확인한 build/run/capture 결과가 충분히 모인 뒤
- 제출 또는 public subset 선별을 위해 한 장짜리 검증 요약이 필요할 때
## 작성 기준

- 확인하지 않은 항목을 성공처럼 쓰지 않는다.
- 실패 원인은 숨기지 않고 known issue로 남긴다.
- 오래된 import manifest를 최신 검증 정본으로 사용하지 않는다.
- Chapter README와 Git history에 남은 과거 확인 범위는 provenance 근거로
  사용할 수 있으나, 현재 재실행 결과처럼 표현하지 않는다.
- 코드 import commit이나 코드 존재만으로 build/run 성공을 추론하지 않는다.
