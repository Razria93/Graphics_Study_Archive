# Chapter14 Ex1401 Basic Demo

## 목적

Back buffer UAV를 compute shader 출력 대상으로 사용하는 Chapter14의 최소 compute visual 기준선을 확인한다.

## 책임 범위

- `Ex1401_Basic`의 command argument, back buffer UAV 생성, dispatch와 GUI scale 입력을 설명한다.
- Build/run/capture 사실은 [Verification](../../02_Verification/Part4_Chapter14-20/verification-index.md)으로 위임한다.
- public 후보 판단은 [Publication Candidate List](../../05_Publication/candidate-list.md)로 위임한다.

## 결과 미리보기

현재 tracked screenshot은 없다. Debug x64 파일럿에서는 checker pattern local 후보를 확인했으며, fixed UI와 안정된 bounds 기준의 desktop 재촬영 후 승격 여부를 판단한다.

## 입력과 출력

| 구분 | 내용 |
| --- | --- |
| 입력 | command argument `1401`, back buffer texture, `Scale` GUI 값 |
| 출력 | compute shader가 back buffer UAV에 기록한 checker visual local 후보 |

## 구현 흐름

1. Back buffer format을 `DXGI_FORMAT_R16G16B16A16_FLOAT`로 설정한다.
2. Swap chain back buffer에서 UAV를 생성한다.
3. `Scale` 상수를 constant buffer로 갱신한다.
4. Compute shader를 바인딩하고 화면 크기에 맞춰 dispatch한다.
5. Dispatch 이후 `ComputeShaderBarrier`로 compute resource binding을 정리한다.

## 핵심 구현

- [Back buffer UAV 생성](../../../Part4_Chapter14-20/Ex1401_Basic.cpp#L23-L58)
- [Scale constant buffer 갱신](../../../Part4_Chapter14-20/Ex1401_Basic.cpp#L67-L70)
- [Compute dispatch와 barrier](../../../Part4_Chapter14-20/Ex1401_Basic.cpp#L73-L114)

## 시각 결과

이 Step은 Chapter14의 최소 화면 출력 기준선이다. 현재는 local screenshot 후보만 있으므로, 공개용 tracked visual로 쓰기 전 `HLAB_CAPTURE_UI=collapsed`, centered window와 visible client area 기준으로 재촬영한다.

## 구현 범위와 한계

- 현재 문서는 직접 확인한 Debug x64 파일럿 결과만 사용한다.
- tracked screenshot 승격은 아직 하지 않는다.
- Release 현재 재검증은 별도 범위다.

## 검증

- [Verification Index](../../02_Verification/Part4_Chapter14-20/verification-index.md)
- Debug x64 build/run 성공
- checker pattern local screenshot 후보 확인

## 관련 코드

- [ExampleDocs](../../../Part4_Chapter14-20/ExampleDocs/14_01_Basic.md)
- [Example selection entry point](../../../Part4_Chapter14-20/main.cpp)

## 관련 문서

- [Demo Index](demo-index.md)
- [Compute Shader And Resource Flow](../../01_Topics/ComputeAndSimulation/ComputeShaderAndResourceFlow.md)
- [WorkLog WU-Part4](../../04_WorkLogs/work-units/WU-Part4.md)
