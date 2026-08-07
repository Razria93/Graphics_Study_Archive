# Chapter19 Ex1901 PhysX

## Overview

`Ex1901_PhysX`는 PhysX gravity scene의 dynamic block stack을 fixed simulation step으로 갱신하고 actor shape pose를 render model world transform으로 동기화하는 예제다. `Examples.exe 1901`은 PhysX runtime DLL과 SDK dependency를 필요로 하며 block collapse storyboard를 rendered evidence로 사용한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1901`
- Working directory: `Part4_Chapter14-20` source root
- Runtime dependency: PhysX runtime DLL과 HDRI files, 세부 복구 조건은 Verification 정본 참조
- 주요 source: `Ex1901_Physx.cpp`
- Shader: standard model render path

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L101) | command argument `1901`을 `Ex1901_PhysX` instance에 연결 |
| [Ex1901_Physx.cpp](../Ex1901_Physx.cpp#L13) | PhysX foundation, dispatcher, gravity scene과 material을 초기화 |
| [Ex1901_Physx.cpp](../Ex1901_Physx.cpp#L57) | static ground plane과 dynamic block stack을 구성 |
| [Ex1901_Physx.cpp](../Ex1901_Physx.cpp#L85) | fixed time step simulation과 result fetch를 수행 |
| [Ex1901_Physx.cpp](../Ex1901_Physx.cpp#L99) | actor shape pose를 render model transform과 constant buffer에 반영 |

## Capture/Result

![Chapter19 PhysX storyboard](../../Docs/_assets/captures/part4_chapter19_01_physx.png)

대표 storyboard는 PhysX actor pose가 render transform으로 동기화된 block wall collapse 결과다. timestamp와 capture 판정은 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | representative visual 1개만 연결 |

## Limitations

- simulation은 fixed `1/60` step을 사용하며 frame-time accumulator를 구현하지 않는다.
- collision event callback, contact impulse 분석과 general gameplay rule은 실행 경로가 아니다.

## Related Docs

- [Animation Physics And Gameplay Integration](../../Docs/01_Topics/AnimationAndPhysics/AnimationPhysicsAndGameplayIntegration.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter19 Ex1901 PhysX Demo](../../Docs/03_Demos/Part4_Chapter14-20/19_01_PhysX.md)