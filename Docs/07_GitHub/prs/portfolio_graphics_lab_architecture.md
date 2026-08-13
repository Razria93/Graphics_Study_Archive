# Portfolio GraphicsLab 재구성 전략과 architecture 기준

## 요약

이 PR은 2025년 original software ray tracer의 개발 의도와 단계별 evidence를 보존하면서 `Portfolio_GraphicsLab`을 새 canonical source로 확장할 reconstruction 전략과 architecture 기준을 정한다.

Original source를 bulk import하거나 완성본을 먼저 옮긴 뒤 전면 refactoring하지 않는다. 기능별로 original intent와 observed behavior를 확인하고, canonical contract를 다시 결정한 뒤 새 구현·즉시 refactoring·검증을 한 Work Unit에서 완료하는 흐름을 사용한다.

## 범위

- Phase S verified reconstruction 전략과 original/canonical history 구분
- Phase A original source snapshot, local media와 known issue의 read-only evidence 기준
- WU-A0 application, platform, asset, scene와 rendering module 경계
- ownership, coordinate, transform, error와 threading contract
- Part1 WU-R1부터 WU-R14까지의 reconstruction roadmap
- Part2부터 Part4까지의 capability를 future constraint로 반영
- 전체 책임 지도, frame·asset 흐름과 lifetime 구조 상세화
- Module별 역할, 비책임 범위, 구성 근거와 확장 조건 기록
- Unreal 지향 책임 원칙과 미래 abstraction 도입 조건 기록
- Work Unit, project README, study map과 publication candidate 연결 갱신
- renderer code, project/build contract, asset와 capture/result 변경 제외

## 주요 변경

- Original source와 local media를 수정하지 않는 evidence로 보존하고 현재 repository history를 original Git history로 표현하지 않는다.
- Original class 구조와 ownership을 자동 승계하지 않고 기능 단위로 의도, observed implementation, canonical decision과 verification을 연결한다.
- 마지막 `15-01_Texturing`과 `16-01_Sampling` snapshot의 비산출물 evidence 파일 51개가 모두 동일한 점을 기록하고 directory 이름만으로 sampling 완료를 주장하지 않는다.
- Application을 composition root로 두고 Platform/Windows, Asset, Scene, Rendering/Common, D3D11 Presentation과 CPU RayTracing 책임을 분리한다.
- Backend 독립 domain data와 D3D11 resource ownership을 분리하고 단일 ownership을 기본으로 사용한다.
- Left-handed world/view, column-vector matrix, inverse-transpose normal과 world-space hit ordering을 canonical transform contract로 정한다.
- 두 번째 실제 consumer가 생기기 전에는 범용 renderer interface, RHI, render graph, ECS와 job system을 만들지 않는다.
- Unreal Engine의 구체 class hierarchy를 복제하지 않고 module encapsulation, lifetime 기반 subsystem과 domain/resource 분리 방향을 참고한다.
- `World`, Object/Component, Asset Registry, rendering frontend, common D3D11 backend, Render Graph, job system과 RHI의 도입 조건을 고정한다.
- WU-R1 Window/Presentation부터 WU-R14 Environment/Part1 Closeout까지 기능과 검증 단위로 진행한다.
- 출처와 재배포 조건이 확인되지 않은 original texture를 canonical/public tree에서 제외한다.

## 검증

- Original source root에 Git history가 없음을 확인
- Local development media의 MP4 54개와 PNG 22개 inventory 확인
- `15-01_Texturing`과 `16-01_Sampling`의 비산출물 evidence 파일 51개가 added 0, removed 0, changed 0, same 51임을 SHA-256으로 확인
- GitHub body, GitHub quality, Demo, Topic, video와 Markdown validator 전체 통과
- 변경 Markdown wrap, render와 table validator 통과
- 변경 문서 strict UTF-8과 상대 링크 검사 통과
- source, project, build output과 tracked asset 변경 없음 확인
- user-specific absolute path가 tracked 문서에 포함되지 않음 확인
- `git diff --check origin/main...HEAD` 통과

## 미확인 / 제한

- 이번 PR은 architecture와 reconstruction 기준만 정하며 Win32 window, D3D11 presentation과 RayTracing 기능을 구현하지 않는다.
- source와 project를 변경하지 않아 Debug/Release build와 executable smoke run을 새로 수행하지 않는다. WU-R0의 기존 검증 상태를 유지한다.
- Original media는 source와 frame 단위로 자동 연결된 증거가 아니며 public tree에 포함하지 않는다.
- Original Git history가 없으므로 snapshot 번호와 timestamp를 commit 단위 개발 이력으로 표현하지 않는다.
- Object-space transform, sampling, reflection, refraction과 environment는 roadmap의 해당 Work Unit에서 새 구현과 numeric·visual 검증을 완료해야 한다.
- Part2부터 Part4까지의 capability는 현재 architecture의 제약이며 해당 engine subsystem 구현 완료를 의미하지 않는다.
- Coordinate와 ownership contract는 이 PR review에서 승인한 뒤 WU-R1 구현 기준으로 사용한다.

## 문서

- Project 안내: [Portfolio GraphicsLab README](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-architecture/Portfolio_GraphicsLab/README.md)
- Architecture 정본: [GraphicsLab Architecture](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-architecture/Portfolio_GraphicsLab/ARCHITECTURE.md)
- Architecture 확장 결정: [GraphicsLab Architecture Evolution Decision](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-architecture/Docs/04_WorkLogs/decisions/graphics-lab-architecture-evolution.md)
- Reconstruction 전략: [GraphicsLab Reconstruction Strategy](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-architecture/Docs/04_WorkLogs/decisions/graphics-lab-reconstruction-strategy.md)
- Original evidence 판단: [GraphicsLab Original Evidence Review](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-architecture/Docs/04_WorkLogs/reviews/graphics-lab-original-evidence.md)
- Work Unit 기록: [WU-GraphicsLab-Architecture](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-architecture/Docs/04_WorkLogs/work-units/WU-GraphicsLab-Architecture.md)
- Work Unit Index: [Work Unit Index](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-architecture/Docs/04_WorkLogs/work-unit-index.md)
- Publication 후보: [Candidate List](https://github.com/Razria93/Graphics_Study_Archive/blob/portfolio/graphics-lab-architecture/Docs/05_Publication/candidate-list.md)

## 관련 이슈

- [Progress Issue #7](https://github.com/Razria93/Graphics_Study_Archive/issues/7)
- [Part1 Chapter03 Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12)
- [WU-R0 PR #40](https://github.com/Razria93/Graphics_Study_Archive/pull/40)

## 다음 단계

- WU-R1에서 Win32 window lifecycle, resize, CPU framebuffer upload와 D3D11 presentation을 구현한다.
- WU-R1에서는 camera ray, primitive intersection과 shading을 포함하지 않는다.
- WU-R2에서 math, coordinate와 object transform contract를 numeric test로 고정한다.
- 이후 WU-R3부터 primary ray와 Part1 RayTracing 기능을 순차적으로 재구성한다.
