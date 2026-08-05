# Part4_Chapter14-20 Verification Index

이 문서는 `Part4_Chapter14-20`의 build/run/capture 상태를 기록한다.

## Provenance

- 확인 근거: 과거 확인
- 확인 시점: 문서화 이전(날짜 미기록)
- 현재 재검증: 필요
- 근거: Chapter README에 기록된 Ex1401~Ex2001 Debug/Release build/run 성공

| 예제 | Command argument | Solution | Debug build | Debug run | Release build | Release run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `Ex1401_Basic` | `1401` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | local 후보 | 2026-08-06 Debug x64 build/run과 checker screenshot 후보 확인. Release는 과거 확인 |
| `Ex1402_Blur` | `1402` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | tracked 후보 | 2026-08-06 Debug x64 build/run과 5000ms 안정화 screenshot 후보를 `Docs/_assets/captures`에 승격([VI-006](../known-issues.md)). Release는 과거 확인 |
| `Ex1403_MatVecMult` | `1403` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 불필요 | 2026-08-06 Debug x64 stdout과 exit code 0 확인. Release는 과거 확인 |
| `Ex1404_StructuredBuffer` | `1404` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | tracked 후보 | 2026-08-06 Debug x64 point cloud screenshot 후보를 `Docs/_assets/captures`에 승격. Release는 과거 확인 |
| `Ex1405_ConsumeAppendBuffer` | `1405` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | tracked 후보 | 2026-08-06 Debug x64 point cloud screenshot 후보를 `Docs/_assets/captures`에 승격하고 `AppendBuffer count: 25600` stdout 확인. Release는 과거 확인 |
| `Ex1406_DensityField` | `1406` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | tracked 후보 | 2026-08-06 Debug x64 density trail screenshot 후보를 `Docs/_assets/captures`에 승격. Release는 과거 확인 |
| `Ex1407_IndirectArguments` | `1407` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | tracked 후보 | 2026-08-06 Debug x64 density trail screenshot 후보를 `Docs/_assets/captures`에 승격하고 `DrawInstancedIndirect` code evidence 확인. Release는 과거 확인 |
| `Ex1408_BitonicSort` | `1408` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 불필요 | 2026-08-06 Debug x64 element count별 CPU/GPU sort `OK`와 exit code 0 확인. Release는 과거 확인 |
| `Ex1501_ParticleSystem` | `1501` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1502_SpriteFireEffect` | `1502` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1503_SphWater` | `1503` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1601_StableFluids` | `1601` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1602_CurlNoise` | `1602` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1603_Cloud` | `1603` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1604_RealtimeSmoke` | `1604` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1605_SmokeCpu` | `1605` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1606_HybridWater` | `1606` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1701_SkeletalAnimation` | `1701` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1801_Tree` | `1801` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1802_Grass` | `1802` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1803_Landscape` | `1803` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex1901_PhysX` | `1901` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |
| `Ex2001_GamePlay` | `2001` | `Part4_Chapter14-20/Examples.sln` | 성공 | 성공 | 성공 | 성공 | 미확인 | 과거 확인 · 현재 재검증 필요 |

## 실행 선택 방식

- `Part4_Chapter14-20`은 `Examples` 단일 executable에서 command-line argument로 예제를 선택한다.
- 인자가 없으면 `main.cpp`가 `Please specify the example number`를 출력하고 종료한다.
- 알 수 없는 argument는 `not a valid example number`를 출력하고 종료한다.
- 실제 재검증 시 working directory, Debugging command arguments와 runtime asset dependency를 예제별로 함께 확인한다.

## Chapter14 재검증 계획

| Example | 현재 확인할 증거 | Capture 필요성 | 확인 포인트 |
| --- | --- | --- | --- |
| `Ex1401_Basic` | screenshot | 필요 | checker pattern, `Scale` GUI, back buffer UAV 출력 |
| `Ex1402_Blur` | screenshot | 필요 | 고강도 RGB 점이 1000회 blur pass 뒤 넓게 퍼지는지 확인 |
| `Ex1403_MatVecMult` | console output | 불필요 | `Result CPU`, `GPU Result`, `Error GPU 0`, exit code 0 |
| `Ex1404_StructuredBuffer` | screenshot | 필요 | vertex buffer 없이 point cloud가 출력되고 particle이 움직이는지 확인 |
| `Ex1405_ConsumeAppendBuffer` | screenshot + console output | 후보 | point cloud와 `AppendBuffer count` 출력 확인 |
| `Ex1406_DensityField` | screenshot | 필요 | colored sprite/density trail 누적과 감쇠 확인 |
| `Ex1407_IndirectArguments` | screenshot | 후보 | Ex1406 계열 density visual과 indirect argument buffer offset 0 draw 확인 |
| `Ex1408_BitonicSort` | console output | 불필요 | element count별 CPU/GPU sort compare가 `OK`인지 확인 |

## Chapter14 파일럿 결과

| Example | Configuration | Command argument | 결과 | Evidence | 비고 |
| --- | --- | --- | --- | --- | --- |
| `Ex1401_Basic` | Debug x64 | `1401` | 성공 | local screenshot 후보 | checker pattern과 `HongLabGraphics Example` window 확인. tracked capture로 승격하지 않음 |
| `Ex1402_Blur` | Debug x64 | `1402` | 성공 | [tracked screenshot](../../_assets/captures/part4_chapter14_02_blur.png) | 초기 capture는 white frame에 가까웠으나 5000ms 안정화 대기, centered client-visible fixed UI capture에서 RGB blur visual 확인 |
| `Ex1403_MatVecMult` | Debug x64 | `1403` | 성공 | stdout log | `Result CPU`, `GPU Result`, `Error GPU 0`, `ExitCode: 0` 확인. screenshot 불필요 |
| `Ex1404_StructuredBuffer` | Debug x64 | `1404` | 성공 | [tracked screenshot](../../_assets/captures/part4_chapter14_04_structured_buffer.png) | `RWStructuredBuffer` particle point cloud 확인. centered client-visible fixed UI capture를 승격 |
| `Ex1405_ConsumeAppendBuffer` | Debug x64 | `1405` | 성공 | [tracked screenshot](../../_assets/captures/part4_chapter14_05_consume_append_buffer.png) + stdout log | point cloud와 `AppendBuffer count: 25600` 확인. centered client-visible fixed UI capture를 승격 |
| `Ex1406_DensityField` | Debug x64 | `1406` | 성공 | [tracked screenshot](../../_assets/captures/part4_chapter14_06_density_field.png) | colored density trail 확인. centered client-visible fixed UI capture를 승격. 시간 변화는 video 후보 |
| `Ex1407_IndirectArguments` | Debug x64 | `1407` | 성공 | [tracked screenshot](../../_assets/captures/part4_chapter14_07_indirect_arguments.png) + code evidence | density trail visual과 `DrawInstancedIndirect(m_argsGPU.Get(), offset)` 확인. screenshot만으로 indirect draw 차이는 설명 부족 |
| `Ex1408_BitonicSort` | Debug x64 | `1408` | 성공 | stdout log | element count `1024`~`1048576` CPU/GPU sort compare `OK`, `ExitCode: 0` 확인. screenshot 불필요 |

Debug x64 build는 2026-08-06 `Examples.sln` 기준 경고 0개, 오류 0개로 확인했다. Git Bash 실행 환경에서는 build 후 Debug output의 runtime DLL이 정리되어 `PhysXCommon_64.dll` loader error가 발생했으며([VI-005](../known-issues.md)), vcpkg `x64-windows/debug/bin` runtime DLL을 ignored `x64/Debug` output에 복구한 뒤 파일럿 run을 수행했다. `Ex1402_Blur`는 500ms, 1500ms, 3000ms capture에서 white frame에 가까웠고 5000ms capture에서 RGB blur visual이 확인되어 timing/안정화 대기 이슈로 판정한다.

노트북 환경에서는 Part4 visual 후보 일부에 taskbar 또는 ImGui control panel이 크게 포함된다([VI-007](../known-issues.md)). 2026-08-06 `AppBase`에 capture UI mode를 추가해 `HLAB_CAPTURE_UI=collapsed` 실행에서 공통 `Scene Control` titlebar를 좌측 상단 margin에 고정하고 접힌 상태로 유지하는 기준을 확인했다. visible client area capture probe는 taskbar를 제외한다. 큰 모니터 연결 후 `CenterWindow` 기준으로 `Ex1402_Blur`는 1280×768, `Ex1404_StructuredBuffer`와 `Ex1405_ConsumeAppendBuffer`는 1280×1280, `Ex1406_DensityField`는 1024×1024, `Ex1407_IndirectArguments`는 640×640 전체 client 후보를 확인했다. 해당 후보는 `Docs/_assets/captures`에 승격했다. `file` 확인 결과 PNG RGBA non-interlaced이며, PNG text metadata chunk는 없다. 이 기준은 ImGui `imgui.ini`의 저장 위치를 덮지 않는다. video 승격은 desktop 환경에서 별도 검수한다.

## Chapter14 evidence 후보 선별

| Example | Evidence 방향 | 현재 후보 | 승격 판단 | 후속 조치 |
| --- | --- | --- | --- | --- |
| `Ex1401_Basic` | 최소 compute visual | checker screenshot | desktop 재촬영 후보 | `HLAB_CAPTURE_UI=collapsed`와 안정된 bounds로 재촬영 후 tracked 여부 판단 |
| `Ex1402_Blur` | 대표 blur visual | [tracked screenshot](../../_assets/captures/part4_chapter14_02_blur.png) | tracked 후보 | 5000ms 안정화 대기와 centered client-visible fixed UI 기준으로 1280×768 전체 client 확인 |
| `Ex1403_MatVecMult` | console result compare | stdout log | stdout-only 후보 | screenshot 없이 log 요약과 exit code를 evidence로 사용 |
| `Ex1404_StructuredBuffer` | structured buffer visual | [tracked screenshot](../../_assets/captures/part4_chapter14_04_structured_buffer.png) | tracked 후보 | 큰 모니터에서 taskbar-free 1280×1280 전체 client 확인 |
| `Ex1405_ConsumeAppendBuffer` | append counter result | [tracked screenshot](../../_assets/captures/part4_chapter14_05_consume_append_buffer.png) + stdout log | tracked 후보 | 큰 모니터에서 taskbar-free 1280×1280 전체 client 확인. `AppendBuffer count: 25600`을 핵심 evidence로 함께 사용 |
| `Ex1406_DensityField` | 대표 density visual | [tracked screenshot](../../_assets/captures/part4_chapter14_06_density_field.png) | tracked 후보 | 큰 모니터에서 taskbar-free 1024×1024 전체 client 확인. 시간 변화는 desktop video 후보 |
| `Ex1407_IndirectArguments` | indirect draw evidence | [tracked screenshot](../../_assets/captures/part4_chapter14_07_indirect_arguments.png) + code evidence | tracked 후보 | 큰 모니터에서 taskbar-free 640×640 전체 client 확인. visual은 Ex1406과 유사하므로 `DrawInstancedIndirect` code evidence를 함께 사용 |
| `Ex1408_BitonicSort` | console sort compare | stdout log | stdout-only 후보 | screenshot 없이 element count별 `OK`와 exit code를 evidence로 사용 |

Chapter14 최소 evidence set은 `Ex1401_Basic`, `Ex1402_Blur`, `Ex1403_MatVecMult`, `Ex1408_BitonicSort`로 둔다. Chapter14 확장 evidence set은 `Ex1404_StructuredBuffer`, `Ex1405_ConsumeAppendBuffer`, `Ex1406_DensityField`, `Ex1407_IndirectArguments`로 둔다. tracked screenshot 승격은 fixed UI, bounds, taskbar, metadata 검수 이후에만 수행한다.

## 갱신 기준

- `Examples.sln`의 startup project와 실행 argument를 확인한다.
- 실제 sample 단위 재검증을 수행하면 확인 시점과 근거를 행별로 갱신한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
