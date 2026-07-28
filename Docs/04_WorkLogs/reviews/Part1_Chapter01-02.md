# Part1 Chapter01-02 Review Summary

## 범위

`Part1_Chapter01-02/01_DX11InitAndImGui`와 `Part1_Chapter01-02/02_Bloom`에 적용한 pilot 검토의 재사용 가능한 결론을 기록한다. raw/reference/origin 비교와 source comment inventory 상세는 `local/study-review/`에 위임한다.

## 공통 판단

- 예제 설명 정본은 각 코드 폴더의 `README.md`에 둔다.
- 이전 PartDocs는 참고 전용이며 새 README에는 직접 이해한 public-safe 설명만 남긴다.
- build/run 상태는 `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`를 기준으로 둔다.
- capture/result 상태는 `Docs/03_Demos/Part1_Chapter01-02/demo-index.md`를 기준으로 둔다.
- publication 판단은 `Docs/05_Publication/candidate-list.md`에 위임한다.

## 01_DX11InitAndImGui

### 판단 요약

- Win32 window, DirectX11 device/swap chain, back buffer render target, shader compile, dynamic texture, SRV, full-screen quad, ImGui overlay 흐름을 설명한다.
- ImGui slider와 `backgroundColor` 연결, 움직이는 RGB pixel을 통한 dynamic texture upload를 핵심 구현 포인트로 둔다.
- shader blob release 보강은 resource lifetime 설명 포인트로 활용할 수 있다.
- resize 처리 구현 여부는 후속 코드 검토에서 다시 확인한다.
- 이번 pilot에서는 코드 수정과 Topic 신설을 하지 않는다.
- 기반 render loop 설명용 예제이므로 별도 capture를 만들지 않는다.

### 검증 결과

- Debug/Release x64 build/run: 확인
- shader working directory 의존성: 실행 기준 문제 없음
- Capture: 제외

## 02_Bloom

### 판단 요약

- bloom 개념은 `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md`로 분리한다.
- 내부 조사 기록과 source comment inventory는 Example README에 노출하지 않는다.
- CPU bloom 처리와 DirectX11 dynamic texture upload를 연결하는 pilot 예제로 사용한다.

### 검증 및 승격 결과

- Debug/Release x64 build/run: 확인
- runtime result image 생성: 확인
- ChatGPT 생성 입력 이미지 기반 result를 `Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png`로 승격
- 육안상 강의명, 강사명, watermark, 개인 식별자: 보이지 않음

## 후속 작업

1. Part1의 다음 예제에 같은 workflow를 적용한다.
2. `02_Bloom` result image의 public 후보 여부를 Publication 정본에서 검토한다.
3. Part1 Chapter01-02 이후 범위의 대표 Example과 Demo를 선정한다.
