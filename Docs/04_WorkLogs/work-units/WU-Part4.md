# WU-Part4

## 범위

- `Part4_Chapter14-20`

## 현재 상태

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| Source/import | 반영 완료 | `SRC-P4-C14-20`으로 source provenance를 추적한다. |
| Branch | 진행 중 | `docs/part4-chapter14-20-workflow`에서 baseline 문서 축 정규화를 시작한다. |
| Build/run | Chapter14 Debug 확인 | Ex1401~Ex1408 Debug x64 build/run을 2026-08-06 현재 확인했다. Chapter15~20과 Release 현재 재검증은 남아 있다. |
| Capture | local 후보 | Ex1401~Ex1402, Ex1404~Ex1407 local screenshot 후보와 Ex1403, Ex1405, Ex1408 stdout log 후보를 생성했다. tracked capture 승격은 하지 않았다. |
| Demo | 후보 정리 중 | stale 후보를 제거하고 실제 Ex 기반 후보로 재정렬한다. |
| Publication | 검토 필요 | public 후보 확정이 아니라 asset/public risk 검토 축으로만 기록한다. |
| GitHub | 미게시 | Issue, PR, comment remote 게시를 이번 범위에 포함하지 않는다. |

## 시작 결정

- Part4는 예제별 solution이 아니라 `Examples.sln` 단일 project와 command argument 기반 sample 선택 구조로 유지한다.
- 첫 작업은 Chapter14 compute slice나 build/run 재검증이 아니라 baseline 문서 축 정규화로 제한한다.
- 이번 범위에서는 build/run/capture를 수행하지 않고, 과거 확인과 현재 재검증 필요 상태를 분리한다.
- Demo Issue, Progress comment, PR remote 게시는 후속 승인 범위로 둔다.

## Chapter14 문서화 기준

- `Ex1401_Basic`과 `Ex1402_Blur`는 compute shader visual 기준선과 대표 visual 후보로 둔다.
- `Ex1403_MatVecMult`와 `Ex1408_BitonicSort`는 screenshot보다 console CPU/GPU result compare를 핵심 evidence로 둔다.
- `Ex1404_StructuredBuffer`와 `Ex1405_ConsumeAppendBuffer`는 structured buffer update/render와 append counter 흐름을 확인한다.
- `Ex1406_DensityField`와 `Ex1407_IndirectArguments`는 density trail visual을 공유하되, Ex1407은 indirect argument buffer 사용 여부를 code evidence와 함께 설명한다.
- Chapter14 문서화 기준 수립 단계에서는 build/run/capture를 수행하지 않는다.

## Chapter14 파일럿 결과

- 2026-08-06 `Ex1401_Basic`~`Ex1403_MatVecMult`를 command argument `1401`→`1402`→`1403` 순서로 Debug x64 재검증했다.
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
- 2026-08-06 local capture helper의 visible client area probe로 taskbar 제외 capture를 확인했다. 큰 모니터 연결 후 `CenterWindow` 기준으로 `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1406_DensityField`, `Ex1407_IndirectArguments` 모두 taskbar-free 전체 client 후보를 확보했다. 생성 후보는 `local/capture-run/Part4_Chapter14/capture-ui-fixed-large-monitor-20260806`에 둔다.

## Chapter14 evidence 후보 선별

- 최소 evidence set은 `Ex1401_Basic` checker visual, `Ex1402_Blur` RGB blur visual, `Ex1403_MatVecMult` stdout compare, `Ex1408_BitonicSort` stdout compare로 둔다.
- 확장 evidence set은 `Ex1404_StructuredBuffer` fixed UI point cloud, `Ex1405_ConsumeAppendBuffer` fixed UI point cloud와 append count stdout, `Ex1406_DensityField` fixed UI density trail, `Ex1407_IndirectArguments` fixed UI density trail과 indirect draw code evidence로 둔다.
- tracked 승격 우선 screenshot 후보는 `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1406_DensityField`, `Ex1407_IndirectArguments` centered client-visible fixed UI 후보로 둔다. 현재 local 후보는 tracked asset이 아니며, tracked 승격 전 metadata와 public 노출 검수를 별도로 수행한다.
- `Ex1401_Basic`, `Ex1402_Blur`는 최소 set 후보지만 fixed UI와 안정된 bounds 기준의 desktop 재촬영 후 승격 여부를 판단한다.
- `Ex1403_MatVecMult`, `Ex1408_BitonicSort`는 stdout-only 후보로 두며 screenshot을 만들지 않는다.
- `Ex1405_ConsumeAppendBuffer`는 Consume/Append buffer의 counter 흐름과 `AppendBuffer count: 25600`을 핵심 evidence로 두고 fixed UI screenshot을 visual 보조 evidence로 둔다.
- `Ex1407_IndirectArguments`는 visual이 `Ex1406_DensityField`와 유사하므로 fixed UI screenshot과 `DrawInstancedIndirect(m_argsGPU.Get(), offset)` code evidence를 함께 사용한다.
- `Ex1404_StructuredBuffer`와 `Ex1405_ConsumeAppendBuffer`는 point cloud visual이 유사하지만, `Ex1404`는 단일 StructuredBuffer SRV/UAV draw 흐름이고 `Ex1405`는 Consume/Append UAV counter와 append count 기반 draw 흐름이다.
- `Ex1406_DensityField`와 `Ex1407_IndirectArguments`는 density trail visual이 유사하지만, `Ex1406`은 CPU가 particle count를 직접 넘기는 draw 흐름이고 `Ex1407`은 GPU argument buffer를 넘기는 `DrawInstancedIndirect` 흐름이다.

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

1. Chapter14 tracked capture 승격은 `HLAB_CAPTURE_UI=collapsed`, 안정된 bounds, taskbar 노출, metadata를 검수한 뒤 수행한다.
2. Chapter14 GitHub Demo Issue 후보는 최소 evidence set과 확장 evidence set 중 게시 범위를 선택해 작성한다.
3. Chapter15 진입 전 runtime DLL 복구 절차와 desktop video 후보 분리를 유지한다.