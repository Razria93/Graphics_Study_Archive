# WU-Part3

## 범위

- `Part3_Chapter09`
- `Part3_Chapter10-13`

## 현재 상태

| Chapter | 코드 | Build/run | Example | Topic | Demo | Publication |
| --- | --- | --- | --- | --- | --- | --- |
| Chapter09 | 보관 완료 | Step1–6 현재 확인 | Step1–6 작성 | camera·picking·quaternion 작성 | Step1–6 작성 | Step5 public 후보, 나머지 공개 가능 |
| Chapter10-13 | 보관 완료 | 21개 예제 현재 확인 | Chapter10→13 작성 | geometry·texturing·PBR·shadow 작성 | Chapter10→13 작성 | rendered evidence 공개 후보 |

## GitHub 마감 snapshot

| 범위 | Demo Issue | Progress comment | PR | 상태 |
| --- | --- | --- | --- | --- |
| Chapter09 | [Issue #21](https://github.com/Razria93/Graphics_Study_Archive/issues/21) | Chapter09 로컬 정규화 완료 | [PR #23](https://github.com/Razria93/Graphics_Study_Archive/pull/23) · [`3467f09`](https://github.com/Razria93/Graphics_Study_Archive/commit/3467f0961c9717998cf4fab76112d01e88680d0a) | Merged |
| Chapter10-13 | [#25](https://github.com/Razria93/Graphics_Study_Archive/issues/25) · [#26](https://github.com/Razria93/Graphics_Study_Archive/issues/26) · [#27](https://github.com/Razria93/Graphics_Study_Archive/issues/27) · [#28](https://github.com/Razria93/Graphics_Study_Archive/issues/28) | [Phase 4-2 완료 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5189162548) | [PR #24](https://github.com/Razria93/Graphics_Study_Archive/pull/24) · [`75d1c71`](https://github.com/Razria93/Graphics_Study_Archive/commit/75d1c715d90a2e031680f2f30a586eb54674ae5b) | Merged |

- 누적 Progress comment [댓글 5091068690](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)은 Phase 4-2 Chapter10-13 게시 상태와 PR #24 마감 상태를 반영한다.
- `docs/part3-chapter10-13-workflow` local/remote branch는 PR #24 merge 후에도 보존한다.
- Part4 작업은 이 snapshot 시점에 시작하지 않았다.

## Chapter09 결정

- Step1–6은 camera → GPU picking → CPU picking → quaternion → trackball → drag 순서로 유지한다.
- Step2와 Step3은 같은 문제의 GPU·CPU 비교이며 하나의 구현으로 합치지 않는다.
- Raw `Quaternian` 경로는 유지하고 공개 문서에서는 `Quaternion`을 사용한다.
- Cubemap, UV grid와 Earth texture 원본은 비공개 runtime dependency로 유지하고 직접 실행 visual만 승인된 Chapter09 Bundle 예외로 공개한다.
- 2026-08-03 사용자 승인으로 Chapter09에 Bundle 단위 rendered evidence 예외를 적용하며 다른 Chapter에는 자동 적용하지 않는다.
- 대표 visual은 Step5 VirtualTrackball, Step1 FirstPersonView, Step6 MouseDragMove 순서로 선정한다.
- 기본 screenshot 6장과 Step2 hover·Step3 press screenshot을 archive evidence로 추적한다.
- Step1·3·4·5·6 selected video는 foreground 검증과 full decode를 통과한 local evidence로 유지한다.
- 초기 foreground 검증 실패 후보와 39.77초 Step4 통합 take는 선택하지 않고 `local/`에만 둔다.
- Step5 selected video는 [Demo Issue #21 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/21#issuecomment-5164633305)에 한 번 게시하고 나머지 7개는 local evidence로 유지한다.

## Chapter09 runtime asset limitation

`SRC-P3-C09` raw import에서 archive로 이동한 다음 asset은 Step1부터 Step6까지 실행 재현용 원본으로 유지한다. Runtime 사용과 SHA-256은 확인했지만 원저작자, 공식 배포처와 재배포 license는 완전히 확정하지 않았다.

| ID | Asset | 사용 범위 | SHA-256 | 처리 |
| --- | --- | --- | --- | --- |
| `CH09-ASSET-001` | `Assets/Textures/blender_uv_grid_2k.png` | Step1부터 Step2까지 ground | `0F59CDE48741A02ED844B3AC99B42F6C9E0D95B206DA0128A4873CE36092F95E` | archive 유지 |
| `CH09-ASSET-002` | `Assets/Textures/earth.jpg` | Step3부터 Step6까지 sphere | `59A410F2FDF3FC7466FFCFBEEFF6FD9C641DC662AF16F5A6D1003B42B96A999A` | archive 유지 |
| `CH09-ASSET-003` | `Assets/Textures/Cubemaps/skybox/cubemap_bgra.dds` | Step1부터 Step6까지 skybox | `72DDE96BF3D06A9D01617915AB71B8E3F8A269CE4F010D702463FDB75AF76D22` | archive 유지 |
| `CH09-ASSET-004` | `Assets/Textures/Cubemaps/skybox/cubemap_diffuse.dds` | Step1부터 Step6까지 diffuse IBL | `B02F847C5C16F9761C08A92D8709C6256FCFD2A99A2976AA0C7269027B1DFC61` | archive 유지 |
| `CH09-ASSET-005` | `Assets/Textures/Cubemaps/skybox/cubemap_specular.dds` | Step1부터 Step6까지 specular IBL | `4DB7AA1450E63AEC34663AE9D35E6CD60C7DC2C2E632E9A3B6C9C713BBE16F8A` | archive 유지 |

- 강의 예제에서 사용한 asset이지만 원본 재배포 권리까지 확인됐다고 단정하지 않는다.
- 원본 asset과 직접 다운로드 링크는 public 후보로 선정하지 않는다.
- 직접 실행한 screenshot, storyboard와 video는 구현 evidence로 공개할 수 있다.
- 공개 안전한 대체 asset 교체는 필수 gate가 아닌 장기 선택 backlog로 유지한다.
- 명확한 제한 근거, 삭제 요청 또는 사용 중단 요청이 확인되면 관련 visual을 교체하거나 비공개로 전환한다.

## Chapter10-13 결정

- 21개 Example은 Chapter10 geometry pipeline, Chapter11 texturing, Chapter12 PBR와 Chapter13 light/shadow 순서로 유지한다.
- Chapter10 Step1은 point에서 네 vertex triangle strip을 생성한다.
- Chapter10 Step5는 Manual을 기본 경로로 유지하고 Distance Adaptive를 사용자 확장으로 분리한다.
- Chapter13의 중복 raw Step2 경로는 보존하고 공개 표시를 Step2 PipelineStateObject와 Step2B Shadow Prototype으로 구분한다.
- Chapter13 대표 visual은 hard shadow→PCF→PCSS 비교 sheet로 둔다.
- 출처 불완전 runtime asset은 원본과 직접 링크를 공개하지 않고 직접 실행한 rendered evidence만 후보로 사용한다.
- Chapter13은 정지 image만으로 구현 차이가 분명하므로 video를 제외한다.

## 마감 결과

- Chapter10→13 Demo Issue 4개를 Chapter10→11→12→13 순서로 게시했다.
- 실제 Issue URL을 Demo index, PR body와 Progress comment 후보에 동기화했다.
- PR #24를 Ready for Review로 전환하고 review feedback을 반영한 뒤 일반 merge commit으로 병합했다.
- Progress 누적 댓글과 Phase 4-2 완료 댓글을 게시했다.

## 남은 선택 backlog

- 원본 runtime asset 교체는 시간과 필요성을 검토할 선택 backlog로 유지한다.
- Part4 진입 전에는 main 기준 checkout과 WorkLog 상태를 확인한다.

## 관련 문서

- [Chapter09 README](../../../Part3_Chapter09/README.md)
- [Chapter10-13 README](../../../Part3_Chapter10-13/README.md)
- [Chapter09 Verification](../../02_Verification/Part3_Chapter09/verification-index.md)
- [Chapter10-13 Verification](../../02_Verification/Part3_Chapter10-13/verification-index.md)
- [Chapter09 Demo Index](../../03_Demos/Part3_Chapter09/demo-index.md)
- [Chapter10-13 Demo Index](../../03_Demos/Part3_Chapter10-13/demo-index.md)
- [Chapter10-13 Capture Plan](../../../Part3_Chapter10-13/capture-plan.md)
- [Publication Candidate List](../../05_Publication/candidate-list.md)
