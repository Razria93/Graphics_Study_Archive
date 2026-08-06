## Phase 3-1 완료 기록

## 완료 내용

- `Part2_Chapter04`의 기존 Step1부터 Step10까지 CPU software rasterization 예제를 순서대로 재검증하고 Example README, Topic, Verification과 상세 Demo를 연결했다.
- Step8 PerspectiveProjection을 Chapter 대표 Demo, Step10 Lights를 기술 보조 Demo로 확정했다.
- Step1A Triangle To Circle을 사용자 Personal Extension, Step4 Animation2D를 시간 변화 Demo로 분리했다.
- [Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14)에 Chapter 대표 결과와 핵심 구현 요약을 게시했다.
- Debug/Release x64 build/run과 application window screenshot 19개를 현재 기준으로 확인했다.
- 반복 가능한 screenshot·video capture, 검사 도구와 문서 validator·GitHub Actions 기준을 Chapter 작업에 적용했다.

## 검증

- Step1, Step1A와 Step2부터 Step10까지 Debug/Release x64 build/run: 성공
- Chapter04 tracked capture 19개: 확보와 공개 안전성 확인
- 필수 문서·Markdown rendering·video asset validator: 통과
- GitHub Actions `Docs Validation`: 문서·fixture·asset 정책 검사 구성

## 남은 제한

- Step8은 full projection matrix와 clip-space clipping을 포함하지 않는 학습용 projection이다.
- Step10은 단일 Light와 선형 거리 감쇠를 사용하는 CPU Blinn-Phong 비교다.
- 이 기록은 WU-Part2 전체 완료가 아니라 Phase 3-1 Chapter04 완료 범위다.

## Related PR

- [PR #15](https://github.com/Razria93/Graphics_Study_Archive/pull/15) - Part2 Chapter04 CPU Software Rasterization 단계별 정규화와 Demo
