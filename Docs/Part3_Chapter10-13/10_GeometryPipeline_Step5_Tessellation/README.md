# 10_GeometryPipeline_Step5_Tessellation

## Chapter Focus

이 예제는 Direct3D 11 tessellation pipeline의 Hull Shader와 Domain Shader를 사용해 quad patch를 세분화하는 흐름을 확인하는 단계입니다.

## Archive Notes

- Primary raw: `C:\ComputerGraphics\Part3_Chapter10_13\10_GeometryPipeline_Step5_Tessellation`
- Reference raw: `C:\ComputerGraphics\Part3_Chapter10_13_2\10_GeometryPipeline_Step5_Tessellation`
- Reference snapshot과 파일 목록은 같지만 `TessellatedQuadHS.hlsl`, `TessellatedQuadDS.hlsl`, `TessellatedQuad.h` 내용이 다릅니다.
- Archive에는 사용자 작업 흐름과 실험 메모가 포함된 primary raw 기준 파일을 반영했습니다.
- 장문 학습 메모와 source comment 정리는 2차 문서 정리 단계에서 분리합니다.

## Runtime Assets

새로 추가한 asset은 없습니다. 이전 Step에서 반영한 공용 texture/cubemap asset을 사용합니다.

## Verification

- Static verification: 완료
- Debug x64 run: 성공
- Release x64 run: 성공
