#pragma once

#include "ModelLoader.h"

// vcpkg install assimp:x64-windows
// Preprocessor definitions에 NOMINMAX 추가
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "AnimationClip.h"
#include "MeshData.h"
#include "Vertex.h"

namespace hlab
{

using std::map;
using std::string;
using std::vector;

class ModelLoader
{
  public:
	void Load(string basePath, string filename, bool revertNormals);
	void LoadAnimation(string basePath, string filename);

	const aiNode* FindParent(const aiNode* node);

	void ProcessNode(aiNode* node, const aiScene* scene,
	                 DirectX::SimpleMath::Matrix tr);

	MeshData ProcessMesh(aiMesh* mesh, const aiScene* scene);

	void ReadAnimation(const aiScene* scene);

	std::string ReadTextureFilename(const aiScene* scene, aiMaterial* material,
	                                aiTextureType type);

	void UpdateTangents();

	// 버텍스의 변형에 직접적으로 참여하는 뼈들의 목록을 만듭니다.
	void FindDeformingBones(const aiScene* scene);

	void UpdateBoneIDs(aiNode* node, int* counter)
	{
		// 최초 호출 때, node 매개변수에 pScene->mRootNode를 넣고 호출함
		static int id = 0;
		if (node) // rootNode
		{
			// vertex의 변형에 참여하는 것들만 counter를 저장해줌
			if (m_aniData.boneNameToId.count(node->mName.C_Str()))
			{
				m_aniData.boneNameToId[node->mName.C_Str()] = *counter;
				*counter += 1;
			}
			// 재귀형태로 root의 mChildren를 순회
			for (UINT i = 0; i < node->mNumChildren; i++)
			{
				UpdateBoneIDs(node->mChildren[i], counter);
			}
		}
	}

  public:
	string m_basePath;
	vector<MeshData> m_meshes;

	AnimationData m_aniData;

	bool m_isGLTF = false; // gltf or fbx
	bool m_revertNormals = false;
};
} // namespace hlab