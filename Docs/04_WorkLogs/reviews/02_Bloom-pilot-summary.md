# 02_Bloom Pilot Summary

## 범위

`Part1_Chapter01-02/02_Bloom`을 새 문서화 workflow의 첫 pilot으로 검증했다.

## 판단 요약

- 예제 README 정본은 `Part1_Chapter01-02/02_Bloom/README.md`로 둔다.
- 내부 조사 기록, raw/reference/origin 비교, source comment inventory는 README에 노출하지 않는다.
- bloom 설명은 `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md`로 분리한다.
- build/run 상태는 `Docs/02_Verification/Part1_Chapter01-02/verification-index.md`를 기준으로 둔다.
- demo capture/result 상태는 `Docs/03_Demos/Part1_Chapter01-02/demo-index.md`를 기준으로 둔다.
- publication 후보 판단은 `Docs/05_Publication/candidate-list.md`에서 `검토 필요`로 유지한다.

## 검증 결과

- Debug x64 build/run: 확인
- Release x64 build/run: 확인
- runtime result image 생성: 확인
- tracked capture/result 승격: 보류

## 보류 사유

`result.png`는 ChatGPT 생성 입력 이미지로 재생성했고 육안상 강의명/강사명/워터마크/개인 식별자는 보이지 않는다. 다만 `Docs/_assets` 승격과 public capture/result 판단은 별도 검수 전까지 보류한다.

## 후속 작업

- Part1의 다음 예제에 같은 workflow를 적용한다.
- `02_Bloom` result image를 `Docs/_assets`로 승격할지 별도 검수한다.
- Part1 단위 Issue/PR draft 작성 여부는 다음 예제 정리 후 판단한다.
