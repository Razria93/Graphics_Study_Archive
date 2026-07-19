#include "StableFluids.h"

namespace hlab
{

void StableFluids::Initialize(ComPtr<ID3D11Device>& device, const UINT width,
                              const UINT height)
{

	m_width = width;
	m_height = height;

	// Update const buffer
	m_constsCPU.dt = 0.0f;
	// m_constsCPU.viscosity = 1000.0f; // 밀도에 대한 계수, 확산계수, 속도의 점성계수에 공통적으로 사용하는 상수 [정교하게 하려면 분리해서 사용해야함]
	m_constsCPU.viscosity = 0.0f;	
	m_constsCPU.sourcingVelocity = Vector2(-0.1f, 0.0f);
	m_constsCPU.sourcingDensity = Vector4(1.0f);
	m_constsCPU.i = -1;
	m_constsCPU.j = -1;

	// Initialize const buffer
	D3D11Utils::CreateConstBuffer(device, m_constsCPU, m_constsGPU);

	// Initialize shaders
	D3D11Utils::CreateComputeShader(device, L"Ex1601_AdvectionCS.hlsl",
	                                m_advectionCS);
	D3D11Utils::CreateComputeShader(device, L"Ex1601_ApplyPressureCS.hlsl",
	                                m_applyPressureCS);
	D3D11Utils::CreateComputeShader(device, L"Ex1601_DiffuseCS.hlsl",
	                                m_diffuseCS);
	D3D11Utils::CreateComputeShader(device, L"Ex1601_DivergenceCS.hlsl",
	                                m_divergenceCS);
	D3D11Utils::CreateComputeShader(device, L"Ex1601_JacobiCS.hlsl",
	                                m_jacobiCS);
	D3D11Utils::CreateComputeShader(device, L"Ex1601_SourcingCS.hlsl",
	                                m_sourcingCS);
	D3D11Utils::CreateComputeShader(device, L"Ex1601_ComputeVorticityCS.hlsl",
	                                m_computeVorticityCS);
	D3D11Utils::CreateComputeShader(device, L"Ex1601_ConfineVorticityCS.hlsl",
	                                m_confineVorticityCS);

	// Initialize Textures

	m_velocity.Initialize(device, width, height, DXGI_FORMAT_R16G16_FLOAT);
	m_velocityTemp.Initialize(device, width, height, DXGI_FORMAT_R16G16_FLOAT);

	m_pressure.Initialize(device, width, height, DXGI_FORMAT_R16_FLOAT);
	m_pressureTemp.Initialize(device, width, height, DXGI_FORMAT_R16_FLOAT);
	m_divergence.Initialize(device, width, height, DXGI_FORMAT_R16_FLOAT);
	m_vorticity.Initialize(device, width, height, DXGI_FORMAT_R16_FLOAT);

	m_density.Initialize(device, width, height, DXGI_FORMAT_R16G16B16A16_FLOAT);
	m_densityTemp.Initialize(device, width, height,
	                         DXGI_FORMAT_R16G16B16A16_FLOAT);
}

void StableFluids::Update(ComPtr<ID3D11Device>& device,
                          ComPtr<ID3D11DeviceContext>& context, float dt)
{
	// StableFluids 시뮬레이션 업데이트 (예제에서 하고 있음)
	m_constsCPU.dt = dt;

	D3D11Utils::UpdateBuffer(context, m_constsCPU, m_constsGPU);
	context->CSSetConstantBuffers(0, 1, m_constsGPU.GetAddressOf());

	ID3D11SamplerState* samplerStates[2] = {Graphics::pointWrapSS.Get(),
	                                        Graphics::linearWrapSS.Get()};
	context->CSSetSamplers(0, 2, samplerStates);

	Sourcing(context);
	Diffuse(context);
	Projection(context);
	Advection(context);
}

void StableFluids::ComputeShaderBarrier(ComPtr<ID3D11DeviceContext>& context)
{
	ID3D11ShaderResourceView* nullSRV[2] = {0, 0};
	context->CSSetShaderResources(0, 2, nullSRV);
	ID3D11UnorderedAccessView* nullUAV[2] = {0, 0};
	context->CSSetUnorderedAccessViews(0, 2, nullUAV, NULL);
}

void StableFluids::Sourcing(ComPtr<ID3D11DeviceContext>& context)
{
	// 말그대로 조작에 의한 소스를 제공하는 부분
	// 제공된 소스가 이후 Diffuse, Projection, Advection 에 의해 유체의 형태로 시뮬레이션 됨

	// 마우스를 조작했을 때 density 추가
	// 마우스를 조작하여 움직임을 만들어줌
	// 예제구현 없이 실행할 경우 그림판과 같이 Density를 추가/제공(Sourcing)해주는 형식
	// 점차 흐려짐 (ColorDensity에서 값을 빼도록 설정함)

	ID3D11UnorderedAccessView* uavs[2] = {m_velocity.GetUAV(),
	                                      m_density.GetUAV()};
	context->CSSetUnorderedAccessViews(0, 2, uavs, NULL);
	context->CSSetShader(m_sourcingCS.Get(), 0, 0);
	context->Dispatch(UINT(ceil(m_width / 32.0f)), UINT(ceil(m_height / 32.0f)), 1);
	ComputeShaderBarrier(context);

	// Vorticity confinemenet
	//  - 유체가 상세도가 더 높아질 수 있도록 하는 패턴 (말단 부분이 말리는 패턴)
	//  - F에 더해지는 것처럼 구현하는 것이 일반적임
	//	- 상세도를 올려주는 디테일 효과 (장식)

	// 계산부
	context->CSSetShaderResources(0, 1, m_velocity.GetAddressOfSRV());
	context->CSSetUnorderedAccessViews(0, 1, m_vorticity.GetAddressOfUAV(),
	                                   NULL);
	context->CSSetShader(m_computeVorticityCS.Get(), 0, 0);
	context->Dispatch(UINT(ceil(m_width / 32.0f)), UINT(ceil(m_height / 32.0f)), 1);
	ComputeShaderBarrier(context);

	// 적용부
	context->CSSetShaderResources(0, 1, m_vorticity.GetAddressOfSRV());
	context->CSSetUnorderedAccessViews(0, 1, m_velocity.GetAddressOfUAV(),
	                                   NULL);
	context->CSSetShader(m_confineVorticityCS.Get(), 0, 0);
	context->Dispatch(UINT(ceil(m_width / 32.0f)), UINT(ceil(m_height / 32.0f)), 1);
	ComputeShaderBarrier(context);
}

void StableFluids::Diffuse(ComPtr<ID3D11DeviceContext>& context)
{
	// 점성을 적용하는 부분 (라플라시안)

	ID3D11ShaderResourceView* evenSRVs[2] = {m_velocity.GetSRV(),
	                                         m_density.GetSRV()};
	ID3D11ShaderResourceView* oddSRVs[2] = {m_velocityTemp.GetSRV(),
	                                        m_densityTemp.GetSRV()};
	ID3D11UnorderedAccessView* evenUAVs[2] = {m_velocityTemp.GetUAV(),
	                                          m_densityTemp.GetUAV()};
	ID3D11UnorderedAccessView* oddUAVs[2] = {m_velocity.GetUAV(),
	                                         m_density.GetUAV()};

	context->CSSetShader(m_diffuseCS.Get(), 0, 0);

	// 점성을 한번에 크게 넣어줄 경우 시뮬레이션이 불안정해짐
	// 따라서 쪼개서 여러번 적용하는 방식으로 구현함
	for (int i = 0; i < 10; i++)
	{
		// 2개 버퍼 번갈아가면서 사용함
		if (i % 2 == 0)
		{
			context->CSSetShaderResources(0, 2, evenSRVs);
			context->CSSetUnorderedAccessViews(0, 2, evenUAVs, NULL);
		}
		else
		{
			context->CSSetShaderResources(0, 2, oddSRVs);
			context->CSSetUnorderedAccessViews(0, 2, oddUAVs, NULL);
		}

		context->Dispatch(UINT(ceil(m_width / 32.0f)),
		                  UINT(ceil(m_height / 32.0f)), 1);

		ComputeShaderBarrier(context);
	}
}

void StableFluids::Projection(ComPtr<ID3D11DeviceContext>& context)
{
	// Compute divergence
	// 라프라시안 p^{n+1}의 우항 부분을 계산하는 부분

	context->CSSetShaderResources(0, 1, m_velocity.GetAddressOfSRV());

	ID3D11UnorderedAccessView* uavs[3] = {
	    m_divergence.GetUAV(), m_pressure.GetUAV(), m_pressureTemp.GetUAV()};

	context->CSSetUnorderedAccessViews(0, 3, uavs, NULL);
	context->CSSetShader(m_divergenceCS.Get(), 0, 0);
	context->Dispatch(UINT(ceil(m_width / 32.0f)), UINT(ceil(m_height / 32.0f)),
	                  1);
	ComputeShaderBarrier(context);

	// Jacobi iteration
	// 해당 방식을 통해서 조건을 만족하는 압력을 찾는 것
	// 반복횟수를 변경해도 됨
	// 해당 부분을 거치면 압력값이 나옴

	context->CSSetShader(m_jacobiCS.Get(), 0, 0);

	for (int i = 0; i < 100; i++)
	{
		if (i % 2 == 0)
		{
			context->CSSetShaderResources(0, 1, m_pressure.GetAddressOfSRV());
			context->CSSetUnorderedAccessViews(
			    0, 1, m_pressureTemp.GetAddressOfUAV(), NULL);
		}
		else
		{
			context->CSSetShaderResources(0, 1,
			                              m_pressureTemp.GetAddressOfSRV());
			context->CSSetUnorderedAccessViews(
			    0, 1, m_pressure.GetAddressOfUAV(), NULL);
		}
		context->CSSetShaderResources(1, 1, m_divergence.GetAddressOfSRV());
		context->Dispatch(UINT(ceil(m_width / 32.0f)),
		                  UINT(ceil(m_height / 32.0f)), 1);
		ComputeShaderBarrier(context);
	}

	// Apply pressure
	// 해당 압력을 가지고 속도 업데이트 (u^{n+1})

	context->CSSetShaderResources(0, 1, m_pressure.GetAddressOfSRV());
	context->CSSetUnorderedAccessViews(0, 1, m_velocity.GetAddressOfUAV(),
	                                   NULL);
	context->CSSetShader(m_applyPressureCS.Get(), 0, 0);
	context->Dispatch(UINT(ceil(m_width / 32.0f)), UINT(ceil(m_height / 32.0f)),
	                  1);
	ComputeShaderBarrier(context);
}

void StableFluids::Advection(ComPtr<ID3D11DeviceContext>& context)
{
	// 시뮬레이션은 반복되는 구조이기 때문에 사실상 해당 함수가 맨 처음
	// 1번 식의 1번항 부분
	// 압력을 적용해서 비압축성 조건이 적용된 다음에 해당 부분을 푸는게 좋기 때문에 이렇게 구성함

	context->CopyResource(m_velocityTemp.GetTexture(), m_velocity.GetTexture());
	context->CopyResource(m_densityTemp.GetTexture(), m_density.GetTexture());

	ID3D11ShaderResourceView* srvs[2] = {m_velocityTemp.GetSRV(),
	                                     m_densityTemp.GetSRV()};
	ID3D11UnorderedAccessView* uavs[2] = {m_velocity.GetUAV(),
	                                      m_density.GetUAV()};

	context->CSSetShaderResources(0, 2, srvs);
	context->CSSetUnorderedAccessViews(0, 2, uavs, NULL);

	context->CSSetShader(m_advectionCS.Get(), 0, 0);
	context->Dispatch(UINT(ceil(m_width / 32.0f)), UINT(ceil(m_height / 32.0f)),
	                  1);
	ComputeShaderBarrier(context);
}

} // namespace hlab