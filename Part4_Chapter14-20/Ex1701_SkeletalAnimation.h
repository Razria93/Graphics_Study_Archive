#pragma once

#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <iostream>
#include <memory>

#include "AnimationClip.h"
#include "AppBase.h"
#include "GeometryGenerator.h"
#include "ImageFilter.h"
#include "Model.h"
#include "SkinnedMeshModel.h"

namespace hlab
{

using DirectX::BoundingSphere;
using DirectX::SimpleMath::Vector3;

class Ex1701_SkeletalAnimation : public AppBase
{
  public:
	Ex1701_SkeletalAnimation();

	virtual bool InitScene() override;

	void UpdateLights(float dt) override;
	void UpdateGUI() override;
	void Update(float dt) override;
	void Render() override;

  protected:
	shared_ptr<Model> m_ground;

	// 렌더링이 되는건 뼈대 위의 Mesh이며, 이는 뼈대 위에 '붙어있는 피부'와 같은 Mesh이기 때문에 SkinnedMesh
	shared_ptr<SkinnedMeshModel> m_character;
};

} // namespace hlab
