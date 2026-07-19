#pragma once

#include "AppBase.h"
#include "BitonicSort.h"
#include "Buffers.h"
#include "Model.h"
#include "StructuredBuffer.h"
#include "Texture3D.h"

namespace hlab
{

class Ex1604_RealtimeSmoke : public AppBase
{
  public:
	__declspec(align(256)) struct FluidConsts
	{
		Vector3 dxBase = Vector3(1.0f);
		float dt = 1.0f / 60.0f;
		Vector3 dxUp = Vector3(1.0f);
		float time = 0.0f;
		int upScale = 1;
		int numNewParticles = 0;
		float turbulence = 0.8f;
		float sourceStrength = 2.2f;
		float buoyancy = 0.0f;
	};

	Ex1604_RealtimeSmoke();

	virtual bool InitScene() override;
	virtual void UpdateGUI() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	void Sourcing();
	void Projection();
	void Advection();
	void DownSample();
	void DiffUpSample();

  protected:
	shared_ptr<Model> m_volumeModel;

	// Low Resolution
	// Pressure Projection은 낮은 해상도에서
	// Pressure Projection : 유체의 속도를 무압축(Divergence-free) 상태로 만드는 단계
	//						 외력을 적용하면 속도장이 발산을 가지게 되며, 압력장을 계산하여 해당 영향력을 제거해야 함 
	// Divergence(발산) : 유체의 어떤 지점에서 유입과 유출의 양이 다른 것 (그 지점에서 유체가 새거나 압축되고 있다는 것)

	Texture3D m_velocity, m_velocityTemp;
	Texture3D m_pressure, m_pressureTemp;
	Texture3D m_divergence;
	Texture3D m_density, m_densityTemp;
	Texture3D m_bc; // Boundary conditions

	// Upsampling
	// Low Resolution -> High Resolution
	// Advection은 높은 해상도에서
	Texture3D m_velocityUp, m_velocityUpTemp;
	Texture3D m_densityUp, m_densityUpTemp;

	ComPtr<ID3D11ComputeShader> m_advectionCS;
	ComPtr<ID3D11ComputeShader> m_applyPressureCS;
	ComPtr<ID3D11ComputeShader> m_divergenceCS;
	ComPtr<ID3D11ComputeShader> m_jacobiCS;
	ComPtr<ID3D11ComputeShader> m_sourcingCS;
	ComPtr<ID3D11ComputeShader> m_downSampleCS;
	ComPtr<ID3D11ComputeShader> m_diffUpSampleCS;
	ComPtr<ID3D11ComputeShader> m_vorticityConfinementCS;

	ConstantBuffer<FluidConsts> m_fluidConsts;
	ConstantBuffer<VolumeConsts> m_volumeConsts;

	UINT m_width = 0;
	UINT m_height = 0;
	UINT m_depth = 0;
	UINT m_widthUp = 0;
	UINT m_heightUp = 0;
	UINT m_depthUp = 0;

	// 업스케일 해상도
	// 해상도 또한 감각적인 것 (모사적인 느낌)
	int m_upScale = 1;
};

} // namespace hlab