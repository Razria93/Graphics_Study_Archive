# Ex1407 IndirectArguments

`Ex1407_IndirectArguments`는 `DrawInstancedIndirect()`를 사용해 draw call의 인자를 GPU buffer에서 읽는 예제입니다. 시각 출력은 `Ex1406_DensityField`의 density/sprite rendering 흐름을 거의 그대로 재사용하지만, draw count를 CPU 함수 인자로 직접 넘기지 않고 indirect argument buffer에 저장된 값으로 실행합니다.

## 목적

- `D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS` buffer의 역할을 확인합니다.
- `DrawInstanced()`와 `DrawInstancedIndirect()`의 호출 방식 차이를 확인합니다.
- GPU에서 생성하거나 갱신할 수 있는 draw argument를 렌더링 단계에서 사용하는 흐름을 확인합니다.
- 이후 GPU culling, indirect draw, particle rendering 최적화 예제로 이어질 기반을 확인합니다.

## 핵심 흐름

1. CPU에서 256개의 particle position/color를 생성합니다.
2. `StructuredBuffer<Particle>`와 density texture를 초기화합니다.
3. `IndirectArgs` 배열을 만들고 `CreateIndirectArgsBuffer()`로 GPU argument buffer를 생성합니다.
4. compute shader가 density texture를 감쇠시키고 particle position을 갱신합니다.
5. vertex shader/geometry shader/pixel shader는 `Ex1406`과 같은 sprite rendering 경로를 사용합니다.
6. `DrawInstancedIndirect(m_argsGPU.Get(), offset)`이 argument buffer의 `UINT` 4개 값을 읽어 draw를 실행합니다.

## 핵심 파일

| File | Role |
| --- | --- |
| `Ex1407_IndirectArguments.cpp` | indirect args buffer 생성, density update, `DrawInstancedIndirect()` 호출 |
| `Ex1407_IndirectArguments.h` | `IndirectArgs` 구조체와 argument buffer 멤버 정의 |
| `D3D11Utils.cpp` / `D3D11Utils.h` | `CreateIndirectArgsBuffer()` helper |
| `Ex1406_DensitySourcingCS.hlsl` | particle position 갱신 |
| `Ex1406_DensityDissipationCS.hlsl` | density texture 감쇠 |
| `Ex1406_SpriteGS.hlsl` | point를 quad sprite로 확장 |
| `Ex1406_SpritePS.hlsl` | sprite 내부 원형 falloff 출력 |
| `Ex1404_StructuredBufferVS.hlsl` | particle structured buffer를 vertex shader에서 읽음 |
| `main.cpp` | command argument `1407`로 `Ex1407_IndirectArguments` 선택 |

## 실행 메모

Part4는 단일 executable이 command-line argument로 예제를 선택합니다. Visual Studio에서 직접 실행할 경우 `Debugging > Command Arguments`에 `1407`을 지정해야 합니다.

```text
Examples.exe 1407
```

## 확인 포인트

- Debug x64 build/run
- Release x64 build/run
- `Ex1406`과 유사한 density sprite/trail이 출력되는지 확인
- indirect argument buffer offset 0 기준으로 일부 particle만 그려지는지 확인
- 별도 runtime asset 없이 실행되는지 확인

## Archive 상태

- Source/project import: 완료
- Required asset: 없음
- Build/run: 미확인
- Source comment split: 2차 문서 정리 단계로 보류
- Public readiness: 검토 필요
