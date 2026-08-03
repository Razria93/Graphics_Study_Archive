# Video Plan

이 문서는 video 필요성, selected 후보와 게시 상태를 기록하는 registry다. 촬영·검수·저장 규칙은 [Demo Capture Policy](../06_Policies/demo-capture-policy.md)를 따른다.

## 상태 위치

- raw, attempt와 selected video: `local/`
- 게시된 video reference와 운영 안내: `Docs/_assets/videos/`
- published video: GitHub Demo Issue attachment
- 게시 전 설명 초안: `local/github/draft`

## 우선 video 후보

| 범위 | 후보 | 필요성 | 보여줄 개념 | selected | published |
| --- | --- | --- | --- | --- | --- |
| Part2_Chapter04 Step1A | triangle count 3→32 slider 조작 | 필수 | triangle fan 재생성과 polygonal circle 수렴 과정 | 검증 완료 | [Demo Issue #14 attachment](https://github.com/user-attachments/assets/fc86477d-36bf-44bc-b279-a0824fa0c447) |
| Part2_Chapter04 Step4 | Animation2D 실행 | 필수 | 시간에 따른 계층적 2D orbit | 검증 완료 | 미게시: Chapter Issue의 3개 visual에서 Step1A Personal Extension을 우선하고 중복을 줄임 |
| Part2_Chapter04 Step5 | circle depth 순서 변경 | 필수 | Per-pixel depth test에 따른 visibility 반전 | 검증 완료 | 미게시 |
| Part2_Chapter04 Step6 | 자동 square rotation | 선택 | CPU vertex stage의 per-frame transform 결과 | 검증 완료 | 미게시 |
| Part2_Chapter04 Step7 | culling checkbox On→Off→On | 선택 | Post-transform winding에 따른 backface rejection 전환 | 기술·사용자 시각 검수 완료 | 미게시 |
| Part2_Chapter05-08 Chapter06 Step8 | Default→Wide→Compact window resize | 필수 | Swap chain dependent resource 재생성과 projection aspect 유지 | 보류: recorder 고정 bounds 계약과 충돌 | 미게시 |
| Part2_Chapter05-08 Chapter06 Step9 | Phong↔Blinn-Phong checkbox 전환 | 선택 | 동일 조건에서 reflection vector와 halfway vector 기반 highlight 변화 | 제외: 정적 screenshot 2장이 상태와 결과를 충분히 설명 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step1 | Solid↔Wireframe checkbox 전환 | 선택 | triangle-list mesh의 fill mode 변화 | 제외: Wireframe On과 UI를 담은 정적 screenshot 1장이 topology를 충분히 설명 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step2 | Vertex normal line 표시와 mesh 회전 | 선택 | 여러 면의 normal 방향과 분포 | 제외: 비스듬한 box와 normal line을 담은 정적 screenshot 1장이 구현을 충분히 설명 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step3 | Grid 분할 수와 topology 표시 | 선택 | Procedural sample과 cell triangulation | 제외: 5×3 wireframe screenshot 1장이 cell과 triangle 구성을 충분히 설명 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step4 | Cylinder ring·slice topology 표시 | 선택 | 열린 side surface의 ring 연결과 triangle 분할 | 제외: 비스듬한 wireframe screenshot 1장이 열린 top과 topology를 충분히 설명 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step5 | Sphere latitude·longitude·pole topology 표시 | 선택 | 두 반구 합성, equator 결합과 pole fan | 제외: wireframe screenshot 1장이 topology를 충분히 설명 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step6 | Subdivision 전후 triangle density와 sphere projection | 선택 | 1→4 triangle 분할과 2회 적용 결과 | 제외: 최종 wireframe screenshot 1장과 문서의 단계별 triangle 수로 충분히 설명 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step7 | Face normal 표시와 sphere 회전 | 선택 | Triangle winding과 face normal 방향 | 제외: solid surface와 corner 기반 normal line을 담은 정적 screenshot 1장이 방향과 분포를 충분히 설명 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step8 SphereMapping | Spherical UV seam과 pole 확인 | 제외 | Fictional planet texture의 U seam·pole mapping | 전체 창 screenshot 한 장에서 texture 방향과 seam 결과를 판독 가능 | 미게시 |
| Part2_Chapter05-08 Chapter07 Step9 | Imported model 회전과 submesh 확인 | 선택 | Assimp node traversal 결과와 submesh별 texture binding | 제외: 정적 전체 창 screenshot 한 장에서 model과 material 경계를 판독 가능 | 미게시 |
| Part2_Chapter05-08 Chapter08 Step1 | Rim power와 shaping 변화 | 선택 | Normal·view angle 기반 silhouette 강조 | 제외: 파란 rim과 parameter UI를 정적 전체 창 screenshot 한 장에서 판독 가능 | 미게시 |
| Part2_Chapter05-08 Chapter08 Step7 | Star surface와 corona의 시간 변화 | 필수 | `iTime` 기반 procedural animation | 9.83초, 30 FPS selected local video 기술 검수 완료 | 미게시 |
| Part3_Chapter09 Step1 | WASD 이동과 절대 cursor 시선 전환 | 필수 | camera translation과 orientation | 17.57초 WASD, 31초 mouse-look selected local video 검증 완료 | 미게시 |
| Part3_Chapter09 Step3 | Press·marker 이동·release | 필수 | CPU picking ray collision lifecycle | 13.97초 selected local video 검증 완료 | 미게시 |
| Part3_Chapter09 Step4 | X·Y·Z axis별 Theta drag | 필수 | Axis-angle quaternion rotation | 축별 15초 selected local video 3개 검증 완료 | 미게시 |
| Part3_Chapter09 Step5 | Sphere 안쪽 virtual trackball drag | 필수 | Surface vector 기반 누적 quaternion 회전 | 18.6초 selected local video 검증 완료 | 미게시 |
| Part3_Chapter09 Step6 | 오른쪽→위쪽 object drag | 필수 | 동일 ray depth의 world-space translation | 16.07초 selected local video 검증 완료 | 미게시 |
| Part3_Chapter10-13 | shadow quality 비교 | 선택 | shadow mapping, PCF, PCSS | 미확인 | 미게시 |
| Part4_Chapter14-20 | 대표 sample 실행 | 선택 | advanced graphics 후보 | 미확인 | 미게시 |
| Portfolio_RayTracer | feature progression | 선택 | ray tracing extension | 미확인 | 미게시 |

## Video Checklist

| 항목 | 기준 |
| --- | --- |
| 길이 | 짧고 반복 시청 가능함 |
| 흐름 | 시작, 조작, 결과가 분명함 |
| 설명 | 화면 밖 설명은 README/PR 본문으로 분리함 |
| 권리 검토 | 강의 화면·유료 자료가 없고 외부 asset 출처 또는 승인된 Bundle rendered evidence 예외를 확인함 |
| 연결 문서 | Example, Topic, Verification 문서와 연결됨 |
| 자동 검수 | container, codec, pixel format, CFR, stream, 민감 metadata, hash와 decode를 확인함 |
| 사용자 시각 검수 | 조작과 결과 대응, 화면 노출, 시작·종료 frame과 추가 설명 가치를 확인함 |
| 게시 | Demo Issue에 한 번 첨부하고 PR은 대표성이 있을 때 동일 URL을 재사용함 |

## 갱신 기준

- MP4, MOV와 WEBM을 일반 Git history에 추가하지 않으며 예외는 별도 Publication 판단과 사용자 승인을 따른다.
- public 공개 전에는 `Docs/05_Publication` 기준으로 다시 점검한다.
- Published 상태와 actual URL은 merge 전에 관련 tracked 정본에 동기화한다.
