# Import Plan: Part3

## Source / Target

- Primary raw source:
  - `C:\ComputerGraphics\Part3_Chapter09`
  - `C:\ComputerGraphics\Part3_Chapter10_13`
- Reference-only raw source:
  - `C:\ComputerGraphics\Part3_Chapter10_13_2`
- Archive target:
  - `Part3_Chapter09`
  - `Part3_Chapter10-13`
- Docs target:
  - `Docs/Part3_Chapter09`
  - `Docs/Part3_Chapter10-13`
- Branch: `archive/part3`
- Import status: Chapter09 and Chapter10-13 imported
- Build/run status: Chapter09 and Chapter10-13 Debug/Release 성공
- Public readiness: 검토 필요

## Part3 Working Goal

Part3는 1차로 code import, asset selection, build/run 확인을 우선합니다.

소스 내부 장문 학습 메모 정리와 최종 portfolio 문서 품질 개선은 Part1부터 전체 code import가 끝난 뒤 2차 문서 정리 단계에서 진행합니다. 단, 코드 변경으로 기존 주석이 틀려진 경우나 실행 흐름을 오해하게 만드는 주석은 import 중에도 최소 수정합니다.

## Raw Folder Decision

### Chapter09

| Raw folder | Import decision | Archive naming | Note |
| --- | --- | --- | --- |
| `09_UserInteraction_Step1_FirstPersonView` | archive 후보 | same | first-person camera |
| `09_UserInteraction_Step2_MousePicking` | archive 후보 | same | mainline mouse picking 작업본 |
| `09_UserInteraction_Step2_MousePicking_Debug` | 제외 / reference-only | none | debug/memo 실험 흔적. `memo.txt` 포함, picking readback 흐름이 mainline과 다름 |
| `09_UserInteraction_Step3_MousePickingRayCollision` | archive 후보 | same | 사용자 작업본. source memo가 많아 local 분리 필요 |
| `09_UserInteraction_Step3_MousePickingRayCollision_Debug` | 제외 / reference-only | none | debug variant |
| `09_UserInteraction_Step3_MousePickingRayCollision_Solution` | reference solution 후보 | `09_UserInteraction_Step3_MousePickingRayCollision_ReferenceSolution` | 정리된 reference solution 성격. public 후보 아님 |
| `09_UserInteraction_Step4_QuaternianRotation` | archive 후보 | same | raw spelling 유지 여부는 import 시 확인 |
| `09_UserInteraction_Step5_VirtualTrackball` | archive 후보 | same | mainline virtual trackball 작업본 |
| `09_UserInteraction_Step5_VirtualTrackball_Debug` | 제외 / reference-only | none | 회전 벡터 계산 실험, debug 출력 흔적 |
| `09_UserInteraction_Step6_MouseDragMove` | archive 후보 | same | mouse drag movement |
| `Assets` | 선별 포함 | `Part3_Chapter09/Assets` | 실행에 필요한 asset만 포함 |
| `copy_dlls.py` | 검토 필요 | none | archive 실행에 필요할 때만 포함 |

### Chapter10-13

| Raw folder | Import decision | Archive naming | Note |
| --- | --- | --- | --- |
| `C:\ComputerGraphics\Part3_Chapter10_13` | primary source | `Part3_Chapter10-13` | 최신 진행본으로 판단 |
| `C:\ComputerGraphics\Part3_Chapter10_13_2` | reference-only snapshot | none | 2025-09-26 시점 백업/snapshot 성격. 직접 import 기준 아님 |

`Part3_Chapter10_13_2` 판단 근거:

- 대부분 코드 파일의 최신 시간이 `2025-09-26 10:33~10:34`에 고정되어 있습니다.
- `Part3_Chapter10_13`은 이후 `2025-10-04`부터 `2025-10-22`까지 계속 갱신된 흔적이 있습니다.
- `_2`에는 `10_GeometryPipeline_Step1_GeometryShader` 기본 폴더가 없고 `10_GeometryPipeline_Step1_GeometryShader_Solution`만 있습니다.
- `_2/Assets`에는 zip asset 4개가 더 있으나, zip 원본 asset은 archive import 기준이 아니라 별도 검토 대상입니다.
- 코드 차이는 대부분 1~8개 파일 수준이며, 일부 항목은 완전히 동일합니다.

따라서 `Part3_Chapter10_13`을 primary로 사용하고, `_2`는 build/run 문제나 기능 누락 의심이 있을 때만 비교합니다.

## Chapter10-13 Inventory

| Raw example | Import decision | Build/run | Public readiness | Note |
| --- | --- | --- | --- | --- |
| `10_GeometryPipeline_Step1_GeometryShader` | archive 후보 | 미확인 | 검토 필요 | `_2`에는 기본 폴더 없음 |
| `10_GeometryPipeline_Step1_GeometryShader_Solution` | reference solution 후보 | 미확인 | 검토 필요 | public 후보 아님 |
| `10_GeometryPipeline_Step2_Billboards` | archive 후보 | 미확인 | 검토 필요 | primary 쪽 billboard model matrix update 차이 확인됨 |
| `10_GeometryPipeline_Step3_NormalLines` | archive 후보 | 미확인 | 검토 필요 | primary 쪽 `NormalGeometryShader.hlsl` 추가 |
| `10_GeometryPipeline_Step4_Fireball` | archive 후보 | 미확인 | 검토 필요 | geometry/fireball shader |
| `10_GeometryPipeline_Step5_Tessellation` | archive 후보 | 미확인 | 검토 필요 | hull/domain shader |
| `11_TexturingTechniques_Step1_Mipmaps` | archive 후보 | 미확인 | 검토 필요 | `_2`와 mipmap slider 상태 차이 있음 |
| `11_TexturingTechniques_Step2_NormalMapping` | archive 후보 | 미확인 | 검토 필요 | normal map workflow |
| `11_TexturingTechniques_Step3_HeightMapping` | archive 후보 | 미확인 | 검토 필요 | height/tessellation workflow |
| `11_TexturingTechniques_Step4_HDRI` | archive 후보 | 미확인 | 검토 필요 | HDRI/cubemap |
| `11_TexturingTechniques_Step5_HDRPipeline` | archive 후보 | 미확인 | 검토 필요 | HDR/post-processing |
| `12_PBR_Step1_UnrealPBR` | archive 후보 | 미확인 | 검토 필요 | PBR shader |
| `12_PBR_Step2_PBRModels` | archive 후보 | 미확인 | 검토 필요 | `_2`와 code hash 동일 |
| `13_LightAndShadow_Step1_Mirror` | archive 후보 | 미확인 | 검토 필요 | mirror/stencil |
| `13_LightAndShadow_Step2_PipelineStateObject` | archive 후보 | 미확인 | 검토 필요 | PSO abstraction |
| `13_LightAndShadow_Step2_Shadow` | archive 후보 | 미확인 | 검토 필요 | `_2`와 code hash 동일 |
| `13_LightAndShadow_Step3_DepthBufferAndFog` | archive 후보 | 미확인 | 검토 필요 | depth/fog |
| `13_LightAndShadow_Step4_ShadowMapping` | archive 후보 | 미확인 | 검토 필요 | shadow map |
| `13_LightAndShadow_Step5_SoftShadowPCF` | archive 후보 | 미확인 | 검토 필요 | PCF |
| `13_LightAndShadow_Step6_SoftShadowPCSS` | archive 후보 | 미확인 | 검토 필요 | PCSS |
| `13_LightAndShadow_Step7_Halo` | archive 후보 | 미확인 | 검토 필요 | halo/post effect |
| `13_LightAndShadow_Step8_UnrealSphereLight` | archive 후보 | 미확인 | 검토 필요 | sphere light |

## Include Candidates

- `.sln`, `.vcxproj`, `.vcxproj.filters`
- `*.cpp`, `*.h`, `*.hlsl`, `*.hlsli`
- 실행에 필요한 selected asset
- app-local DLL copy script는 실제 실행에 필요할 때만 포함합니다.

## Exclude / Defer

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`
- `.clang-format`
- raw result/capture/video
- `captured.png` 같은 raw 실행 결과물
- zip asset 원본 파일
- `_Debug`, `_Backup`, 실험/중간 폴더
- 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료

## Variant Naming Rule

- `_Debug`는 기본 제외하고 reference-only로 둡니다.
- `_Solution`은 필요할 경우 `ReferenceSolution`으로 이름을 바꾸어 보관합니다.
- `ReferenceSolution`은 private archive 비교용이며 public 공개 후보가 아닙니다.
- 사용자 작업본과 reference solution을 둘 다 가져올 때는 Part2처럼 `UserSolution` / `ReferenceSolution` 의미를 명확히 합니다.

## Import Order

1. `Part3_Chapter09` manifest/detail docs 생성
2. `09_UserInteraction_Step1_FirstPersonView` import
3. Ch09 mainline 예제 순차 import
4. Ch09 `_Solution`은 필요한 경우 reference solution으로 분리
5. `Part3_Chapter10-13` scaffold 정상화
6. Ch10 geometry pipeline부터 순차 import
7. `_2`는 build/run 실패 또는 기능 차이 의심 시에만 비교

## Per-example Finish Check

각 예제 import 종료 전 다음을 확인합니다.

- raw result/capture/build output 미포함
- `.vcxproj` XML namespace 정상
- HLSL/HLSLI BOM 없음
- shader include 파일이 build 대상이 아닌 include/document file로 남아 있는지 확인
- selected asset hash raw와 일치
- raw와 다르게 바꾼 project/source 설정은 `status.md`에 이유 기록
- build/run은 사용자가 확인하기 전까지 `미확인`으로 기록

## Final Import Check

- Chapter09 archive 대상 예제 import 완료
- Chapter10-13 archive 대상 예제 import 완료
- 사용자 Debug/Release 실행 확인 기록 완료
- tracked build output/local state file 없음 확인
- HLSL/HLSLI BOM 없음 확인
- `.vcxproj` XML parse 확인
- `.clang-format` project reference 없음 확인
- Release shader model `5.0` 기준 정리 확인

## Current Next Action

1. Part3 branch 마무리 커밋을 정리합니다.
2. `Docs/_repo/pull-requests/archive-part3.md` 기준으로 PR을 구성합니다.
3. merge 후 Part4 import branch로 이동합니다.
