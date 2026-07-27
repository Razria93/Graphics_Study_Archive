## Phase 2-1 완료 기록

## 완료 내용

- `Part1_Chapter01-02` Chapter/Bundle 범위의 README, Topic, Verification, Demo, PR 후보 연결을 정리했다.
- `02_Bloom` input/result 비교 이미지를 Chapter PR과 정본 문서에서 참조 가능한 형태로 정리했다.
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
- `Docs/02_Verification/known-issues.md`의 VI-003 기준으로 build 성공과 별개로 `pwsh.exe` 경고가 관찰된다.
- input/result 이미지는 private archive PR 기준으로 사용 가능 상태다. public subset 승격 확정은 `Docs/05_Publication` 기준으로 별도 판단한다.

## Related PR

- 예정: Part1 Chapter01-02 DirectX11 Initialization and CPU Bloom PR
- 댓글 게시 전에는 예정 표기를 실제 PR 번호 또는 PR URL로 교체한다.