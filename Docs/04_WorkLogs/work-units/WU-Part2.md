# WU-Part2 WorkLog

## 범위

| 항목 | 내용 |
| --- | --- |
| Work Unit | `WU-Part2` |
| 현재 마감 대상 | Chapter08 rendered evidence 공개 판단과 Demo Issue 후보 마감 |
| 후속 코드 범위 | Chapter05–08 순차 정규화 완료, 원본 runtime asset은 비공개 유지 |
| 주요 문서 축 | 코드 폴더 README, `01_Topics`, `02_Verification`, `03_Demos`, `05_Publication` |

## Chapter04 마감 snapshot

- Step1 Triangle부터 Step10 Lights까지 순차 Example README와 상세 Demo 정규화를 완료한다.
- Step1A Triangle To Circle은 사용자가 Step1을 확장한 Personal Extension으로 분리한다.
- Debug/Release x64 build/run과 capture 사실은 [Verification](../../02_Verification/Part2_Chapter04/verification-index.md)에 위임한다.
- Chapter 대표·보조·확장·시간 변화 구성은 [Demo Index](../../03_Demos/Part2_Chapter04/demo-index.md)와 [Demo Priority](../../03_Demos/demo-priority.md)에 위임한다.
- Step별 공개 가능성과 게시 선정 판단은 [Publication](../../05_Publication/candidate-list.md)에 위임한다.

## 결정

- Step1 Triangle을 최소 기준선으로 둔다.
- Step8 PerspectiveProjection을 Chapter 대표 Demo로 둔다.
- Step10 Lights를 기술 보조 Demo로 둔다.
- Step1A Triangle To Circle을 사용자 확장 Demo로 둔다.
- Step4 Animation2D를 시간 변화 Demo로 둔다.
- selected video는 조작과 시간 변화를 확인하는 local evidence로 유지하고 일반 Git history에는 추가하지 않는다.

## 정본 연결

| 책임 | 정본 |
| --- | --- |
| Chapter와 Example 흐름 | [Part2 Chapter04 README](../../../Part2_Chapter04/README.md) |
| build/run/capture 사실 | [Verification Index](../../02_Verification/Part2_Chapter04/verification-index.md) |
| 순차·대표 Demo | [Demo Index](../../03_Demos/Part2_Chapter04/demo-index.md) |
| Chapter05–08 흐름 | [Part2 Chapter05–08 README](../../../Part2_Chapter05-08/README.md) |
| Chapter05–08 build/run/capture | [Chapter05–08 Verification](../../02_Verification/Part2_Chapter05-08/verification-index.md) |
| Chapter05–08 순차·대표 Demo | [Chapter05–08 Demo Index](../../03_Demos/Part2_Chapter05-08/demo-index.md) |
| video 필요성과 상태 | [Video Plan](../../03_Demos/video-plan.md) |
| 공개 후보와 미선정 판단 | [Candidate List](../../05_Publication/candidate-list.md) |
| GitHub 게시 상태 | [Work Unit GitHub Index](../work-unit-github-index.md) |

## 게시 snapshot

- [Chapter04 Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14) 게시와 실제 URL 동기화를 완료했다.
- [Chapter04 PR #15](https://github.com/Razria93/Graphics_Study_Archive/pull/15)을 일반 merge commit 방식으로 병합해 실제 URL과 최종 상태 동기화를 완료했다.
- [누적 Progress 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)을 Chapter04 상태로 갱신했다.
- [Phase 3-1 완료 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5150875726) 게시와 실제 URL 동기화를 완료했다.
- Chapter05 [Demo Issue #17](https://github.com/Razria93/Graphics_Study_Archive/issues/17), Chapter06 [Demo Issue #18](https://github.com/Razria93/Graphics_Study_Archive/issues/18), Chapter07 [Demo Issue #19](https://github.com/Razria93/Graphics_Study_Archive/issues/19)를 번호 순서대로 게시했다.
- [Chapter05–08 PR #20](https://github.com/Razria93/Graphics_Study_Archive/pull/20)을 Draft로 게시하고 Ready for Review로 전환한 뒤 일반 merge commit 방식으로 병합했다.
- [누적 Progress 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)을 Phase 3-2 상태로 갱신했다.
- [Phase 3-2 완료 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5160239752) 게시와 실제 URL 동기화를 완료했다.

## Chapter05 마감 snapshot

- Chapter05 Step1 Matrix(GLM)의 Debug/Release x64 현재 재검증과 문서 정규화를 완료했다.
- Step1은 결정적 console 예제로 screenshot과 video를 제외하고 Step2에서 Chapter 최소 visual을 확보했다.
- Chapter05 Step2 Lights(GLM)의 Debug/Release x64 현재 재검증, 기본·non-uniform scale screenshot과 상세 Demo 정규화를 완료했다.
- Step2를 Chapter 최초 graphics Example과 최소 visual로 두고 video는 정지 image 두 장으로 차이를 설명할 수 있어 제외한다.
- Chapter05 Step3 DirectXMath의 Debug/Release x64 현재 재검증과 문서 정규화를 완료했다.
- Step3은 결정적 console 예제로 screenshot과 video를 제외하고 DirectXMath·SimpleMath API 비교를 상세 Demo에 기록한다.
- Chapter05 Step4 Lights(SimpleMath)의 코드 정합성 보완, Debug/Release x64 현재 재검증과 screenshot 승격을 완료했다.
- Chapter05 Step1~4를 GLM matrix 기초·적용에서 DirectXMath/SimpleMath API·graphics 적용으로 이어지는 하나의 affine transformation bundle로 정리한다.
- Step2 GLM과 Step4 SimpleMath는 같은 transform 의도의 대응 visual로 유지하고, Step1·3 console 예제는 설명 중심 단계로 둔다.
- `RowPitch`, `Map()` 실패, runtime shader path와 Step1A project identity는 별도 code task로 둔다.

## Chapter06 마감 snapshot

- Step1 COM의 Debug/Release x64 현재 재검증과 문서 정규화를 완료했다.
- Step1은 D3D11 device·immediate context 생성과 `ComPtr` ownership을 분리해 설명한다.
- Graphics window와 시간 변화가 없는 console 예제이므로 screenshot과 video를 제외한다.
- Step2 InitializingD3D의 Debug/Release x64 현재 재검증과 Example·Topic·상세 Demo 정규화를 완료했다.
- Step2는 device·context에서 swap chain, render target, depth buffer, viewport와 indexed draw까지 연결하는 첫 end-to-end graphics pipeline 단계로 둔다.
- 기본 perspective 전체 창 screenshot의 자동 기술 검수와 사용자 시각 확인을 완료해 tracked capture로 승격했다.
- Orthographic 조정 screenshot과 video는 제외하고 projection parameter 비교를 Step3으로 위임한다.
- Step3 ModelViewProj의 Debug/Release x64 현재 재검증과 Example·Topic·상세 Demo 정규화를 완료했다.
- Step3는 Model·View·Projection parameter와 dynamic constant buffer 갱신을 분리하고 perspective·orthographic 결과를 비교한다.
- Perspective·Orthographic 전체 창 screenshot 2장의 기술 검사와 사용자 시각 확인을 완료해 tracked capture로 승격했다.
- Model Y rotation은 한 방향 연속 drag selected video로 검증하고 Publication 단계 전까지 local evidence로 유지한다.
- Step4 Shaders의 deterministic `xSplitPoint=0.5`, pixel constant-buffer alignment와 application title을 최소 보완했다.
- Step4의 Debug/Release x64 현재 재검증과 Example·Shader Stage Topic·상세 Demo 정규화를 완료했다.
- 기본 `0.5`와 조정 `0.25` 전체 창 screenshot 2장의 기술 검사와 사용자 시각 확인을 완료해 tracked capture로 승격했다.
- Step4 video는 정적 screenshot 비교로 UV 분기 이동을 충분히 설명할 수 있어 제외했다.
- Step5 Texturing의 texture load·GPU resource 실패 전파, 기본 `xSplit=0.5`와 application title을 최소 보완했다.
- 출처 불명 input 2개를 외부 원문 pixel을 복제하지 않은 generated 석재·목재 PNG로 교체하고 metadata·hash를 확인했다.
- Step5의 Debug/Release x64 현재 재검증과 Example·Texture Sampling Topic·상세 Demo 정규화를 완료했다.
- 기본 `0.5`와 조정 `0.25` 전체 창 screenshot 2장의 기술 검사와 사용자 시각 확인을 완료해 tracked capture로 승격했다.
- Step5 video는 정적 screenshot 비교로 texture 선택 경계를 충분히 설명할 수 있어 제외했다.
- Step5A Texturing LightingSelf의 texture load·resource 실패 전파, camera position 동기화와 attenuation denominator 제한을 보완했다.
- Step5에서 검수한 generated 목재 PNG의 동일 바이트 사본을 사용하고 미사용 texture·shader resource를 제거했다.
- Step5A의 Debug/Release x64 현재 재검증과 Example·기존 Topic·상세 Demo 정규화를 완료했다.
- 기본 light와 위치 조정 전체 창 screenshot 2장의 기술 검사와 사용자 시각 확인을 완료해 tracked capture로 승격했다.
- Step5A video는 단일 light position의 정적 결과 비교로 구현 효과를 충분히 설명할 수 있어 제외했다.
- Step6 Lighting의 texture·shader·buffer 실패 전파, deterministic UI, camera position과 attenuation invariant를 보완했다.
- 출처 불명 texture 2개를 제거하고 Step5·Step5A에서 검수한 generated 목재 PNG의 동일 바이트 사본을 사용했다.
- Step6의 Debug/Release x64 현재 재검증과 Example·기존 Topic·상세 Demo 정규화를 완료했다.
- Directional·Point·Spot 전체 창 screenshot 3장의 기술 검사와 사용자 시각 확인을 완료해 tracked capture로 승격했다.
- Spot은 Point와 같은 위치·falloff에서 `spotPower=16`을 사용해 cone 차이를 응축하고, 세 이산 상태가 구현 차이를 충분히 설명하므로 video를 제외했다.
- Step7의 panel 기반 viewport 계산, projection aspect 정렬과 Step6 lighting 유지 경로를 정규화했다.
- 출처 불명 texture 2개와 미사용 두 번째 texture resource를 제거하고 Step5·Step5A·Step6의 generated 목재 PNG와 동일한 사본을 사용했다.
- Step7 Debug/Release x64 현재 재검증과 전체 창 screenshot의 기술 검사·사용자 승인을 완료했다.
- Step7은 정적 screenshot으로 panel과 scene 경계를 설명할 수 있어 video를 제외하고, window resize와 dependent resource 재생성은 Step8 책임으로 유지했다.
- Step8은 정규화된 Step7을 기준으로 `WM_SIZE`, swap chain dependent resource 재생성과 projection 갱신을 추가했다.
- Step8 Debug/Release x64와 반복 resize·minimize/restore를 현재 확인하고, 출처 불명 texture를 제거한 뒤 기존 generated 목재 PNG의 동일 바이트 사본을 사용했다.
- Compact·default·wide screenshot은 동일 process에서 기술·시각 검수와 사용자 확인을 완료했다. Window resize video는 기존 recorder의 고정 bounds 계약과 충돌하므로 도구 확장 전까지 후속 개선으로 둔다.
- Step9은 정규화된 Step8의 resource·resize 경로를 유지하고 동일 scene에서 Phong reflection vector와 Blinn halfway vector branch를 전환한다.
- Constant buffer flag를 32-bit 정수로 고정하고 halfway vector의 zero-length guard, ambient 중복 제거와 attenuation denominator 제한을 적용했다.
- Blinn-Phong branch의 `shininess * 2`는 같은 입력값에서 lobe 폭을 조정하는 예제 고유 선택으로 유지하고 상세 Demo에 명시했다.
- 출처 불명 texture를 제거하고 Step5~8에서 검수한 generated 목재 PNG의 동일 바이트 사본을 사용했다.
- Step9 Debug/Release x64와 반복 resize·minimize/restore를 현재 확인하고, 동일 material·shininess 32의 Phong·Blinn-Phong screenshot 2장을 기술·시각 검수했다.
- Step9 video는 두 정적 상태가 specular model 차이를 충분히 설명하므로 제외했다.

## Chapter07 마감 snapshot

- Step1은 24개 face vertex와 36개 index의 box를 `TRIANGLELIST`로 유지하고 rasterizer fill mode만 wireframe으로 전환한다.
- 출처 불명 texture 2개와 사용되지 않는 두 번째 shader resource를 제거하고 검증된 generated wood를 solid mode 보조 input으로 사용한다.
- Debug/Release x64 build/run, 반복 resize·minimize/restore와 전체 창 wireframe screenshot을 2026-08-02 현재 확인했다.
- Step1 video는 고정 wireframe 결과와 UI 상태를 screenshot 한 장으로 충분히 설명할 수 있어 제외했다.
- Step2는 surface `TRIANGLELIST`와 vertex normal `LINELIST`를 분리하고 Shader Model 5.0, viewport binding과 resource 실패 전파를 정렬했다.
- Debug/Release x64 build/run, 반복 resize·minimize/restore와 전체 창 normal screenshot을 2026-08-02 현재 확인했다.
- Step2 video는 비스듬한 surface와 normal 분포를 screenshot 한 장으로 충분히 설명할 수 있어 제외했다.
- Step3는 폭·높이와 5×3 분할로 XY plane의 24개 vertex와 30개 triangle을 절차적으로 생성한다.
- 출처 불명 texture 3개를 제거하고 검수된 generated wood의 동일 바이트 사본을 runtime 보조 input으로 사용한다.
- Debug/Release x64 build/run, wide·compact·minimize/restore와 전체 창 Grid screenshot을 2026-08-02 현재 확인했다.
- Step3 video는 정적 wireframe으로 cell 분할과 triangle topology를 충분히 설명할 수 있어 제외했다.
- Step4는 2개 ring과 40 slices로 82개 vertex와 80개 triangle의 열린 Cylinder side surface를 절차적으로 생성한다.
- 출처 불명 texture 2개를 제거하고 검수된 generated wood의 동일 바이트 사본을 runtime 보조 input으로 사용한다.
- Debug/Release x64 build/run, wide·compact·minimize/restore와 전체 창 Cylinder screenshot을 2026-08-02 현재 확인했다.
- Step4 video는 정적 wireframe으로 열린 top과 ring·slice topology를 충분히 설명할 수 있어 제외했다.
- Cap·height subdivision 부재와 taper 시 normal 재계산 필요성, winding의 outward 방향 확인을 구현 한계로 기록했다.
- Step5는 위·아래 반구를 분리 생성하고 equator에서 결합하는 구현을 공개 정본으로 선정했다.
- 선정한 구현은 242 vertices와 380 triangles를 만들고 pole band를 한 triangle씩 마감해 면적 0 pole triangle을 피한다.
- 비교가 끝난 중복 구현은 canonical 정본 확정 단계에서 제거했다.
- 출처 불명·미사용 texture 3개를 제거하고 검수된 generated wood의 동일 바이트 사본을 runtime 보조 input으로 사용한다.
- Debug/Release x64 build/run, wide·compact·minimize/restore와 전체 창 Sphere wireframe screenshot을 2026-08-02 현재 확인했다.
- Step5 video는 정적 wireframe으로 두 반구, equator와 pole topology를 충분히 설명할 수 있어 제외했다.
- Bottom UV의 wrap sampler 의존과 equator·pole 중복 vertex를 구현 한계로 기록했다.
- Step5 Sphere의 380개 triangle winding을 직접 수치 검사해 모두 outward이며 inward·degenerate triangle이 없음을 확인했다.
- Step6은 별도 latitude·longitude seed의 50 triangles를 두 번 1→4 분할하고 각 midpoint를 sphere surface로 projection해 800 triangles를 만든다.
- Shared midpoint cache가 없는 triangle-soup 구조와 pole의 degenerate triangle 160개, 단순 UV midpoint 보간의 seam 한계를 문서화한다.
- 출처 불명·미사용 texture 3개와 두 번째 texture resource를 제거하고 검증된 generated wood의 동일 바이트 사본을 runtime 보조 input으로 사용한다.
- Debug/Release x64 build/run, wide·compact·minimize/restore와 전체 창 Subdivision wireframe screenshot을 2026-08-02 현재 확인한다.
- Step6 video는 정적 wireframe과 단계별 triangle 수로 구현 결과를 충분히 설명할 수 있어 제외한다.
- Step7은 같은 sphere seed에 subdivision을 한 번 적용한 200 triangles에 triangle-local face normal을 할당한다.
- Non-degenerate 160개 face는 모두 outward이고 pole의 40개 degenerate face는 zero-length normal을 유지한다.
- Face center당 line 하나가 아니라 각 triangle corner에서 같은 방향의 line 세 개를 그리는 실제 구현을 문서화한다.
- 출처 불명·미사용 texture 3개와 두 번째 texture resource를 제거하고 검증된 generated wood의 동일 바이트 사본을 runtime 보조 input으로 사용한다.
- Debug/Release x64 build/run, wide·compact·minimize/restore와 전체 창 FaceNormals screenshot을 2026-08-02 현재 확인한다.
- Step7 video는 정적 screenshot에서 normal 방향과 분포를 충분히 설명할 수 있어 제외한다.
- Step8 SphereMapping은 20-triangle icosahedron을 세 번 1→4 분할하고 각 midpoint를 sphere surface로 projection해 1280 triangles를 만든다.
- 각 triangle의 spherical UV를 계산하고 U span이 0.5보다 큰 seam triangle에서 triangle-local vertex copy의 U를 0 또는 1로 보정한다.
- 출처 불명·미사용 texture 3개와 두 번째 texture resource를 제거하고 공개 안전한 generated fictional planet equirectangular PNG를 runtime input으로 사용한다.
- Debug/Release x64 build/run, wide·compact·minimize/restore, generated texture runtime 결과와 1282×992 전체 창 screenshot을 2026-08-03 현재 확인한다.
- 비교가 끝난 Step8 중복 구현은 canonical 정본 확정 단계에서 제거했다.
- Step8 video는 정적 screenshot에서 texture 방향과 seam 결과를 판독할 수 있어 제외한다.
- Step9는 Assimp scene과 node hierarchy를 순회하고 FBX submesh별 vertex/index buffer와 diffuse texture를 구성한다.
- Model load 실패, 빈 mesh 결과와 resize resource 실패를 전파하고 Debug/Release x64와 1282×992 전체 창 screenshot을 2026-08-03 현재 확인한다.
- 사용하지 않는 root image 3개를 제거했으며 Zelda FBX bundle은 실행 근거로 유지한다.
- Zelda bundle의 공개 재배포 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 유지하고 video는 제외한다.

## Chapter08 마감 snapshot

- Step1은 normal과 eye direction의 dot product를 뒤집어 Dragon silhouette에 rim color를 가산한다.
- Power와 smoothstep shaping이 모두 rim contribution을 유지하도록 branch를 교정하고 파란 rim이 보이는 결정적 기본값을 둔다.
- Debug/Release x64, Assimp runtime dependency Clean/Rebuild, resize·minimize/restore와 1282×992 전체 창 screenshot을 2026-08-03 현재 확인한다.
- 사용하지 않는 root image 3개를 제거했으며 Stanford Dragon은 실행 근거로 유지한다.
- Dragon asset 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 유지하고 video는 제외한다.
- Step2는 DDS texture cube, 내부 면 skybox와 rotation-only view를 사용해 camera 주변 배경을 그린다.
- Debug/Release x64 Clean/Rebuild, Assimp·DirectXTK runtime dependency, resize·minimize/restore와 1282×992 전체 창 screenshot을 2026-08-03 현재 확인한다.
- 사용하지 않는 root asset 4개를 제거했으며 Zelda FBX와 skybox DDS는 실행 근거로 유지한다.
- Zelda와 skybox asset 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 유지하고 video는 제외한다.
- Step3은 `reflect(-V, N)` direction으로 NightPath cubemap을 sampling해 environment reflection을 만든다.
- 실제 shader에 연결되지 않던 `Use Reflection` UI와 HLSL vector truncation warning을 제거한다.
- Debug/Release x64, resize·minimize/restore와 1282×992 전체 창 screenshot을 2026-08-03 현재 확인한다.
- NightPath attribution을 유지하고 Zelda 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 둔다.
- Step4는 diffuse irradiance와 specular environment cubemap을 sphere lighting에 결합한다.
- Shader scalar type과 `pow` 입력 범위를 명시하고 Debug/Release Clean/Rebuild, runtime preflight, resize와 1282×992 screenshot을 확인한다.
- Atrium cubemap과 surface texture 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 둔다.
- Step5는 Step4 IBL에 Schlick Fresnel factor와 `fresnelR0` UI를 추가한다.
- Fresnel 주석의 정면·grazing angle 설명을 바로잡고 Debug/Release Clean/Rebuild, runtime DLL, resize와 1282×992 screenshot을 확인한다.
- Assimp 오류창은 사용자가 수동 종료했음을 기록하고 Stonewall cubemap과 surface texture 권리 근거가 충분하지 않아 Publication은 `검토 필요`로 둔다.
- Step6는 Step5 scene을 GPU threshold, downsample, separable blur와 original composite filter chain으로 확장한다.
- Blur accumulator 초기화, 작은 window dimension 제한과 resize 시 post-process resource 재생성을 보완한다.
- Debug/Release Clean/Rebuild, wide·compact resize, minimize/restore와 1282×992 screenshot을 확인하고 asset 권리 근거 미확정으로 Publication은 `검토 필요`로 둔다.
- Step7은 full-screen Star shader에 `iTime`, 현재 `iResolution`과 texture channel 0을 연결한다.
- 고정 aspect를 현재 resolution으로 교체하고 resize 시 filter resource를 재생성하며 비활성 Seascape shader는 build에서 제외한다.
- Debug/Release Clean/Rebuild, wide·compact resize, minimize/restore, 1282×992 screenshot과 9.83초 selected local video를 확인한다.
- Star shader license와 `shadertoytexture0.jpg` 출처 근거가 충분하지 않아 Publication은 `검토 필요`로 둔다.
- 2026-08-03 사용자 승인으로 Chapter08 Bundle에 rendered evidence 예외를 적용하고 원본 runtime asset은 비공개로 유지한다.
- Step1 RimLighting, Step6 BloomEffect와 Step7 Shadertoy를 서로 다른 surface shading·post-processing·procedural shader 설명 축의 Demo Issue 대표 visual로 선정한다.
- Chapter08 screenshot은 공개 가능으로 판정하고 실제 Issue 번호와 URL은 원격 게시 후 동기화한다.
