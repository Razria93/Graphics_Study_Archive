## Phase 4-1부터 Phase 4-2까지 완료 기록

## 완료 내용

### Phase 4-1. Part3 Chapter09 User Interaction

- `Part3_Chapter09` Step1부터 Step6까지 camera, GPU·CPU picking, quaternion rotation, VirtualTrackball과 MouseDragMove를 재검증했다.
- Example README, Topic, Verification과 독립 상세 Demo를 연결했다.
- Step5 VirtualTrackball을 대표 visual로 선정하고 Step1 FirstPersonView와 Step6 MouseDragMove를 보조 visual로 유지했다.
- 대표 interaction을 [Demo Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21)에 게시하고 Step5 selected video는 [전용 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/21#issuecomment-5164633305)로 분리했다.

### Phase 4-2. Part3 Chapter10-13

- `Part3_Chapter10-13`의 21개 예제를 Geometry Pipeline, Texturing Techniques, PBR와 Light/Shadow 순서로 재검증했다.
- Example README 21개, 관련 Topic, Verification과 독립 상세 Demo 21개를 연결했다.
- Chapter10 Step1의 quad strip, Step5 Manual·Distance Adaptive 분리와 Chapter13 Step2B 공개 표시를 확정했다.
- Chapter10 [Demo Issue #25](https://github.com/Razria93/Graphics_Study_Archive/issues/25), Chapter11 [Demo Issue #26](https://github.com/Razria93/Graphics_Study_Archive/issues/26), Chapter12 [Demo Issue #27](https://github.com/Razria93/Graphics_Study_Archive/issues/27), Chapter13 [Demo Issue #28](https://github.com/Razria93/Graphics_Study_Archive/issues/28)에 rendered evidence를 게시했다.

## 검증

### Phase 4-1

- Step1부터 Step6까지 Debug/Release x64 build/run: 성공
- 기본 screenshot 6장과 picking 상태 screenshot: 확보
- Step1·3·4·5·6 selected local video full decode와 foreground 검수: 통과
- Demo, Markdown과 GitHub body validator: 통과

### Phase 4-2

- 21개 예제 Debug/Release x64 Clean/Rebuild와 run: 성공
- 전체 application window screenshot 21장과 Chapter13 shadow comparison sheet: 확보
- Capture full decode, metadata와 공개 안전성 검사: 통과
- 문서, Markdown rendering, table, asset validator와 GitHub Actions: 통과

## 남은 제한

### Phase 4-1

- 원본 runtime texture와 cubemap은 비공개 dependency로 유지한다.
- 직접 실행한 rendered evidence만 승인된 Chapter09 Bundle 범위에서 사용한다.
- Step5 video 외의 selected video는 local evidence로 유지한다.

### Phase 4-2

- 강의 제공·출처 불완전 runtime asset 원본은 직접 공개하지 않고 rendered evidence만 사용한다.
- Chapter10 Step4 Fireball의 animation video는 정적 결과가 충분해 필수 자료에서 제외한다.
- P2 architecture와 portability 개선은 별도 후속 후보로 유지한다.

## Related PR

- [PR #23](https://github.com/Razria93/Graphics_Study_Archive/pull/23) - Part3 Chapter09 User Interaction 구현과 Demo
- [Demo Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21) - Part3 Chapter09 User Interaction Demo
- [PR #24](https://github.com/Razria93/Graphics_Study_Archive/pull/24) - Part3 Chapter10-13 Geometry·Texturing·PBR·Light/Shadow 구현과 Demo
- [Demo Issue #25](https://github.com/Razria93/Graphics_Study_Archive/issues/25) - Part3 Chapter10 Geometry Pipeline Demo
- [Demo Issue #26](https://github.com/Razria93/Graphics_Study_Archive/issues/26) - Part3 Chapter11 Texturing Techniques Demo
- [Demo Issue #27](https://github.com/Razria93/Graphics_Study_Archive/issues/27) - Part3 Chapter12 PBR Demo
- [Demo Issue #28](https://github.com/Razria93/Graphics_Study_Archive/issues/28) - Part3 Chapter13 Light and Shadow Demo
