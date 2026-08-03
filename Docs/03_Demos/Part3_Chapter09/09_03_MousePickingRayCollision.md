# Chapter09 Step3 MousePickingRayCollision Demo

## 목적

Cursor에서 만든 world-space ray와 bounding sphere의 CPU collision으로 object를 식별하는 경로를 보여준다.

## 책임 범위

- NDC 역변환, ray 구성과 bounding sphere hit를 설명한다.
- Picking 이론은 [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md), 검증 사실은 [Verification](../../02_Verification/Part3_Chapter09/verification-index.md)에 위임한다.

## 결과 미리보기

![Chapter09 Step3 MousePickingRayCollision](../../_assets/captures/part3_chapter09_03_mouse_picking_ray_collision.png)

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | Cursor NDC, inverse view-projection, bounding sphere |
| 출력 | Hit 여부, distance와 world-space hit marker |

## 구현 흐름

1. Cursor near/far NDC를 만든다.
2. Inverse view-projection으로 world near/far를 계산한다.
3. 두 점에서 normalized ray를 구성한다.
4. Bounding sphere intersection 결과로 selection과 marker를 갱신한다.

## 핵심 구현

### World Ray Collision

GPU ID readback 대신 CPU가 단순 bounding volume과 교차해 선택 여부와 거리를 얻는다.

- [Cursor NDC 변환](../../../Part3_Chapter09/09_UserInteraction_Step3_MousePickingRayCollision/AppBase.cpp#L140-L157)
- [Ray와 bounding sphere 교차](../../../Part3_Chapter09/09_UserInteraction_Step3_MousePickingRayCollision/ExampleApp.cpp#L110-L166)

## 시각 결과

Earth sphere는 picking 대상과 bounding volume의 위치를 명확히 보여준다. Hit marker는 pointer hold 동안 표시되는 동적 진단 결과다.

## 구현 범위와 한계

- Triangle surface가 아닌 bounding sphere 근사 교차다.
- Step3은 `_Solution` 기반이며 개인 고유 구현으로 주장하지 않는다.
- Earth와 cubemap asset의 공개 권리 근거가 부족해 Publication은 `검토 필요`다.

## 검증

- [Verification Index](../../02_Verification/Part3_Chapter09/verification-index.md)

## 관련 코드

- [Hit marker 갱신](../../../Part3_Chapter09/09_UserInteraction_Step3_MousePickingRayCollision/ExampleApp.cpp#L141-L166)
- [Example README](../../../Part3_Chapter09/09_UserInteraction_Step3_MousePickingRayCollision/README.md)

## 관련 문서

- [Picking And Screen Ray](../../01_Topics/AnimationAndPhysics/PickingAndScreenRay.md)
- [이전 Demo](09_02_MousePicking.md)
- [다음 Demo](09_04_QuaternionRotation.md)
- [Demo Index](demo-index.md)
