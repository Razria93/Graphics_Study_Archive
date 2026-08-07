# Chapter14 Ex1401 Basic

## Overview

`Ex1401_Basic`은 compute shader가 back buffer UAV에 checker pattern을 기록하는 최소 Chapter14 예제다. `Examples.exe 1401`은 back buffer format, UAV binding, thread group dispatch와 compute resource binding 해제의 연결을 보여 준다.

## 실행 진입점

- Solution: `Part4_Chapter14-20/Examples.sln`
- Application entry: `Examples.exe 1401`
- 주요 source: `Ex1401_Basic.cpp`, `Ex1401_CS.hlsl`
- Shader: `Ex1401_CS.hlsl`

## Code Map

| 파일 | 역할 |
| --- | --- |
| [main.cpp](../main.cpp#L38) | command argument `1401`을 `Ex1401_Basic` instance에 연결 |
| [Ex1401_Basic.cpp](../Ex1401_Basic.cpp#L23) | back buffer UAV, constant buffer, dispatch와 compute barrier 구성 |
| [Ex1401_CS.hlsl](../Ex1401_CS.hlsl#L1) | checker pattern을 back buffer UAV에 기록 |

## Capture/Result

tracked capture는 아직 없다. checker pattern은 local 후보로만 확인했으며, 대표 visual 승격 전에는 상세 Demo의 capture 기준과 Verification 기록을 사용한다.

## Verification

| 항목 | 결과 | 비고 |
| --- | --- | --- |
| Debug x64 build/run | 성공 | 2026-08-06 파일럿 확인 |
| Release x64 build/run | 과거 확인 | 현재 재검증은 별도 범위 |
| Capture/Result | local 후보 | tracker visual 승격 전 상태 |

## Limitations

- checker pattern은 compute dispatch와 back buffer UAV 출력 기준선이며 복잡한 simulation 결과를 표현하지 않는다.
- 대표 capture는 fixed UI와 안정된 window bounds 기준 재촬영 후 별도 승격한다.

## Related Docs

- [Chapter14-20 README](../README.md)
- [Compute Shader And Resource Flow](../../Docs/01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [Part4 Verification](../../Docs/02_Verification/Part4_Chapter14-20/verification-index.md)
- [Chapter14 Ex1401 Basic Demo](../../Docs/03_Demos/Part4_Chapter14-20/14_01_Basic.md)
- [Publication Candidate List](../../Docs/05_Publication/candidate-list.md)