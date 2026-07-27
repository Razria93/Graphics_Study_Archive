# Graphics Study Archive Progress Plan

## 요약

이 Issue는 Graphics Study Archive 전체 진행판이다. Part와 Chapter 단위로 문서화, 검증, demo 정리, PR 준비 상태를 추적한다.

## 목표

Progress Issue 1개, 누적 진행 댓글 1개, Chapter/Bundle 완료 댓글 여러 개, Chapter PR 여러 개를 기본 게시 객체로 운영한다. 선택 Issue는 독립 작업, 장기 논의, 별도 승인 범위가 있을 때만 생성한다.

## Phase 범위

- Phase 1: 문서 구조와 workflow 정립
	- 완료 기준: Source docs와 GitHub 게시 후보 책임 경계가 문서 전체에서 일치한다.
- Phase 2: Part1_Chapter01-02
	- 완료 기준: Chapter README, Topic, Verification, Demo, Chapter PR 후보가 연결되고 제한 사항이 명시된다.
- Phase 3: Part1_Chapter03
	- 완료 기준: ray tracing 단계별 대표 예제, 검증 상태, demo 후보, Chapter PR 후보가 정리된다.
- Phase 4: Portfolio_RayTracer
	- 완료 기준: Part1 연계 범위, 검증 상태, demo 후보, Chapter 또는 bundle PR 계획이 정리된다.
- Phase 5: Part2_Chapter04
	- 완료 기준: rasterization 기초 예제의 대표 개념, 검증 상태, Chapter PR 후보가 정리된다.
- Phase 6: Part2_Chapter05-08
	- 완료 기준: pipeline/modeling/shader toys 묶음의 Chapter 또는 bundle PR 후보와 검증 상태가 정리된다.
- Phase 7: Part3_Chapter09
	- 완료 기준: interaction 예제의 대표 흐름, 검증 상태, Chapter PR 후보가 정리된다.
- Phase 8: Part3_Chapter10-13
	- 완료 기준: geometry/texturing/PBR/shadow 묶음의 Chapter 또는 bundle PR 후보가 정리된다.
- Phase 9: Part4_Chapter14-20
	- 완료 기준: advanced graphics/compute 범위의 대표 예제, 검증 상태, Chapter 또는 bundle PR 후보가 정리된다.
- Phase 10: 최종 검증과 Publication 후보 정리
	- 완료 기준: known issue와 limitation이 정리되고 publication 후보 상태가 최신으로 반영된다.

## 완료 조건

- Progress Issue, 누적 진행 댓글, Chapter/Bundle 완료 댓글, Chapter PR 책임이 명확하다.
- 선택 Issue 생성 기준이 일관되게 적용된다.
- Part1~Part4와 Portfolio_RayTracer의 Phase가 누락 없이 추적된다.
- known issue와 limitation이 누락 없이 연결된다.

## 기본 게시 객체

- Progress Issue 1개
- 누적 진행 댓글 1개
- Chapter/Bundle 완료 댓글 여러 개
- Chapter 또는 작은 Chapter 묶음 단위 PR 여러 개

## 선택 Issue 생성 기준

- Progress Issue 댓글과 Chapter PR만으로 추적하기 어려운 독립 작업
- 장기 논의가 필요한 정책/기술 판단
- 별도 승인 범위가 필요한 검증, demo, publication 판단

## 관련 문서

- GitHub workflow 정책: [github-workflow-policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/06_Policies/github-workflow-policy.md)
- Work Unit workflow 정책: [work-unit-workflow-policy](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/06_Policies/work-unit-workflow-policy.md)
- Work Unit GitHub Index: [work-unit-github-index](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/04_WorkLogs/work-unit-github-index.md)
- Verification known issues: [known-issues](https://github.com/Razria93/Graphics_Study_Archive/blob/docs/part1-pilot-workflow/Docs/02_Verification/known-issues.md)

## 제외 범위

- 강의 원문, 슬라이드, 정답, 워터마크가 있는 자료의 게시
- public subset 최종 확정
- Part1~Part4와 Portfolio_RayTracer 범위 밖의 예제 정리