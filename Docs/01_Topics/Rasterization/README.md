# Rasterization

이 폴더는 Rasterization 관련 graphics concept 문서의 정본 위치다.

## 범위

- 주요 개념: triangle rasterization, 2D transformation, depth buffer, projection, backface culling
- 직접 연결 예제: Part2_Chapter04 Step1·Step1A·Step2·Step3·Step5·Step7·Step8
- 기반 공유 예제: Step4·Step6·Step9·Step10은 CPU rasterizer를 공유하고 다른 Topic group이 직접 책임진다.
- 우선순위: P0

## 문서 목록

- [Triangle Rasterization](TriangleRasterization.md)
- [2D Transformations](Transformations2D.md)
- [Depth Buffer](DepthBuffer.md)
- [Backface Culling](BackfaceCulling.md)
- [Perspective Projection](PerspectiveProjection.md)
- [Topic Index](topic-index.md)

## 상태

- Topic 목록: 작성
- 상세 Topic 문서: Triangle Rasterization, 2D Transformations, Depth Buffer, Backface Culling과 Perspective Projection 작성
- 직접 연결 예제 검토: Step1·Step1A·Step2·Step3·Step5·Step7·Step8 현재 확인
- Chapter 기반 공유: Step4·Step6·Step9·Step10 연결 확인

## 다음 작업

1. Part2 Chapter05-08의 GPU rasterization pipeline과 연결한다.
2. Chapter04 CPU software rasterizer와 DirectX11 pipeline의 책임 차이를 유지한다.
