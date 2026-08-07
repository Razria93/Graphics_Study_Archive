# Chapter17 Ex1701 SkeletalAnimation

## Overview

`Ex1701_SkeletalAnimation`은 character mesh와 FBX animation clip을 분리해 읽고 bone transform을 structured buffer로 전달해 skinned mesh pose를 표시하는 예제다. `Examples.exe 1701`은 runtime character, animation, texture와 HDRI asset을 필요로 하며 원본 asset 대신 rendered storyboard를 evidence로 사용한다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1701`
- Working directory: `Part4_Chapter14-20` source root
- Runtime assets: `Assets/Characters/Mixamo` FBX clips, PBR texture와 HDRI files
- 주요 source: `Ex1701_SkeletalAnimation.cpp`, `SkinnedMeshModel.h`, `AnimationClip.h`
- Shader: skinned mesh pipeline shader

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L89) | command argument `1701`을 `Ex1701_SkeletalAnimation` instance에 연결 |
| [Ex1701_SkeletalAnimation.cpp](../Ex1701_SkeletalAnimation.cpp#L78) | character mesh와 여러 animation clip을 `AnimationData`로 구성 |
| [Ex1701_SkeletalAnimation.cpp](../Ex1701_SkeletalAnimation.cpp#L225) | fixed state와 frame count를 animation update에 전달 |
| [AnimationClip.h](../AnimationClip.h#L117) | bone hierarchy와 root transform을 갱신 |
| [SkinnedMeshModel.h](../SkinnedMeshModel.h#L88) | bone transform을 structured buffer로 upload하고 skinned render resource에 bind |

## Capture/Result

![Chapter17 SkeletalAnimation storyboard](../../Docs/_assets/captures/part4_chapter17_01_skeletal_animation.png)

대표 storyboard는 frame별 bone transform이 skinned vertex pose에 반영된 결과다. animation asset과 timestamp provenance는 상세 Demo와 Verification에 둔다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Release x64 build/run | 성공 | 2026-08-07 smoke, Verification 정본 참조 |
| Capture/Result | tracked storyboard | rendered evidence만 사용 |

## Limitations

- 실행 경로는 fixed `state = 2`와 frame-count 기반 sampling을 사용하며 주석 처리된 motion graph 전환은 적용하지 않는다.
- character, animation FBX, texture와 HDRI 원본 asset은 공개 범위가 아니며 직접 링크하지 않는다.

## Related Docs

- [Animation Physics And Gameplay Integration](../../Docs/01_Topics/AnimationAndPhysics/AnimationPhysicsAndGameplayIntegration.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter17 Ex1701 SkeletalAnimation Demo](../../Docs/03_Demos/Part4_Chapter14-20/17_01_SkeletalAnimation.md)