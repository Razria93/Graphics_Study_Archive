# Publication Checklist

이 문서는 public subset 후보를 공개하기 전 확인할 체크리스트다.

## 문서 체크

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| 직접 작성한 설명으로 재작성함 | 미확인 |  |
| 강의 원문 구조와 표현을 복제하지 않음 | 미확인 |  |
| 존댓말, 대화체, draft 문구를 제거함 | 미확인 |  |
| 개인 정보와 로컬 절대 경로를 제거함 | 미확인 |  |
| 미확인 상태를 성공처럼 표현하지 않음 | 미확인 |  |

## 코드/검증 체크

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| 공개할 코드가 독자 구현 또는 공개 가능한 범위임 | 미확인 |  |
| build/run 결과를 직접 확인함 | 미확인 |  |
| 실패와 known issue를 숨기지 않음 | 미확인 |  |
| 검증 문서와 WorkLog가 일치함 | 미확인 |  |

## Asset/Demo 체크

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| capture/result가 직접 실행 결과임 | 미확인 |  |
| 강의 화면과 유료 자료가 포함되지 않음 | 미확인 |  |
| asset 출처 상태와 외부 자료 복제 여부를 확인함 | 미확인 |  |
| 외부 asset이면 출처와 라이선스를 확인함 | 미확인 | 대상에 외부 asset이 없을 때만 `해당 없음`으로 판정 |
| 파일명이 Part/Topic/Demo를 명확히 드러냄 | 미확인 |  |
| Chapter·Bundle visual이 서로 다른 설명 축을 담당함 | 미확인 | 단일 Example이면 `해당 없음`으로 판정 |
| 반복 상태와 설명 가치가 겹치는 visual을 제외함 | 미확인 |  |
| video container·codec·pixel format·CFR·stream·decode를 확인함 | 미확인 | 대상에 video가 없을 때만 `해당 없음`으로 판정 |
| video의 민감 metadata와 화면 노출을 확인함 | 미확인 | 자동 검수와 사용자 시각 검수를 분리해 확인 |
| video 게시 위치와 private repository 접근 범위를 확인함 | 미확인 | 대상에 video가 없을 때만 `해당 없음`으로 판정 |

## 게시 체크

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| `Docs/07_GitHub`의 게시 후보 본문을 검토함 | 미확인 |  |
| Issue/PR 번호와 WorkLog 연결을 확인함 | 미확인 |  |
| 게시 후 snapshot 필요 여부를 판단함 | 미확인 |  |
| video를 Demo Issue 전용 댓글에 한 번만 첨부하고 PR의 중복 업로드를 피함 | 미확인 | 대상에 video가 없을 때만 `해당 없음`으로 판정 |
| selected video의 게시 또는 미게시 판단과 이유를 기록함 | 미확인 | 대상에 selected video가 없을 때만 `해당 없음`으로 판정 |
| video 댓글 permalink, attachment URL과 게시 상태를 merge 전에 동기화함 | 미확인 | PR은 댓글 permalink만 연결하고 대상에 video가 없을 때만 `해당 없음`으로 판정 |

## Bundle 단위 rendered evidence 예외 체크

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| 예외를 적용할 Chapter 또는 Bundle과 사용자 승인을 기록함 | 미확인 | 다른 범위에 자동 적용하지 않음 |
| 원본 runtime asset을 public subset과 GitHub body에 첨부하지 않음 | 미확인 | 원본 파일과 직접 다운로드 링크 포함 금지 |
| 공개 대상이 asset 자체가 아니라 직접 실행한 rendered evidence임 | 미확인 | 구현 동작과 graphics 결과를 설명해야 함 |
| 원본 asset에 대한 권리 확보를 주장하지 않음 | 미확인 | 출처 한계는 Publication 정본에 기록 |
| screenshot·storyboard·video의 공개 안전성을 확인함 | 미확인 | 강의 화면, 워터마크, 계정, 개인정보와 로컬 경로 없음 |
| 원본 asset 교체 backlog와 삭제 요청 대응 기준을 기록함 | 미확인 | 공개 중단 필요 시 evidence 재검토 |
