# Ex1404 StructuredBuffer

`Ex1404_StructuredBuffer`는 GPU buffer에 particle 데이터를 담고, compute shader가 위치를 갱신한 뒤 vertex shader가 같은 buffer를 읽어 point list로 렌더링하는 예제입니다.

## 목적

- `StructuredBuffer` / `RWStructuredBuffer` 기반 GPU data flow를 확인합니다.
- compute shader가 particle position을 갱신하는 흐름을 확인합니다.
- vertex buffer 없이 `SV_VertexID`로 structured buffer를 조회해 point를 그리는 방식을 확인합니다.
- SRV/UAV view를 같은 GPU buffer에 대해 단계별로 사용하는 구조를 확인합니다.

## 핵심 흐름

1. CPU에서 25,600개의 particle position/color를 생성합니다.
2. `StructuredBuffer<Particle>` helper로 GPU buffer, SRV, UAV를 생성합니다.
3. compute shader가 `RWStructuredBuffer<Particle>`를 통해 particle position을 갱신합니다.
4. `ComputeShaderBarrier()`로 compute shader binding을 정리합니다.
5. input layout과 vertex buffer 없이 point list draw를 수행합니다.
6. vertex shader가 `SV_VertexID`로 `StructuredBuffer<Particle>`를 인덱싱합니다.
7. pixel shader가 particle color를 출력합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1404_StructuredBuffer.cpp` | particle 초기화, structured buffer 생성, compute update, point rendering |
| `Ex1404_StructuredBuffer.h` | `Particle` 구조와 structured buffer/shader 멤버 정의 |
| `Ex1404_StructuredBufferCS.hlsl` | `RWStructuredBuffer`로 particle position 갱신 |
| `Ex1404_StructuredBufferVS.hlsl` | `StructuredBuffer`와 `SV_VertexID`로 point position/color 생성 |
| `Ex1404_StructuredBufferPS.hlsl` | particle color 출력 |
| `StructuredBuffer.h` | SRV/UAV/staging buffer helper |
| `main.cpp` | command argument `1404`로 `Ex1404_StructuredBuffer` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1404`를 지정해야 합니다.

```text
Examples.exe 1404
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- 검은 배경 위에 여러 색의 point cloud가 출력되는지 확인
- particle들이 시간이 지나며 회전/이동하는지 확인
- 별도 GUI 조작은 핵심 확인 대상이 아닙니다.

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
