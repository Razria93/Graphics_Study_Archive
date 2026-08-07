# Chapter14 Ex1407 IndirectArguments Demo

## 목적

Indirect argument buffer를 생성하고 `DrawInstancedIndirect`로 GPU buffer에 저장된 draw argument를 사용한다.

## 책임 범위

- `Ex1407_IndirectArguments`의 indirect argument buffer, density visual과 code evidence를 설명한다.
- Build/run/capture 사실은 [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md)으로 위임한다.
- public 후보 판단은 [Publication Candidate List](../../05_Publication/candidate-list.md)로 위임한다.

## 결과 미리보기

![Chapter14 IndirectArguments](../../_assets/captures/part4_chapter14_07_indirect_arguments.png)

Visual은 `Ex1406` 계열 density trail과 유사하므로, indirect draw 여부는 code evidence와 함께 해석한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | command argument `1407`, particle buffer, density texture, indirect argument buffer |
| 출력 | taskbar-free 640×640 density trail screenshot, `DrawInstancedIndirect` code evidence |

## 구현 흐름

1. Particle buffer와 density texture를 준비한다.
2. `IndirectArgs` 배열을 GPU argument buffer로 만든다.
3. Density texture를 compute shader로 감쇠하고 particle sourcing을 수행한다.
4. Sprite draw에서 SRV와 geometry shader를 바인딩한다.
5. Argument buffer offset을 지정하고 `DrawInstancedIndirect`를 호출한다.

## 핵심 구현

- [Indirect argument buffer 생성](../../../Part4_Chapter14-20/Ex1407_IndirectArguments.cpp#L56-L64)
- [Density update sequence](../../../Part4_Chapter14-20/Ex1407_IndirectArguments.cpp#L91-L137)
- [DrawInstancedIndirect 호출](../../../Part4_Chapter14-20/Ex1407_IndirectArguments.cpp#L142-L190)

## 시각 결과

`Ex1407`의 screenshot은 density trail이 실제로 표시되는지 확인하는 보조 evidence다. 핵심 차이는 CPU draw count가 아니라 GPU argument buffer를 draw call에 넘긴다는 점이다.

## 구현 범위와 한계

- Screenshot만으로 indirect draw 차이는 드러나지 않으므로 code evidence를 필수로 병행한다.
- Trail의 시간 변화는 video 후보지만 현재 범위에서는 static screenshot만 사용한다.
- Release 현재 재검증은 별도 범위다.

## 검증

- [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)
- Debug x64 build/run 성공
- `DrawInstancedIndirect(m_argsGPU.Get(), offset)` code evidence 확인
- PNG RGBA non-interlaced, text metadata chunk 없음

## 관련 코드

- [Example README](../../../Part4_Chapter14-20/README.md)
- [Example selection entry point](../../../Part4_Chapter14-20/main.cpp)

## 관련 문서

- [Demo Index](demo-index.md)
- [Compute Shader And Resource Flow](../../01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [WorkLog WU-Part4](../../04_WorkLogs/work-units/WU-Part4.md)
