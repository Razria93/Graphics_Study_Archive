# Verification

이 폴더는 build, run, capture, known issue의 최신 상태를 기록하는 source docs다. 문서 작성 여부와 실제 검증 여부를 분리해서 기록한다.

## 책임

- 전체 build/run 상태는 `build-run-matrix.md`에 기록한다.
- capture 상태는 `capture-matrix.md`와 `Docs/03_Demos`로 연결한다.
- 실패, 보류, 미확인 항목은 `known-issues.md`에 남긴다.
- 예제별 상세 검증은 Part/Chapter 하위 `verification-index.md`에서 시작한다.
- legacy import 기록과 WorkLog는 참고 자료이며 최신 검증 정본이 아니다.
- GitHub PR/Issue/comment에는 이 폴더의 상세 로그를 복제하지 않고 `Docs/07_GitHub`에서 요약과 링크로 재구성한다.

## 문서 목록

| 문서 | 책임 |
| --- | --- |
| [Build Run Matrix](build-run-matrix.md) | Part/Chapter 단위 build/run 최신 상태 |
| [Capture Matrix](capture-matrix.md) | capture/result 상태 요약 |
| [Known Issues](known-issues.md) | 실패, 보류, 미확인 사유 목록 |

## Part/Chapter Verification

| 범위 | 문서 위치 | 문서 상태 |
| --- | --- | --- |
| Part1 Chapter01-02 | [Part1_Chapter01-02](Part1_Chapter01-02/verification-index.md) | 골격 작성 |
| Part1 Chapter03 | [Part1_Chapter03](Part1_Chapter03/verification-index.md) | 골격 작성 |
| Part2 Chapter04 | [Part2_Chapter04](Part2_Chapter04/verification-index.md) | 작성 완료 |
| Part2 Chapter05-08 | [Part2_Chapter05-08](Part2_Chapter05-08/verification-index.md) | Chapter05 Step1–4와 Chapter06 Step1–5A 현재 확인 |
| Part3 Chapter09 | [Part3_Chapter09](Part3_Chapter09/verification-index.md) | Step1–6 현재 확인 완료 |
| Part3 Chapter10-13 | [Part3_Chapter10-13](Part3_Chapter10-13/verification-index.md) | Chapter10·11 현재 확인 완료, Chapter12–13 진행 예정 |
| Part4 Chapter14-20 | [Part4_Chapter14-20](Part4_Chapter14-20/verification-index.md) | 골격 작성 |
| Portfolio RayTracer | [Portfolio_RayTracer](Portfolio_RayTracer/verification-index.md) | 골격 작성 |

## 문서 상태값

Part/Chapter 표의 `문서 상태`는 build/run/capture 결과가 아니라 검증 문서 골격의 작성 상태를 뜻한다.

| 상태 | 의미 |
| --- | --- |
| `골격 작성` | 기본 문서만 있으며 실제 검증 기록은 아직 부족함 |
| `작성 중` | build/run/capture 결과를 갱신하는 중 |
| `작성 완료` | 현재 범위의 검증 기록이 정리됨 |
| `후속 필요` | 추가 실행, 실패 원인 분석, capture/result 확인이 남음 |

## 최종 검증 요약 예약

`final-verification-summary.md`는 지금 생성하지 않는다. Part/Chapter별 `verification-index.md`, `build-run-matrix.md`, `capture-matrix.md`, `known-issues.md`가 충분히 채워진 뒤 최종 제출 또는 public subset 선별 직전에 작성한다.

생성 조건:

- P0 또는 대표 예제의 build/run 상태가 직접 확인되어 있다.
- capture/result 상태가 `확보`, `미확인`, `보류`, `제외`로 구분되어 있다.
- known issue와 follow-up이 최신 상태로 정리되어 있다.
- `Portfolio_RayTracer`와 Part1~Part4의 대표 검증 결과를 한 문서에서 비교할 필요가 있다.

문서 책임:

- 기능별 또는 Part별 검증 결과 요약
- 대표 capture/result 링크
- 남은 제한과 미확인 항목
- public subset 판단에 필요한 build/run 확인 기록

상세 로그와 최신 상태의 정본은 계속 matrix와 각 `verification-index.md`에 둔다. `final-verification-summary.md`는 최종 요약 문서이며 검증 정본을 대체하지 않는다.

## 상태값

| 상태 | 의미 |
| --- | --- |
| `미확인` | 직접 build/run/capture하지 않음 |
| `성공` | 직접 확인한 성공 상태 |
| `실패` | 직접 확인한 실패 상태 |
| `부분 성공` | 실행 가능하지만 known issue가 남음 |
| `보류` | 의도적으로 확인을 미룸 |
| `제외` | 검증 대상에서 제외함 |

## Provenance와 현재 재검증

검증 결과와 확인 시점은 분리한다. 문서화 이전에 직접 확인한 성공은 결과를 `성공`, provenance를 `과거 확인`, 현재 재검증을 `필요`로 기록한다. 표에서는 `현재 재검증 | 필요` 형식을 사용하고, 본문에서는 이를 `재검증 필요`라고 표현할 수 있다. 상세 기준은 [Verification Policy](../06_Policies/verification-policy.md)를 따른다.

## 작성 기준

- Debug x64를 기본 검증 기준으로 둔다.
- 대표 예제만 필요하면 Release x64를 확인한다.
- 직접 확인하지 않은 항목은 `미확인`으로 둔다.
- 실패 상태는 숨기지 않고 known issue로 남긴다.
