# Build Guide

이 문서는 예제 build/run 확인의 공통 기준을 둔다. 최신 검증 결과의 정본은 `Docs/03_Verification`에 둔다.

## 기본 기준

- Visual Studio solution을 기준으로 확인한다.
- `Debug x64`를 우선 확인한다.
- 대표 예제나 release candidate는 필요하면 `Release x64`도 확인한다.
- shader, texture, model 경로 문제를 known issue로 기록한다.
- 직접 확인하지 않은 항목은 `미확인`으로 기록한다.

## 기록 위치

| 항목 | 위치 |
| --- | --- |
| 전체 build/run matrix | `Docs/03_Verification/build-run-matrix.md` |
| capture 상태 | `Docs/03_Verification/capture-matrix.md` |
| known issue | `Docs/03_Verification/known-issues.md` |
| 검증 정책 | `Docs/07_Policies/verification-policy.md` |

## 운영 순서

1. 대상 solution 경로를 확인한다.
2. `Debug x64` build를 실행한다.
3. 실행 가능 여부를 확인한다.
4. capture가 필요하면 `Docs/04_Demos` 기준에 맞춰 기록한다.
5. 결과를 `Docs/03_Verification`에 기록한다.