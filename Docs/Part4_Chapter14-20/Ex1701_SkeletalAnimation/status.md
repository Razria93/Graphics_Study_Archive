# Ex1701 SkeletalAnimation Status

## Assimp 6.x compatibility result

- Assimp 6.x FBX import에서 `_$AssimpFbx$_Translation/Rotation` helper node가 생성되며 skeletal hierarchy가 예제 코드의 기대와 달라지는 문제가 있었습니다.
- `ModelLoader::Load()`와 `ModelLoader::LoadAnimation()`에 `AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS=false`를 적용해 단순 bone hierarchy로 읽도록 보정했습니다.
- 사용자 확인 기준으로 Debug x64 / Release x64 모두 캐릭터 형태와 animation 재생이 정상입니다.
- 상세 기록: [`assimp-6x-fbx-pivot.md`](assimp-6x-fbx-pivot.md)

## Final execution confirmation

- Debug x64: 사용자 실행 확인 완료
- Release x64: 사용자 실행 확인 완료
- 확인 기준: command argument `1701`, 최소 변경 상태(`AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS=false` only)에서 캐릭터 형태와 skeletal animation 정상 재생

## 현재 상태

| 항목 | 상태 |
| --- | --- |
| Code import | 보정 반영 |
| Build Debug x64 | 성공 |
| Run Debug x64 | 성공 |
| Build Release x64 | 성공 |
| Run Release x64 | 성공 |
| Runtime asset | 반영 완료 |
| Public readiness | 검토 필요 |

## 확인한 내용

- `main.cpp`는 command argument `1701`을 `Ex1701_SkeletalAnimation`으로 매핑합니다.
- `Examples.vcxproj`에는 `Ex1701_SkeletalAnimation.cpp/.h`, `AnimationClip.h`, `SkinnedMeshModel.h`, `SkeletalMeshActor.h`가 등록되어 있습니다.
- Ex1701 source/header files는 primary raw hash와 일치합니다.
- Ex1701은 Mixamo character/animation FBX, character texture PNG, PBR ground texture PNG, clear puresky HDRI DDS를 runtime asset으로 요구합니다.
- 필요한 runtime asset만 archive에 선별 반영했습니다.
- `.fbx`와 `.dds`는 LFS 추적 대상입니다.
- `.png` texture는 현재 LFS 추적 대상이 아니므로 public 공개 전 license/source와 용량 검토가 필요합니다.
- raw result/capture/build output은 포함하지 않았습니다.

## 실행 확인 기준

1. Visual Studio에서 `Part4_Chapter14-20/Examples.sln`을 엽니다.
2. `Examples` project의 `Debugging > Command Arguments`를 `1701`로 설정합니다.
3. Debug x64에서 build/run합니다.
4. Release x64에서 build/run합니다.
5. character model과 skeletal animation이 표시되는지 확인합니다.
6. ground, mirror/reflection, skybox/IBL이 함께 표시되는지 확인합니다.
7. GUI가 표시되고 material/mirror/post processing/env map 항목이 조작 가능한지 확인합니다.

## 보류 항목

- public 공개 가능 여부는 Mixamo/PBR/HDRI asset license/source 검토 후 판단합니다.
