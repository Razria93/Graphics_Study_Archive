# PR: Part4 Compute/Simulation/Animation archive import 정리

## Title

```text
docs: Part4 Compute/Simulation/Animation archive import 정리
```

## Body

## 요약

- Part4 Chapter14-20 `Examples` 단일 project를 private archive 기준으로 import했습니다.
- Compute shader, particle/simulation, skeletal animation, foliage/landscape, PhysX, gameplay integration 예제를 command argument 기반 실행 흐름으로 정리했습니다.
- 예제별 README/status, Part4 import manifest, build/run tracking, migration board를 갱신했습니다.
- source/project import와 사용자 Debug/Release 실행 확인 기록을 우선 정리했고, 학습 문서의 세부 재작성은 전체 code import 완료 후 Part1부터 일괄 진행합니다.

## 범위

- Part:
  - `Part4_Chapter14-20`
- Docs:
  - `Docs/Part4_Chapter14-20`
  - `Docs/_repo/manifests/Part4_Chapter14-20.md`
  - `Docs/_repo/tracking/build-guide.md`
  - `Docs/_repo/tracking/migration-board.md`
  - `Docs/_repo/reference/raw-to-archive-map.md`
  - `Docs/_repo/workflow/import-integrity-checklist.md`
- Captures/videos:
  - 보류
- Build checks:
  - 사용자가 Visual Studio Debug x64 / Release x64 build-run 확인
  - Part4는 `Ex` 뒤 4자리 숫자를 `Debugging > Command Arguments`에 입력해서 예제를 선택

## 주요 변경

- Chapter14 compute shader examples:
  - Basic checkerboard, separable blur, matrix-vector multiplication, structured buffer, consume/append buffer, density field, indirect arguments, bitonic sort
- Chapter15 particle examples:
  - CPU particle system, sprite fire effect, SPH water
- Chapter16 simulation examples:
  - Stable fluids, curl noise, cloud, realtime smoke, CPU smoke, hybrid water
- Chapter17 animation example:
  - Skeletal animation, Mixamo character/animation clips, Assimp 6.x FBX pivot node compatibility 보정
- Chapter18 environment examples:
  - Tree, grass, landscape/ocean, terrain raw fallback
- Chapter19 physics example:
  - PhysX rigid body simulation and render transform sync
- Chapter20 gameplay example:
  - Character animation, PhysX box stack, fireball collision, fireball notify spawn/GUI tuning
- Project fixes / archive adjustments:
  - tracked build output/local state file 없음 확인
  - Part4 command argument 실행 기준 문서화
  - `.dds`, `.exr`, `.fbx`, `.hdr` asset은 LFS 추적 기준 적용
  - Ex1605/Ex1606 performance-sensitive examples는 archive 실행 확인 가능한 기본값으로 조정
  - Ex1701은 Assimp 6.x pivot helper node 문제를 최소 importer option으로 보정
  - Ex1803은 missing terrain FBX 대신 `terrain.raw` height-field fallback 반영
  - Ex2001은 gameplay TODO를 archive 실행 확인 가능한 수준으로 보강
- Local-only study review documents remain under ignored `local/` and are not part of this PR.

## 체크리스트

- [x] README 갱신
- [x] Notes/status 추가 또는 갱신
- [x] Import manifest 갱신
- [x] Build guide / migration board 갱신
- [x] Raw-to-archive map 갱신
- [x] Import integrity 기준 문서 갱신
- [x] tracked build output 또는 local state files 미포함
- [x] Part4 command argument 실행 기준 기록
- [ ] Demo index 갱신
- [ ] Topic index 갱신
- [ ] 사용 가능한 captures/videos 링크 연결

## Build / Run

- 확인된 예제:
  - `Ex1401`-`Ex1408` Debug/Release 실행 확인
  - `Ex1501`-`Ex1503` Debug/Release 실행 확인
  - `Ex1601`-`Ex1606` Debug/Release 실행 확인
  - `Ex1701` Debug/Release 실행 확인
  - `Ex1801`-`Ex1803` Debug/Release 실행 확인
  - `Ex1901` Debug/Release 실행 확인
  - `Ex2001` Debug/Release 실행 확인
- Known issues:
  - captures/videos는 보류
  - public readiness는 전체적으로 `검토 필요`
  - Mixamo, HDRI, PBR texture, foliage/terrain assets는 public 공개 전 별도 license/attribution 검토 필요
  - Ex1605/Ex1606 등 simulation-heavy examples는 환경에 따라 frame rate가 크게 낮아질 수 있음
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

- Part4 branch merge 후 private archive code import 완료 상태 확인
- code import 완료 기준으로 Part1부터 문서 전체 재정리
- capture/video 촬영 및 demo index 갱신
- public subset 후보는 private archive 정리 완료 후 별도 repo 기준으로 선별
