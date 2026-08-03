# WU-Part3

## 범위

- `Part3_Chapter09`
- `Part3_Chapter10-13`

## 현재 상태

| Chapter | 코드 | Build/run | Example | Topic | Demo | Publication |
| --- | --- | --- | --- | --- | --- | --- |
| Chapter09 | 보관 완료 | Step1–6 현재 확인 | Step1–6 작성 | camera·picking·quaternion 작성 | Step1–6 작성 | 검토 필요 |
| Chapter10-13 | 보관 완료 | 과거 확인 | 대기 | 대기 | 대기 | 대기 |

## Chapter09 결정

- Step1–6은 camera → GPU picking → CPU picking → quaternion → trackball → drag 순서로 유지한다.
- Step2와 Step3은 같은 문제의 GPU·CPU 비교이며 하나의 구현으로 합치지 않는다.
- Raw `Quaternian` 경로는 유지하고 공개 문서에서는 `Quaternion`을 사용한다.
- Cubemap, UV grid와 Earth texture는 권리 근거가 확인될 때까지 공개 대표 visual과 GitHub 게시 후보에서 제외한다.
- 기본 screenshot 6장과 Step2 hover·Step3 press screenshot을 archive evidence로 추적한다.
- Step1·3·4·5·6 selected video는 foreground 검증과 full decode를 통과한 local evidence로 유지한다.
- 초기 foreground 검증 실패 후보와 39.77초 Step4 통합 take는 선택하지 않고 `local/`에만 둔다.

## 다음 작업

1. Chapter09 Publication asset 권리 근거 또는 공개 안전한 대체 asset을 검토한다.
2. Chapter09 GitHub 게시 후보는 Publication 판정 뒤 별도 작업으로 작성한다.
3. Chapter10-13 착수 감사를 수행한다.

## 관련 문서

- [Chapter09 README](../../../Part3_Chapter09/README.md)
- [Verification](../../02_Verification/Part3_Chapter09/verification-index.md)
- [Demo Index](../../03_Demos/Part3_Chapter09/demo-index.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
