# Ex1701 Assimp 6.x FBX Pivot Compatibility

## 문제 요약

`Ex1701_SkeletalAnimation`에서 Mixamo 캐릭터가 사람 형태로 보이지 않고 뭉개진 형태로 렌더링되는 문제가 있었다.

처음에는 skeletal animation 구현, bone index, animation channel binding, Assimp 버전 차이, asset 문제를 의심했다. 최종 원인은 Assimp 6.x의 FBX pivot 보존 방식과 예제 코드가 기대하는 단순 skeleton hierarchy 사이의 불일치였다.

## 증상

- `1701` 실행 시 캐릭터가 사람 형태가 아니라 뭉개진 덩어리처럼 보였다.
- 캐릭터가 바닥 기준으로 자연스럽게 걷지 않고, 잘못된 위치/자세로 움직였다.
- build 자체는 성공했고, texture와 scene rendering도 진행되었다.
- asset을 교체하거나 raw 파일을 다시 비교해도 source import 누락 문제로 보이지 않았다.

## 원인

Assimp 6.x는 FBX를 읽을 때 pivot/pre-rotation/offset 같은 FBX transform stack을 보존하기 위해 helper node를 scene graph에 삽입할 수 있다.

문제 상황에서는 skeleton hierarchy가 다음처럼 읽혔다.

```text
mixamorig:Hips
  mixamorig:Spine_$AssimpFbx$_Translation
    ...
```

또는 animation channel 이름이 다음처럼 들어왔다.

```text
mixamorig:Spine_$AssimpFbx$_Rotation
mixamorig:LeftUpLeg_$AssimpFbx$_Translation
```

하지만 이 예제 코드는 다음과 같은 단순 bone hierarchy를 전제로 한다.

```text
mixamorig:Hips
  mixamorig:Spine
  mixamorig:LeftUpLeg
  mixamorig:RightUpLeg
```

스켈레탈 애니메이션은 parent transform을 누적해서 child bone의 최종 위치와 방향을 정한다. helper node가 중간에 생기면 해당 helper transform layer까지 누적해야 정상이다. 기존 예제 코드는 deforming bone 이름을 기준으로 skeleton을 구성하므로, 중간 helper node의 transform layer가 계산에서 빠질 수 있다.

결과적으로 `Hips -> Spine`처럼 이름은 이어진 것처럼 보이지만, 실제로는 `Hips`와 `Spine` 사이에 있었어야 할 FBX pivot/translation/rotation layer가 누락되어 최종 bone transform이 잘못 계산된다.

## 해결 방법

모델과 animation clip을 읽는 양쪽 `Assimp::Importer`에 아래 옵션을 설정한다.

```cpp
importer.SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);
```

이를 위해 `ModelLoader.h`에 다음 include가 필요하다.

```cpp
#include <assimp\config.h>
```

적용 위치:

- `ModelLoader::Load()`
- `ModelLoader::LoadAnimation()`

두 경로 모두 동일한 FBX import 정책을 사용해야 base character model과 animation FBX의 skeleton/channel 구조가 서로 맞는다.

## 적용 후 확인 결과

옵션 적용 후 helper node가 사라지고 예제 코드가 기대하는 hierarchy로 읽혔다.

```text
mixamorig:Hips
  mixamorig:Spine
  mixamorig:LeftUpLeg
  mixamorig:RightUpLeg
```

진단 시 확인한 상태:

```text
missingChannels=0
normalizedChannels=0
mismatchedKeyCounts=0
```

사용자 실행 확인 결과:

- Debug x64: 정상 렌더링 확인
- Release x64: 정상 렌더링 확인
- 캐릭터가 사람 형태로 표시되고 animation이 정상 재생됨

## 왜 다른 실험은 제거했는가

초기 조사 중에는 다음 실험도 시도했다.

- `_$AssimpFbx$_` suffix를 제거해서 animation channel name을 base bone name으로 정규화
- position/rotation/scale key count가 다른 channel을 병합
- missing channel 진단 로그 추가

하지만 최종적으로 `AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS=false`만 적용하면 Assimp가 helper node를 생성하지 않고, channel/key 구조도 예제 코드가 기대한 형태로 돌아온다.

따라서 archive에는 진단용 코드나 channel 병합 코드를 남기지 않고, import option만 최소 변경으로 유지한다.

## 비유

예제 코드는 단순 pipeline을 기대한다.

```text
Hips -> Spine -> Spine1
```

Assimp 6.x가 pivot을 보존하면 중간 단계가 추가된다.

```text
Hips -> Spine_$AssimpFbx$_Translation -> Spine_$AssimpFbx$_Rotation -> Spine
```

중간 단계를 처리하지 않는 코드에서 이 구조를 그대로 사용하면, pipeline 중간 stage를 건너뛰는 것처럼 transform 누적이 깨진다. 이번 해결은 중간 stage를 직접 구현한 것이 아니라, Assimp에게 예제 코드가 기대하는 단순 hierarchy로 접어서 읽도록 지시한 것이다.

## 재발 방지

Part4에서 Assimp로 FBX skeletal animation을 읽는 예제를 추가하거나 수정할 때는 다음을 확인한다.

- `Assimp::Importer`가 model과 animation clip 양쪽에서 동일한 import property를 사용하는가
- FBX import 결과에 `_$AssimpFbx$_` helper node/channel이 섞이지 않는가
- helper node를 보존해야 하는 경우, skeleton hierarchy update에서 해당 transform layer까지 누적하는 코드가 있는가
- 단순 강의 예제 재현 목적이라면 `AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS=false`를 우선 검토한다
