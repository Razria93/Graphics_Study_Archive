#include "ModelLoader.h"

#include <filesystem>

namespace hlab
{

using namespace DirectX::SimpleMath;

void ModelLoader::Load(std::string basePath, std::string filename)
{
	// 기본경로가 되는 주소를 string으로 저장
	this->basePath = basePath;

	Assimp::Importer importer;
	/**
	 Scene: 장면을 구성하는 데이터 파일
	
	 1. 매시 데이터
	 - 버텍스 정보 (좌표, 색상, 노멀, 텍스처 좌표 등)
	   → 각 버텍스에 대한 자세한 속성 정보 정의
	 - 인덱스 정보 (삼각형 인덱스 배열)
	   → 삼각형 혹은 다른 프리미티브를 정의하는 데 필요
	 - 프리미티브 정보 (도형 타입, 예: 삼각형 리스트, 스트립 등)
	   → 매시를 어떻게 렌더링할지에 대한 정보 (D3D11_PRIMITIVE_TOPOLOGY)
	 - UV 정보 (텍스처 좌표)
	   → UV 맵핑을 위한 각 버텍스의 텍스처 좌표 값
	
	 2. 텍스쳐 데이터
	 - 텍스처 이미지 파일 (텍스처 이미지 포맷, 압축 여부)
	   → 텍스처의 파일 포맷 (PNG, JPEG, DDS 등)과 압축 포맷을 고려
	 - 쉐이딩 데이터 (셰이더에서 텍스처의 사용 방법)
	   → 텍스처에 대한 셰이더 처리 (예: 텍스처 샘플러, 텍스처 인덱스)
	
	 3. 노드 데이터
	 - 노드 위치 (변환 행렬: 위치, 회전, 크기)
	   → 위치, 회전, 크기 데이터를 포함하는 변환 행렬
	 - 부모-자식 관계 (씬 그래프)
	   → 부모-자식 노드 관계를 통해 계층적인 객체 구조 관리
	   → 예: 각 객체의 상대적 위치를 관리
	
	 4. 애니메이션 데이터
	 - 매시나 노드의 시간에 따른 변형 정보 (위치, 회전, 크기 변화)
	   → 키프레임 애니메이션을 사용하거나, 보간법을 사용하여 애니메이션 처리
	   → 예: 트랜스폼 애니메이션, 스켈레톤 애니메이션 등
	
	 5. 프레임워크 데이터
	 - 카메라 (위치, 방향, 투영 방식)
	   → 카메라는 씬을 어떻게 볼지에 대한 정의 (직교/원근 투영, 포지션, 타겟)
	   → 뷰 행렬, 프로젝션 행렬을 포함
	 - 조명 (빛의 종류, 색상, 방향, 밝기)
	   → 조명의 타입 (점광원, 방향광원, 영역광원 등)
	   → 각 조명의 색상, 밝기, 범위 등을 설정
	 - 추가적인 카메라 및 조명 설정
	   → 조명 모델(예: Phong, Blinn-Phong), 그림자 처리, 환경광 등
	
	 6. 씬 그래프 최적화 및 관리
	 - 씬의 최적화 (Octree, BVH, 프러스트럼 컬링 등)
	   → 큰 씬에서 객체를 효율적으로 관리하기 위한 공간 분할 기법
	 - 메모리 효율성 (GPU/CPU 메모리 관리)
	   → 씬 데이터를 GPU에 효율적으로 로드하기 위한 관리 기법 (예: 메쉬 스트리밍)
	
	 7. 추가 고려 사항
	 - 텍스처와 쉐이더의 일관성 유지
	   → 텍스처의 해상도와 쉐이더의 텍스처 샘플링 방식이 일치해야 성능 최적화
	 - 애니메이션 리소스 로딩 최적화
	   → 애니메이션 데이터를 미리 로드하거나 지연 로드하는 전략 고려
	 - 병렬 처리 및 멀티스레딩
	   → 씬 처리나 렌더링 파이프라인에서 병렬 처리를 통해 성능 향상 가능
	*/

	// ReadFile은 Assimp::Importer 클래스 객체가 파일 내 데이터들을 aiScene과 그 하위 객체들의 필드에 채워주는 함수
	//	- 동작과정
	//		1. 파일 포멧 감지
	//		2. 파서를 기반으로 파싱하여 로드
	//		3. 지정한 post-process 플래그에 해당하는 작업을 적용
	//		4. 결과를 aiScene와 하위 객체에 채워서 반환함

	const aiScene *pScene = importer.ReadFile(
	    this->basePath + filename,
	    aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	Matrix tr; // Initial transformation
	ProcessNode(pScene->mRootNode, pScene, tr);

	// 노멀 벡터가 없는 경우를 대비하여 다시 계산
	// 한 위치에는 한 버텍스만 있어야 연결 관계를 찾을 수 있음
	/* for (auto &m : this->meshes) {

	    vector<Vector3> normalsTemp(m.vertices.size(), Vector3(0.0f));
	    vector<float> weightsTemp(m.vertices.size(), 0.0f);

	    for (int i = 0; i < m.indices.size(); i += 3) {

	        int idx0 = m.indices[i];
	        int idx1 = m.indices[i + 1];
	        int idx2 = m.indices[i + 2];

	        auto v0 = m.vertices[idx0];
	        auto v1 = m.vertices[idx1];
	        auto v2 = m.vertices[idx2];

	        auto faceNormal =
	            (v1.position - v0.position).Cross(v2.position - v0.position);

	        normalsTemp[idx0] += faceNormal;
	        normalsTemp[idx1] += faceNormal;
	        normalsTemp[idx2] += faceNormal;
	        weightsTemp[idx0] += 1.0f;
	        weightsTemp[idx1] += 1.0f;
	        weightsTemp[idx2] += 1.0f;
	    }

	    for (int i = 0; i < m.vertices.size(); i++) {
	        if (weightsTemp[i] > 0.0f) {
	            m.vertices[i].normal = normalsTemp[i] / weightsTemp[i];
	            m.vertices[i].normal.Normalize();
	        }
	    }
	}*/
}

// NodeData 조회
void ModelLoader::ProcessNode(aiNode *node, const aiScene *scene, Matrix tr)
{

	// std::cout << node->mName.C_Str() << " : " << node->mNumMeshes << " "
	//           << node->mNumChildren << std::endl;

	// ai는 Assimp 라이브러리의 요소임을 명시하는 접두어라고 보면 됨
	// ai_real은 AssimpLibrary에서 사용하눈 실수형 데이터 타입 (real Number [float, double형이 여기에 해당함])
	// 기본적으로는 float로 정의되어 있으나 플랫폼에 따라 double형으로도 바뀔 수 있도록 유연성을 두기 위해 만들어진 별도의 타입
	
	// 행렬의 요소를 읽는 법에는 크게 2가지가 있음
	// float4X4나 Matrix4 를 읽는다고 했을 때,
	// 
	// - 선형적 번호 (1차원 배열번호)
	//		- 행렬의 요소를 행우선으로 읽으며, 행의 요소를 다 읽으면 다음 열의 새로운 행을 기존의 행 번호 다음에 붙여 읽는 방식
	//		- a1, a2, a3, a4 / a5, a6 ... a11, a12, / a13 a14, a15, a16 
	//
	// - 행렬적 번호 (2차원 배열번호)
	//		- 행과 열을 동시에 기입하는 방식
	//		- _m11, _m12, _m13, _m14 / _m21, _m22 ... _m33, _m34 / _m41, _m42, _m43, _m44

	Matrix m;
	ai_real *temp = &node->mTransformation.a1;	// Load한 Scene의 Transformation행렬의 시작주소를 저장함
	float *mTemp = &m._11;						// 데이터를 저장할 Matrix 행렬의 시작주소를 저장함
	for (int t = 0; t < 16; t++)
	{
		mTemp[t] = float(temp[t]);				// mTransformation의 행렬 요소값을 _11부터 _44까지 모두 저장함
	}
	m = m.Transpose() * tr;						// Assimp의 대수관례는 열벡터(M·v, 우곱) 으로 구성되어 있음. 
												// 따라서 행벡터 (v·M, 좌곱)을 따르는 현재프로젝트에서는 전치가 필요한 것
												// tr은 부모노드의 변환행렬을 받아오는 것으로, 해당 노드의 변환행렬과 부모 노드의 변환행렬을 곱하여 최종 변환행렬을 도출
												// 참고로 메모리배치(row-Major, column-Major) / 대수관례(M·v, v·M) / 좌표계 (LH, RH)는 모두 별개의 요소임

	
	// 노드 내의 메시 Vector를 순환
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		// Scene에 구성된 Mesh정보들을 하나씩 꺼내어 newMesh에 저장하고 meshes에 push
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		auto newMesh = this->ProcessMesh(mesh, scene);

		//vertices의 Pos를 m으로 변환 (Transform)
		for (auto &v : newMesh.vertices)
		{
			v.position = DirectX::SimpleMath::Vector3::Transform(v.position, m);
		}

		meshes.push_back(newMesh);
	}
	// 본인의 자식 노드들에 대한 재귀함수 [본인 포함, 자식들을 모두 완료해야 본인 차례 끝]
	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene, m);
	}
}

// Mesh 구조체 내의 데이터를 해당 객체의 형태로 구성하여 반환하는 함수
MeshData ModelLoader::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	// Data to fill
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	// Walk through each of the mesh's vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		vertex.normal.Normalize();

		if (mesh->mTextureCoords[0])
		{
			vertex.texcoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.texcoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	MeshData newMesh;
	newMesh.vertices = vertices;
	newMesh.indices = indices;

	// Material의 Diffuse의 텍스쳐 filename 저장
	// http://assimp.sourceforge.net/lib_html/materials.html
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString filepath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &filepath);

			std::string fullPath =
			    this->basePath +
			    std::string(std::filesystem::path(filepath.C_Str())
			                    .filename()
			                    .string());

			newMesh.textureFilename = fullPath;
		}
	}

	return newMesh;
}

} // namespace hlab