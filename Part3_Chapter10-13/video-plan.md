# Part3 Chapter10-13 Video Plan

이 문서는 `Part3_Chapter10-13`의 video evidence 책임과 게시 기준을 기록한다.

## 운영 기준

- video는 일반 Git history에 넣지 않는다.
- video는 `local/` selected evidence 또는 GitHub Demo Issue comment attachment 후보로 둔다.
- 상세 Demo 본문과 PR/Issue 본문은 screenshot, storyboard, contact sheet를 우선한다.
- 같은 동적 의미를 안정적으로 설명할 수 있으면 storyboard 또는 contact sheet로 대체한다.
- video 필요성은 각 Step capture 작업에서 실제 조작 결과를 확인한 뒤 확정한다.
- 권리·출처 risk가 있는 runtime asset은 원본을 직접 공개·링크하지 않고 rendered evidence만 사용한다.

## Chapter별 video 후보

| 대상 | video 후보 | 본문 대체 visual | 비고 |
| --- | --- | --- | --- |
| `10_04 Fireball` | procedural billboard animation | 3-frame storyboard | selected local video는 기술 검수 후 Issue comment attachment 후보로만 둔다. |
| `11_05 HDRPipeline` | HDRI 방향 변화 | bloom Off/On screenshot 또는 storyboard | Chapter11 대표 노출 축 중 동적 후보로 둔다. |
| `12_01 UnrealPBR` | trackball material response | PBR Off/On screenshot 또는 contact sheet | Chapter12 대표 노출 축 중 동적 후보로 둔다. |
| `13_05 SoftShadowPCF` | light position 이동 | 기본 screenshot 또는 shadow movement storyboard | soft shadow 위치 변화를 설명할 때만 사용한다. |
| `13_08 UnrealSphereLight` | alpha 변화 | 기본 screenshot 또는 alpha storyboard | sphere light approximation의 material response 후보로 둔다. |

## 게시 기준

- GitHub Issue 본문은 안정적인 정적 visual을 먼저 사용한다.
- video는 본문에 직접 넣기보다 Issue comment attachment로 분리한다.
- 본문 visual이 같은 목적을 충분히 설명하면 video comment를 생략한다.
- 같은 의미의 video를 보완 촬영하면 기존 comment update 후보로 둔다.
- 다른 개념을 보여주는 video는 새 comment 후보로 분리한다.
- 원본 asset, 구매 증빙, license 원문과 local path는 video 설명에 포함하지 않는다.

## 관련 문서

- [Capture Plan](capture-plan.md)
- [Demo Index](../Docs/03_Demos/Part3_Chapter10-13/demo-index.md)
- [Publication Candidate List](../Docs/05_Publication/candidate-list.md)
