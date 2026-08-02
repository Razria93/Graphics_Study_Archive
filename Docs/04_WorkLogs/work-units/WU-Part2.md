# WU-Part2 WorkLog

## 범위

| 항목 | 내용 |
| --- | --- |
| Work Unit | `WU-Part2` |
| 현재 마감 대상 | `Part2_Chapter05-08` Chapter06 순차 정규화 |
| 후속 코드 범위 | Chapter06 Step6 Lighting부터 Chapter08까지 |
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
| video 필요성과 상태 | [Video Plan](../../03_Demos/video-plan.md) |
| 공개 후보와 미선정 판단 | [Candidate List](../../05_Publication/candidate-list.md) |
| GitHub 게시 상태 | [Work Unit GitHub Index](../work-unit-github-index.md) |

## 게시 snapshot

- [Chapter04 Demo Issue #14](https://github.com/Razria93/Graphics_Study_Archive/issues/14) 게시와 실제 URL 동기화를 완료했다.
- [Chapter04 PR #15](https://github.com/Razria93/Graphics_Study_Archive/pull/15)을 일반 merge commit 방식으로 병합해 실제 URL과 최종 상태 동기화를 완료했다.
- [누적 Progress 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5091068690)을 Chapter04 상태로 갱신했다.
- [Phase 3-1 완료 댓글](https://github.com/Razria93/Graphics_Study_Archive/issues/7#issuecomment-5150875726) 게시와 실제 URL 동기화를 완료했다.

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

## Chapter06 진행

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
