#include "Ex1406_DensityField.h"
#include "GeometryGenerator.h"
#include "GraphicsCommon.h"

#include <numeric>
#include <random>

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Ex1406_DensityField::Ex1406_DensityField() : AppBase() {}

bool Ex1406_DensityField::Initialize()
{

	cout << "Ex1406_DensityField::Initialize()" << endl;

	// ComputeShader에서 Backbuffer를 사용
	AppBase::m_backBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;

	m_screenWidth = 1024;
	m_screenHeight = 1024;

	if (!AppBase::Initialize())
		return false;

	// 1. 데이터 초기화
	m_particles.m_cpu.resize(256);

	std::vector<Vector3> rainbow = {
	    {1.0f, 0.0f, 0.0f},  // Red
	    {1.0f, 0.65f, 0.0f}, // Orange
	    {1.0f, 1.0f, 0.0f},  // Yellow
	    {0.0f, 1.0f, 0.0f},  // Green
	    {0.0f, 0.0f, 1.0f},  // Blue
	    {0.3f, 0.0f, 0.5f},  // Indigo
	    {0.5f, 0.0f, 1.0f}   // Violet/Purple
	};

	std::mt19937 gen(0);
	std::uniform_real_distribution<float> dp(-1.0f, 1.0f);
	std::uniform_int_distribution<size_t> dc(0, rainbow.size() - 1);
	for (auto& p : m_particles.m_cpu)
	{
		p.position = Vector3(dp(gen), dp(gen), 1.0f);
		p.color = rainbow[dc(gen)];
	}

	m_particles.Initialize(m_device);

	// 주의: Vertex Shader에서 Vertex 정보 미사용

	// VS는 이전 예제와 동일
	const vector<D3D11_INPUT_ELEMENT_DESC> inputElements = {
	    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	     D3D11_INPUT_PER_VERTEX_DATA, 0}}; // Dummy
	D3D11Utils::CreateVertexShaderAndInputLayout(
	    m_device, L"Ex1404_StructuredBufferVS.hlsl", inputElements,
	    m_vertexShader, m_inputLayout);
	D3D11Utils::CreatePixelShader(m_device, L"Ex1406_SpritePS.hlsl",
	                              m_pixelShader);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1406_DensitySourcingCS.hlsl",
	                                m_densitySourcingCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1406_DensityDissipationCS.hlsl",
	                                m_densityDissipationCS);

	m_densityTex.Initialize(m_device, m_screenWidth, m_screenHeight,
	                        DXGI_FORMAT_R16G16B16A16_FLOAT);

	D3D11Utils::CreateGeometryShader(m_device, L"Ex1406_SpriteGS.hlsl",
	                                 m_spriteGS);

	return true;
}

void Ex1406_DensityField::Update(float dt)
{
	// 입자들의 위치를 바꿔주는 작업도 GPU에서 진행
}

void Ex1406_DensityField::Render()
{

	// Timer timer(m_device);
	// timer.Start(m_context, true);

	DissipateDensity();
	AdvectParticles(); // Advect : 입자를 움직임 (움직임의 장을 기반으로 입자들이 움직이는 것)
	DrawSprites();

	// m_densityTex -> backBuffer
	ComPtr<ID3D11Texture2D> backBuffer;
	ThrowIfFailed(
	    m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));
	m_context->CopyResource(backBuffer.Get(), m_densityTex.GetTexture());

	// timer.End(m_context);
}

void Ex1406_DensityField::DissipateDensity()
{
	// [Compute Shader]
	// Density Field의 Dissipation
	// 소산(사라짐) 처리
	//	- DissipateDensity()는 매 프레임마다 densityField의 모든 픽셀 색상값을 0.1f 만큼 줄여서,
	//	  시간이 지날수록 잔상(밀도, 색상)이 서서히 사라지도록 만드는 감쇠 단계의 함수

	m_context->CSSetUnorderedAccessViews(0, 1, m_densityTex.GetAddressOfUAV(),
	                                     NULL);
	m_context->CSSetShader(m_densityDissipationCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_screenWidth / 32.0f)),
	                    UINT(ceil(m_screenHeight / 32.0f)), 1);

	AppBase::ComputeShaderBarrier();
}

void Ex1406_DensityField::AdvectParticles()
{
	// [Compute Shader]
	// m_particles	: 각 입자의 position과 color를 저장하고 있는 StructuredBuffer
	// m_densityTex : Particle Rendering 결과를 저장하는 Texture2D
	//	 - AdvectParticles 단계	: CS에서 입자들의 pos 갱신 [Sourcing]
	//	 - DrawSprites 단계		: AdvectParticles에서 갱신한 데이터를 기반으로 렌더링
	//
	// [주의]
	// ComputeShader는 Thread-safe 하지 않아서 연산의 선후 판정을 할 수 없음
	// 따라서 모든 Thread를 대상으로 ComputeShader의 연산이 모두 끝나면 렌더링 파이프라인으로 진입

	ID3D11UnorderedAccessView* uavs2[2] = {m_particles.GetUAV(),
	                                       m_densityTex.GetUAV()};
	m_context->CSSetUnorderedAccessViews(0, 2, uavs2, NULL);
	m_context->CSSetShader(m_densitySourcingCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_particles.m_cpu.size() / 256.0f)), 1, 1);

	AppBase::ComputeShaderBarrier();
}

void Ex1406_DensityField::DrawSprites()
{
	// Geometry Shader로 Particle Sprites 그리기

	AppBase::SetMainViewport();

	// 시간에 따른 누적 효과(모션 블러)를 원할때는 Clear 생략
	//  - Clear를 생략안할 경우 아무것도 구현안된 예제에서도 잔상이 남음

	// const float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	// m_context->ClearRenderTargetView(m_densityTex.GetRTV(), clearColor);

	// Set Shader
	m_context->OMSetRenderTargets(1, m_densityTex.GetAddressOfRTV(), NULL);
	m_context->VSSetShader(m_vertexShader.Get(), 0, 0);
	m_context->GSSetShader(m_spriteGS.Get(), 0, 0);
	m_context->PSSetShader(m_pixelShader.Get(), 0, 0);
	m_context->CSSetShader(NULL, 0, 0);

	// [BlendState]
	//  - "기존 렌더 타깃의 색상(DestColor)" 과 "새로 출력될 픽셀의 색상(SrcColor)"을 어떻게 조합(Blend)할지를 정의하는 규칙 집합
	//  - 각 채널(RGB, Alpha)에 대해 Src/Dest 가중치(SrcBlend, DestBlend)와 결합 연산(BlendOp, BlendOpAlpha)을 지정함

	// [blendColor]
	//  - OMSetBlendState()의 두 번째 인자.
	//  - BlendFactor라고도 하며, BlendDesc 내에서
	//    [D3D11_BLEND_BLEND_FACTOR / D3D11_BLEND_INV_BLEND_FACTOR]
	//    옵션이 사용될 때 해당 상수값이 블렌드 연산에 직접 영향을 줌
	//  - 예) SrcColor * BlendFactor + DestColor * (1 - BlendFactor)

	// [SampleMask]
	//  - OMSetBlendState()의 세 번째 인자
	//  - 개발자가 **1차적으로 제어 가능한 "샘플 활성 한계선(upper bound mask)"**
	//  - 각 비트가 MSAA 샘플 하나를 나타내며,
	//    [1 → 활성화(색상 기록 가능) / 0 → 비활성화(기록 차단)]
	//  - 예) 0xffffffff → 모든 샘플 활성화 (제한 없음)
	//
	//  - 실제 픽셀에 적용되는 최종 커버리지 마스크는 아래처럼 계산됨
	//        최종 마스크 = RasterizerCoverage
	//                   ∧ AlphaToCoverageMask
	//                   ∧ SampleMask
	//                   ∧ DepthStencilResult
	//
	//  - 이 중 AlphaToCoverageMask는 픽셀의 알파값을 기반으로 하드웨어가 생성하며,
	//    각 픽셀의 위치에 따라 pseudo-random한 패턴을 사용하여 동일한 샘플만 반복적으로 덮이지 않도록함 (균일한 공간 분포 유지) 

	const float blendColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	m_context->OMSetBlendState(Graphics::accumulateBS.Get(), blendColor,
	                           0xffffffff);

	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_context->VSSetShaderResources(0, 1, m_particles.GetAddressOfSRV());
	m_context->Draw(UINT(m_particles.m_cpu.size()), 0);
}

void Ex1406_DensityField::UpdateGUI() {}

} // namespace hlab