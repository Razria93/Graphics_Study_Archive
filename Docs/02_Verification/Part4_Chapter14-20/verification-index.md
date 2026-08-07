# Part4_Chapter14-20 Verification Index

이 문서는 `Part4_Chapter14-20`의 build/run/capture 상태를 기록한다.

## Provenance

- 확인 근거: 과거 확인
- 확인 시점: 문서화 이전(날짜 미기록)
- 현재 재검증: 필요
- 근거: Chapter README에 기록된 Ex1401부터 Ex2001까지 Debug/Release build/run 성공

| 예제                           | Command argument | Solution                          | Debug build | Debug run | Release build | Release run | Capture    | 비고                                                                                                                                                      |
| ---------------------------- | ---------------- | --------------------------------- | ----------- | --------- | ------------- | ----------- | ---------- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Ex1401_Basic`               | `1401`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | local 후보   | 2026-08-06 Debug x64 build/run과 checker screenshot 후보 확인. Release는 과거 확인                                                                                |
| `Ex1402_Blur`                | `1402`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-06 Debug x64 build/run과 5000ms 안정화 screenshot 후보를 `Docs/_assets/captures`에 승격([VI-006](../known-issues.md)). Release는 과거 확인                     |
| `Ex1403_MatVecMult`          | `1403`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | 불필요        | 2026-08-06 Debug x64 stdout과 exit code 0 확인. Release는 과거 확인                                                                                             |
| `Ex1404_StructuredBuffer`    | `1404`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-06 Debug x64 point cloud screenshot 후보를 `Docs/_assets/captures`에 승격. Release는 과거 확인                                                             |
| `Ex1405_ConsumeAppendBuffer` | `1405`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-06 Debug x64 point cloud screenshot 후보를 `Docs/_assets/captures`에 승격하고 `AppendBuffer count: 25600` stdout 확인. Release는 과거 확인                     |
| `Ex1406_DensityField`        | `1406`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-06 Debug x64 density trail screenshot 후보를 `Docs/_assets/captures`에 승격. Release는 과거 확인                                                           |
| `Ex1407_IndirectArguments`   | `1407`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-06 Debug x64 density trail screenshot 후보를 `Docs/_assets/captures`에 승격하고 `DrawInstancedIndirect` code evidence 확인. Release는 과거 확인                |
| `Ex1408_BitonicSort`         | `1408`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | 불필요        | 2026-08-06 Debug x64 element count별 CPU/GPU sort `OK`와 exit code 0 확인. Release는 과거 확인                                                                   |
| `Ex1501_ParticleSystem`      | `1501`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | Debug x64 시연 video의 1.163s, 3.878s, 6.593s frame storyboard를 `Docs/_assets/captures`에 승격. Release는 과거 확인                                                |
| `Ex1502_SpriteFireEffect`    | `1502`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | Debug x64 시연 video의 1.695s, 5.650s, 9.605s frame storyboard를 `Docs/_assets/captures`에 승격. 원본 `flare0.dds`는 직접 링크하지 않음. Release는 과거 확인                   |
| `Ex1503_SphWater`            | `1503`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | Debug x64 시연 video의 2.200s, 4.600s, 12.467s frame storyboard를 `Docs/_assets/captures`에 승격. Release는 과거 확인                                               |
| `Ex1601_StableFluids`        | `1601`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 5.200s, 13.000s, 22.100s interaction storyboard를 `Docs/_assets/captures`에 승격함                 |
| `Ex1602_CurlNoise`           | `1602`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 0.765s, 1.500s, 4.335s colored curl-noise density trail storyboard를 `Docs/_assets/captures`에 승격함 |
| `Ex1603_Cloud`               | `1603`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 0.870s, 2.900s, 4.930s volumetric cloud storyboard를 `Docs/_assets/captures`에 승격함 |
| `Ex1604_RealtimeSmoke`       | `1604`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 4.025s, 13.417s, 22.808s HDRI rendered storyboard를 승격하고 원본 HDRI는 직접 게시하지 않음                   |
| `Ex1605_SmokeCpu`            | `1605`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 1.350s, 4.500s, 7.650s CPU smoke storyboard를 `Docs/_assets/captures`에 승격하고 HDRI 원본은 직접 게시하지 않음 |
| `Ex1606_HybridWater`         | `1606`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 1.885s, 6.283s, 10.682s `RenderDensity` storyboard를 승격함                                       |
| `Ex1701_SkeletalAnimation`   | `1701`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 0.800s, 2.500s, 4.300s skeletal pose storyboard를 승격하고 원본 character asset은 직접 게시하지 않음          |
| `Ex1801_Tree`                | `1801`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 1.140s, 3.800s, 6.460s tree scene storyboard를 `Docs/_assets/captures`에 승격하고 foliage 원본 asset은 직접 게시하지 않음 |
| `Ex1802_Grass`               | `1802`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 1.190s, 3.967s, 6.743s wind phase storyboard를 승격함                                             |
| `Ex1803_Landscape`           | `1803`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 1.140s, 3.800s, 6.460s terrain/ocean storyboard를 승격함                                          |
| `Ex1901_PhysX`               | `1901`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 1.415s, 4.717s, 8.018s block collapse storyboard를 승격함                                         |
| `Ex2001_GamePlay`            | `2001`           | `Part4_Chapter14-20/Examples.sln` | 성공          | 성공        | 성공            | 성공          | tracked 후보 | 2026-08-07 Debug와 Release x64 build/run/capture smoke 성공. 4.260s, 14.200s, 24.140s gameplay destruction storyboard를 승격하고 원본 character asset은 직접 게시하지 않음 |

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
| `Ex1408_BitonicSort` | Debug x64 | `1408` | 성공 | stdout log | element count `1024`부터 `1048576`까지 CPU/GPU sort compare `OK`, `ExitCode: 0` 확인. screenshot 불필요 |

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

## Chapter15 파일럿 결과

| Example | Configuration | Command argument | 결과 | Evidence | 비고 |
| --- | --- | --- | --- | --- | --- |
| `Ex1501_ParticleSystem` | Debug x64 | `1501` | 성공 | [tracked storyboard](../../_assets/captures/part4_chapter15_01_particle_system.png) | 1.163s, 3.878s, 6.593s frame과 `ComputerGraphics` title 확인 |
| `Ex1502_SpriteFireEffect` | Debug x64 | `1502` | 성공 | [tracked storyboard](../../_assets/captures/part4_chapter15_02_sprite_fire_effect.png) | 1.695s, 5.650s, 9.605s frame과 `ComputerGraphics` title 확인. 원본 `Assets/Textures/flare0.dds`는 직접 링크하지 않고 rendered evidence만 사용 |
| `Ex1503_SphWater` | Debug x64 | `1503` | 성공 | [tracked storyboard](../../_assets/captures/part4_chapter15_03_sph_water.png) | 2.200s, 4.600s, 12.467s frame과 `ComputerGraphics` title 확인 |

Debug x64 build는 2026-08-06 `Examples.sln` 기준 경고 0개, 오류 0개로 확인했다. `capture-example-window.ps1`에 `ArgumentList` option을 추가해 `Examples.exe 1501`, `1502`, `1503` 단일 executable command argument 구조를 직접 실행했다. 기존 capture smoke는 run 확인 근거로 유지하고, tracked evidence는 `ComputerGraphics` title이 보이는 시연 video timestamp storyboard로 교체한다. `Ex1501`, `Ex1502`, `Ex1503` storyboard는 text metadata chunk가 없으며 01부터 03까지 timestamp frame을 기록한다. `Ex1502`는 원본 `flare0.dds`를 직접 링크하지 않고 rendered evidence만 사용한다. Capture/run 종료 후 `Examples` process와 error dialog가 남지 않았다.

## Chapter15 evidence 승격 후보 감사

| Example | Local 후보 | 감사 결과 | 승격 판단 | 후속 조치 |
| --- | --- | --- | --- | --- |
| `Ex1501_ParticleSystem` | video timestamp storyboard | 1.163s, 3.878s, 6.593s frame과 `ComputerGraphics` title 확인. PNG text metadata chunk 없음 | tracked 승격 | [tracked storyboard](../../_assets/captures/part4_chapter15_01_particle_system.png)을 Chapter15 particle baseline으로 사용 |
| `Ex1502_SpriteFireEffect` | video timestamp storyboard | 1.695s, 5.650s, 9.605s frame과 `ComputerGraphics` title 확인. PNG text metadata chunk 없음. `flare0.dds` runtime asset을 사용함 | tracked 승격 | [tracked storyboard](../../_assets/captures/part4_chapter15_02_sprite_fire_effect.png)을 rendered evidence로 사용하고 원본 `flare0.dds`는 직접 링크하지 않음 |
| `Ex1503_SphWater` | video timestamp storyboard | 2.200s, 4.600s, 12.467s frame과 `ComputerGraphics` title 확인. PNG text metadata chunk 없음 | tracked 승격 | [tracked storyboard](../../_assets/captures/part4_chapter15_03_sph_water.png)을 사용하고 video attachment URL은 미게시 |

## Chapter16 Debug x64 smoke

`Examples.sln`은 2026-08-07 Debug x64 build에서 경고 0개, 오류 0개를 기록한다. `Examples.exe`는 source root `Part4_Chapter14-20`을 working directory로 사용하고 `HLAB_CAPTURE_UI=collapsed`, `CenterWindow` 조건에서 command argument `1601`부터 `1606`까지를 실행했다. build 후 ignored Debug output에서 runtime DLL이 정리되므로 vcpkg `x64-windows/debug/bin` DLL을 복구한 뒤 smoke를 수행했다.

| Example | 결과 | Local evidence | 판단 | 후속 조치 |
| --- | --- | --- | --- | --- |
| `Ex1601_StableFluids` | 성공 | 초기 frame capture | run smoke | source injection 전 화면이 검정이므로 interaction capture를 별도 후보로 둠 |
| `Ex1602_CurlNoise` | 성공 | colored density trail capture | local visual 후보 | 안정화 대기와 desktop video 필요성을 후속 검토 |
| `Ex1603_Cloud` | 성공 | volumetric cloud capture | local visual 후보 | animation과 lighting 조정은 후속 검토 |
| `Ex1604_RealtimeSmoke` | 성공 | HDRI background와 smoke capture | local-only 후보 | runtime HDRI asset의 공개 위험을 별도 판단 |
| `Ex1605_SmokeCpu` | 성공 | HDRI background와 CPU smoke capture | local-only 후보 | runtime HDRI asset의 공개 위험을 별도 판단 |
| `Ex1606_HybridWater` | 성공 | hybrid particle/grid surface capture | local visual 후보 | state 안정화와 motion evidence를 후속 검토 |

## Chapter17부터 Chapter20까지 Debug x64 smoke

`Examples.sln` Debug x64 build는 2026-08-07 경고 0개, 오류 0개로 확인했다. `Examples.exe`는 source root `Part4_Chapter14-20`을 working directory로 사용하고 `HLAB_CAPTURE_UI=collapsed`, `CenterWindow` 조건에서 Chapter17부터 Chapter20까지 command argument를 실행했다. build 후 vcpkg `x64-windows/debug/bin` DLL을 복구하는 runtime precondition은 Chapter16과 동일하게 적용한다.

| Chapter | Example | 결과 | Local evidence | 판단 | 후속 조치 |
| --- | --- | --- | --- | --- | --- |
| Chapter17 | `Ex1701_SkeletalAnimation` | 성공 | skeletal animation capture | local visual 후보 | animation state를 포함한 evidence 방향을 별도 검토 |
| Chapter18 | `Ex1801_Tree` | 성공 | tree scene capture | local visual 후보 | foliage asset과 framing을 별도 검토 |
| Chapter18 | `Ex1802_Grass` | 성공 | grass field capture | local-only 후보 | 강한 grass material 표현의 품질 검토 후 승격 여부 판단 |
| Chapter18 | `Ex1803_Landscape` | 성공 | landscape/ocean capture | local-only 후보 | 과노출된 landscape/ocean 표현의 품질 검토 후 승격 여부 판단 |
| Chapter19 | `Ex1901_PhysX` | 성공 | block simulation capture | local visual 후보 | physics motion evidence를 별도 검토 |
| Chapter20 | `Ex2001_GamePlay` | 성공 | gameplay scene capture | local visual 후보 | gameplay state와 framing을 별도 검토 |

## Chapter16부터 Chapter20까지 Release x64 smoke와 storyboard

`Examples.sln`은 2026-08-07 Release x64 build에서 경고 4개, 오류 0개를 기록한다. warning은 `Ex1402_BlurXGroupCacheCS.hlsl`의 signed/unsigned mismatch 2개와 FXC performance/internal warning 2개이며 Chapter16부터 Chapter20까지 source 오류는 아니다. vcpkg `x64-windows/bin` DLL 23개를 `x64/Release`에 복구한 뒤 source root working directory, `HLAB_CAPTURE_UI=collapsed`, `CenterWindow` 조건에서 command argument `1601`부터 `1606`, `1701`, `1801`부터 `1803`, `1901`, `2001`을 실행하고 local capture 12개를 확인했다.

`local/GraphicsVideo` 원본 MP4는 Git에 추가하지 않는다. Chapter16부터 Chapter20까지 모든 Example의 start, middle, end preview를 `local/storyboard-candidates/Part4_Chapter16-20/20260807`에 생성했고, 검수한 final timestamp storyboard PNG 12개를 `Docs/_assets/captures`에 승격했다.

| Example | Timestamp 후보 | Storyboard 설명 | Asset 주의 |
| --- | --- | --- | --- |
| `Ex1601_StableFluids` | 5.200s, 13.000s, 22.100s | source injection 뒤 색 density field 변화 | [tracked storyboard](../../_assets/captures/part4_chapter16_01_stable_fluids.png) |
| `Ex1602_CurlNoise` | 0.765s, 1.500s, 4.335s | colored curl-noise density trail 변화 | [tracked storyboard](../../_assets/captures/part4_chapter16_02_curl_noise.png) |
| `Ex1603_Cloud` | 0.870s, 2.900s, 4.930s | procedural cloud volume 변화 | [tracked storyboard](../../_assets/captures/part4_chapter16_03_cloud.png) |
| `Ex1604_RealtimeSmoke` | 4.025s, 13.417s, 22.808s | HDRI 배경의 source, 확산, buoyancy 변화 | [tracked storyboard](../../_assets/captures/part4_chapter16_04_realtime_smoke.png). rendered evidence만 사용하고 원본 HDRI는 직접 게시하지 않음 |
| `Ex1605_SmokeCpu` | 1.350s, 4.500s, 7.650s | CPU density upload와 volume smoke 변화 | [tracked storyboard](../../_assets/captures/part4_chapter16_05_smoke_cpu.png). rendered evidence만 사용하고 원본 HDRI는 직접 게시하지 않음 |
| `Ex1606_HybridWater` | 1.885s, 6.283s, 10.682s | raycasting surface와 `RenderDensity` volume 표시 비교 | [tracked storyboard](../../_assets/captures/part4_chapter16_06_hybrid_water.png). density field 시각화이며 물성 mode 전환으로 설명하지 않음 |
| `Ex1701_SkeletalAnimation` | 0.800s, 2.500s, 4.300s | animation pose 변화 | [tracked storyboard](../../_assets/captures/part4_chapter17_01_skeletal_animation.png). 원본 character asset은 직접 게시하지 않음 |
| `Ex1801_Tree` | 1.140s, 3.800s, 6.460s | trunk/branch와 leaves mesh group tree scene | [tracked storyboard](../../_assets/captures/part4_chapter18_01_tree.png). 원본 foliage asset은 직접 게시하지 않음 |
| `Ex1802_Grass` | 1.190s, 3.967s, 6.743s | wind phase에 따른 instanced grass field 변화 | [tracked storyboard](../../_assets/captures/part4_chapter18_02_grass.png). rendered evidence만 사용 |
| `Ex1803_Landscape` | 1.140s, 3.800s, 6.460s | terrain과 animated ocean surface | [tracked storyboard](../../_assets/captures/part4_chapter18_03_landscape.png). rendered evidence만 사용 |
| `Ex1901_PhysX` | 1.415s, 4.717s, 8.018s | block wall collapse 단계 | [tracked storyboard](../../_assets/captures/part4_chapter19_01_physx.png) |
| `Ex2001_GamePlay` | 4.260s, 14.200s, 24.140s | gameplay destruction 진행 | [tracked storyboard](../../_assets/captures/part4_chapter20_01_gameplay.png). 원본 character asset은 직접 게시하지 않음 |

## 갱신 기준

- `Examples.sln`의 startup project와 실행 argument를 확인한다.
- 실제 sample 단위 재검증을 수행하면 확인 시점과 근거를 행별로 갱신한다.
- 실패 또는 부분 성공 항목은 `../known-issues.md`에 연결한다.
