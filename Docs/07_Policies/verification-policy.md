# Verification Policy

이 문서는 build, run, capture 검증 기록 기준을 정의한다.

## 정본 위치

검증 상태의 정본은 `Docs/03_Verification`에 둔다.

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

## 상태값

- `성공`: 직접 확인한 성공 상태
- `실패`: 직접 확인한 실패 상태
- `미확인`: 아직 직접 확인하지 않은 상태
- `보류`: 확인을 의도적으로 미룬 상태

## 작성 기준

- 확인하지 않은 항목을 성공처럼 쓰지 않는다.
- 실패 원인은 숨기지 않고 known issue로 남긴다.
- 오래된 import manifest를 최신 검증 정본으로 사용하지 않는다.