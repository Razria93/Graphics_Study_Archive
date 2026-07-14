# PR: Part3 Interaction/Advanced Rendering archive import 정리

## Title

```text
docs: Part3 Interaction/Advanced Rendering archive import 정리
```

## Body

## 요약

- Part3 Chapter09 user interaction 예제를 private archive 기준으로 import했습니다.
- Part3 Chapter10-13 geometry pipeline, texturing techniques, PBR, light/shadow 예제를 private archive 기준으로 import했습니다.
- 예제별 README/status, Part3 import manifests, build/run tracking, migration board를 갱신했습니다.
- source/project import와 사용자 Debug/Release 실행 확인 기록을 우선 정리했고, 학습 문서의 세부 재작성은 이후 code import 완료 후 일괄 진행합니다.

## 범위

- Part:
  - `Part3_Chapter09`
  - `Part3_Chapter10-13`
- Docs:
  - `Docs/Part3_Chapter09`
  - `Docs/Part3_Chapter10-13`
  - `Docs/_repo/manifests/Part3.md`
  - `Docs/_repo/manifests/Part3_Chapter09.md`
  - `Docs/_repo/manifests/Part3_Chapter10-13.md`
  - `Docs/_repo/tracking/build-guide.md`
  - `Docs/_repo/tracking/migration-board.md`
  - `Docs/_repo/reference/raw-to-archive-map.md`
- Captures/videos:
  - 보류
- Build checks:
  - 사용자가 Visual Studio Debug x64 / Release x64 build-run 확인

## 주요 변경

- Chapter09 examples:
  - FirstPersonView, MousePicking, MousePickingRayCollision, QuaternianRotation, VirtualTrackball, MouseDragMove import
  - `_Debug` variant는 제외하고, 필요한 경우 `_Solution` 기준 구현만 선별 반영
- Chapter10-13 examples:
  - Geometry pipeline: geometry shader, billboards, normal lines, fireball, tessellation
  - Texturing techniques: mipmaps, normal mapping, height mapping, HDRI, HDR pipeline
  - PBR: UnrealPBR, PBRModels
  - Light and shadow: mirror, pipeline state object, shadow, depth/fog, shadow mapping, PCF, PCSS, halo, sphere light
- Project fixes / archive adjustments:
  - tracked build output/local state file 없음 확인
  - `.clang-format` project reference 제거 확인
  - HLSL/HLSLI BOM 없음 확인
  - Release x64 shader model `5.1` 잔여 설정을 `5.0`으로 통일
  - raw/origin/reference 차이 중 사용자 구현 또는 메모가 있는 파일은 primary raw 기준으로 보존
- Local-only study review documents remain under ignored `local/` and are not part of this PR.

## 체크리스트

- [x] README 갱신
- [x] Notes/status 추가 또는 갱신
- [x] Import manifest 갱신
- [x] Build guide / migration board 갱신
- [x] Raw-to-archive map 갱신
- [x] HLSL/HLSLI BOM 확인
- [x] `.vcxproj` XML parse 확인
- [x] tracked build output 또는 local state files 미포함
- [x] Release shader model `5.0` 기준 정리
- [ ] Demo index 갱신
- [ ] Topic index 갱신
- [ ] 사용 가능한 captures/videos 링크 연결

## Build / Run

- 확인된 예제:
  - `Part3_Chapter09` archive 대상 예제 Debug/Release 실행 확인
  - `Part3_Chapter10-13` archive 대상 예제 Debug/Release 실행 확인
- Known issues:
  - captures/videos는 보류
  - public readiness는 전체적으로 `검토 필요`
  - texture/model/HDRI/cubemap assets는 public 공개 전 별도 license/attribution 검토 필요
  - 학습 메모/최종 포트폴리오 문서 재정리는 code import 완료 후 일괄 진행 예정

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
- 코드 스타일/취향
- 리팩토링 제안
- 성능 최적화
- public 공개 가능성 최종 판단
- capture/video 완료 여부
- 최종 포트폴리오 문서 완성도

## 후속 작업

- Part3 branch merge 후 Part4 import branch로 이동
- code import 완료 후 Part1부터 문서 전체 재정리
- capture/video 촬영 및 demo index 갱신
- public subset 후보는 private archive 정리 완료 후 별도 repo 기준으로 선별
