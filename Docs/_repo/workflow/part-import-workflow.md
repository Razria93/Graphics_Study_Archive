# Part Import 작업 방식

이 문서는 raw/reference repo의 Part 예제를 private archive로 정리할 때 반복해서 따를 실제 작업 순서를 기록합니다.

대상 흐름은 `C:\ComputerGraphics` raw/reference에서 `C:\Graphics_Study_Archive` private archive로 선별 이동하는 것입니다. public repo 구성은 이 단계에서 하지 않습니다.

예제 문서는 산출물 종류별 폴더가 아니라 `Docs/Part*_Chapter*/ExampleName/README.md`에 정리합니다. 원문 메모와 draft는 `local/`에 두고, 실제 캡처/영상 파일은 필요할 때 `Docs/_assets/` 아래에 둡니다.

## 기본 원칙

- `C:\ComputerGraphics`는 읽기 전용 참고 자료로만 사용합니다.
- raw Part 폴더를 archive로 통째로 복사하지 않습니다.
- 먼저 후보를 조사하고, manifest를 만든 뒤, 포함/제외 기준을 확인한 다음에만 파일을 옮깁니다.
- 강의 원문 코드, 강의 원본 영상, 슬라이드, 퀴즈, 정답, 유료 자료, 강의 화면 캡처, 문제/해설 전문은 archive/public 후보로 확정하지 않습니다.
- 출처나 라이선스가 불명확한 asset은 `검토 필요`로 둡니다.
- 빌드/실행을 직접 확인하지 않은 항목은 `미확인`으로 기록합니다.

## 작업 순서

1. Raw Part 구조 확인
   - raw 폴더의 최상위 구조를 읽습니다.
   - `.sln`, `.vcxproj`, shader, asset, capture/video 후보 위치를 확인합니다.
   - `.vs/`, `x64/`, `Debug/`, `Release/`, `.user`, `imgui.ini` 같은 제외 대상을 확인합니다.

2. Import manifest 작성
   - 실제 복사 전에 포함/제외 파일 목록을 문서로 남깁니다.
   - manifest에는 source, target, include patterns, exclude patterns, unresolved risks를 적습니다.
   - manifest 작성만으로는 파일을 복사하지 않습니다.

3. 선별 복사
   - manifest 기준으로 필요한 파일만 archive Part 폴더에 복사합니다.
   - build output, Visual Studio local state, raw-only 자료는 제외합니다.
   - 외부 asset은 출처와 라이선스가 불명확하면 복사하지 않거나 `검토 필요`로 분리합니다.

4. 경로 의존성 점검
   - `.sln`, `.vcxproj`, shader path, asset path가 raw 경로에 의존하는지 확인합니다.
   - archive 폴더명 변경으로 깨질 수 있는 상대 경로를 기록합니다.
   - 확인 전에는 build/run 상태를 `미확인`으로 둡니다.

5. Source/comment 정리
   - 기존 장문 학습 주석은 제거하고 필요한 내용은 note로 재작성합니다.
   - 코드에는 섹션 구분, 구현 의도, lifetime/path 주의처럼 유지보수에 필요한 주석만 남깁니다.
   - 코드 동작을 바꾸는 리팩터링은 별도 build/run 확인 단위로 진행합니다.

6. Build/run 확인
   - Visual Studio에서 `Debug x64`를 먼저 확인합니다.
   - 대표 예제만 `Release x64`를 추가 확인합니다.
   - 실패하면 실패 원인과 다음 조치를 [build-guide.md](../tracking/build-guide.md)에 기록합니다.
   - Part4 `Examples` project는 단일 executable이므로 예제 이름의 `Ex` 뒤 4자리 숫자를 Visual Studio `Debugging > Command Arguments`에 넣어 실행합니다. 예: `Ex1401_Basic`은 `1401`, `Ex1402_Blur`는 `1402`.

7. Demo/capture 정리
   - raw capture를 그대로 가져오지 않습니다.
   - archive 기준으로 직접 실행한 결과를 새로 캡처합니다.
   - 강의 화면, 슬라이드, 유료 자료, 문제/해설 캡처는 제외합니다.

8. 상태 갱신
   - Part README의 `Archive/Public 검토` 표를 갱신합니다.
   - [migration-board.md](../tracking/migration-board.md)의 해당 row를 갱신합니다.
   - public 공개 가능성은 [public-readiness.md](public-readiness.md)를 기준으로 판단합니다.

## Part1 Chapter01-02 시작 기준

첫 실제 작업 대상은 `Part1_Chapter01-02`입니다.

| 항목 | 값 |
| --- | --- |
| Raw reference | `C:\ComputerGraphics\Part1_Chapter01-02` |
| Archive target | `Part1_Chapter01-02` |
| 우선 후보 | `01_DX11InitAndImGui`, `02_Bloom` |
| Import status | 검토 필요 |
| Public readiness | 검토 필요 |
| Build/run status | 미확인 |

다음 작업은 raw 구조를 조사하고 `Part1_Chapter01-02`용 import manifest를 작성하는 것입니다. 파일 복사는 manifest 확인 뒤 별도 단계에서 진행합니다.

## Manifest 템플릿

```md
# Import Manifest: Part Name

## Source / Target

- Source:
- Target:
- Import status:
- Public readiness:
- Build/run status:

## Include candidates

- 

## Exclude patterns

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`

## Unresolved risks

- Asset/license:
- Path dependency:
- Private-only notes:

## Next action

- 
```
