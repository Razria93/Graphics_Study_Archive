#pragma once

#include "AppBase.h"
#include "Model.h"

namespace hlab
{

class Ex1402_Blur : public AppBase
{
  public:
	Ex1402_Blur();

	virtual bool Initialize() override;
	virtual void UpdateGUI() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

  protected:
	void PrepareForStagingTexture();
	void ComputeShaderBlur(const bool useGroupCache); // GroupCache 사용유무
	void PixelShaderBlur();                           // 이전에 구현했던 PS Blur

	// Separable Gaussian Blur
	//  - X, Y 분리해서 Blur하는 방식

	// CS_Resource & View
	ComPtr<ID3D11Texture2D> m_stagingTexture;
	ComPtr<ID3D11Texture2D> m_texA, m_texB;
	ComPtr<ID3D11RenderTargetView> m_rtvA, m_rtvB;    // PS에서 사용할 RTV
	ComPtr<ID3D11ShaderResourceView> m_srvA, m_srvB;  // PS, CS에서 사용할 SRV
	ComPtr<ID3D11UnorderedAccessView> m_uavA, m_uavB; // CS에서 사용할 UAV         [RWTexture2D : Read & Write 모두 가능]
	// ----

	// CS_GroupCache 미사용
	ComPtr<ID3D11ComputeShader> m_blurXCS;
	ComPtr<ID3D11ComputeShader> m_blurYCS;

	ComputePSO m_blurXComputePSO;
	ComputePSO m_blurYComputePSO;
	// ----

	// CS_GroupCache 사용
	ComPtr<ID3D11ComputeShader> m_blurXGroupCacheCS;
	ComPtr<ID3D11ComputeShader> m_blurYGroupCacheCS;

	ComputePSO m_blurXGroupCacheComputePSO;
	ComputePSO m_blurYGroupCacheComputePSO;

	// ----
	// PS
	ComPtr<ID3D11PixelShader> m_blurXPS;
	ComPtr<ID3D11PixelShader> m_blurYPS;

	GraphicsPSO m_blurXPixelPSO;
	GraphicsPSO m_blurYPixelPSO;
	// ----

	shared_ptr<Mesh> m_screenMesh;
};

} // namespace hlab