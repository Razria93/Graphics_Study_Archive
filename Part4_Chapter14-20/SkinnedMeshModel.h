#pragma once

#include "GeometryGenerator.h"
#include "Model.h"

namespace hlab
{

using std::make_shared;

class SkinnedMeshModel : public Model
{
  public:
	SkinnedMeshModel(ComPtr<ID3D11Device>& device,
	                 ComPtr<ID3D11DeviceContext>& context,
	                 const vector<MeshData>& meshes,
	                 const AnimationData& aniData)
	{
		Initialize(device, context, meshes, aniData);
	}

	void Initialize(ComPtr<ID3D11Device>& device,
	                ComPtr<ID3D11DeviceContext>& context,
	                const vector<MeshData>& meshes,
	                const AnimationData& aniData)
	{
		InitAnimationData(device, aniData); // SkinnedMeshModel 에서 추가한 부분
		Model::Initialize(device, context, meshes);
	}

	GraphicsPSO& GetPSO(const bool wired) override
	{
		return wired ? Graphics::skinnedWirePSO : Graphics::skinnedSolidPSO;
	}

	GraphicsPSO& GetReflectPSO(const bool wired) override
	{
		return wired ? Graphics::reflectSkinnedWirePSO
		             : Graphics::reflectSkinnedSolidPSO;
	}

	GraphicsPSO& GetDepthOnlyPSO() override
	{
		return Graphics::depthOnlySkinnedPSO;
	}

	// 어떤 Mesh를 사용할지 (Model::Initialize에서 실행함)
	void InitMeshBuffers(ComPtr<ID3D11Device>& device, const MeshData& meshData,
	                     shared_ptr<Mesh>& newMesh) override
	{
		// skinnedVertices가 BindPose Mesh의 Vertices
		D3D11Utils::CreateVertexBuffer(device, meshData.skinnedVertices,
		                               newMesh->vertexBuffer);
		newMesh->indexCount = UINT(meshData.indices.size());
		newMesh->vertexCount = UINT(meshData.skinnedVertices.size());
		newMesh->stride = UINT(sizeof(SkinnedVertex));
		D3D11Utils::CreateIndexBuffer(device, meshData.indices,
		                              newMesh->indexBuffer);
	}

	// 기본 Animation을 설정하는 함수
	void InitAnimationData(ComPtr<ID3D11Device>& device,
	                       const AnimationData& aniData)
	{
		if (!aniData.clips.empty())
		{
			m_aniData = aniData; // aniData는 공통으로 사  용할 수가 있음 -> 라이브러리 구성 / 여기서는 직접 복사해서 저장
			                     // 따라서 공통으로 사용하는 애님데이터를 포인터로 저장하면 메모리를 아낄 수 있음
			                     // 다만, 자원 공용문제는 해결해야할 수도 있음

			// 여기서는 AnimationClip이 SkinnedMesh라고 가정하겠습니다.
			// 일반적으로는 모든 Animation이 SkinnedMesh Animation은 아닙니다.	-> 모든 애니메이션을 재생할 수는 없음 [Mixamo 한정으로는 어느정도 가능]
			m_boneTransforms.m_cpu.resize(aniData.clips.front().keys.size()); // resize(bone의 갯수) : m_key[boneIdx][frameIdx]

			// 주의: 모든 keys() 개수가 동일하지 않을 수도 있습니다.
			// ex. 안움직이는 프레임의 경우 키값이 1~2개만 있을수도 있으므로 인덱스 관리의 필요성이 있을수도 있음
			for (int i = 0; i < aniData.clips.front().keys.size(); i++)
				m_boneTransforms.m_cpu[i] = Matrix();

			m_boneTransforms.Initialize(device);
		}
	}

	void UpdateAnimation(ComPtr<ID3D11DeviceContext>& context, int clipId, int frame) override
	{

		m_aniData.Update(clipId, frame); // 현재 frame에 대한 clipId의 본 변환행렬을 준비해줌 (내부에 TODO 있음)

		for (int i = 0; i < m_boneTransforms.m_cpu.size(); i++)
		{
			// 위에서 설정한 clipId와 frame을 기반으로 i번째 bone이 변형되어야 할 Transform 데이터를 버퍼에 업데이트
			// 이를 모든 본에 대해서 업데이트를 하면 m_boneTransforms에 다음 애니메이션 동작을 위해 모든 본에 각각 적용될 행렬이 갱신되었음
			m_boneTransforms.m_cpu[i] =
			    m_aniData.Get(clipId, i, frame).Transpose(); // clipId	: 애니메이션 클립(애니메이션 자체)의 Index
			                                                 // i		: bone의 Index
			                                                 // frame	: 애니메이션 중 몇번째 frame인지
		}

		m_boneTransforms.Upload(context); // m_boneTransforms에 저장된 데이터를 CB를 통하여 GPU로 넘김 -> 움직인 자세로 skinnedMesh를 업데이트 해줌
	}

	void Render(ComPtr<ID3D11DeviceContext>& context) override
	{

		// ConstBuffer 대신 StructuredBuffer 사용
		// m_boneTransforms : Matrix 구조체를 사용한 버퍼
		// context->VSSetConstantBuffers(3, 1, m_skinnedConsts.GetAddressOf()); -> CB 사용도 가능함
		
		// m_boneTransforms : 애니메이션을 구성하는 각 본의 속성값을 저장한 텍스쳐버퍼
		context->VSSetShaderResources(9, 1, m_boneTransforms.GetAddressOfSRV()); // 항상 slot index 주의
		                                                                         // VertexShader에서 뼈의 움직임에 맞춰서 Mesh의 Vertex들을 움직임
		                                                                         // m_boneTransforms : 뼈의 움직임 정보를 저장한 버퍼

		// Skinned VS/PS는 GetPSO()를 통해서 지정되기 때문에
		// Model::Render(.)를 같이 사용 가능
		// 쉐이더에서 #ifdef 도 사용가능하고 많이 활용함 (성능때문)
		// 쉐이더는 같은 쉐이더코드인데 빌드할 때 다르게 빌드해서 사용함 (Skinned VS가 별개로 있는게 아니라 BasicVS(PBR용)인데 매크로를 통해 다르게 빌드함)
		// 내부적으로는 다른 VS를 사용함 (디버거 추적 [다형성])

		Model::Render(context);
	};

	// SkinnedMesh는 BoundingBox를 그릴 때 Root의 Transform을 반영해야 합니다.
	// virtual void RenderWireBoundingBox(ComPtr<ID3D11DeviceContext> &context);
	// virtual void RenderWireBoundingSphere(ComPtr<ID3D11DeviceContext>
	// &context);

  public:
	// ConstantBuffer<SkinnedConsts> m_skinnedConsts;
	StructuredBuffer<Matrix> m_boneTransforms; // Animation을 구성하는 각 프레임들의 본(bone) 변환행렬

	AnimationData m_aniData; // 해당 SkinnedMesh가 사용할 애니메이션 관련 데이터
};

} // namespace hlab