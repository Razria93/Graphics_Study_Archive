## Phase 3-2 완료 기록

## 완료 내용

- `Part2_Chapter05-08` Chapter05–08의 30개 예제를 순서대로 재검증하고 Example README, Topic, Verification과 상세 Demo를 연결했다.
- Chapter05는 GLM과 DirectXMath·SimpleMath affine transformation 비교, Chapter06은 DirectX11 pipeline·lighting·resize, Chapter07은 procedural modeling과 SphereMapping 흐름으로 정리했다.
- Chapter05 [Demo Issue #17](https://github.com/Razria93/Graphics_Study_Archive/issues/17), Chapter06 [Demo Issue #18](https://github.com/Razria93/Graphics_Study_Archive/issues/18), Chapter07 [Demo Issue #19](https://github.com/Razria93/Graphics_Study_Archive/issues/19)에 공개 안전한 대표 visual을 게시했다.
- Chapter08은 shader·environment·post-processing 구현 검증을 완료하고 외부 asset을 대표 publication visual에서 제외했다.

## 검증

- Chapter05 Step1–4, Chapter06 Step1–9, Chapter07 Step1–9와 Chapter08 Step1–7 Debug/Release x64 build/run: 성공
- Graphics Example tracked screenshot: 확보와 공개 안전성 검사 완료
- 필수 문서·Markdown rendering·table·video asset validator와 fixture 검사: 통과
- GitHub Actions `Docs Validation`: 문서·fixture·asset 정책 검사 구성

## 남은 제한

- Chapter06 Step8 resize interaction video는 후속 개선으로 유지한다.
- Chapter07 Step9와 Chapter08의 외부 asset은 권리 근거 확인 전 대표 publication visual로 사용하지 않는다.
- RowPitch·Map failure와 project metadata 정리는 별도 code maintenance 범위로 유지한다.

## Related PR

- [PR #20](https://github.com/Razria93/Graphics_Study_Archive/pull/20) (Draft) - Part2 Chapter05-08 DirectX11 Pipeline·Modeling·Shader 예제 정규화와 Demo
