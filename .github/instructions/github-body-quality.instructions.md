---
applyTo: Docs/07_GitHub/**/*.md
description: "Use when writing or editing GitHub body docs. Enforce portfolio-grade quality for structure, narrative flow, media attachment, code blocks, and C++-style pseudocode."
---

# GitHub Body Quality Instructions

이 문서는 `Docs/07_GitHub` 본문 품질을 항상 같은 수준으로 유지하기 위한 고정 규칙이다.

## 목표

- 문서 양식과 전개 순서를 일관되게 유지한다.
- screenshot/video/result image 첨부 방식을 표준화한다.
- 코드 블럭은 복제보다 이해 중심 요약을 우선한다.
- 의사코드는 C++ 독자가 바로 읽을 수 있는 형태로 작성한다.

## 공통 규칙

- 첫 H1을 title source로 유지한다.
- 필수 `##` 섹션 순서를 지킨다.
- 섹션은 비워 두지 않는다.
- source docs 복제 대신 요약과 링크를 사용한다.
- 내부 메모, TODO, TBD, draft 문구를 남기지 않는다.

## Demo Issue 전개

- `요약`: 결과와 핵심 구현 2~4문장
- `결과`: 대표 visual 1~3개
- `핵심 구현`: 결과에 직접 연결되는 선택 3~5개
- `처리 흐름`: 짧은 단계형 목록
- `구현 범위와 한계`: 독자가 오해하기 쉬운 제한
- `검증`: build/run과 capture/result 요약
- `더 자세히 보기`: 상세 Demo, Example, Topic, Verification, PR 링크

## 이미지와 동영상 규칙

- Demo Issue는 screenshot 최소 1개를 포함한다.
- Demo Issue는 대표 visual을 최소 1개 포함한다.
- GitHub body 이미지 URL은 GitHub absolute URL만 사용한다.
- screenshot/result image는 `Docs/_assets/captures`를 사용한다.
- video가 없으면 `없음`과 사유를 함께 적는다.
- 각 이미지는 `###` 소제목 + 설명 문장 + 이미지 Markdown 순서를 유지한다.

## Demo 검증 상태 규칙

- Demo Issue의 검증 상태는 build/run과 capture/result 결과만 2~3줄로 요약한다.
- 결과에 영향을 주지 않는 환경 경고와 조사 메모는 `Docs/02_Verification` 정본으로 위임한다.
- 구현의 기술적 제한은 `## 구현 범위와 한계`에 둔다.
- 관련 PR은 별도 운영 섹션을 만들지 않고 `## 관련 문서`에 링크한다.

## 코드 블럭 규칙

- 코드 섹션은 원문 복제가 아니라 구조 전달이 목적이다.
- 긴 식은 2~3줄로 분해한다.
- 한 줄 길이는 약 80자 내외를 권장한다.
- 중첩 루프/조건문의 한 줄 압축 표기를 피한다.

## 의사코드 규칙

- 의사코드는 핵심 구현 이해에 도움이 될 때만 사용한다.
- 사용한 의사코드는 C++ 스타일 문법(함수, 블록, for, if)으로 작성한다.
- 블럭 시작에 `Pseudo C++` 성격을 명시한다.
- 입력, 처리 단계, 실패 분기, 출력을 모두 보여준다.
- 구현 세부는 생략하고 알고리즘 구조만 남긴다.
- 각 의사코드 블럭 아래에 원본 코드 링크를 둔다.

## PR 연계 규칙

- PR 본문은 요약과 링크 허브 역할만 유지한다.
- Demo 상세(시각 자료, 의사코드, 구현 하이라이트)는 Demo Issue로 위임한다.
- PR 대표 visual은 0~1개만 사용한다.
- Demo Issue가 미게시 상태면 상세 Demo 정본으로 직접 연결한다.

## 작성 후 자기 검수

- 필수 섹션 순서가 맞는지 확인한다.
- 의사코드가 C++ 독자 기준으로 읽히는지 확인한다.
- 긴 줄이 뷰포트에서 과도하게 잘리지 않는지 확인한다.
- 이미지 URL이 절대 URL인지 확인한다.
- source docs 링크가 누락되지 않았는지 확인한다.
