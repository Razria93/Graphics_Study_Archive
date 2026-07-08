# 02_Bloom Status

## Source

- Raw reference: `C:\ComputerGraphics\Part1_Chapter01-02\02_Bloom`
- Archive path: `Part1_Chapter01-02\02_Bloom`
- Related raw docs:
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter01_BloomEffect.md`
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\Chapter02_Blur.md`
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\@ Texturing & Sampling.md`
  - `C:\ComputerGraphics\Docs_Graphics\_99_Study\_01_Graphics\@ Sampling 규칙 2가지.md`

## Progress

| 항목 | 상태 | 메모 |
| --- | --- | --- |
| Code/document split | 완료 | code files 선별 반영, 기본 입력 이미지 1개 private archive 반영, raw result/capture assets 제외, source comments local-only 분리 |
| Build/run | 성공 | `Debug x64` MSBuild 성공. 사용자가 Debug/Release 실행 정상 확인 |
| Raw/original diff review | 완료 | 장문 주석 제거, 입력 asset 범위 축소, fallback 보조 경로 추가 확인 |
| Refactor review | 완료 | `stbi_image_free`, Debug x64 OpenMP, 입력 누락 시 fallback 반영 완료 |
| Ready for capture | 보류 | 사용자가 Debug/Release 실행 정상 확인. 촬영은 현재 보류 |

## User memo sources

- Source comments: `local/Part1_Chapter01-02/02_Bloom/source-comments.md`
- Raw md notes: `local/Part1_Chapter01-02/02_Bloom/raw-md-notes.md`
- Included image: `Part1_Chapter01-02/02_Bloom/image_1_360.JPG` private archive 입력 asset
- Missing/excluded images: raw docs의 `Pasted image ...`, raw result/capture/intermediate files는 복사하지 않음

## Local-only docs

| 문서 | 상태 |
| --- | --- |
| `local/Part1_Chapter01-02/02_Bloom/source-comments.md` | 생성 완료 |
| `local/Part1_Chapter01-02/02_Bloom/raw-md-notes.md` | 생성 완료 |
| `local/Part1_Chapter01-02/02_Bloom/memo-review.md` | 생성 완료 |
| `local/Part1_Chapter01-02/02_Bloom/final-doc-plan.md` | 생성 완료 |

## Next action

1. 촬영 재개 시 실행 결과 링크 또는 capture 파일명을 기록합니다.
2. public 후보 여부는 입력 이미지 권리 검토 후 판단합니다.
