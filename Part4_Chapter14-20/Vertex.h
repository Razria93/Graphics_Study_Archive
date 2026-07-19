#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>

namespace hlab
{

using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Vector4;

struct Vertex
{
	Vector3 position;
	Vector3 normalModel;
	Vector2 texcoord;
	Vector3 tangentModel;
	// Vector3 biTangentModel; // biTangent는 쉐이더에서 계산
};

struct SkinnedVertex
{
	Vector3 position;
	Vector3 normalModel;
	Vector2 texcoord;
	Vector3 tangentModel;

	// 일반 Vertex와의 차이점
	// 뼈대가 움직일 때, 그 뼈대에 연결되어 있는 Vertex들이 같이 움직이도록 지정을 해줘야함
	// boneIndices	: 어떤 Vertex가 어떤 bone들에 연결되어있는지, 영향을 받는지			 [영향을 줄 수 있는 bone의 Index]
	// blendWeights : 그리고 그 영향의 정도가 본노드의 거리에 따라서 가중치가 달라질 것임 [영향을 줄 수 있는 bone의 Weight]
	float blendWeights[8] = {0.0f, 0.0f, 0.0f, 0.0f,
	                         0.0f, 0.0f, 0.0f, 0.0f};  // BLENDWEIGHT0 and 1	[시멘틱] -> Weight의 합은 1에 근사해야함 (원래는 정확히 1.0)
	uint8_t boneIndices[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // BLENDINDICES0 and 1	[시멘틱]

	// boneWeights가 최대 8개라고 가정 (Luna 교재에서는 4개)
	// bone의 수가 256개 이하라고 가정 uint8_t
};

struct GrassVertex
{
	// 모델 1개에 대한 Vertex
	Vector3 posModel;
	Vector3 normalModel;
	Vector2 texcoord;

	// 주의: Instance World는 별도의 버퍼로 보냄
};

// GrassVS, grassIL과 일관성이 있어야 합니다.
// Instance의 변환들을 따로 저장
struct GrassInstance
{
	// 풀 1개를 어디로 옮겨놓고 그릴 것인지
	//grassIEs 참고
	Matrix instanceWorld; // <- Instance 단위의 Model to World 변환
	float windStrength;
};

} // namespace hlab