# Part1-Part4 진행 상태 closeout과 PR body 유형 분리

## 요약

이 PR은 PR #38 병합 이후 Part1부터 Part4까지의 진행 상태를 실제 완료 기록에 맞추고, 완료된 Demo index와 관련 문서 링크를 정리한다. 그래픽 결과가 중심이 아닌 closeout PR을 간결하게 작성할 수 있도록 Chapter PR과 maintenance PR의 문서 계약도 분리한다.

## 범위

- root README, work unit, publication candidate와 progress plan의 완료 상태 정합화
- Part1 Chapter03, Part2 Chapter04, Part2 Chapter05-08, Part3 Chapter10-13의 완료된 Demo index 정리
- Part1 Chapter03 Demo 파일명을 `03_04_DrawingSphere.md`와 같이 Chapter와 Step을 함께 표시하는 형식으로 통일하고 관련 링크 갱신
- Phase 1, Phase 2 Part1과 Phase 4 Part3 완료 댓글 구조와 Part1-Part4 후속 작업 계획 정리
- maintenance PR 정책, template, validator와 회귀 fixture 추가
- 문서와 README만 변경하며 예제 코드, build 산출물, capture와 video는 변경하지 않음

## 주요 변경

- GitHub 병합 결과, work unit, publication 상태와 전체 진행 계획을 같은 완료 기록으로 맞춘다.
- 완료된 상세 Demo를 index와 코드 폴더 README에서 직접 찾을 수 있도록 연결한다.
- Part1 Chapter03 Demo 이름에 Chapter 번호와 Step 번호를 함께 기록해 다른 Part의 번호 체계와 구분한다.
- 기존 Progress 완료 댓글의 permalink와 시간 순서를 유지하면서 Phase별 작업 묶음으로 tracked 후보를 통합한다.
- `## 주요 변경`을 maintenance PR 식별자로 정의하고 Chapter 전용 section과 혼합하지 않도록 검사한다.
- 정상 Chapter PR, 정상 maintenance PR, 필수 section 누락과 유형 혼합을 fixture로 검증한다.

## 검증

- 문서 validator 10종 전체 통과
- 변경 범위의 이전 Part1 Chapter03 Demo 경로 잔존 여부 확인
- `git diff --check main...HEAD` 통과
- 코드, binary, capture와 video 변경 없음 확인
- 새 build/run 검증은 수행하지 않으며 기존 Verification 기록을 유지함

## 미확인 / 제한

- `Portfolio_RayTracer` 조사와 변경은 포함하지 않는다.
- Part2 Demo 번호 체계 통일과 Part1부터 Part4까지의 학습용 코드 주석 정리는 포함하지 않는다.
- Part4 Chapter14-Chapter15 Release x64 재검증과 runtime DLL 배치 자동화는 포함하지 않는다.
- Part4 selected video 검수, 원격 게시와 permalink 동기화는 포함하지 않는다.

## 문서

- 전체 진입점: [README](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-part4-closeout/README.md)
- 작업 계획: [Part1-Part4 Closeout Plan](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-part4-closeout/Docs/04_WorkLogs/active/part1-part4-closeout-plan.md)
- 작업 단위: [Work Unit Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-part4-closeout/Docs/04_WorkLogs/work-unit-index.md)
- Demo 진입점: [Demo Index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-part4-closeout/Docs/03_Demos/README.md)
- 전체 진행 상태: [Plan Progress](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-part4-closeout/Docs/07_GitHub/plan/plan-progress.md)
- PR 운영 정책: [GitHub Workflow Policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-part4-closeout/Docs/06_Policies/github-workflow-policy.md)
- Validator: [Validators](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-part4-closeout/Docs/98_Tools/validators/README.md)

## 관련 이슈

- [PR #38](https://github.com/Razria93/Graphics_Study_Archive/pull/38)
- [Progress Issue #7](https://github.com/Razria93/Graphics_Study_Archive/issues/7)
- [Part1 Chapter03 Demo Issue #12](https://github.com/Razria93/Graphics_Study_Archive/issues/12)

## 다음 단계

- `Portfolio_RayTracer`를 read-only로 조사하고 별도 작업 범위와 검증 계획을 확정한다.
- Part2 Demo 번호 체계, Part1부터 Part4까지의 코드 주석, Part4 Release와 runtime DLL을 각각 독립 작업으로 처리한다.
- Part4 selected video를 검수한 뒤 승인된 원격 게시와 permalink 동기화를 수행한다.
