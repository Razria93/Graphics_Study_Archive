# Session Troubleshooting Notes

이 문서는 archive migration 작업 중 반복될 수 있는 시행착오를 줄이기 위한 기록입니다. 새 예제 import 전에 빠르게 확인하는 용도이며, 법적 판단이나 최종 문서가 아니라 작업 메모에 가깝습니다.

## 기본 확인

- 작업 전 `git status --short --branch`로 branch와 clean 여부를 확인합니다.
- raw repo `C:\ComputerGraphics`는 읽기 전용 reference로만 사용합니다.
- archive에는 source/project/shader/실행 필수 asset만 선별 반영합니다.
- build/run은 사용자가 직접 확인하기 전까지 `미확인`으로 둡니다.
- local-only 문서는 `local/` 아래에 두고 commit하지 않습니다.

## Raw Copy 권한 문제

증상:

- raw에서 복사한 파일이 archive 내부에 있는데도 일반 shell/write 또는 `apply_patch` 수정이 실패합니다.
- `Access denied`, `UnauthorizedAccessException`, parent directory creation denied가 발생합니다.

대응:

- 복사 직후 archive 복사본의 file attribute를 확인합니다.
- source 정리 전에 read-only 속성 해제가 필요한지 확인합니다.
- 권한 문제로 막히면 archive 내부 대상에 한정해서 승인된 명령으로 속성 해제 또는 쓰기 작업을 진행합니다.
- raw repo 원본에는 쓰지 않습니다.

## Source Comment Split

증상:

- raw source에 장문 학습 메모, 출력 결과 주석, 강의 안내용 주석이 많이 남아 있습니다.

대응:

- archive source에는 실행 흐름 이해에 필요한 짧은 주석만 남깁니다.
- 원문 메모와 문맥은 `local/<Part>/<Example>/source-comments.md`에 분리합니다.
- 관련 raw `.md` 문서 검토 내용은 `local/<Part>/<Example>/study-review.local.md`에 기록합니다.
- source comment 제거 후 `rg -n "//|/\*|\*/"`로 잔여 주석을 확인합니다.

## Project File Checks

증상:

- 실제 파일은 제외했는데 `.vcxproj`나 `.filters`에 `.clang-format`, `.user`, 제거된 asset 참조가 남아 있습니다.
- Debug는 되지만 Release에서 shader compile 설정이 달라 실패할 수 있습니다.

대응:

- import 후 `.vcxproj`와 `.vcxproj.filters`에서 제외 파일 참조를 확인합니다.
- `.clang-format`, `.vcxproj.user`, `imgui.ini`, build output 참조는 제거합니다.
- `BasicPixelShader.hlsl`, `BasicVertexShader.hlsl`의 Debug/Release x64 shader type을 확인합니다.
- `Common.hlsli` 같은 include shader는 build 대상이 아니라 문서/include 파일로 유지되는지 확인합니다.

## Part4 Command Argument

증상:

- Part4에서 빌드는 성공하지만 예상한 예제가 실행되지 않습니다.
- 비슷한 이름의 다른 solution/project를 열어 놓고 실행 결과를 비교하게 됩니다.
- Debug에서는 맞는 예제가 뜨는데 Release에서는 다른 예제나 기본 실행 흐름으로 보입니다.

대응:

- `Part4_Chapter14-20/Examples.sln`을 열었는지 먼저 확인합니다.
- `Examples` project의 `Debugging > Command Arguments`에 `Ex` 뒤 4자리 숫자를 입력합니다.
- Debug x64와 Release x64를 각각 확인할 때 같은 command argument가 유지되는지 확인합니다.
- 예: `Ex1401_Basic`은 `1401`, `Ex1701_SkeletalAnimation`은 `1701`, `Ex2001_GamePlay`는 `2001`입니다.

## Part4 Runtime/Dependency Issues

증상:

- character mesh가 뭉개지거나 skeleton hierarchy가 예상과 다르게 보입니다.
- `.fbx`, `.dds`, `.hdr`, `.raw` 같은 runtime asset이 없어서 build는 되지만 실행 중 실패합니다.
- simulation-heavy 예제에서 frame rate가 크게 낮게 나옵니다.

대응:

- Ex1701 계열 skeletal animation 문제는 Assimp 6.x FBX pivot helper node 생성 여부를 먼저 확인합니다.
- 현재 archive 기준은 `AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS=false` 최소 보정을 사용합니다.
- runtime asset은 raw 폴더 전체가 아니라 예제 실행에 필요한 파일만 선별하고, LFS 대상 확장자는 `.gitattributes` 기준을 확인합니다.
- 성능 민감 예제는 정상 출력 여부와 기본 조작 가능 여부를 우선 확인하고, 해상도/grid size 조정은 별도 변경으로 기록합니다.

## Document Encoding / Patch Issues

증상:

- PowerShell 출력에서 UTF-8 한글이 깨져 보입니다.
- 기존 문서가 이미 깨진 상태라 단순 라인 수정이 어렵습니다.
- `apply_patch`가 기존 파일 삭제/교체에서 실패합니다.

대응:

- VSCode/GitHub 표시를 기준으로 파일 인코딩을 최종 확인합니다.
- 큰 문서 교체보다 작은 패치로 나눠 적용합니다.
- 기존 문서 전체가 깨져 있으면 최소 상태표 중심으로 정상화합니다.
- 문서 내용은 과하게 늘리지 말고, import/run tracking에 필요한 정보만 남깁니다.

## Static Verification

예제 import 후 최소 확인:

```powershell
git status --short --branch
rg --files <archive-example-path>
rg -n "//|/\*|\*/" <archive-example-path> -g "*.cpp" -g "*.h" -g "*.hlsl" -g "*.hlsli"
rg -n "\.user|imgui\.ini|\.clang-format|x64|Debug|Release|result|capture" <archive-example-path>
git diff --check
```

주의:

- `.sln`/`.vcxproj` 내부의 `Debug`, `Release`, `x64` 문자열은 정상 configuration일 수 있습니다.
- raw result/capture나 build output 경로가 실제 파일로 들어왔는지를 우선 확인합니다.

## Commit Rhythm

- 예제 import commit: source/project/shader/asset 반영.
- 문서 commit: README/status/manifest/tracking 반영.
- 실행 확인 commit: 사용자가 Debug/Release 실행을 확인한 뒤 성공/실패 상태만 갱신.
- Part 마지막에는 old local docs와 tracked docs 품질을 한 번에 보강합니다.

## Next Example Checklist

1. raw 예제 폴더와 관련 raw docs를 확인합니다.
2. import 대상/제외 대상을 먼저 분류합니다.
3. archive로 복사한 뒤 권한/속성을 확인합니다.
4. source 주석을 local-only 문서로 분리합니다.
5. `.vcxproj`와 `.filters`의 제외 파일 참조와 shader 설정을 확인합니다.
6. README/status/manifest/tracking을 최소 갱신합니다.
7. 정적 검증 후 source/docs 커밋을 분리합니다.
