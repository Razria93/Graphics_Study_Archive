# Part3 Chapter10-13 Capture Plan

이 문서는 `Part3_Chapter10-13`의 Step별 Demo screenshot과 video 촬영 기준을 정의한다.

## 운영 기준

- 자동모드 작업자는 Step별 visual 대상과 수량을 결정하기 전에 이 문서를 확인한다.
- 실제 구현 조사 결과와 이 문서가 충돌하면 capture 전에 사용자 확인을 요청한다.
- 정적 차이만 중요한 Step은 screenshot 비교를 우선하고 video를 만들지 않는다.
- camera movement, billboard animation, HDRI, trackball, fog, alpha 변화처럼 시간 변화나 조작 과정 자체가 핵심인 Step은 video를 사용한다.
- tracked 상세 Demo 본문은 안정적인 정적 visual 또는 storyboard를 우선한다.
- video는 일반 Git history에 넣지 않고 selected local evidence 또는 GitHub Demo Issue comment attachment로 운용한다.
- 같은 동작을 보완하는 재촬영은 기존 기준을 갱신하고, 다른 개념을 보여주는 visual은 별도 항목으로 추가한다.
- `10_03 NormalLines`는 현재 정적 screenshot만으로 목적을 설명할 수 있으므로 재촬영 우선순위에서 제외한다.

## Chapter11-13 노출 기준

- Chapter11은 `NormalMapping`, `HeightMapping`, `HDRPipeline`을 대표 노출 축으로 둔다.
- `Mipmaps`와 `HDRI`는 texture LOD와 HDR input을 설명하는 보조 축으로 유지한다.
- Chapter12는 `UnrealPBR`과 `PBRModels`를 함께 대표 노출 축으로 둔다.
- `PBRModels`의 character는 사용자 구매 asset 기반 rendered evidence로만 사용한다.
- 원본 FBX, texture, 구매 자료와 license 원문은 공개 body에서 직접 링크하지 않는다.
- Chapter13은 mirror, shadow, depth/fog, halo와 sphere light를 visual 노출 대상으로 둔다.
- `PipelineStateObject`는 시각 차이보다 pipeline state 구조 개선을 설명하는 code 중심 단계로 둔다.
- Chapter13 대표 비교는 `ShadowMapping` → `SoftShadowPCF` → `SoftShadowPCSS`로 둔다.
- 권리·출처 risk가 남은 runtime asset은 blocker로 삼지 않고 rendered evidence only와 추후 수정 가능 상태를 함께 기록한다.
- 이번 기준 정렬은 asset 교체, 생성, 삭제 없이 다음 capture와 GitHub body 선정을 위한 판단 기준만 고정한다.

## Step별 촬영 기준

| 정본 대상 | Demo | 목적 | Screenshot 기준 | Video 기준 |
| --- | --- | --- | --- | --- |
| `10_02 Billboards` | [Billboards](../Docs/03_Demos/Part3_Chapter10-13/10_02_Billboards.md) | camera 위치에 따라 billboard가 camera를 향하도록 회전하는 차이를 보여준다. | 3장: left, center, right camera 위치 비교 | 없음 |
| `10_03 NormalLines` | [NormalLines](../Docs/03_Demos/Part3_Chapter10-13/10_03_NormalLines.md) | vertex normal diagnostic line 분포를 보여준다. | 기존 capture 유지 | 없음 |
| `10_04 Fireball` | [Fireball](../Docs/03_Demos/Part3_Chapter10-13/10_04_Fireball.md) | billboard 기반 procedural animation의 시간 변화를 보여준다. | 3장: billboard가 camera-facing quad임을 판독할 수 있는 frame | 필수: fireball animation이 움직이는 것을 짧게 보여준다. |
| `10_05 Tessellation` | [Tessellation](../Docs/03_Demos/Part3_Chapter10-13/10_05_Tessellation.md) | LOD 성격의 tessellation factor 차이가 polygon density로 나타나는 것을 보여준다. | 2장: low-poly, high-poly | 없음 |
| `11_01 Mipmaps` | [Mipmaps](../Docs/03_Demos/Part3_Chapter10-13/11_01_Mipmaps.md) | texture LOD가 낮은 해상도와 높은 해상도 sampling 결과를 바꾸는 것을 보여준다. | 2장: 낮은 해상도, 높은 해상도 | 없음 |
| `11_02 NormalMapping` | [NormalMapping](../Docs/03_Demos/Part3_Chapter10-13/11_02_NormalMapping.md) | normal mapping 적용 유무가 조명 반응을 바꾸는 것을 보여준다. | 2장: normal mapping Off, normal mapping On | 없음 |
| `11_03 HeightMapping` | [HeightMapping](../Docs/03_Demos/Part3_Chapter10-13/11_03_HeightMapping.md) | height mapping 적용 유무가 sphere silhouette과 요철을 바꾸는 것을 보여준다. | 2장: height mapping Off, height scale `0.1` On | 없음 |
| `11_04 HDRI` | [HDRI](../Docs/03_Demos/Part3_Chapter10-13/11_04_HDRI.md) | exposure와 gamma parameter가 display mapping을 바꾸는 것을 보여준다. | 4장: exposure/gamma `0.5/0.5`, `2.0/0.5`, `0.5/1.0`, `2.0/1.0` | 없음 |
| `11_05 HDRPipeline` | [HDRPipeline](../Docs/03_Demos/Part3_Chapter10-13/11_05_HDRPipeline.md) | bloom strength와 HDRI camera 방향 변화가 최종 composite를 바꾸는 것을 보여준다. | 2장: bloom `0`, bloom `0.7` | 필수: 중심에서 오른쪽 끝까지 mouse 이동으로 HDRI 방향 변화를 5초에서 10초 안에 보여준다. |
| `12_01 UnrealPBR` | [UnrealPBR](../Docs/03_Demos/Part3_Chapter10-13/12_01_UnrealPBR.md) | PBR texture set 적용 유무와 trackball 조작에 따른 재질 반응을 보여준다. | 2장: PBR map 전체 Off, PBR map 전체 On과 height scale `0.015` | 필수: PBR map On 상태에서 중심 drag를 우상단으로 이동하고 대기한 뒤 좌하단으로 이동해 대기한다. |
| `12_02 PBRModels` | [PBRModels](../Docs/03_Demos/Part3_Chapter10-13/12_02_PBRModels.md) | imported model의 PBR option 적용 유무를 보여준다. | 2장: PBR option 전체 Off, height mapping 제외 PBR option On | 없음 |
| `13_01 Mirror` | [Mirror](../Docs/03_Demos/Part3_Chapter10-13/13_01_Mirror.md) | mirror post-process parameter가 반사 표면을 바꾸는 것을 보여준다. | 2장: alpha/metallic/roughness `0.0/0.0/0.0`, `0.5/0.7/0.5` | 없음 |
| `13_02B Shadow Prototype` | [ShadowPrototype](../Docs/03_Demos/Part3_Chapter10-13/13_02B_ShadowPrototype.md) | point light parameter가 prototype shadow 결과를 바꾸는 것을 보여준다. | 2장: 기본값, 세 번째 parameter `1.0` | 없음 |
| `13_03 DepthBufferAndFog` | [DepthBufferAndFog](../Docs/03_Demos/Part3_Chapter10-13/13_03_DepthBufferAndFog.md) | depth scale `0.5`에서 render view와 depth view의 차이를 보여준다. | 2장: Post Effects `Render`, Post Effects `Depth` | 없음 |
| `13_05 SoftShadowPCF` | [SoftShadowPCF](../Docs/03_Demos/Part3_Chapter10-13/13_05_SoftShadowPCF.md) | light position 변화에 따른 soft shadow 위치 변화를 보여준다. | 1장: light position `(1.0, 1.5, 1.5)` 기본값 | 필수: 첫 번째 position 값을 `2.0`에서 `-2.0`으로 약 5초 동안 이동한다. |
| `13_06 SoftShadowPCSS` | [SoftShadowPCSS](../Docs/03_Demos/Part3_Chapter10-13/13_06_SoftShadowPCSS.md) | PCSS 결과를 기본 screenshot으로 유지한다. | 1장: 기본값 | 없음 |
| `13_07 Halo` | [Halo](../Docs/03_Demos/Part3_Chapter10-13/13_07_Halo.md) | depth-aware halo post effect의 기본 결과를 보여준다. | 1장: 기본값 | 없음 |
| `13_08 UnrealSphereLight` | [UnrealSphereLight](../Docs/03_Demos/Part3_Chapter10-13/13_08_UnrealSphereLight.md) | sphere light approximation에서 material alpha 변화가 highlight와 transparency를 바꾸는 것을 보여준다. | 1장: 기본값 | 필수: metallic `0.5`, roughness `0.3` 상태에서 alpha를 `0`에서 `1.0`으로 약 10초 동안 이동한다. |

## 번호와 정본명 매핑

- 사용자 촬영 메모의 `13_02 Mirror`는 현재 정본 `13_01 Mirror`에 대응한다.
- 사용자 촬영 메모의 `13_02 Shadow`는 현재 정본 `13_02B Shadow Prototype`에 대응한다.
- 사용자 촬영 메모의 `13_06 Fog`는 현재 정본에서 별도 Step이 아니므로 `13_03 DepthBufferAndFog`의 fog/depth post effect 기준과 충돌하지 않는지 촬영 전에 확인한다.
- 사용자 촬영 메모의 `13_08 Halo` parameter 기준은 현재 정본 `13_08 UnrealSphereLight`의 alpha, metallic, roughness 조작 기준으로 기록한다.

## 촬영 전 확인

- camera, UI, post-process와 material parameter가 기준값에 맞는지 확인한다.
- assimp 또는 asset load 오류 창이 남아 있으면 실행과 capture를 폐기하고 오류 창을 먼저 정리한다.
- 자동 capture 도구가 창 크기를 변경해야 하는 경우 resize-sensitive 예제는 launch 전 고정 크기 또는 in-place capture 전략을 우선한다.
- 사용자가 조작하거나 화면을 건드렸다고 알리면 해당 take를 폐기하고 sequence를 처음부터 다시 수행한다.

## 촬영 후 판정

- screenshot은 전체 application window, 공개 application title, 핵심 UI와 결과 대응을 포함해야 한다.
- storyboard가 video의 동적 의미를 충분히 대체하면 상세 Demo 본문은 storyboard를 우선한다.
- video가 필요한 Step은 selected local video로 기술 검사를 통과한 뒤 GitHub Demo Issue comment attachment 게시 여부를 별도로 판단한다.
- final visual 선정 뒤 `Docs/03_Demos/Part3_Chapter10-13/demo-index.md`, `Docs/02_Verification/Part3_Chapter10-13/verification-index.md`, `Docs/05_Publication/candidate-list.md`와 GitHub 게시 후보를 함께 확인한다.
