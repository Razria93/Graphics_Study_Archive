# Demo Issues

이 폴더는 Demo Issue 정본을 둔다.

## 파일명 규칙

- `demo_<slug>.md`

## 생성 기준

- 독립적인 시각·기술 공개 가치가 있을 때 생성한다.

## 게시 후보

- [Part3 Chapter10 Geometry Pipeline](demo_part3_chapter10.md)
- [Part3 Chapter11 Texturing Techniques](demo_part3_chapter11.md)
- [Part3 Chapter12 Physically Based Rendering](demo_part3_chapter12.md)
- [Part3 Chapter13 Light And Shadow](demo_part3_chapter13.md)
- [Part4 Chapter14 Compute Shader Evidence](demo_part4_chapter14.md)

## 작성 기준

- 첫 H1을 title source로 유지한다.
- PR 본문 요약으로 부족한 시각 자료와 구현 개괄을 보강한다.
- 대표 visual 1~3개와 각 결과가 무엇을 보여주는지 설명한다.
- 본문 visual은 screenshot 또는 storyboard로 구성하고 video 없이도 구현과 결과를 이해할 수 있게 작성한다.
- Storyboard는 제목, 읽는 방향, 입력 또는 상태 변화, 관찰 결과와 구현 목적을 함께 설명한다.
- Video는 하나의 독립 설명 축마다 전용 댓글로 게시하고 본문에 직접 삽입하지 않는다.
- 같은 설명 축을 개선하면 기존 댓글을 수정하고 다른 설명 축이면 새 댓글을 추가한다.
- PR은 video attachment 대신 Demo Issue video comment permalink를 연결한다.
- 핵심 구현은 구현 선택, 결과에 미치는 영향, 인접한 commit permalink를 함께 제공한다.
- 구현 설명은 하이라이트 중심으로 제한하고 상세 구현은 상세 Demo로 위임한다.
- 기술 keyword만 나열하거나 여러 역할을 포괄적인 코드 링크 하나로 연결하지 않는다.
- 의사코드는 설명에 도움이 될 때만 선택적으로 사용한다.
- 의사코드는 가능하면 C++ 스타일 문법(함수, for, if, 블록)으로 작성해 읽기 흐름을 유지한다.
- 의사코드는 핵심 구조(입력, 처리 단계, 출력, 실패 분기)만 보여주고 세부 구현은 생략한다.
- 의사코드 한 줄 길이는 약 80자 내외를 권장하고, 긴 식은 2~3줄로 분해한다.
- 의사코드를 사용하면 각 블럭 아래에 원본 라인 링크를 둔다.
- 상세 Demo에 같은 의사코드가 있으면 Demo Issue에 그대로 복제하지 않는다.
- 검증 상태는 요약 2~3줄로 유지한다.
- 결과에 영향을 주지 않는 환경 경고와 조사 메모는 Verification 정본으로 위임한다.
- 기술적 제한은 `## 구현 범위와 한계`에 기록한다.
- 토픽 이론 설명은 `Docs/01_Topics`로 위임하고, Demo Issue는 시각 정보와 구현 개괄 중심으로 유지한다.
- capture/result 상세 근거는 `Docs/03_Demos` 정본으로 연결한다.
- 관련 PR은 별도 운영 섹션 대신 `## 관련 문서`에 링크한다.
- 작업 관리용 `## 제외 범위`는 사용하지 않는다.
- Demo Issue는 게시 시점 snapshot이며 중요한 구현, 결과, limitation 변경 시 갱신 필요 여부를 확인한다.
