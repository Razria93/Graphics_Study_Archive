# Picking And Screen Ray

## 목적

Screen cursor가 가리키는 scene object를 식별하는 GPU ID picking과 CPU screen-ray collision의 공통 원리를 설명한다.

## 책임 범위

Picking의 좌표 변환과 두 접근의 차이를 다룬다. Render target 구성, readback과 collision 함수의 실제 코드는 Step2·3 Example README에 위임한다.

## 개념 흐름

Cursor 좌표를 viewport와 연결한 뒤 GPU가 기록한 object ID를 읽거나, near/far NDC를 world space로 역변환해 ray를 만들고 primitive와 교차한다.

## 핵심 개념

### GPU ID Picking

Object마다 고유 ID color를 별도 render target에 기록하고 cursor의 한 pixel을 CPU로 읽는다. 복잡한 geometry와 render 결과를 그대로 활용할 수 있지만 GPU 동기화와 readback 비용이 발생한다.

### CPU Screen Ray

Cursor의 near/far NDC를 inverse view-projection으로 world space에 옮겨 ray origin과 direction을 만든다. Bounding volume 교차는 빠르지만 실제 triangle 표면과 다른 근사 결과를 낼 수 있다.

## 데모 연결

Step2는 ID buffer 기반 hover picking을, Step3은 bounding sphere 기반 CPU collision을 보여준다. 두 Step은 누적 구현이 아니라 같은 입력 문제를 다른 경로로 비교한다.

## 한계

Triangle-level picking, asynchronous readback, MSAA edge의 ID resolve와 다중 hit 정렬은 범위 밖이다.

## 관련 문서

- [Step2 Example](../../../Part3_Chapter09/09_UserInteraction_Step2_MousePicking/README.md)
- [`Docs/03_Demos` Step2 Demo](../../03_Demos/Part3_Chapter09/09_02_MousePicking.md)
- [`Docs/02_Verification`](../../02_Verification/Part3_Chapter09/verification-index.md)
