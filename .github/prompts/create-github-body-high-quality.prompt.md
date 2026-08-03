---
description: "Create a high-quality GitHub body draft with clear results, implementation evidence, and source-doc links."
mode: ask
tools:
  - codebase
  - editFiles
---

# Create High Quality GitHub Body

다음 입력을 받아 `Docs/07_GitHub` 후보 본문을 생성한다.

## 입력

- body 유형: PR / Demo Issue / Verification Issue / Work Unit Issue / plan body / plan comment
- 대상 파일 경로
- 대상 범위(Part/Chapter/Example)
- 연결 source docs 경로 목록
- screenshot/storyboard/result image 경로 또는 URL
- 게시된 video 댓글 permalink(있는 경우)
- 원본 코드 링크 후보

## 생성 규칙

1. 파일 첫 줄은 H1 title source로 시작한다. comment body는 H1을 쓰지 않는다.
2. 해당 유형의 필수 섹션 순서를 지킨다.
3. source docs를 복제하지 말고 요약+링크로 재구성한다.
4. Demo Issue는 대표 결과를 먼저 제시하고 상세 Demo 정본을 연결한다.
5. 핵심 구현은 구현 선택, 결과 영향, 인접한 게시 시점 코드 증거로 구성한다.
6. 코드 link label은 파일명 대신 확인할 구현 역할을 설명한다.
7. 의사코드는 핵심 구현 이해에 도움이 될 때만 1개 이내로 사용한다.
8. 상세 Demo에 같은 의사코드가 있으면 Demo Issue에 복제하지 않는다.
9. 의사코드를 사용하면 아래에 원본 코드 permalink를 둔다.
10. 문체는 한국어 중심 평서형 현재형을 유지한다.
11. TODO/TBD/placeholder를 남기지 않는다.
12. 일반 문단과 하나의 목록 항목은 각각 하나의 물리적 줄로 작성하고 화면 줄바꿈은 GitHub에 맡긴다. 상세 기준은 [Docs Authoring Flow Policy](../../Docs/06_Policies/docs-authoring-flow-policy.md)를 따른다.

## C++ 스타일 의사코드 형식

```cpp
// Pseudo C++: 구조 설명용 요약
void FunctionPseudo(...)
{
    // 입력/전처리
    if (...)
    {
        return;
    }

    for (...)
    {
        ...
    }

    // 출력/반영
}
```

## 완료 체크리스트

- 섹션 순서와 필수 섹션 확인
- 이미지 URL 형식 확인
- code block의 80자 권장과 120자 상한, 일반 문단의 단일 물리 줄 확인
- `Pseudo C++` 함수와 제어문의 Allman brace style 및 한 줄 block 금지 확인
- 의사코드와 원본 코드 링크 쌍 확인
- 구현 선택과 결과 영향이 연결되는지 확인
- 코드 증거가 commit permalink와 line anchor를 사용하는지 확인
- link label이 확인할 구현 역할을 설명하는지 확인
- validator 실행 가능 상태 확인
- Demo Issue는 상세 Demo 전체를 복제하지 않았는지 확인
- 출처 또는 재배포 조건이 불완전한 runtime asset 원본과 직접 링크가 없는지 확인
- 승인된 Bundle 예외는 구현 결과 visual만 사용하고 내부 출처 검토 문구를 public body에서 제외
