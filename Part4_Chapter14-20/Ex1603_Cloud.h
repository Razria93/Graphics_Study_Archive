#pragma once

#include "AppBase.h"
#include "Model.h"

namespace hlab
{

class Ex1603_Cloud : public AppBase
{
  public:
	Ex1603_Cloud();

	virtual bool InitScene() override;
	virtual void UpdateGUI() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

  protected:
	int m_volumeWidth = 64;
	int m_volumeHeight = 64;
	int m_volumeDepth = 64;

	// 조명에 대한 정보를 가지고 있는 라이트맵에 대한 해상도
	// 라이트맵은 낮은 해상도로 저장
	int m_lightWidth = 64 / 4; 
	int m_lightHeight = 64 / 4;
	int m_lightDepth = 64 / 4;

	// 볼륨 텍스쳐
	// 해당 볼륨에 대한 자세한 렌더링(구름인 부분이나 투명인 부분을 렌더링하는 것)은 PS에서
	// 실질적으로는 정육면체의 볼륨임. 보이는 것이 구름처럼 보일뿐.
	shared_ptr<Model> m_volumeModel;

	ComPtr<ID3D11ComputeShader> m_cloudDensityCS;
	ComPtr<ID3D11ComputeShader> m_cloudLightingCS;

	VolumeConsts m_volumeConstsCpu;
	ComPtr<ID3D11Buffer> m_volumeConstsGpu;
};

} // namespace hlab