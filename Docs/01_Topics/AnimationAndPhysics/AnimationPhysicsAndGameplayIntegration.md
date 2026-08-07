# Animation Physics And Gameplay Integration

## 목적

Character animation, rigid-body simulation, gameplay input은 서로 다른 update source를 render transform과 visual event에 연결한다. 이 Topic은 animation pose, physics pose, gameplay state의 ownership을 구분하고 frame update에서 render state로 합치는 경계를 설명한다.

## 책임 범위

- skeletal animation, rigid-body simulation, gameplay event가 render state에 반영되는 흐름을 설명한다.
- simulation coordinate와 render coordinate를 맞추는 transform synchronization의 책임을 설명한다.
- asset, animation clip, physics scene 설정과 gameplay parameter는 상세 Demo로 위임한다.
- build/run/capture 사실은 `Docs/02_Verification/Part4_Chapter14-20`의 [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)로 위임한다.
- 구현 흐름과 시각 결과는 `Docs/03_Demos/Part4_Chapter14-20`의 상세 Demo로 위임한다.

## 핵심 개념

### Skeletal Pose Update

Skeletal animation은 clip time에서 bone transform을 계산하고 mesh skinning에 필요한 pose를 갱신한다. render transform은 character 전체의 world transform이고 bone transform은 mesh 내부 deformation에 쓰이므로 두 계층을 구분한다. `Ex1701_SkeletalAnimation`은 animation state와 frame count로 character animation update를 수행한다.

### Physics To Render Synchronization

Rigid-body simulation은 physics scene의 actor pose를 갱신하고 render object는 해당 pose를 world transform으로 반영한다. simulation unit, axis convention, scale이 render world와 다르면 변환을 명시적으로 적용해야 한다. synchronization은 physics 결과를 보여 주는 경계이며 renderer가 physics solver를 대체하지 않는다.

### Gameplay State And Visual Event

Gameplay integration은 input, animation state, physics interaction과 effect spawning을 같은 frame update에서 조정한다. event 발생 시점과 render output을 분리하면 animation transition, rigid-body response, particle effect의 책임을 각각 추적할 수 있다. `Ex2001_GamePlay`는 character animation과 PhysX object update를 gameplay state에 연결한다.

## 한계

- animation blending, inverse kinematics, network replication과 gameplay architecture 전체를 다루지 않는다.
- PhysX solver parameter와 collision filtering의 세부 조정은 다루지 않는다.
- character와 animation runtime asset은 rendered evidence와 구분하며 직접 게시 대상으로 다루지 않는다.

## 관련 문서

- [Part4 Chapter14-20 README](../../../Part4_Chapter14-20/README.md)
- [Chapter17 SkeletalAnimation Demo](../../03_Demos/Part4_Chapter14-20/17_01_SkeletalAnimation.md)
- [Part4 Demo Index](../../03_Demos/Part4_Chapter14-20/demo-index.md)
- [Part4 Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)
- [Animation And Physics Topic Index](topic-index.md)