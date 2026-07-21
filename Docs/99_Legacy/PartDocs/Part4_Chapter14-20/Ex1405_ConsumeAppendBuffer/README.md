# Ex1405 ConsumeAppendBuffer

`Ex1405_ConsumeAppendBuffer`는 `ConsumeStructuredBuffer`와 `AppendStructuredBuffer`를 사용해 particle 데이터를 GPU 안에서 꺼내고 다시 쌓는 예제입니다. `Ex1404_StructuredBuffer`의 particle 렌더링 흐름을 재사용하되, compute shader에서 consume/append counter를 이용해 버퍼를 처리합니다.

## 목적

- consume/append structured buffer의 counter 기반 동작을 확인합니다.
- compute shader가 particle을 consume하고 갱신한 뒤 append하는 흐름을 확인합니다.
- `CopyStructureCount()`로 append buffer에 쌓인 element count를 읽는 과정을 확인합니다.
- append count만큼 point list를 draw하는 흐름을 확인합니다.

## 핵심 흐름

1. CPU에서 25,600개의 particle position/color를 생성합니다.
2. `m_consume`, `m_append` 두 개의 `AppendBuffer<Particle>`를 초기화합니다.
3. compute shader에 consume UAV와 append UAV를 함께 바인딩합니다.
4. `initCounts`로 consume buffer의 초기 count와 append buffer의 초기 count를 지정합니다.
5. compute shader가 `Consume()`으로 particle을 읽고 position을 갱신한 뒤 `Append()`로 출력합니다.
6. `CopyStructureCount()`로 append buffer count를 staging buffer로 복사합니다.
7. vertex shader는 `m_append`의 SRV를 읽어 point list를 렌더링합니다.
8. 프레임 끝에서 `m_consume`과 `m_append`를 swap해 다음 프레임의 입출력 역할을 바꿉니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1405_ConsumeAppendBuffer.cpp` | consume/append buffer 초기화, compute dispatch, append count draw |
| `Ex1405_ConsumeAppendBuffer.h` | consume/append buffer와 count staging 멤버 정의 |
| `Ex1405_ConsumeAppendCS.hlsl` | `Consume()` / `Append()`로 particle 갱신 |
| `StructuredBuffer.h` | `AppendBuffer<T>` helper와 swap 구현 |
| `Buffers.h` | `StagingBuffer<uint32_t>` helper |
| `Ex1404_StructuredBufferVS.hlsl` | append 결과 particle rendering |
| `Ex1404_StructuredBufferPS.hlsl` | particle color 출력 |
| `main.cpp` | command argument `1405`로 `Ex1405_ConsumeAppendBuffer` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1405`를 지정해야 합니다.

```text
Examples.exe 1405
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- 검은 배경 위에 particle point cloud가 출력되는지 확인
- console에 `AppendBuffer count`가 출력되는지 확인
- particle들이 시간에 따라 이동/회전하는지 확인

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
