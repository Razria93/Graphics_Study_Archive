# Import Policy

이 문서는 raw/reference 자료를 Graphics Study Archive로 선별 반영할 때 적용한 import 정책과 규칙을 정의합니다.

## 역할

- 포함/제외 기준의 기준 문서입니다.
- raw/reference, private archive, public subset의 관계를 정의합니다.
- tracked 문서와 local-only 문서의 경계를 정의합니다.
- 실제 작업 순서는 [Import Workflow](02_ImportWorkflow.md)를 따릅니다.
- 작업 전후 확인은 [Import Checklist](03_ImportChecklist.md)를 따릅니다.
- 파일/project/asset 무결성 검증은 [Import Verification](04_ImportVerification.md)을 따릅니다.

## 기본 흐름

```text
raw reference -> private archive -> public subset
```

- raw에서 public으로 직접 이동하지 않습니다.
- raw에서 private archive로도 선별된 자료만 이동합니다.
- public subset은 private archive 정리 후 별도 검토로 선별합니다.

## Raw Reference 기준

- `C:\ComputerGraphics`는 읽기 전용 참고 자료로만 사용합니다.
- raw Part 폴더를 archive로 통째로 복사하지 않습니다.
- 먼저 후보를 조사하고, import manifest를 작성한 뒤, 포함/제외 기준을 확인한 다음에만 파일을 반영합니다.

## 포함 후보

- 실행에 필요한 `.sln`, `.vcxproj`, `.vcxproj.filters`
- 실행에 필요한 source/header/shader 파일
- 실행 재현에 필요한 최소 runtime asset
- 직접 작성하거나 archive 기준으로 재작성한 README/status 문서
- import 당시 포함/제외 판단을 기록한 manifest

## 제외 또는 검토 대상

기본 제외 대상:

- `.vs/`
- `x64/`
- `Debug/`
- `Release/`
- `*.user`
- `*.suo`
- `imgui.ini`
- `.clang-format` project reference
- raw result/capture/video
- build output, runtime output, Visual Studio local state

archive/public 후보로 확정하지 않는 항목:

- 강의 원문 코드
- 강의 원본 영상, 슬라이드, 퀴즈, 정답
- 유료 자료
- 강의 화면 캡처
- 문제/해설 전문
- 강의 고유 구조를 그대로 재현한 문서
- 출처/라이선스가 불명확한 asset
- private-only 개인 메모, 계정 정보, 로컬 절대 경로

## Asset 기준

- 외부 asset은 출처와 라이선스가 불명확하면 `검토 필요`로 둡니다.
- 실행에 꼭 필요한 asset만 선별 반영합니다.
- binary asset은 text 변환 대상이 아니며, raw와 hash를 비교해 무결성을 확인합니다.
- public 공개 여부는 import 단계에서 확정하지 않습니다.

## Source Comment 기준

- 기존 장문 학습 주석은 source에서 제거하거나 local-only 문서로 분리합니다.
- 코드에 남길 주석은 섹션 구분, 구현 의도, lifetime/path 주의 정도로 제한합니다.
- 이해 과정, 질문, 장문 이론 메모, raw 문서 원문은 tracked source가 아니라 local-only 문서나 재작성된 archive 문서로 분리합니다.

## Tracked / Local-only 기준

Tracked 문서에는 다음을 둡니다.

- 예제 목적
- 핵심 키워드
- 관련 이론/원리 요약
- 핵심 코드 흐름과 짧은 코드 조각
- build/run 상태
- capture 준비 상태
- 공개 가능성 상태
- import manifest

Local-only 문서에는 다음을 둡니다.

- 소스코드에 있던 사용자 메모 원문
- raw repo 관련 `.md` 문서 원문 또는 위치
- 이미지 누락 파일명과 위치
- 메모의 의도, 오류 가능성, 보완점 검토
- GitHub PR 초안과 원문 사본

`local/`은 `.gitignore` 대상이므로 private 작업 재료 보관용으로 사용합니다.

## Commit / PR Draft 기준

- commit은 사용자가 명시적으로 요청할 때만 수행합니다.
- import 작업 중 PR 초안이나 원문 사본이 필요하면 tracked Docs가 아니라 `local/` 계열에 둡니다.
- 기존 tracked PR summary 문서는 폐기했습니다. import 단계의 판단 근거는 [Manifests](Manifests/)를 기준으로 봅니다.
