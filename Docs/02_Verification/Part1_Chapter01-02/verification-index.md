# Part1_Chapter01-02 Verification Index

이 문서는 `Part1_Chapter01-02` 예제의 build/run/capture 상태를 기록한다. 직접 확인하지 않은 항목은 `미확인`으로 둔다.

| 예제 | solution | Debug build | Debug run | Release build | Release run | Capture | 비고 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `01_DX11InitAndImGui` | `Part1_Chapter01-02/01_DX11InitAndImGui/01_DX11InitAndImGui.sln` | 확인 | 확인 | 확인 | 확인 | 제외 | Debug/Release x64 build/run 확인. 기반 렌더 루프 설명용 예제로 별도 capture는 만들지 않음 |
| `02_Bloom` | `Part1_Chapter01-02/02_Bloom/02_Bloom.sln` | 확인 | 확인 | 확인 | 확인 | 확인 | ChatGPT 생성 입력 이미지로 교체 후 Debug/Release x64 build/run과 `result.png` 생성 확인. result image를 `Docs/_assets/captures`에 승격함 |


## 01_DX11InitAndImGui 검증 기록

| 항목 | 결과 | 확인 내용 |
| --- | --- | --- |
| Debug x64 build | 확인 | MSBuild 17.14, `01_DX11InitAndImGui.vcxproj -> x64/Debug/01_DX11InitAndImGui.exe` 생성 |
| Debug x64 run | 확인 | 실행 후 5초 이상 프로세스 유지, 수동 종료 |
| Release x64 build | 확인 | MSBuild 17.14, `01_DX11InitAndImGui.vcxproj -> x64/Release/01_DX11InitAndImGui.exe` 생성 |
| Release x64 run | 확인 | 실행 후 5초 이상 프로세스 유지, 수동 종료 |
| Capture | 제외 | 기반 렌더 루프 설명용 예제로 별도 capture는 만들지 않음 |

## 02_Bloom 검증 기록

| 항목 | 결과 | 확인 내용 |
| --- | --- | --- |
| Debug x64 build | 확인 | MSBuild 17.14, `02_Bloom.vcxproj -> x64/Debug/02_Bloom.exe` 생성 |
| Debug x64 run | 확인 | 실행 후 5초 이상 프로세스 유지, `result.png` 생성, 종료 코드 0 |
| Release x64 build | 확인 | MSBuild 17.14, `02_Bloom.vcxproj -> x64/Release/02_Bloom.exe` 생성 |
| Release x64 run | 확인 | 실행 후 5초 이상 프로세스 유지, `result.png` 생성, 종료 코드 0 |
| Runtime output | 확인 | `Part1_Chapter01-02/02_Bloom/result.png` 생성. `.gitignore` 기준에 따라 tracked 파일로 추가하지 않음 |
| Capture/Result | 확인 | ChatGPT 생성 입력 이미지 기반 `result.png` 생성 확인. 육안상 강의명/강사명/워터마크/개인 식별자는 보이지 않음. input/result 비교 이미지를 `Docs/_assets/captures`에 승격함 |

## 갱신 기준

- 실제 build/run을 수행한 뒤에만 상태를 `확인`으로 바꾼다.
- 실패한 항목은 숨기지 않고 비고 또는 known issue에 남긴다.
- capture/result는 `Docs/03_Demos`와 `Docs/_assets` 기준에 맞춰 연결한다.
