# Ex1801 Tree

## 목적

`Ex1801_Tree`는 Chapter 18 자연물 렌더링 흐름의 첫 예제로, FBX tree model을 scene에 배치하고 기존 Part4 PBR/IBL rendering path로 렌더링하는 예제입니다.

이 단계의 핵심은 procedural/particle 예제에서 벗어나 실제 foliage asset을 `Model`로 읽어 scene object로 사용하는 것입니다.

## 실행 기준

| 항목 | 값 |
| --- | --- |
| Executable | `Part4_Chapter14-20/x64/<Config>/Examples.exe` |
| Command argument | `1801` |
| Working directory | `Part4_Chapter14-20` |
| Runtime asset | Gledista tree FBX/textures, PBR ground textures, HDRI cubemap |
| Build/run status | 미확인 |
| Public readiness | 검토 필요 |

확인할 동작:

- tree model이 scene에 표시되는지 확인합니다.
- ground plane, skybox/IBL, post processing GUI가 정상 표시되는지 확인합니다.
- Debug/Release x64 모두 command argument `1801`로 확인합니다.

## 주요 파일

| 파일 | 역할 |
| --- | --- |
| `Ex1801_Tree.cpp/.h` | example entry, scene setup, GUI, render path |
| `Model.*`, `ModelLoader.*` | FBX model loading and rendering |
| `BasicVS/PS` 계열 | shared PBR/static mesh shader path |
| `main.cpp` | command argument `1801` mapping |
| `Examples.vcxproj` | source/header registration |

## Runtime Asset

이번 예제는 raw result, capture, build output을 포함하지 않고 실행에 필요한 selected asset만 archive에 반영합니다.

| 경로 | 용도 |
| --- | --- |
| `Assets/Foliage/Gledista_Triacanthos_FBX/Gledista_Triacanthos_3.fbx` | tree model |
| `Assets/Foliage/Gledista_Triacanthos_FBX/gleditsia triacanthos bark2 a1.jpg` | bark base color |
| `Assets/Foliage/Gledista_Triacanthos_FBX/gleditsia triacanthos stem.jpg` | stem texture |
| `Assets/Foliage/Gledista_Triacanthos_FBX/gleditsia triacanthos leaf color a1.jpg` | leaf base color |
| `Assets/Foliage/Gledista_Triacanthos_FBX/gleditsia triacanthos leaf mask.jpg` | leaf alpha mask |
| `Assets/Foliage/Gledista_Triacanthos_FBX/gleditsia triacanthos beans color.jpg` | bean base color |
| `Assets/Foliage/Gledista_Triacanthos_FBX/gleditsia triacanthos beans mask.jpg` | bean alpha mask |
| `Assets/Foliage/Gledista_Triacanthos_FBX/gleditsia triacanthos bark reflect.jpg` | bark reflect/specular texture |
| `Assets/Textures/PBR/stringy-marble-ue/*.png` | ground PBR textures |
| `Assets/Textures/Cubemaps/HDRI/clear_puresky*.dds` | skybox/IBL cubemap textures |

`.fbx`는 repo LFS 추적 대상입니다. `.jpg` foliage textures는 public 공개 전 asset license/source 검토가 필요합니다.

## Import 메모

- `Ex1801_Tree.cpp/.h`는 primary raw `C:\ComputerGraphics\Part4_HongLabGraphics\Examples`와 동일합니다.
- `_2`와 `OriginalExamples/Part4_HongLabGraphics_v03`의 `Ex1801_Tree.cpp`는 archive와 formatting 중심 차이가 있으므로, 이번 archive 기준은 primary raw로 둡니다.
- `Ex1801_Tree.cpp`는 `Gledista_Triacanthos_3.fbx`만 직접 로드합니다.
- FBX가 참조하는 texture filename을 기준으로 필요한 JPG만 선별 반영했습니다.
- `ModelLoader::ReadTextureFilename()`은 filename만 추출해 `basePath + fileName`에서 찾으므로 texture files는 FBX와 같은 folder root에 둡니다.
