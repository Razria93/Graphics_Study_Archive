---
description: "Create a high-quality GitHub body draft for Docs/07_GitHub with strict structure, visual attachments, and C++-style pseudocode sections."
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
- screenshot/video/result image 경로 또는 URL
- 원본 코드 링크 후보

## 생성 규칙

1. 파일 첫 줄은 H1 title source로 시작한다. comment body는 H1을 쓰지 않는다.
2. 해당 유형의 필수 섹션 순서를 지킨다.
3. source docs를 복제하지 말고 요약+링크로 재구성한다.
4. Demo 계열은 시각 정보를 먼저 제시한다.
5. 코드 섹션은 C++ 스타일 의사코드 1부터 2개만 포함한다.
6. 의사코드 아래에는 반드시 원본 코드 링크를 둔다.
7. 문체는 한국어 중심 평서형 현재형을 유지한다.
8. TODO/TBD/placeholder를 남기지 않는다.

## C++ 스타일 의사코드 형식

```cpp
// Pseudo C++: 구조 설명용 요약
void FunctionPseudo(...)
{
    // 입력/전처리
    if (...) {
        return;
    }

    for (...) {
        ...
    }

    // 출력/반영
}
```

## 완료 체크리스트

- 섹션 순서와 필수 섹션 확인
- 이미지 URL 형식 확인
- 줄 길이 과밀 여부 확인
- 의사코드와 원본 코드 링크 쌍 확인
- validator 실행 가능 상태 확인
