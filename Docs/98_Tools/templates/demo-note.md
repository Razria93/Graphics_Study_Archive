# Demo Name

이 template은 `Docs/03_Demos/<Part*>`의 상세 Demo 기술 정본에 사용한다. GitHub Demo Issue는 이 문서를 복제하지 않고 공개 가치가 높은 결과와 구현을 선별해 작성한다.

## 목적

Demo가 보여주는 결과와 기술적 목표를 2~4문장으로 정의한다.

## 책임 범위

- 포함:
- 위임: 개념과 이론은 Topic, 검증 사실은 Verification으로 연결한다.

## 결과 미리보기

대표 visual을 1개 이상 연결하고 결과가 보여주는 차이를 설명한다.

![Result](../../_assets/captures/<tracked-result>.png)

동적 입력이나 상태 전환을 storyboard로 설명할 때는 다음 항목을 사용한다.

### <Storyboard 제목>

`<초기 상태> → <입력 상태> → <결과 상태>` 순서로 왼쪽 위에서 오른쪽 아래로 본다.

![Storyboard](../../_assets/captures/<tracked-storyboard>.png)

- 입력 변화:
- 관찰 지점:
- 구현 결과:

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 |  |
| 출력 |  |

## 구현 흐름

1. 입력을 준비한다.
2. 핵심 처리를 수행한다.
3. 결과를 출력한다.

## 핵심 구현

### Implementation Choice

선택한 구현 방식, 주요 코드 위치, 선택 이유를 설명한다.

### 선택형 의사코드

처리 단계가 여러 함수나 CPU/GPU 경계를 넘어 prose만으로 구조를 파악하기 어려울 때만 사용한다. 실제 코드를 복제하지 않고 입력, 핵심 처리, 출력 흐름을 짧게 요약한다. 함수와 제어문 block은 Allman brace style을 사용한다.

```cpp
// Pseudo C++: 구현 구조 요약
auto input = PrepareInput();
if (!input.IsValid())
{
    return;
}

auto result = Process(input);
Publish(result);
```

- [입력 준비와 핵심 처리](../../../Part_Chapter/Example/Example.cpp#L1-L20)

## 시각 결과

시각 자료가 구현 단계나 결과 차이를 어떻게 보여주는지 설명한다. 같은 asset을 README와 GitHub body에서도 사용할 수 있지만 설명은 이 문서 책임에 맞게 쓴다.

Video가 필수 또는 선택이면 필요성, 관찰할 변화, selected와 published 상태를 짧게 기록한다. Tracked 상세 Demo는 핵심 screenshot을 유지하고 published video는 실제 Demo Issue로 연결한다.

## 구현 범위와 한계

- 포함하는 구현 범위:
- 다루지 않는 범위:
- 성능 또는 품질 trade-off:

## 검증

최신 build/run/capture 사실을 복제하지 않고 Verification 정본으로 연결한다.

- Verification:

## 관련 코드

- Example README:
- [Scene 구성과 핵심 처리](../../../Part_Chapter/Example/Example.cpp#L1-L20)
- [결과 texture sampling](../../../Part_Chapter/Example/PS.hlsl#L1-L20)

## 관련 문서

- Topic:
- Verification:
- Demo index:
- GitHub Demo Issue 후보:

## 작성 기준

- Example README의 코드 map과 실행 안내를 장문으로 복제하지 않는다.
- Topic의 일반 개념과 수학적 설명을 복제하지 않는다.
- 실제 Markdown 링크와 tracked `Docs/_assets`만 사용한다.
- `local/`, Legacy, placeholder, 로컬 절대 경로를 남기지 않는다.
- 상세 Demo의 `cpp` fence는 첫 비공백 줄에 `// Pseudo C++:`와 요약을 두고 대응 원본 코드 링크를 함께 둔다.
- 실제 C++ source는 code block으로 복제하지 않고 source line 링크로 연결한다.
- 함수와 `if`, `else`, `for`, `while`의 여는 중괄호는 다음 줄에 둔다.
- 제어문과 함수 block을 한 줄로 압축하지 않는다.
- braced initializer와 multiline signature는 의미를 유지하고 수동 확인한다.
- 의사코드는 모든 Demo의 필수 항목으로 강제하지 않는다.
- Source line 코드 근거 bullet은 구현 역할을 나타내는 명사형 link label을 사용하고 끝에 마침표를 붙이지 않는다.
- 일반 문단과 하나의 목록 항목은 각각 하나의 물리적 줄로 작성한다. 상세 기준은 [Docs Authoring Flow Policy](../../06_Policies/docs-authoring-flow-policy.md)를 따른다.
- 의사코드와 code block은 한 줄 80자 내외를 권장하고 120자를 초과하지 않는다.
