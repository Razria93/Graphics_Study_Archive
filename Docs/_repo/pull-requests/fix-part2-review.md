# PR: Part2 review fixes

## Title

```text
fix: Part2 review blocking 이슈 보완
```

## Body

## 요약

- Part2 archive PR 이후 남은 review blocking 이슈 4건을 `main` 기준 fix 브랜치에서 보완합니다.
- 강의 원본 자료와 reference solution 후보의 의미를 문서에서 분리했습니다.
- clean checkout 빌드 재현성을 위해 Part2 공통 STB include 경로를 추가했습니다.
- Texturing 예제의 RGBA texture load 경로를 보정했습니다.
- BloomEffect의 back buffer 복사 경로를 `CopyResource()` 기준으로 정리하고 실행 확인 기록을 갱신했습니다.

## 범위

- Base: `main`
- Head: `fix/part2-review`
- 변경 대상:
  - `Docs/_repo/manifests/Part2_Chapter05-08.md`
  - `Part2_Chapter05-08/README.md`
  - `Part2_Chapter05-08/Directory.Build.props`
  - `Part2_Chapter05-08/06_GraphicsPipeline_Step5_Texturing/AppBase.cpp`
  - `Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/ExampleApp.cpp`
  - `Docs/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/README.md`
  - `Docs/Part2_Chapter05-08/08_ShaderToys_Step6_BloomEffect/status.md`

## 리뷰 대응

- `*_Lecture` 문구를 강의 원본 자료가 아니라 private archive 비교용 reference solution 후보로 명확히 수정
- Part2 전체 프로젝트에서 `ThirdParty/stb`를 찾을 수 있도록 `Directory.Build.props` 추가
- `DXGI_FORMAT_R8G8B8A8_UNORM` texture 생성에 맞춰 `stbi_load(..., 4)`로 RGBA load 강제
- BloomEffect back buffer 복사를 `CopyResource()`로 변경하고 clean/rebuild 후 Debug/Release 실행 및 blur 조작 정상 확인

## Build / Run

- `06_GraphicsPipeline_Step5_Texturing`
  - Debug/Release 실행 확인
  - texture 2개 정상 출력 및 조작 정상 확인
- `08_ShaderToys_Step6_BloomEffect`
  - clean/rebuild 후 Debug/Release 실행 확인
  - bloom blur 및 GUI 조작 정상 확인
- `07_Modeling_Step3_Grid`
  - clean/rebuild 후 Debug/Release 실행 확인
  - Part2 공통 STB include path 재현성 확인용

## Review Scope

이 PR은 Part2 archive migration 이후의 review blocking 대응만 포함합니다.

확인 범위:

- clean checkout/build 재현성
- 실행에 필요한 header/source/asset 누락 여부
- 리뷰에서 지적된 런타임/API 사용 이슈
- private/public 기준 문서 오해 소지

범위 제외:

- 전체 source comment 정리
- Part2 문서 품질 전면 개선
- 최종 portfolio 문서화
- capture/video 업로드
