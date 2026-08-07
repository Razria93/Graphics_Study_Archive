# Part4 Chapter17 Skeletal Animation Demo

## 요약

Chapter17은 character mesh와 animation clip을 분리해 읽고, frame별 bone transform을 GPU structured buffer로 전달하는 skeletal animation evidence다. 대표 visual은 `Ex1701_SkeletalAnimation` 시연 video에서 선택한 timestamp frame 3개를 배치한 storyboard로 구성한다. character mesh, animation FBX, texture와 HDRI 원본 asset은 직접 게시하지 않고 rendered storyboard만 사용한다.

## 핵심 목표

- Character mesh와 FBX animation clip을 분리해 하나의 animation data set으로 구성
- Bone hierarchy, clip key, root motion과 frame index 기반 animation update 연결
- Bone transform structured buffer upload와 skinned mesh render path 기록

## Demo Assets

| 구분 | 파일 | 설명 |
| --- | --- | --- |
| Input screenshot | 없음 | 별도 입력 screenshot을 사용하지 않음 |
| Result screenshot | 없음 | 단일 screenshot 대신 timestamp storyboard를 사용함 |
| Result image | Chapter17 storyboard 1장 | 0.800s, 2.500s, 4.300s frame을 배치한 skeletal pose evidence |
| Video | 없음 | GitHub attachment URL을 아직 게시하지 않음 |

## 시각 정보

### Skeletal pose progression

`Ex1701_SkeletalAnimation`은 현재 clip과 frame index를 기준으로 bone hierarchy를 갱신하고, skinned vertex shader가 업로드된 bone transform을 사용해 pose를 표시한다. Storyboard는 0.800s, 2.500s, 4.300s frame을 순서대로 기록한다.

![Skeletal pose progression](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/_assets/captures/part4_chapter17_01_skeletal_animation.png?raw=true)

## 구현 하이라이트

### Animation clip and bone hierarchy

`ModelLoader`는 vertex deformation에 참여하는 bone을 root부터 child 순서로 index화하고, clip channel의 position, rotation, scale key를 bone index별 배열에 저장한다. `AnimationData::Update`는 parent transform을 반영해 hierarchy를 갱신하고 root motion을 accumulated root transform으로 분리한다.

- [Animation clip key 추출](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/ModelLoader.cpp#L72-L197)
- [Bone hierarchy와 root motion 갱신](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/AnimationClip.h#L117-L191)

### Skinned render resource binding

`SkinnedMeshModel`은 frame별 bone transform을 transpose해 structured buffer에 업로드하고, render 시 vertex shader resource slot `9`에 연결한다. Visual frame의 pose 차이는 camera 또는 material 변경이 아니라 animation clip key와 hierarchy transform이 skinned vertex에 반영된 결과다.

- [Frame count 기반 animation update](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/Ex1701_SkeletalAnimation.cpp#L225-L232)
- [Bone transform upload와 skinned render binding](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/SkinnedMeshModel.h#L88-L125)

### 처리 흐름

1. `Examples.exe` command argument `1701`로 skeletal animation 예제를 선택한다.
2. Character mesh와 여러 animation clip을 읽어 `AnimationData` clip 목록을 만든다.
3. 현재 state와 frame count가 clip key sampling과 bone hierarchy update를 결정한다.
4. Bone transform structured buffer를 vertex shader에 연결한다.
5. Skinned pipeline이 vertex별 bone weight와 transform을 사용해 current pose mesh를 렌더링한다.

## 핵심 로직 의사코드

```cpp
// Pseudo C++
void UpdateSkeletalAnimationPseudo(int state, int frameCount)
{
	AnimationClip& clip = animationData.clips[state];
	SampleClipKeys(clip, frameCount);
	UpdateBoneHierarchyFromParents();
	ExtractAccumulatedRootMotion();
	UploadBoneTransformsToStructuredBuffer();
	RenderSkinnedMeshWithBoneWeights();
}
```

원본 코드: [Animation update와 skinned render binding](https://github.com/Razria93/Graphics_Study_Archive/blob/7fbaccfee1180e5686b29aea663ebcaa283ef4e8/Part4_Chapter14-20/SkinnedMeshModel.h#L88-L125)

## 검증 상태

- `Part4_Chapter14-20/Examples.sln` Debug x64 build/run/capture smoke 성공
- `Part4_Chapter14-20/Examples.sln` Release x64 build/run/capture smoke 성공
- Storyboard PNG는 `ComputerGraphics` title, 01부터 03까지 timestamp frame, full decode와 text metadata chunk 부재를 확인함

## 구현 범위와 한계

- 현재 예제는 `state = 2`를 사용해 한 animation state를 frame count로 반복 재생한다.
- Frame count는 frame-rate independent time sampling이 아니며 clip key index 기반으로 순환한다.
- Storyboard는 local-only MP4에서 선별한 pose frame이며 연속 animation과 input transition 전체를 대체하지 않는다.
- Character mesh, animation FBX, texture와 HDRI 원본 asset은 첨부하거나 직접 링크하지 않는다.
- 원본 MP4와 raw preview는 Git에 추가하지 않는다.

## 관련 문서

- [Part4 Chapter14-20 README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Part4_Chapter14-20/README.md)
- [Ex1701 SkeletalAnimation 상세 Demo](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/03_Demos/Part4_Chapter14-20/17_01_SkeletalAnimation.md)
- [Chapter17 Verification](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Animation Physics And Gameplay Topic](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part4-chapter14-20-workflow/Docs/01_Topics/AnimationAndPhysics/AnimationPhysicsAndGameplayIntegration.md)