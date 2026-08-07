# Part4 ExampleDocs

이 폴더는 `Examples.sln` 단일 project에 모인 Part4 Example의 근거리 안내 정본을 둔다. Part4는 예제별 코드 폴더를 만들지 않으므로, 이 폴더의 Markdown 문서가 다른 Part의 예제 폴더 `README.md`와 같은 책임을 맡는다.

## 작성 기준

- 파일명은 상세 Demo와 같은 `Chapter_ExampleName.md` 형식을 사용한다.
- 각 문서는 예제 목적, command argument, 주요 source 또는 shader, 예제 고유 구조, limitation과 관련 정본 링크를 둔다.
- build/run/capture 결과는 [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)으로, 구현 흐름과 시각 결과는 [Part4 Demo Index](../../Docs/03_Demos/Part4_Chapter14-20/demo-index.md)로 위임한다.
- capture/result가 있는 경우 대표 visual은 최대 1개만 연결하고 다중 frame 해석은 상세 Demo로 위임한다.

## 현재 문서

| Chapter | ExampleDocs | 상태 |
| --- | --- | --- |
| Chapter14 | [Ex1401 Basic](14_01_Basic.md) | pilot |

## 관련 문서

- [Part4 Chapter14-20 README](../README.md)
- [Example README Template](../../Docs/98_Tools/templates/example-readme.md)
- [ExampleDocs Validator](../../Docs/98_Tools/validators/validate-example-doc-quality.ps1)