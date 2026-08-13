# GraphicsLab Reconstruction Strategy

## 목적

이 문서는 2025년 original software ray tracer의 개발 의도와 단계별 증빙을 보존하면서 `Portfolio_GraphicsLab`의 canonical source를 새로 구성하는 기준을 고정한다. 기존 완성본을 그대로 옮긴 뒤 한 번에 고치는 방식과 원본 계보를 지우는 무관한 재작성을 모두 피한다.

## 전략 결정

- original source, 실행 영상과 결과 이미지는 수정하지 않는 evidence로 유지한다.
- canonical source는 빈 scaffold에서 시작해 기능 단위로 다시 구현한다.
- 각 기능은 `original intent 확인 -> observed implementation 분석 -> canonical contract 결정 -> 구현 -> 즉시 refactoring -> 검증` 순서로 진행한다.
- original code의 class 구조, ownership과 이름을 자동 승계하지 않는다. 의도와 동작을 이해하기 위한 evidence로만 사용한다.
- 강의 예제는 graphics 기능의 순서와 비교 기준으로 사용하며 source 구조를 복제하지 않는다.
- 재구성한 기능은 WorkLog, verification과 commit history에서 original evidence와 canonical implementation을 구분해 기록한다.
- 발견한 결함은 전체 import 이후로 미루지 않는다. 해당 기능의 contract를 정하는 Work Unit에서 수정하거나 명시적으로 보류한다.

## 저작과 계보 표현

original software ray tracer는 사용자가 바닥부터 구현한 개인 작업이다. 당시에는 웹 기반 GPT에 조각별 질문을 했으나 agent가 저장소 전체를 구성하거나 기존 프로젝트를 일괄 생성한 작업은 아니다. original Git history가 없으므로 raw 단계별 source와 local media를 개발 계보의 보조 증빙으로 사용한다.

현재 저장소의 canonical history는 original commit history의 복원이 아니다. original intent와 observed behavior를 확인하고 설계 결정을 다시 내린 verified reconstruction history다. 공개 설명에서는 `original implementation`, `original evidence`, `verified reconstruction`을 구분하며 동일한 history라고 주장하지 않는다.

## 기능 단위 기록 계약

| 항목 | 기록 내용 |
| --- | --- |
| Original intent | 사용자가 구현하려던 graphics 개념과 동작 |
| Observed evidence | 단계별 source, 실행 media와 결과에서 직접 확인한 사실 |
| Canonical decision | 유지·변경·제외한 설계와 이유 |
| Implementation | 새 canonical source에서 구현한 책임과 경계 |
| Verification | numeric test, build/run, visual comparison과 미확인 항목 |
| Provenance | original evidence, 강의 예제와 replacement asset의 역할 구분 |

tracked 문서에는 공개 가능한 판단과 검증 결과만 둔다. 절대 경로, 파일별 hash와 media inventory 상세는 `local/Portfolio_GraphicsLab`에 유지하며 tracked 문서에서 직접 링크하지 않는다.

## 설계 기준

- 현재 필요한 책임을 분리하되 미래 backend를 가정한 추상화는 만들지 않는다.
- 두 번째 실제 consumer가 생기기 전에는 범용 interface, factory와 RHI를 도입하지 않는다.
- CPU에서 GPU pipeline의 암묵적 단계를 구현하고 관찰하는 Part1 목표를 우선한다.
- CPU 구현이 이후 D3D11 기능으로 대체될 때 Scene, Asset과 application lifecycle을 함께 폐기하지 않도록 renderer 경계를 둔다.
- correctness와 설명 가능성을 성능 최적화보다 먼저 검증한다.
- asset 출처와 재배포 권한이 확인되지 않으면 canonical/public tree에 포함하지 않는다.

## 채택하지 않는 접근

| 접근 | 채택하지 않는 이유 |
| --- | --- |
| Original을 무시한 독립 재작성 | 사용자 구현의 의도, 변천사와 비교 가능한 증빙이 사라진다. |
| 완성본 bulk import 후 전면 refactoring | CWD, ownership, naming, inactive state와 미완성 contract를 canonical history에 먼저 고정한다. |
| Part1부터 Part4까지의 범용 engine 선행 구현 | 실제 consumer가 없는 계층과 추상화를 만들며 학습 기능의 검증 단위를 흐린다. |
| 강의 예제 구조의 통합 복제 | 개인 구현의 구조적 판단과 공개 가능한 독립 설명을 약화한다. |

## 변경 관리

이 전략은 project 수준 decision이다. 세부 module과 Work Unit 경계는 architecture 문서에서 조정할 수 있지만 evidence read-only, no bulk import, 기능 단위 verified reconstruction 원칙을 바꾸려면 별도 decision record와 사용자 검수가 필요하다.

## 관련 문서

- [Original Evidence Review](../reviews/graphics-lab-original-evidence.md)
- [GraphicsLab Architecture](../../../Portfolio_GraphicsLab/ARCHITECTURE.md)
- [Architecture Evolution Decision](graphics-lab-architecture-evolution.md)
- [WU-GraphicsLab-Architecture](../work-units/WU-GraphicsLab-Architecture.md)
