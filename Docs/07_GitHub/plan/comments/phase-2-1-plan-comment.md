## Phase 2-1 완료 기록

## 완료 내용

- `Part1_Chapter01-02` Chapter/Bundle 범위의 README, Topic, Verification, Demo, Draft PR #8 연결을 정리했다.
- `02_Bloom` input/result 비교 이미지와 구현 요약을 [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9)에 게시했다.
- 이 기록은 WU-Part1 전체 완료가 아니라 WU-Part1 안의 Chapter01-02 완료 기록이다.

## 검증

- `01_DX11InitAndImGui` Debug x64 build/run: 확인
- `01_DX11InitAndImGui` Release x64 build/run: 확인
- `02_Bloom` Debug x64 build/run: 확인
- `02_Bloom` Release x64 build/run: 확인
- `02_Bloom` input/result image를 README, Demo, PR 본문에서 연결 확인

## 남은 제한

- `01_DX11InitAndImGui`는 기반 렌더 루프 설명용 예제라 별도 capture/result를 만들지 않는다.
- `02_Bloom`은 GPU multi-pass bloom pipeline이 아니라 CPU image processing 결과를 dynamic texture로 표시하는 예제다.
- input/result 이미지는 metadata와 개인 식별자 검수를 완료했다.

## Related PR

- PR #8 (Draft): Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom
