#include "Ex1407_IndirectArguments.h"
#include "GeometryGenerator.h"
#include "GraphicsCommon.h"

#include <numeric>
#include <random>

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Ex1407_IndirectArguments::Ex1407_IndirectArguments() : AppBase() {}

bool Ex1407_IndirectArguments::Initialize()
{

	cout << "Ex1407_IndirectArguments::Initialize()" << endl;

	// ComputeShader에서 Backbuffer를 사용
	AppBase::m_backBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;

	m_screenWidth = 640;
	m_screenHeight = 640;

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
	// 안내: m_argsGPU 초기화
	// 여기서는 지정된 값으로 초기화를 해주고 있지만 ComputeShader에서
	// 그때그때 조건에 따라 다른 값으로 업데이트를 할 수도 있습니다.
	// (UAV 필요)

	// IndirectArgs 여러개
	// IndirectArgs 로 쓸 Buffer는 해당 함수를 호출하여 Create 해야함
	D3D11Utils::CreateIndirectArgsBuffer(m_device, UINT(m_argsCPU.size()),
	                                     sizeof(IndirectArgs), m_argsCPU.data(),
	                                     m_argsGPU);

	// 주의: Vertex Shader에서 Vertex 정보 미사용

	// VS는 이전 예제와 동일
	const vector<D3D11_INPUT_ELEMENT_DESC> inputElements = {{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	                                                         D3D11_INPUT_PER_VERTEX_DATA, 0}}; // Dummy

	D3D11Utils::CreateVertexShaderAndInputLayout(m_device, L"Ex1404_StructuredBufferVS.hlsl", inputElements,
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

void Ex1407_IndirectArguments::Update(float dt)
{
	DissipateDensity();
	AdvectParticles();
}

void Ex1407_IndirectArguments::Render()
{

	// Timer timer(m_device);
	// timer.Start(m_context, true);

	DrawSprites();

	ComPtr<ID3D11Texture2D> backBuffer;
	ThrowIfFailed(
	    m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));
	m_context->CopyResource(backBuffer.Get(), m_densityTex.GetTexture());

	// timer.End(m_context);
}

void Ex1407_IndirectArguments::DissipateDensity()
{

	// Density Field의 Dissipation (Compute Shader)

	m_context->CSSetUnorderedAccessViews(0, 1, m_densityTex.GetAddressOfUAV(),
	                                     NULL);
	m_context->CSSetShader(m_densityDissipationCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_screenWidth / 32.0f)),
	                    UINT(ceil(m_screenHeight / 32.0f)), 1);
	AppBase::ComputeShaderBarrier();
}

void Ex1407_IndirectArguments::AdvectParticles()
{

	// 입자들이 Density field에 색상 추가 sourcing (Compute Shader)
	// 주의: ComputeShader버전은 Thread-safe 하지 않음 -> Draw() 사용

	ID3D11UnorderedAccessView* uavs2[2] = {m_particles.GetUAV(),
	                                       m_densityTex.GetUAV()};
	m_context->CSSetUnorderedAccessViews(0, 2, uavs2, NULL);
	m_context->CSSetShader(m_densitySourcingCS.Get(), 0, 0);
	m_context->Dispatch(UINT(ceil(m_particles.m_cpu.size() / 256.0f)), 1, 1);
	AppBase::ComputeShaderBarrier();
}

void Ex1407_IndirectArguments::DrawSprites()
{

	// Geometry Shader로 Particle Sprites 그리기

	AppBase::SetMainViewport();

	// 시간에 따른 누적 효과(모션 블러)를 원할때는 Clear 생략
	// const float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	// m_context->ClearRenderTargetView(m_densityRTV.Get(), clearColor);

	m_context->OMSetRenderTargets(1, m_densityTex.GetAddressOfRTV(), NULL);
	m_context->VSSetShader(m_vertexShader.Get(), 0, 0);
	m_context->GSSetShader(m_spriteGS.Get(), 0, 0);
	m_context->PSSetShader(m_pixelShader.Get(), 0, 0);
	m_context->CSSetShader(NULL, 0, 0);
	const float blendColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	m_context->OMSetBlendState(Graphics::accumulateBS.Get(), blendColor,
	                           0xffffffff);
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_context->VSSetShaderResources(0, 1, m_particles.GetAddressOfSRV());

	// m_context->Draw(UINT(m_particlesCPU.size()), 0);
	// m_context->DrawInstanced(UINT(m_particlesCPU.size()), 1, 0, 0);

	const UINT offset = sizeof(IndirectArgs) * 0; // * 0, * 1, * 2 가능

	// - DrawInstanced에서 인수 4개를 넣어주는 것과 다르게
	//	 DrawInstancedIndirect에서는 해당값이 미리 캐싱되어 있는 버퍼의 포인터를 넣어줌
	// - 위의 offset 값에 따라 들어가는 값이 다르며,
	//	 offset에 의한 startLocation으로부터 UINT 4개값이 사용됨
	// - 하지만 해당 방식의 진정한 강점은 m_argsGPU를 GPU 내에서 상황에 따라 연산해서 사용할 수 있다는 것
	// - 사용 예제
	//		1. Frustum Culling 알고리즘
	//			- 그릴 물체들을 모두 GPU에 넣어놓되, 상황에 따라 그릴 물체만 찾아서 Draw()
	//			- 이전에는 CPU에서 연산했으나, 현재는 GPU에서도 구현 가능
	// 
	//		2. Frustum 내부에 물체가 있는지 판단하는 알고리즘
	//			- CPU : Directxcollision.h - BoundingFrustum structure
	//				- Frustum 이지만 충돌을 체크할 수 있는 기능을 포함하고 있음
	//				- 삼각형 하나하나를 체크하는 것이 아닌, object를 감싸는 Bounding 객체를 탐지하는 것 (각각 수행하면 비효율적)
	//				- ObjectOrientedBoundingBox : 물체랑 같이 움직이는 바운딩 박스
	//				- 충돌 체크도 가능함 (물리엔진 파트에서 추가적으로 배움)

	m_context->DrawInstancedIndirect(m_argsGPU.Get(), // <- 인수로 GPU 버퍼 사용
	                                 offset);         // <- GPU 버퍼의 offset
}

void Ex1407_IndirectArguments::UpdateGUI() {}

} // namespace hlab