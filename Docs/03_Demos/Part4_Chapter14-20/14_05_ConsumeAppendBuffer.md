# Chapter14 Ex1405 ConsumeAppendBuffer Demo

## 목적

Consume/Append buffer counter를 확인하고 append count를 draw count로 사용하는 흐름을 설명한다.

## 책임 범위

- `Ex1405_ConsumeAppendBuffer`의 append counter, stdout evidence와 tracked screenshot을 설명한다.
- Build/run/capture 사실은 [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md)으로 위임한다.
- public 후보 판단은 [Publication Candidate List](../../05_Publication/candidate-list.md)로 위임한다.

## 결과 미리보기

![Chapter14 ConsumeAppendBuffer](../../_assets/captures/part4_chapter14_05_consume_append_buffer.png)

Point cloud visual과 `AppendBuffer count: 25600` stdout을 함께 evidence로 사용한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | command argument `1405`, consume buffer, append buffer |
| 출력 | taskbar-free 1280×1280 point cloud screenshot, append count stdout |

## 구현 흐름

1. Consume buffer에 particle 25600개를 초기화한다.
2. Append buffer와 counter staging buffer를 준비한다.
3. Compute shader가 consume buffer에서 읽고 append buffer에 다시 쌓는다.
4. `CopyStructureCount`로 append counter를 staging buffer에 복사한다.
5. Download한 `appendCount`를 `Draw(appendCount, 0)`에 사용한다.
6. 프레임 끝에서 consume/append buffer 역할을 교체한다.

## 핵심 구현

- [Consume/Append buffer 준비](../../../Part4_Chapter14-20/Ex1405_ConsumeAppendBuffer.cpp#L26-L55)
- [Append counter 복사와 append count draw](../../../Part4_Chapter14-20/Ex1405_ConsumeAppendBuffer.cpp#L98-L130)
- [Consume/Append buffer swap](../../../Part4_Chapter14-20/Ex1405_ConsumeAppendBuffer.cpp#L134-L139)

## Stdout evidence

```text
AppendBuffer count: 25600
```

## 시각 결과

`Ex1405`는 `Ex1404`와 point cloud가 유사하지만, append counter가 draw count로 이어지는 점이 핵심이다. Screenshot은 visual 보조 evidence이고 stdout이 counter 검증 evidence다.

## 구현 범위와 한계

- Screenshot은 centered client-visible fixed UI 후보로 승격했다.
- 현재 구현은 append count를 CPU staging buffer로 내려받아 draw count로 다시 넘긴다.
- CPU download 없이 draw argument를 넘기는 흐름은 `Ex1407`에서 별도로 설명한다.

## 검증

- [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)
- Debug x64 build/run 성공
- `AppendBuffer count: 25600` stdout 확인
- PNG RGBA non-interlaced, text metadata chunk 없음

## 관련 코드

- [Example README](../../../Part4_Chapter14-20/README.md)
- [Example selection entry point](../../../Part4_Chapter14-20/main.cpp)

## 관련 문서

- [Demo Index](demo-index.md)
- [Compute And Simulation Topic Index](../../01_Topics/ComputeAndSimulation/topic-index.md)
- [WorkLog WU-Part4](../../04_WorkLogs/work-units/WU-Part4.md)
