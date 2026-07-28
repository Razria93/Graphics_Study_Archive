# Document System Audit 2026-07-28

이 문서는 2026-07-28에 수행한 Graphics Study Archive 전체 문서 감사와 사용자
검토 결과를 기록한 snapshot이다. 최신 상태 정본을 대체하지 않으며 실제 상태는
각 책임 문서에서 확인한다.

## 1. Executive summary

- Root, Docs, Chapter, Example README의 진입 흐름
- Topic, Verification, Demo, WorkLog, Publication, GitHub body의 책임과 상태
- AGENTS, Policies, templates, validators의 규칙 일치
- Markdown 링크, stale path, Legacy 오탐
- 로컬 GitHub 기록과 remote Issue/PR 상태

감사는 read-only로 수행했다. 초기와 최종 validator는 모두 통과했고 감사 중
tracked 파일을 변경하지 않았다.

## 2. 현재 문서 구조의 강점

- `Docs/00_Index` 중심의 축별 진입 구조가 명확하다.
- Topic, Verification, WorkLog, Publication의 기본 책임이 분리돼 있다.
- WorkLog는 최신 정본이 아니라 당시 결정의 snapshot으로 운영한다.
- Legacy는 역사 자료로 격리돼 있으며 현재 정본으로 잘못 사용한 사례가 없다.
- Part1 Chapter01-02는 이후 README의 탐색 구조 기준으로 사용할 수 있다.
- GitHub body validator는 source 복제와 내부 경로 노출을 차단한다.

## 3. P0/P1/P2 발견 항목

| ID | 심각도 | 최종 판정 | 사용자 판정 | 상태 |
| --- | --- | --- | --- | --- |
| DOC-001 | P1 | 문서화 이전 build/run 성공 이력이 Verification 정본으로 승격되지 않아 provenance가 단절됨 | 성공 사실을 유지하고 과거 확인 이력을 반영함 | 재분류 |
| DOC-002 | P0 | 현재 상대 링크 5개와 존재하지 않는 GitHub Issue #9 링크가 깨짐 | 수정 동의 | 확정 |
| DOC-003 | P1 | 비파일럿 Chapter README가 import 기록 중심이며 현재 문서 축 연결이 부족함 | 사용자 검토 항목을 먼저 제시함 | 보류 |
| DOC-004 | P1 | Root Study Map의 `정리 예정` 의미가 모호함 | `코드 보관 완료 및 현재 문서화 대기`로 통일 | 확정 |
| DOC-005 | P1 | Demo priority가 Part1 Chapter01-02의 현재 capture/result보다 오래됨 | 수정 동의 | 확정 |
| DOC-006 | P1 | WorkLog GitHub index와 remote Issue #7, PR #8 상태가 다름 | WorkLog index와 PR #8 body 동기화 승인 | 확정 |
| DOC-007 | P1 | Demo Issue가 untracked runtime result를 공개 asset처럼 표시함 | 수정 동의 | 확정 |
| DOC-008 | P1 | Example README와 Demo의 기술 구현 책임이 겹침 | Example의 현재 의미와 대안 재검토 | 보류 |
| DOC-009 | P1 | PR 요약 책임과 screenshot 강제 기준이 충돌함 | 대표 이미지 최대 1개, 상세 이미지는 Demo에 두는 방향 동의 | 확정 |
| DOC-010 | P1 | 관련 문서가 이동 가능한 Markdown 링크가 아닌 plain path로 작성됨 | 수정 동의 | 확정 |
| DOC-011 | P1 | Demo Issue 생성 목적 설명이 실제 공개 구현 안내 역할보다 오래됨 | 수정 동의 | 확정 |
| DOC-012 | P1 | PR body에 내부 workflow가 있고 remote body가 로컬 후보보다 오래됨 | 수정 동의 | 확정 |
| DOC-013 | P2 | 비파일럿 README 일부가 저장소 문체 규칙과 다름 | 수정 동의 | 확정 |
| DOC-014 | P2 | Root와 Docs README의 일부 진입 링크가 실제 축 책임을 생략함 | 수정 동의 | 확정 |
| DOC-015 | P2 | line-length와 validator 범위 설명이 정책·도구 사이에서 다름 | `80자 권장, 120자 초과 실패` 방향 동의 | 확정 |
| DOC-016 | P2 | validator가 링크와 축 간 상태 정합성을 검사하지 않음 | 자동화 경계와 규칙 제안 후 구현 동의 | 확정 |

주요 근거 위치:

- DOC-001: Chapter README 6개와
  `Docs/02_Verification/build-run-matrix.md`
- DOC-002: `Part1_Chapter03/README.md`,
  `Part4_Chapter14-20/README.md`, `Portfolio_RayTracer/README.md`,
  `Docs/07_GitHub/prs/part1_chapter01-02.md`
- DOC-003, DOC-013: 비파일럿 Chapter README 6개와 Portfolio README
- DOC-004: Root `README.md` Study Map
- DOC-005: `Docs/03_Demos/demo-priority.md`와 Part1 Demo index
- DOC-006: `Docs/04_WorkLogs/work-unit-github-index.md`, Issue #7, PR #8
- DOC-007, DOC-010, DOC-012:
  `Docs/07_GitHub/issues/demo/demo_part1_chapter01-02.md`와 Part1 PR body
- DOC-008, DOC-009, DOC-011:
  `canonical-docs-policy.md`, `github-workflow-policy.md`,
  GitHub body instruction과 관련 template
- DOC-014: Root `README.md`와 `Docs/README.md`
- DOC-015, DOC-016: `Docs/98_Tools`, validators와 `.github` 품질 규칙

DOC-002, DOC-004, DOC-005, DOC-007, DOC-010, DOC-013, DOC-014는 목표가
확정되면 자동 또는 반자동 수정할 수 있다. DOC-001, DOC-003, DOC-008,
DOC-009, DOC-011, DOC-015, DOC-016은 정책 또는 사용자 판단을 먼저 반영한다.
DOC-006과 DOC-012의 remote 변경은 별도 GitHub 승인 절차를 따른다.

## 4. 책임 축별 감사 결과

| 책임 축 | 판정 | 감사 결과 |
| --- | --- | --- |
| Root/Index | 보완 필요 | 상태 표현과 일부 진입 링크가 현재 구조보다 오래됨 |
| Chapter/Example | 보완 필요 | 파일럿 외 README가 import 기록 중심이며 Demo 책임과 겹침 |
| Topic | 대체로 적합 | 개념·이론 정본 방향이 명확하나 이전 map 표현이 남음 |
| Verification | 정본 명확 | 과거 성공 이력 provenance를 이전하는 기준이 필요함 |
| Demo | 결정 필요 | capture registry와 기술 구현 설명의 정본 관계가 불명확함 |
| WorkLog | 적합 | 현재 상태가 아닌 당시 결정 snapshot 책임이 명확함 |
| Publication | 적합 | 공개 후보와 제외 판단이 분리돼 있음 |
| GitHub body | 보완 필요 | PR/Demo 중복과 local/remote 동기화 문제가 있음 |
| Policies/Tools | 보완 필요 | 자동 검사와 수동 감사의 coverage 차이가 있음 |

## 5. 상태 불일치

- 과거 build/run 성공 이력이 Verification의 `미확인`으로 이전됨
- Root Study Map의 `정리 예정`이 코드 보관과 문서화 상태를 함께 표현함
- Demo priority가 확보된 Part1 Bloom capture를 반영하지 않음
- WorkLog GitHub index가 실제 Issue #7과 draft PR #8 상태를 반영하지 않음
- Demo Issue가 untracked runtime result를 공개 asset처럼 표시함
- remote PR #8 body가 로컬 게시 후보보다 오래됨

## 6. 깨진 링크와 stale path

- `Part1_Chapter03/README.md`: 폐기된 manifest와 Docs 경로 2개
- `Part4_Chapter14-20/README.md`: 폐기된 Docs와 manifest 경로 2개
- `Portfolio_RayTracer/README.md`: 존재하지 않는 Docs 경로 1개
- `Docs/07_GitHub/prs/part1_chapter01-02.md`: 존재하지 않는 Issue #9 링크

Legacy 내부의 과거 경로, validator의 금지 문자열, template placeholder는 현재
깨진 링크에서 제외했다.

## 7. 정책/template/validator 불일치

- Example README와 Demo가 구현 흐름과 capture 책임을 함께 주장함
- PR은 링크 허브라는 instruction과 screenshot을 요구하는 template이 충돌함
- Demo Issue 생성 목적이 실제 공개 기술 문서 역할보다 오래됨
- 관련 문서를 링크라고 부르지만 template은 plain path를 생성함
- line-length 설명이 80, 100, 120자로 분산됨
- validator가 링크 존재와 축 간 상태를 검사하지 않음

## 8. 공개 문서 품질

- 비파일럿 Chapter README에 import 과정과 로컬 절대 경로가 남아 있음
- 관련 문서 경로가 클릭 가능한 링크가 아님
- PR body에 내부 workflow와 게시 판단 문구가 포함됨
- PR과 Demo Issue가 시각 자료와 구현 설명을 반복함
- 일부 README가 저장소 문체 기준을 따르지 않음

민감한 credential이나 유료 원본 자료의 직접 노출은 발견하지 않았다.

## 9. 권장 수정 작업 묶음

1. P0 현재 링크 복구
2. Verification에 과거 성공 이력의 provenance를 표현할 상태 기준 확정
3. Root와 Demo/GitHub 상태 index 동기화
4. 비파일럿 Chapter README 현대화
5. Example과 Demo 책임 경계 확정
6. GitHub body 정책, template, validator 동기화
7. 링크와 상태 정합성 validator 설계·구현

## 10. 권장 commit 분할

1. `fix: 현재 문서의 깨진 링크 정리`
2. `docs: 기존 검증 이력을 Verification 정본에 반영`
3. `docs: Chapter README를 현재 문서 축으로 정리`
4. `docs: Demo와 GitHub 상태 인덱스 동기화`
5. `docs: Example과 Demo 책임 경계 정리`
6. `chore: 문서 정합성 validator 보강`
7. `fix: GitHub 게시 후보의 공개 문구와 링크 정리`

## 11. 수정 전 사용자 결정

### DOC-001 재분류

사용자는 문서화 이전 코드 복사 단계에서 대상 코드를 직접 build/run하여 성공을
확인했다. 따라서 Chapter README의 성공 기록은 사실과 다른 상태가 아니다.

문제는 새 Verification 체계를 만들 때 기존 성공 이력과 근거 수준을 옮기지 않아
`미확인`으로 보이게 된 provenance 단절이다. `과거 확인` 같은 상태를 실제로
채택하려면 [Verification Policy](../../06_Policies/verification-policy.md)와 [Terminology Policy](../../06_Policies/terminology-policy.md)에서 먼저 정의한다.

### DOC-003 사용자 검토 범위

비파일럿 Chapter README 초안에서 사용자가 확인할 내용은 다음으로 제한한다.

1. Chapter를 portfolio 관점에서 소개하는 대표 목적
2. 우선 노출할 대표 Example
3. import와 dependency 역사 중 공개 README에 남길 사실
4. 과거 build/run 성공과 예제 고유 limitation

현재 축 링크, 절대 경로 제거, 문체, 공통 구조는 규칙에 따라 반자동으로 정리할
수 있다.

### DOC-008 Example 의미와 미결정 사항

Example은 폐기된 `Docs/01_Examples` 축을 뜻하지 않는다. Chapter 코드 폴더 아래의
개별 실행 예제와 그 폴더의 README를 뜻한다.

검토 중인 권장 경계:

- Example README: 예제 목적, 코드 위치, 실행 진입점, 관련 정본 링크
- Topic: 여러 예제에 적용되는 개념과 이론
- Demo: 저장소에서 결과를 만든 기술 흐름, 구현 선택, 시각 결과

이 경계는 아직 정책으로 확정하지 않는다. 상세 Demo 정본을 `Docs/03_Demos`에
둘지, Example README의 기존 구현 설명 책임을 유지할지 추가 결정이 필요하다.

## 12. 초기 및 최종 validator 결과

| Validator | 초기 | 최종 |
| --- | --- | --- |
| `validate-github-body.ps1` | PASS | PASS |
| `validate-github-quality.ps1` | PASS | PASS |
| `validate-demo-index-quality.ps1` | PASS | PASS |
| `validate-topic-doc-quality.ps1` | PASS | PASS |

Validator가 모두 통과했지만 링크와 상태 의미 충돌을 발견하지 못했다. 이는
DOC-016의 자동화 coverage 문제로 분류한다.

## 13. 감사 단계 commit readiness

- 감사 수행 단계의 파일 변경: 없음
- 감사 수행 단계의 commit: 불필요
- remote 조회: read-only
- remote 변경: 없음
- 후속 수정: 사용자 승인 항목별 별도 작업

이 snapshot 작성은 감사 workflow 문서화 작업에 포함한다. 위 발견 항목의 실제
정본 수정은 별도 `감사 결과 반영 시작` 요청에서 수행한다.
