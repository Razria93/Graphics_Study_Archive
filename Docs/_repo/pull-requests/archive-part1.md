# PR: Part1 graphics examples archive import

## Title

```text
docs: Part1 graphics examples archive import
```

## Body

## 요약

- Part1 Chapter01-02 DirectX11 initialization / ImGui / Bloom 예제를 private archive 기준으로 import했습니다.
- Part1 Chapter03 CPU ray tracing step examples를 private archive 기준으로 import했습니다.
- 예제별 README/status, Part1 import manifest, build/run tracking, migration board를 갱신했습니다.
- STB header dependency를 repo에 vendoring해 clean checkout build 재현성을 보강했습니다.
- source/project import와 실행 확인 기록을 우선 정리했고, 문서 전체 재정리는 이후 code import 완료 후 Part1부터 일괄 진행합니다.

## 범위

- Part:
  - `Part1_Chapter01-02`
  - `Part1_Chapter03`
- Docs:
  - `Docs/Part1_Chapter01-02`
  - `Docs/Part1_Chapter03`
  - `Docs/_repo/manifests/Part1_Chapter01-02.md`
  - `Docs/_repo/manifests/Part1_Chapter03.md`
  - `Docs/_repo/tracking/build-guide.md`
  - `Docs/_repo/tracking/migration-board.md`
  - `Docs/_repo/reference/raw-to-archive-map.md`
  - workflow docs for chapter start and migration process
- Dependency:
  - `ThirdParty/stb`
- Captures/videos:
  - 보류
- Build checks:
  - 사용자 Visual Studio Debug x64 / Release x64 build-run 확인 결과를 문서에 기록

## 주요 변경

- Chapter01-02 examples:
  - `01_DX11InitAndImGui`
  - `02_Bloom`
- Chapter03 ray tracing examples:
  - Step4 DrawingSphere
  - Step5 PhongShading
  - Step6 PerspectiveView
  - Step7 Triangle
  - Step8 Shadow
  - Step8 Shadow Square variant
  - Step9 BarycentricCordinates
  - Step10 Texturing
  - Step11 Supersampling
  - Step12 Reflection
  - Step13 Transparency
  - Step14 CubeEnvironment
- Project fixes / archive adjustments:
  - excluded `.vs/`, generated folders, `.vcxproj.user`, build outputs, runtime outputs, local-only notes
  - preserved required source/header/shader/assets for executable examples
  - recorded Step14 cube environment issue and final output implementation state
  - vendored STB headers so Bloom/Texturing examples do not depend on untracked global include state
  - added archive PR review scope limits to keep review focused on migration blockers
- Local-only study review documents remain under ignored `local/` and are not part of this PR.

## 체크리스트

- [x] README 갱신
- [x] Notes/status 추가 또는 갱신
- [x] Import manifest 갱신
- [x] Build guide 갱신
- [x] Migration board 갱신
- [x] Raw-to-archive map 갱신
- [x] 필요한 dependency vendoring 반영
- [ ] Demo index 갱신
- [ ] Topic index 갱신
- [ ] 사용 가능한 captures/videos 링크 연결
- [x] build output 또는 local state files 미포함

## Build / Run

- 확인한 예제:
  - `Part1_Chapter01-02` archive 대상 예제 Debug/Release 실행 확인
  - `Part1_Chapter03` Step4-Step14 archive 대상 예제 Debug/Release 실행 확인
- Known issues:
  - captures/videos는 보류
  - public readiness는 전체적으로 `검토 필요`
  - Step14 cube/environment 관련 이슈는 문서에 기록했고, archive 실행 상태는 확인 완료
  - texture/cubemap assets는 public 공개 전 별도 license/attribution 검토 필요
  - 문서 품질/최종 포트폴리오 문서화는 code import 완료 후 Part1부터 일괄 재정리 예정

## Review Scope

이 PR은 production code review가 아니라 private study/archive migration입니다.

리뷰는 아래 blocking archive issue로 제한합니다.

- clean checkout에서 빌드가 불가능한 경우
- 실행에 필요한 source/header/asset 파일이 누락된 경우
- build output, runtime output, local-only 파일이 실수로 포함된 경우
- private/course-only 자료가 실수로 포함된 경우
- README/status/build tracking 문서가 실제 repo 상태와 모순되는 경우

리뷰 제외 대상:

- 알고리즘 재작성
- 그래픽스 기법 개선 제안
- 코드 스타일/네이밍 취향
- 리팩터링 제안
- 성능 최적화
- 명시된 risk marker 이상의 public 공개성 판단
- capture/video 완료 여부
- 최종 포트폴리오 문서 품질

## 후속 작업

- Part2 import 브랜치로 이동
- code import 완료 후 Part1부터 문서 전체 재정리
- capture/video 촬영 및 demo index 갱신
- public subset 후보는 private archive 정리 완료 후 별도 repo 기준으로 선별
