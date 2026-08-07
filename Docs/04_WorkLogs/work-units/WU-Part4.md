# WU-Part4

## 범위

- `Part4_Chapter14-20`

## 현재 상태

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| Source/import | 반영 완료 | `SRC-P4-C14-20`으로 source provenance를 추적한다. |
| Branch | 진행 중 | `docs/part4-chapter14-20-workflow`에서 Chapter14부터 Chapter20까지 local source docs, Publication, Topic, WorkLog closeout 상태를 기록하고 GitHub body 후보 작성 전 기준을 고정한다. |
| Build/run | Chapter14부터 Chapter20까지 Debug 일부 확인 · Chapter16부터 Chapter20까지 Release 확인 | Chapter14 `Ex1401`부터 `Ex1408`까지와 Chapter15 `Ex1501`부터 `Ex1503`까지를 2026-08-06, Chapter16 `Ex1601`부터 Chapter20 `Ex2001`까지를 2026-08-07 Debug와 Release x64로 현재 확인했다. Chapter14부터 Chapter15까지 Release 현재 재검증은 남아 있다. |
| Capture | tracked/local 후보 | Ex1402, Ex1404부터 Ex1407까지, Ex1501, Ex1502, Ex1503 centered client-visible screenshot 후보와 Chapter16부터 Chapter20까지 모든 Example의 `GraphicsVideo` storyboard PNG 12장을 `Docs/_assets/captures`에 승격했다. 원본 MP4와 raw preview는 local-only로 유지한다. 최신 capture 상태는 [Demo Index](../../03_Demos/Part4_Chapter14-20/demo-index.md)에서 확인한다. |
| Demo | Chapter14부터 Chapter20까지 작성 | Chapter14부터 Chapter20까지 모든 Example별 상세 Demo를 작성했다. 각 Example은 tracked storyboard, static capture 또는 stdout result를 연결한다. 최신 Demo 상태는 [Demo Index](../../03_Demos/Part4_Chapter14-20/demo-index.md)에서 확인한다. |
| Publication | 검토 필요 | public 후보 확정이 아니라 asset/public risk 검토 축으로만 기록한다. |
| GitHub | Chapter14 merged · Chapter15 merged · Chapter16부터 Chapter20까지 게시 진행 중 | Chapter14 Demo Issue #29, Progress Phase 5-1 완료 댓글과 PR #30을 게시·review 대응·merge까지 마감했다. Chapter15 Demo Issue #31, Progress 누적 댓글 갱신, Phase 5-2 완료 댓글과 PR #32를 게시·review 대응·merge까지 마감했다. Chapter16부터 Chapter20까지 Demo Issue #33부터 #37까지를 생성했고, Progress와 Draft PR 게시를 이어서 진행한다. |

## 마감 snapshot

- Publication: Chapter16부터 Chapter20까지 12개 storyboard evidence는 `Docs/05_Publication/candidate-list.md`에서 검토 필요 후보로 유지한다. HDRI, character, foliage, terrain 원본 asset은 직접 첨부하거나 링크하지 않고 rendered evidence만 사용한다.
- Topic: compute/simulation, animation/physics/gameplay, foliage/landscape Topic은 Part4 Example 범위를 연결하고 build/run/capture 사실은 Verification과 Demo 정본으로 위임한다.
- WorkLog: Chapter14와 Chapter15는 GitHub 게시와 merge를 마감했고, Chapter16부터 Chapter20까지는 Demo Issue 게시와 Draft PR 게시 흐름을 분리한다.
- GitHub body 준비: Chapter16부터 Chapter20까지 Demo Issue body, Progress comment와 PR body 후보를 작성하고 Demo Issue #33부터 #37까지를 생성했다.

## 시작 결정

- Part4는 예제별 solution이 아니라 `Examples.sln` 단일 project와 command argument 기반 sample 선택 구조로 유지한다.
- 첫 작업은 Chapter14 compute slice나 build/run 재검증이 아니라 baseline 문서 축 정규화로 제한한다.
- 이번 범위에서는 build/run/capture를 수행하지 않고, 과거 확인과 현재 재검증 필요 상태를 분리한다.
- Demo Issue, Progress comment, PR remote 게시는 후속 승인 범위로 둔다.

## Part4 장기 브랜치 운영 기준

Part4 Chapter14-20은 `Examples.sln` 단일 project와 command argument 기반 예제 선택 구조를 공유하므로 `docs/part4-chapter14-20-workflow` 장기 브랜치를 유지한다. 작업은 예제 단위로 build/run/capture/document evidence 후보를 생성하고, 증거자료 승인과 remote 게시, PR, merge는 Chapter 단위로 수행한다.

각 Chapter PR merge 후에는 `main`의 merge commit을 장기 브랜치에 반영한 뒤 다음 Chapter 작업을 시작한다. 다음 PR 생성 전에는 `origin/main..HEAD` 범위에 해당 Chapter 작업 commit만 남는지 확인한다.

증거자료는 예제 단위 local 후보로 먼저 만들고, Chapter 단위 검수에서 tracked 승격 여부를 승인한다. 승인 전에는 `Docs/_assets` 승격, GitHub Issue/Progress/PR remote 게시를 진행하지 않는다.

## Chapter14 문서화 기준

- `Ex1401_Basic`과 `Ex1402_Blur`는 compute shader visual 기준선과 대표 visual 후보로 둔다.
- `Ex1403_MatVecMult`와 `Ex1408_BitonicSort`는 screenshot보다 console CPU/GPU result compare를 핵심 evidence로 둔다.
- `Ex1404_StructuredBuffer`와 `Ex1405_ConsumeAppendBuffer`는 structured buffer update/render와 append counter 흐름을 확인한다.
- `Ex1406_DensityField`와 `Ex1407_IndirectArguments`는 density trail visual을 공유하되, Ex1407은 indirect argument buffer 사용 여부를 code evidence와 함께 설명한다.
- Chapter14 문서화 기준 수립 단계에서는 build/run/capture를 수행하지 않는다.

## Chapter14 파일럿 결과

- 2026-08-06 `Ex1401_Basic`부터 `Ex1403_MatVecMult`까지를 command argument `1401`부터 `1403`까지 순서로 Debug x64 재검증했다.
- `Ex1401_Basic`은 checker pattern screenshot 후보로 최소 compute visual 기준선을 확인했다.
- `Ex1402_Blur`는 초기 capture가 white frame에 가까웠으나, 5000ms 안정화 대기 재측정에서 RGB blur visual을 확인했다.
- `Ex1403_MatVecMult`는 `Result CPU`, `GPU Result`, `Error GPU 0`, `ExitCode: 0` stdout evidence를 확인했고 screenshot은 불필요로 둔다.
- `Ex1404_StructuredBuffer`는 structured buffer 기반 particle point cloud screenshot 후보를 확인했다.
- `Ex1405_ConsumeAppendBuffer`는 point cloud screenshot 후보와 `AppendBuffer count: 25600` stdout evidence를 확인했다.
- `Ex1406_DensityField`는 colored density trail screenshot 후보를 확인했다. 시간 변화는 video 후보이나 노트북 환경에서는 screenshot만 남긴다.
- `Ex1407_IndirectArguments`는 density trail screenshot 후보와 `DrawInstancedIndirect` code evidence를 확인했다.
- `Ex1408_BitonicSort`는 element count별 CPU/GPU sort compare `OK`와 `ExitCode: 0` stdout evidence를 확인했다.
- Debug build 후 ignored output의 runtime DLL이 정리되어 loader error가 발생했으며, vcpkg Debug runtime DLL을 `x64/Debug`에 복구한 뒤 run/capture를 진행했다.
- 생성 후보는 `local/capture-run/Part4_Chapter14/pilot-1401-1403-rerun-20260806`, `local/capture-run/Part4_Chapter14/ex1402-remeasure-20260806`, `local/capture-run/Part4_Chapter14/pilot-1404-1408-20260806`에 둔다. 이 local 후보는 tracked asset이 아니다.
- 노트북 환경에서는 Part4 video를 생성하지 않고 screenshot/stdout/code evidence 위주로 기록한다. video가 필요한 density trail, simulation, animation, physics, gameplay evidence는 desktop 환경 별도 목표로 분리한다.
- 2026-08-06 capture UI mode를 `AppBase`에 추가했다. `HLAB_CAPTURE_UI=collapsed` 실행에서는 공통 `Scene Control` titlebar를 좌측 상단 margin에 고정하고 접힌 상태를 유지한다. `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1406_DensityField`, `Ex1407_IndirectArguments` fixed UI 후보는 `local/capture-run/Part4_Chapter14/capture-ui-fixed-20260806`에 둔다.
- 2026-08-06 local capture helper의 visible client area probe로 taskbar 제외 capture를 확인했다. 큰 모니터 연결 후 `CenterWindow` 기준으로 `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1406_DensityField`, `Ex1407_IndirectArguments` 모두 taskbar-free 전체 client 후보를 확보했다. 생성 후보는 `local/capture-run/Part4_Chapter14/capture-ui-fixed-large-monitor-20260806`에 두고, 대표 PNG 4개는 `Docs/_assets/captures`에 승격했다.
- 2026-08-06 `Ex1402_Blur`는 5000ms 안정화 대기, `HLAB_CAPTURE_UI=collapsed`, `CenterWindow`, visible client area 기준으로 1280×768 taskbar-free 전체 client 후보를 확보하고 `Docs/_assets/captures`에 승격했다.

## Chapter14 evidence 후보 선별

- 최소 evidence set은 `Ex1401_Basic` checker visual, `Ex1402_Blur` RGB blur visual, `Ex1403_MatVecMult` stdout compare, `Ex1408_BitonicSort` stdout compare로 둔다.
- 확장 evidence set은 `Ex1404_StructuredBuffer` fixed UI point cloud, `Ex1405_ConsumeAppendBuffer` fixed UI point cloud와 append count stdout, `Ex1406_DensityField` fixed UI density trail, `Ex1407_IndirectArguments` fixed UI density trail과 indirect draw code evidence로 둔다.
- tracked screenshot 후보는 `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1406_DensityField`, `Ex1407_IndirectArguments` centered client-visible fixed UI 후보로 둔다. 승격 PNG는 `file` 기준 RGBA non-interlaced이고 PNG text metadata chunk가 없다. public 확정 여부는 `Docs/05_Publication`에서 별도 판단한다.
- `Ex1401_Basic`은 최소 set 후보지만 fixed UI와 안정된 bounds 기준의 desktop 재촬영 후 승격 여부를 판단한다. `Ex1402_Blur`는 5000ms 안정화 기준으로 tracked screenshot을 승격했다.
- `Ex1403_MatVecMult`, `Ex1408_BitonicSort`는 stdout-only 후보로 두며 screenshot을 만들지 않는다.
- `Ex1405_ConsumeAppendBuffer`는 Consume/Append buffer의 counter 흐름과 `AppendBuffer count: 25600`을 핵심 evidence로 두고 fixed UI screenshot을 visual 보조 evidence로 둔다.
- `Ex1407_IndirectArguments`는 visual이 `Ex1406_DensityField`와 유사하므로 fixed UI screenshot과 `DrawInstancedIndirect(m_argsGPU.Get(), offset)` code evidence를 함께 사용한다.
- `Ex1404_StructuredBuffer`와 `Ex1405_ConsumeAppendBuffer`는 point cloud visual이 유사하지만, `Ex1404`는 단일 StructuredBuffer SRV/UAV draw 흐름이고 `Ex1405`는 Consume/Append UAV counter와 append count 기반 draw 흐름이다.
- `Ex1406_DensityField`와 `Ex1407_IndirectArguments`는 density trail visual이 유사하지만, `Ex1406`은 CPU가 particle count를 직접 넘기는 draw 흐름이고 `Ex1407`은 GPU argument buffer를 넘기는 `DrawInstancedIndirect` 흐름이다.

## Chapter15 파일럿과 승격 감사

- 2026-08-06 `Examples.sln` Debug x64 build를 경고 0개, 오류 0개로 확인했다.
- `capture-example-window.ps1`에 `ArgumentList` option을 추가해 `Examples.exe 1501`, `1502`, `1503` command argument 실행을 capture 도구에서 직접 지원했다.
- `Ex1501_ParticleSystem`, `Ex1502_SpriteFireEffect`, `Ex1503_SphWater`는 `HLAB_CAPTURE_UI=collapsed`, `CenterWindow`, immediate screenshot 기준으로 local 후보를 확보했다.
- 생성 후보는 `local/capture-run/Part4_Chapter15/debug-smoke-20260806`에 둔다. PNG 3개는 text metadata chunk가 없고 taskbar-free fixed UI 기준을 충족한다.
- `Ex1501_ParticleSystem`은 particle stream baseline tracked capture로 승격했다.
- `Ex1502_SpriteFireEffect`는 sprite fire rendered evidence를 tracked capture로 승격했다. 원본 `Assets/Textures/flare0.dds`는 직접 링크하지 않고 권리 확보를 주장하지 않는다.
- `Ex1503_SphWater`는 10초 지연 capture에서 아래에 쌓인 SPH particle cluster를 tracked capture로 승격했다. Movement 설명은 desktop video 후속 후보로 분리한다.

## Chapter15 Demo body 후보

- `Ex1501_ParticleSystem`은 CPU particle pool update, gravity/collision과 structured buffer sprite draw를 설명하는 상세 Demo로 연결했다.
- `Ex1502_SpriteFireEffect`는 buoyancy update, sprite texture binding과 tracked rendered evidence를 설명하는 상세 Demo로 연결했다.
- `Ex1503_SphWater`는 dual source spawn, SPH density/pressure/viscosity force, boundary collision과 10초 지연 selected capture를 설명하는 상세 Demo로 연결했다.
- Chapter15 Demo Issue #31은 `Ex1501`, `Ex1502`와 `Ex1503` screenshot 3개를 대표 visual로 사용한다. `Ex1502`는 원본 `flare0.dds`를 직접 링크하지 않고 rendered evidence로만 다룬다.

## Chapter15 원격 게시 결과

- Branch `docs/part4-chapter14-20-workflow`는 `388d2b0c950d3d978179431b1006d8406ef391f4`까지 push했다.
- Chapter15 Demo Issue는 [Issue #31](https://github.com/Razria93/Graphics_Study_Archive/issues/31)에 게시했다.
- Progress 누적 진행 댓글 [5091068690](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)은 Phase 5-2 내용을 포함하도록 갱신했다.
- Phase 5-2 완료 댓글은 [댓글 5200004532](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5200004532)에 게시했다.
- Draft PR은 [PR #32](https://github.com/Razria93/Graphics_Study_Archive/pull/32)에 생성했다.

## Chapter16 Debug x64 smoke

- 2026-08-07 `Examples.sln` Debug x64 build를 경고 0개, 오류 0개로 확인했다.
- `Examples.exe 1601`부터 `1606`까지는 source root working directory, `HLAB_CAPTURE_UI=collapsed`, `CenterWindow` 조건에서 실행과 local capture를 완료했다.
- build가 ignored Debug output의 runtime DLL을 정리하므로 vcpkg Debug DLL 23개를 복구한 뒤 실행했다.
- `Ex1601_StableFluids`는 source injection 전 초기 frame이 검정이므로 interaction capture를 후속 후보로 둔다.
- `Ex1602_CurlNoise`, `Ex1603_Cloud`, `Ex1606_HybridWater`는 local visual 후보를 확인했다.
- `Ex1604_RealtimeSmoke`, `Ex1605_SmokeCpu`는 HDRI runtime asset을 포함하므로 public 판단 전 local-only 후보로 유지한다.
- local capture 후보는 `local/capture-run/Part4_Chapter16/debug-smoke-20260807`에 둔다. `Docs/_assets` 승격, 상세 Demo, GitHub body와 remote 변경은 수행하지 않는다.

## Chapter17부터 Chapter20까지 Debug x64 smoke

- `Examples.exe 1701`, `1801`, `1802`, `1803`, `1901`, `2001`은 source root working directory, `HLAB_CAPTURE_UI=collapsed`, `CenterWindow` 조건에서 실행과 local capture를 완료했다.
- `Ex1701_SkeletalAnimation`은 skeletal animation scene, `Ex1801_Tree`는 tree scene, `Ex1901_PhysX`는 block simulation, `Ex2001_GamePlay`는 gameplay scene의 local visual 후보를 확인했다.
- `Ex1802_Grass`는 강한 녹색 grass material 표현, `Ex1803_Landscape`는 과노출된 landscape/ocean 표현이므로 품질 검토 전 local-only 후보로 유지한다.
- local capture 후보는 `local/capture-run/Part4_Chapter17/debug-smoke-20260807`, `local/capture-run/Part4_Chapter18/debug-smoke-20260807`, `local/capture-run/Part4_Chapter19/debug-smoke-20260807`, `local/capture-run/Part4_Chapter20/debug-smoke-20260807`에 둔다. `Docs/_assets` 승격, 상세 Demo, GitHub body와 remote 변경은 수행하지 않는다.

## Chapter16부터 Chapter20까지 Release x64와 GraphicsVideo storyboard snapshot

- 2026-08-07 `Examples.sln` Release x64 build는 경고 4개, 오류 0개를 기록했다. warning은 Chapter14 `Ex1402_BlurXGroupCacheCS.hlsl`의 signed/unsigned mismatch 2개와 FXC performance/internal warning 2개다.
- `Examples.exe 1601`부터 `1606`, `1701`, `1801`부터 `1803`, `1901`, `2001`은 source root working directory, `HLAB_CAPTURE_UI=collapsed`, `CenterWindow` 조건에서 Release x64 실행과 local capture를 완료했다.
- build가 ignored output의 runtime DLL을 정리하므로 vcpkg Release DLL 23개를 `x64/Release`에 복구한 뒤 실행했다.
- `local/GraphicsVideo`의 MP4는 local 원본으로 유지한다. `Ex1601`부터 `Ex1606`까지, `Ex1701`, `Ex1801`부터 `Ex1803`까지, `Ex1901`, `Ex2001`의 start, middle, end timestamp preview는 `local/storyboard-candidates/Part4_Chapter16-20/20260807`에 생성했다.
- 선택한 12개 timestamp storyboard PNG는 `Docs/_assets/captures`에 tracked evidence로 승격했다. 이 항목은 2026-08-07 선별 snapshot이며 최신 12개 storyboard 승격 상태와 상세 Demo 연결은 [Demo Index](../../03_Demos/Part4_Chapter14-20/demo-index.md)와 [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)에서 확인한다. HDRI, foliage, terrain, character asset은 rendered evidence만 사용하고 원본 asset은 직접 게시하지 않는다.

## 정본 연결

| 책임 | 정본 |
| --- | --- |
| Chapter와 실행 구조 | [Part4 Chapter14-20 README](../../../Part4_Chapter14-20/README.md) |
| build/run/capture 사실 | [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md) |
| Demo 후보와 capture/result 상태 | [Demo Index](../../03_Demos/Part4_Chapter14-20/demo-index.md) |
| compute/simulation Topic 후보 | [Compute And Simulation Topic Index](../../01_Topics/ComputeAndSimulation/topic-index.md) |
| public 후보와 risk 검토 | [Publication Candidate List](../../05_Publication/candidate-list.md) |
| source provenance | [Source Registry](../../99_Legacy/source-registry.md) |

## 다음 작업

1. Chapter16부터 Chapter20까지 Demo Issue, Progress comment와 PR body 후보를 작성하기 전 공개 위험과 대표 visual 범위를 전수 검토한다.
2. GitHub body 후보를 `Docs/07_GitHub`에 작성하고 validator를 실행한 뒤 remote 게시 승인안을 준비한다.
3. Chapter14부터 Chapter15까지 Release x64 재검증 범위, Chapter14 `Ex1401_Basic` tracked capture 승격 여부와 Chapter15 desktop video 후보는 후속 범위로 둔다.

## Chapter 완료 후 전수 정비 TODO

1. Demo Issue를 catalogue로 유지하고, 완료된 Chapter의 Issue body에 published evidence 상태를 일괄 표기한다.
2. Progress Issue #7 본문을 최종 진행 상태로 정합화하고, 누락된 Phase comment는 인근 comment에 번호 순서대로 보강한다.
3. Markdown single tilde 범위 표기를 `부터`와 `까지` 형식으로 전수 교정하고 render validator를 통과시킨다.
4. 학습용 코드 comment를 전수 정리한다. 유지할 기술 comment는 API 제약, invariant, resource lifetime, workaround 또는 성능 근거만 남기고 간결한 English로 변환한다.
5. portfolio/publication 후보를 최종 검토한다.