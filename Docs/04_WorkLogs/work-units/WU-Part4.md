# WU-Part4

## 범위

- `Part4_Chapter14-20`

## 현재 상태

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| Source/import | 반영 완료 | `SRC-P4-C14-20`으로 source provenance를 추적한다. |
| Branch | 진행 중 | `docs/part4-chapter14-20-workflow`에서 baseline 문서 축 정규화를 시작한다. |
| Build/run | 파일럿 검증 중 | Ex1401~Ex1403 Debug x64 build/run을 2026-08-06 현재 확인했다. Ex1404~Ex2001과 Release 현재 재검증은 남아 있다. |
| Capture | local 후보 | Ex1401~Ex1402 local screenshot 후보와 Ex1403 stdout log 후보를 생성했다. tracked capture 승격은 하지 않았다. |
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
- Debug build 후 ignored output의 runtime DLL이 정리되어 loader error가 발생했으며, vcpkg Debug runtime DLL을 `x64/Debug`에 복구한 뒤 run/capture를 진행했다.
- 생성 후보는 `local/capture-run/Part4_Chapter14/pilot-1401-1403-rerun-20260806`에 둔다. 이 local 후보는 tracked asset이 아니다.

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

1. Chapter14 `Ex1404`~`Ex1408` 재검증을 같은 단일 실행 규칙으로 확장한다.
2. visual capture 후보는 예제별 안정화 대기 시간을 기록하고, tracked 승격 전 metadata와 visual을 재검수한다.
3. console 중심 예제는 stdout과 exit code를 evidence로 기록하고, visual 중심 예제만 capture 후보로 둔다.