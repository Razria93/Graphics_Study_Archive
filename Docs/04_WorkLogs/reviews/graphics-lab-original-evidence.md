# GraphicsLab Original Evidence Review

## 목적

이 문서는 original `Graphics Portfolio` 자료에서 반복 조사 없이 재사용할 수 있는 결론만 기록한다. 원본 위치, 파일별 hash와 media 목록은 local evidence manifest에서 관리하고 이 문서에는 공개 가능한 수준의 요약만 둔다.

## 확인한 evidence 집합

| Evidence | 확인 범위 | 판정 |
| --- | --- | --- |
| 단계별 source snapshot | 초기 설정부터 texturing까지 번호가 붙은 source tree | 점진적 기능 추가와 구조 변경을 보여주는 original evidence |
| refactoring 전후 snapshot | 초기 단일 책임 혼재 구조와 후반 Scene·Object·Mesh 구조 | 구조화 의도와 미완성 전환 지점을 비교할 수 있음 |
| 실행 영상 | 54개 MP4 | 시기별 실행 동작을 보조하며 tracked/public 원본으로 포함하지 않음 |
| 결과 이미지 | 22개 PNG | 시각 결과를 보조하며 권리·식별자 검수 전에는 local-only로 유지 |
| original Git history | 없음 | commit 단위 개발 순서를 주장할 수 없음 |

최종 두 source snapshot의 generated output 제외 evidence 파일은 각각 51개이며 SHA-256 비교에서 추가, 제거와 변경이 모두 0개다. 따라서 마지막 번호의 이름만으로 sampling 구현 완료를 주장하지 않으며 texturing 단계와 동일한 code state로 판정한다.

## 확인한 original 구현 의도

- CPU에서 camera ray, intersection, shading, visibility와 framebuffer 생성을 구현해 GPU가 제공하는 처리 단계를 이해한다.
- 기능을 순차적으로 추가한 뒤 Scene, Object, Mesh, Submesh와 Material 책임으로 구조화한다.
- CPU 결과를 DirectX11 dynamic texture로 전달해 application window에 표시한다.
- 장기적으로 graphics pipeline과 후속 rendering 기능을 같은 application framework에서 교체·확장 가능한 축으로 둔다.

## 확인한 구현 범위

후반 structured snapshot에서 Scene에서 Object, Mesh와 Submesh로 이어지는 구조, triangle intersection, barycentric UV·색 보간, material resolve, Phong 계열 조명, shadow test와 CPU framebuffer의 DirectX11 표시 흐름을 확인했다.

active final path에서는 sphere primitive, 실제 multisampling, recursive reflection, refraction과 cubemap environment를 확인하지 못했다. 단계 이름, inactive field와 주석만으로 구현 완료를 주장하지 않는다.

## 재구성 시 바로 교정할 항목

| Original 상태 | 문제 | Canonical 기준 |
| --- | --- | --- |
| 사용자 전역 vcpkg 연결 | 다른 환경에서 dependency restore를 재현하기 어렵다. | manifest와 고정 baseline을 사용한다. |
| shader·texture의 CWD 상대 경로 | 실행 위치에 따라 resource lookup이 달라진다. | executable 기준 `Assets` root를 사용한다. |
| `pwsh.exe` post-build 결합 | optional 단계가 compile/link 결과를 가릴 수 있다. | build와 optional validation을 분리한다. |
| object-space ray transform TODO | transformed object의 intersection contract가 완성되지 않는다. | inverse transform, normal transform과 world-space hit 비교를 numeric test로 검증한다. |
| orphan file과 inactive field | 실제 책임과 미래 추측 상태가 섞인다. | 현재 Work Unit에서 사용하는 최소 상태만 추가한다. |
| 이전 project·namespace·filename | project identity와 코드 검색 결과가 불일치한다. | `GraphicsLab` identity와 책임 기반 이름을 사용한다. |
| source와 historical output 혼재 | 정본과 생성물이 구분되지 않는다. | canonical source와 generated/local evidence를 분리한다. |
| mixed encoding과 Korean source comment | toolchain과 공개 source consistency가 낮다. | 새 source는 UTF-8과 필요한 English comment만 사용한다. |

## Asset와 공개 판정

original texture의 출처와 재배포 조건은 확인되지 않았다. 해당 파일은 original 동작을 이해하기 위한 local evidence로만 유지하고 canonical/public tree에는 복사하지 않는다. 시각 비교가 필요한 Work Unit은 사용자 제작 또는 재배포 가능한 replacement asset을 먼저 확보한다.

## 주장 가능한 범위

- 사용자가 2025년에 original software ray tracer를 직접 구현했다.
- 단계별 source와 media가 점진적 개발과 refactoring 흔적을 보조한다.
- 현재 canonical project는 original source의 bulk import가 아니라 검증 가능한 기능 단위 reconstruction이다.

다음 내용은 주장하지 않는다.

- 현재 repository Git history가 2025년 original development history라는 주장
- snapshot 번호만으로 모든 명명된 기능이 완료됐다는 주장
- 출처 미확인 asset의 재배포 가능 주장
- observed code를 넘어선 성능, 정확도와 engine 완성도 주장

## 관련 문서

- [Reconstruction Strategy](../decisions/graphics-lab-reconstruction-strategy.md)
- [GraphicsLab Architecture](../../../Portfolio_GraphicsLab/ARCHITECTURE.md)
- [Source Registry](../../99_Legacy/source-registry.md)
