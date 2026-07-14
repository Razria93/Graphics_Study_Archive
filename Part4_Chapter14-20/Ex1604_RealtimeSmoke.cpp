#include "Ex1604_RealtimeSmoke.h"
#include "GeometryGenerator.h"
#include "GraphicsCommon.h"

#include <limits>
#include <random>

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Ex1604_RealtimeSmoke::Ex1604_RealtimeSmoke() : AppBase() {}

bool Ex1604_RealtimeSmoke::InitScene()
{

	cout << "Ex1604_RealtimeSmoke::InitScene()" << endl;

	AppBase::m_camera.Reset(Vector3(0.0f, 0.0f, -4.22895f), 0.0f, 0.0f);
	AppBase::InitCubemaps(
	    L"../Assets/Textures/Cubemaps/HDRI/", L"SampleEnvHDR.dds",
	    L"SampleSpecularHDR.dds", L"SampleDiffuseHDR.dds",
	    L"SampleBrdf.dds");
	AppBase::m_globalConstsCPU.strengthIBL = 0.1f;
	AppBase::InitScene();

	m_upScale = 2;

	// 컴퓨터가 느리면 해상도를 낮추세요 (예: 128/2, 64/2, 64/2)
	m_width = 128 / 2;
	m_height = 64 / 2;
	m_depth = 64 / 2;

	m_widthUp = m_width * m_upScale;
	m_heightUp = m_height * m_upScale;
	m_depthUp = m_depth * m_upScale;

	// Initialize fluid const buffer
	m_fluidConsts.m_cpu.time = 0.0f;
	m_fluidConsts.m_cpu.dt = 1 / 60.0f;
	m_fluidConsts.m_cpu.dxBase =
	    Vector3(1.0f / m_width, 1.0f / m_height, 1.0f / m_depth);
	m_fluidConsts.m_cpu.dxUp =
	    Vector3(1.0f / m_widthUp, 1.0f / m_heightUp, 1.0f / m_depthUp);
	m_fluidConsts.m_cpu.upScale = m_upScale;
	m_fluidConsts.Initialize(m_device);

	// Initialize shaders
	D3D11Utils::CreateComputeShader(m_device, L"Ex1604_AdvectionCS.hlsl",
	                                m_advectionCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1604_ApplyPressureCS.hlsl",
	                                m_applyPressureCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1604_DivergenceCS.hlsl",
	                                m_divergenceCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1604_JacobiCS.hlsl",
	                                m_jacobiCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1604_SourcingCS.hlsl",
	                                m_sourcingCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1604_DownSampleCS.hlsl",
	                                m_downSampleCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1604_DiffUpSampleCS.hlsl",
	                                m_diffUpSampleCS);
	D3D11Utils::CreateComputeShader(m_device,
	                                L"Ex1604_VorticityConfinementCS.hlsl",
	                                m_vorticityConfinementCS);

	m_velocity.Initialize(m_device, m_width, m_height, m_depth,
	                      DXGI_FORMAT_R16G16B16A16_FLOAT);
	m_velocityTemp.Initialize(m_device, m_width, m_height, m_depth,
	                          DXGI_FORMAT_R16G16B16A16_FLOAT);
	m_pressure.Initialize(m_device, m_width, m_height, m_depth,
	                      DXGI_FORMAT_R16_FLOAT);
	m_pressureTemp.Initialize(m_device, m_width, m_height, m_depth,
	                          DXGI_FORMAT_R16_FLOAT);
	m_divergence.Initialize(m_device, m_width, m_height, m_depth,
	                        DXGI_FORMAT_R16_FLOAT);
	m_density.Initialize(m_device, m_width, m_height, m_depth,
	                     DXGI_FORMAT_R16_FLOAT);
	m_densityTemp.Initialize(m_device, m_width, m_height, m_depth,
	                         DXGI_FORMAT_R16_FLOAT);

	// Boundary Condition
	m_bc.Initialize(m_device, m_width, m_height, m_depth, DXGI_FORMAT_R32_SINT);

	// Textures for upsampling
	//	- 속도장의 해상도가 높으면 움직임을 더 정밀하게 표현할 수 있고, 더 정밀한 속도장으로 밀도를 Advection(이동,움직임)시키면 더 정교한 애니메이션을 보여줄 수 있음
	//	- 즉, 속도장은 움직임 자체의 해상도 / 밀도장은 유체의 움직임 형태에 대한 해상도
	m_velocityUp.Initialize(m_device, m_widthUp, m_heightUp, m_depthUp,
	                        DXGI_FORMAT_R16G16B16A16_FLOAT);
	m_velocityUpTemp.Initialize(m_device, m_widthUp, m_heightUp, m_depthUp,
	                            DXGI_FORMAT_R16G16B16A16_FLOAT);
	m_densityUp.Initialize(m_device, m_widthUp, m_heightUp, m_depthUp,
	                       DXGI_FORMAT_R16_FLOAT);
	m_densityUpTemp.Initialize(m_device, m_widthUp, m_heightUp, m_depthUp,
	                           DXGI_FORMAT_R16_FLOAT);

	// Volume 쉐이더는 별도로 초기화
	//  - 렌더링 품질을 높이고 싶을 경우 해당 부분을 수정
	//	- 불로 예제를 개선해보면 더 이쁠듯 (온도에 대한 색도 변화하기 때문)
	Graphics::InitVolumeShaders(m_device);
	m_volumeConsts.m_cpu.densityAbsorption = 10.0;
	m_volumeConsts.Initialize(m_device);

	Vector3 center(0.0f);
	m_volumeModel = make_shared<Model>(
	    m_device, m_context, vector{GeometryGenerator::MakeBox(1.0f)});
	m_volumeModel->UpdateWorldRow(Matrix::CreateScale(2.0f * Vector3(1.0f, float(m_height) / m_width,
	                                                                 float(m_depth) / m_width)) *
	                              Matrix::CreateTranslation(center));
	m_volumeModel->UpdateConstantBuffers(m_device, m_context);
	m_volumeModel->m_meshes.front()->densityTex = m_densityUp; // 고해상도
	m_volumeModel->m_meshes.front()->lightingTex.Initialize(
	    m_device, m_width, m_height, m_depth, DXGI_FORMAT_R16_FLOAT, {});

	m_volumeModel->m_isPickable = true;	// 움직일 수 있게 만드느 ㄴ것

	AppBase::m_basicList.push_back(m_volumeModel); // 마우스 선택

	// Rendering
	m_context->CSSetConstantBuffers(4, 1, m_fluidConsts.GetAddressOf());
	ID3D11SamplerState* samplerStates[5] = {
	    Graphics::pointClampSS.Get(), Graphics::linearClampSS.Get(),
	    Graphics::linearMirrorSS.Get(), Graphics::pointWrapSS.Get(),
	    Graphics::linearWrapSS.Get()};
	m_context->CSSetSamplers(0, 5, samplerStates);

	return true;
}

void Ex1604_RealtimeSmoke::Update(float dt)
{

	AppBase::Update(dt);
	m_volumeModel->UpdateConstantBuffers(m_device, m_context);

	if (!AppBase::m_pauseAnimation)
	{

		const int numSubsteps = 2;

		for (int i = 0; i < numSubsteps; i++)
		{
			m_fluidConsts.m_cpu.dt = 1.0f / 60.0f / numSubsteps;
			m_fluidConsts.m_cpu.time += m_fluidConsts.m_cpu.dt;
			m_fluidConsts.m_cpu.numNewParticles = 0; // 꺼놓음
			m_fluidConsts.Upload(m_context);

			// 진행과정

			DownSample();

			Sourcing();		// - Projection만 저해상도에서 하고 Sourcing은 고해상도에서 할 수도 있음

			Projection();

			DiffUpSample();	// - UpSampling을 그냥 사용하게 될 경우, 시뮬레이션이 둔해져버림
							// - 해당 예시의 경우 성능을 위해 고해상도의 텍스쳐를 일부 작업구간에서 
							//	 저해상도로 내리는 것이기 때문에 [고해상도 -> 저해상도] 하는 과정에서 차이를 측정할 수 있음
							// - DownSampling한 직후 위에서 만들어진 차이만 UpSampling을 해서 더함
							// - Sourcing에서 저해상도로 밀도장을 만들기 때문에 여기서 UpSampling 해야 함
							// - 힘을 더하는 것도 저해상도에서 더하기 때문에 여기서 UpSampling 해야 함

			Advection();	// - 고해상도 속도장을 기반으로 고해상도 밀도장을 생성함
		}
	}
}

void Ex1604_RealtimeSmoke::DownSample()
{

	// Apply vorticity confiment to up
	{
		m_context->CopyResource(m_velocityUpTemp.GetTexture(),
		                        m_velocityUp.GetTexture());

		ID3D11ShaderResourceView* srvs[2] = {m_velocityUpTemp.GetSRV(),
		                                     m_densityUp.GetSRV()};
		ID3D11UnorderedAccessView* uavs[1] = {m_velocityUp.GetUAV()};
		m_context->CSSetShaderResources(0, 2, srvs);
		m_context->CSSetUnorderedAccessViews(0, 1, uavs, NULL);
		m_context->CSSetConstantBuffers(4, 1, m_fluidConsts.GetAddressOf());
		m_context->CSSetShader(m_vorticityConfinementCS.Get(), 0, 0);
		m_context->Dispatch(UINT(ceil(m_widthUp / 16.0f)),
		                    UINT(ceil(m_heightUp / 16.0f)),
		                    UINT(ceil(m_depthUp / 4.0f)));
		AppBase::ComputeShaderBarrier();
	}

	// Downsampling
	{
		ID3D11ShaderResourceView* srvs[2] = {m_velocityUp.GetSRV(),
		                                     m_densityUp.GetSRV()};
		ID3D11UnorderedAccessView* uavs[2] = {m_velocity.GetUAV(),
		                                      m_density.GetUAV()};
		m_context->CSSetShaderResources(0, 2, srvs);
		m_context->CSSetUnorderedAccessViews(0, 2, uavs, NULL);
		m_context->CSSetShader(m_downSampleCS.Get(), 0, 0);
		m_context->Dispatch(UINT(ceil(m_width / 16.0f)),
		                    UINT(ceil(m_height / 16.0f)),
		                    UINT(ceil(m_depth / 4.0f)));
		AppBase::ComputeShaderBarrier();
	}

	// Backup old
	//  - 이 부분이 DownSampling한 직후의 데이터를 백업하는 부분
	//  - UpSampling 할 때 사용할 부분
	//	- 이 것과의 차이를 더하는 것
	//	- 저해상도의 필드를 백업하고 있음
	m_context->CopyResource(m_velocityTemp.GetTexture(),
	                        m_velocity.GetTexture());
	m_context->CopyResource(m_densityTemp.GetTexture(), m_density.GetTexture());
}

void Ex1604_RealtimeSmoke::Sourcing()
{
	// 여기서 바운드 컨디션을 설정해줌
	ID3D11UnorderedAccessView* uavs[3] = {m_velocity.GetUAV(),
	                                      m_density.GetUAV(), m_bc.GetUAV()};
	m_context->CSSetUnorderedAccessViews(0, 3, uavs, NULL);
	m_context->CSSetShader(m_sourcingCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_width / 16.0f)),
	                    UINT(ceil(m_height / 16.0f)),
	                    UINT(ceil(m_depth / 4.0f)));
	AppBase::ComputeShaderBarrier();
}

void Ex1604_RealtimeSmoke::Projection()
{
	// Compute divergence
	m_context->CSSetShaderResources(0, 1, m_velocity.GetAddressOfSRV());
	m_context->CSSetShaderResources(2, 1, m_bc.GetAddressOfSRV());
	ID3D11UnorderedAccessView* uavs[3] = {
	    m_divergence.GetUAV(), m_pressure.GetUAV(), m_pressureTemp.GetUAV()};
	m_context->CSSetUnorderedAccessViews(0, 3, uavs, NULL);
	m_context->CSSetShader(m_divergenceCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_width / 16.0f)),
	                    UINT(ceil(m_height / 16.0f)),
	                    UINT(ceil(m_depth / 4.0f)));
	AppBase::ComputeShaderBarrier();

	// Jacobi iteration
	m_context->CSSetShader(m_jacobiCS.Get(), 0, 0);
	for (int i = 0; i < 20; i++)
	{
		if (i % 2 == 0)
		{
			m_context->CSSetShaderResources(0, 1, m_pressure.GetAddressOfSRV());
			m_context->CSSetUnorderedAccessViews(
			    0, 1, m_pressureTemp.GetAddressOfUAV(), NULL);
		}
		else
		{
			m_context->CSSetShaderResources(0, 1,
			                                m_pressureTemp.GetAddressOfSRV());
			m_context->CSSetUnorderedAccessViews(
			    0, 1, m_pressure.GetAddressOfUAV(), NULL);
		}
		m_context->CSSetShaderResources(1, 1, m_divergence.GetAddressOfSRV());
		m_context->CSSetShaderResources(2, 1, m_bc.GetAddressOfSRV());
		m_context->Dispatch(UINT(ceil(m_width / 16.0f)),
		                    UINT(ceil(m_height / 16.0f)),
		                    UINT(ceil(m_depth / 4.0f)));
		AppBase::ComputeShaderBarrier();
	}

	// Apply pressure
	// 해당 Pressure를 기반으로 속도장을 저해상도에서 업데이트함
	m_context->CSSetShaderResources(0, 1, m_pressure.GetAddressOfSRV());
	m_context->CSSetShaderResources(2, 1, m_bc.GetAddressOfSRV());
	m_context->CSSetUnorderedAccessViews(0, 1, m_velocity.GetAddressOfUAV(),
	                                     NULL);
	m_context->CSSetShader(m_applyPressureCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_width / 16.0f)),
	                    UINT(ceil(m_height / 16.0f)),
	                    UINT(ceil(m_depth / 4.0f)));
	AppBase::ComputeShaderBarrier();
}

void Ex1604_RealtimeSmoke::DiffUpSample()
{
	// BackUp한 것을 같이 넣어줌
	// 고해상도의 디테일을 가능한 유지한채로 UpSampling 하는 것
	// Run with Up-res
	ID3D11ShaderResourceView* srvs[4] = {
	    m_velocityTemp.GetSRV(), m_velocity.GetSRV(), m_densityTemp.GetSRV(),
	    m_density.GetSRV()};
	ID3D11UnorderedAccessView* uavs[2] = {m_velocityUp.GetUAV(),
	                                      m_densityUp.GetUAV()};
	m_context->CSSetShaderResources(0, 4, srvs);
	m_context->CSSetUnorderedAccessViews(0, 2, uavs, NULL);
	m_context->CSSetShader(m_diffUpSampleCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_widthUp / 16.0f)),
	                    UINT(ceil(m_heightUp / 16.0f)),
	                    UINT(ceil(m_depthUp / 4.0f)));
	AppBase::ComputeShaderBarrier();
}

void Ex1604_RealtimeSmoke::Advection()
{
	// 고해상도의 속도장을 기반으로 고해상도의 속도장과 밀도장을 Advection(이송)시켜줌 -> 애니메이션
	// Advect Upsampled velocity/density

	m_context->CopyResource(m_velocityUpTemp.GetTexture(),
	                        m_velocityUp.GetTexture());
	m_context->CopyResource(m_densityUpTemp.GetTexture(),
	                        m_densityUp.GetTexture());

	ID3D11ShaderResourceView* srvs[2] = {m_velocityUpTemp.GetSRV(),
	                                     m_densityUpTemp.GetSRV()};
	ID3D11UnorderedAccessView* uavs[2] = {m_velocityUp.GetUAV(),
	                                      m_densityUp.GetUAV()};
	m_context->CSSetShaderResources(0, 2, srvs);
	m_context->CSSetUnorderedAccessViews(0, 2, uavs, NULL);
	m_context->CSSetShader(m_advectionCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_widthUp / 16.0f)),
	                    UINT(ceil(m_heightUp / 16.0f)),
	                    UINT(ceil(m_depthUp / 4.0f)));
	AppBase::ComputeShaderBarrier();
}

void Ex1604_RealtimeSmoke::Render()
{

	// AppBase::Render()에서 그려지지 않도록 설정
	// - 렌더링할 때 빼버림
	// - 종류에 따라서 (PSO를 뭘 쓰는지에 따라서) 타입에 따라 물체의 클래스를 따로 만들어주는 것이 좋음
	// - 이후 해당 예제가 있음
	m_volumeModel->m_isVisible = false;

	AppBase::Render();

	m_volumeModel->m_isVisible = true;

	// Draw volume

	AppBase::SetPipelineState(Graphics::volumeSmokePSO);
	m_context->PSSetConstantBuffers(3, 1, m_volumeConsts.GetAddressOf());
	m_volumeModel->Render(m_context);

	// Draw bounding box

	AppBase::SetPipelineState(Graphics::boundingBoxPSO);
	m_context->OMSetRenderTargets(1, AppBase::m_floatRTV.GetAddressOf(),
	                              NULL); // Depth 끄기
	m_volumeModel->RenderWireBoundingBox(m_context);

	AppBase::PostRender();
}

void Ex1604_RealtimeSmoke::UpdateGUI()
{
	AppBase::UpdateGUI();

	ImGui::SliderFloat("Turbulence", &m_fluidConsts.m_cpu.turbulence, 0.0f,
	                   1.5f);
	ImGui::SliderFloat("Source", &m_fluidConsts.m_cpu.sourceStrength, 0.1f,
	                   3.0f);
	ImGui::SliderFloat("Buoyancy", &m_fluidConsts.m_cpu.buoyancy, 0.0f, 10.0f);
}

} // namespace hlab