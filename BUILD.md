# 빌드 가이드

## 기준 환경

| 항목 | 기준 |
| --- | --- |
| OS | Windows |
| IDE | Visual Studio |
| Graphics API | DirectX11 |
| Platform | x64 |
| Configurations | Debug x64, Release x64 |

## 빌드 기준

각 예제는 독립적인 Visual Studio solution을 기준으로 확인합니다. private archive 정리 과정에서 폴더명을 바꾼 경우, 빌드 실패 시 `.sln`, `.vcxproj`, shader path, asset path 중 어느 항목이 기존 경로에 의존하는지 먼저 확인합니다.

## 권장 확인 순서

1. 대상 예제 폴더의 `.sln`을 Visual Studio로 엽니다.
2. `Debug x64`를 먼저 빌드합니다.
3. 대표 예제는 `Release x64`도 확인합니다.
4. 실행 화면, shader/asset 경로, UI 상태를 확인합니다.
5. 결과를 [DEMOS.md](DEMOS.md) 또는 [Docs/build-guide.md](Docs/build-guide.md)에 기록합니다.

## 커밋 제외 대상

- `.vs/`
- `x64/`, `x86/`, `Debug/`, `Release/`
- `*.user`, `*.suo`
- `imgui.ini`

## 현재 검증 상태

아직 학습 코드가 archive에 정리되지 않았으므로 빌드/실행은 미확인입니다. 최초 검증 대상은 [Docs/build-guide.md](Docs/build-guide.md)의 P0 표를 기준으로 진행합니다.
