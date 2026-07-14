#include "Ex1402_Blur.h"
#include "GeometryGenerator.h"
#include "GraphicsCommon.h"

#include <fp16.h>

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Ex1402_Blur::Ex1402_Blur() : AppBase() {}

bool Ex1402_Blur::Initialize()
{

	cout << "Ex1402_Blur::Initialize()" << endl;

	// ComputeShader에서 BackBuffer를 사용하기 위해서 FLOAT로 설정
	AppBase::m_backBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;

	// 속도 비교를 위해 해상도를 높이기
	AppBase::m_screenWidth = 1280;
	AppBase::m_screenHeight = 768;

	AppBase::m_useMSAA = false;

	if (!AppBase::Initialize())
		return false;

	PrepareForStagingTexture();

	// Texture와 RTV, SRV, UAV 생성 (Texture에 접근하기 위한 View COM객체는 한번에 1개씩만 사용가능[동시접근 불가])
	D3D11Utils::CreateUATexture(m_device, m_screenWidth, m_screenHeight,
	                            DXGI_FORMAT_R16G16B16A16_FLOAT, m_texA, m_rtvA,
	                            m_srvA, m_uavA);

	D3D11Utils::CreateUATexture(m_device, m_screenWidth, m_screenHeight,
	                            DXGI_FORMAT_R16G16B16A16_FLOAT, m_texB, m_rtvB,
	                            m_srvB, m_uavB);

	MeshData meshData = GeometryGenerator::MakeSquare();
	m_screenMesh = std::make_shared<Mesh>();
	D3D11Utils::CreateVertexBuffer(m_device, meshData.vertices,
	                               m_screenMesh->vertexBuffer);
	m_screenMesh->indexCount = UINT(meshData.indices.size());
	m_screenMesh->vertexCount = UINT(meshData.vertices.size());
	m_screenMesh->stride = UINT(sizeof(Vertex));
	D3D11Utils::CreateIndexBuffer(m_device, meshData.indices,
	                              m_screenMesh->indexBuffer);

	// Compute Shader
	D3D11Utils::CreateComputeShader(m_device, L"Ex1402_BlurXCS.hlsl",
	                                m_blurXCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1402_BlurYCS.hlsl",
	                                m_blurYCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1402_BlurXGroupCacheCS.hlsl",
	                                m_blurXGroupCacheCS);
	D3D11Utils::CreateComputeShader(m_device, L"Ex1402_BlurYGroupCacheCS.hlsl",
	                                m_blurYGroupCacheCS);

	D3D11Utils::CreatePixelShader(m_device, L"Ex1402_BlurXPS.hlsl", m_blurXPS);
	D3D11Utils::CreatePixelShader(m_device, L"Ex1402_BlurYPS.hlsl", m_blurYPS);

	// ComputeShader Blur
	m_blurXComputePSO.m_computeShader = m_blurXCS;
	m_blurYComputePSO.m_computeShader = m_blurYCS;

	// blurX/YPixelPSO (ComputerShader와 비교용)
	m_blurXPixelPSO = Graphics::postEffectsPSO;
	m_blurXPixelPSO.m_pixelShader = m_blurXPS;
	m_blurYPixelPSO = Graphics::postEffectsPSO;
	m_blurYPixelPSO.m_pixelShader = m_blurYPS;

	// ComputeShader Blur with groupshared cache
	m_blurXGroupCacheComputePSO.m_computeShader = m_blurXGroupCacheCS;
	m_blurYGroupCacheComputePSO.m_computeShader = m_blurYGroupCacheCS;

	return true;
}

void Ex1402_Blur::Update(float dt)
{
	// Update() 내용 없음
}

void Ex1402_Blur::Render()
{

	m_context->CopyResource(m_texA.Get(), m_stagingTexture.Get());

	Timer timer(m_device);
	timer.Start(m_context, true);

	for (int i = 0; i < 1000; i++)
	{
		// 같은 Blur를 3가지 opts로 구현함
		
		// 직접 Timer를 찍어보자
		// 강사님께서 실행한 실험의 경우 렌더링 파이프라인이 더 빠르게 나왔음
		// 렌더링 파이프라인의 경우 정해진 작업을 반복수행하는 것이기 때문에 최척화하기가 용이하기 때문이라는 추측
		// 드라이버에 의한 차이도 있음

		ComputeShaderBlur(false);		// BlurCS.hlsl 사용
		// ComputeShaderBlur(true);		// BlurGroupCacheCS.hlsl 사용
		// PixelShaderBlur();			// BlurPS.hlsl 사용
	}

	// timer.End(m_context);
	// exit(-1);

	// 주의: 시간 측정 결과는 여러가지 환경에 따라 많이 다릅니다.

	// m_texA -> backBuffer 복사
	ComPtr<ID3D11Texture2D> backBuffer;
	ThrowIfFailed(
	    m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));
	m_context->CopyResource(backBuffer.Get(), m_texA.Get());
}

void Ex1402_Blur::PrepareForStagingTexture()
{

	// Blur 확인을 위해 큰 값으로 초기화
	// 채널 당 32bit float를 사용하는 RGBA 데이터를 저장할 Vector4 컨테이너
	vector<Vector4> f32Image(m_screenWidth * m_screenHeight, Vector4(0.0f));

	// Blur 확인을 위해 큰 값으로 초기화
	//  - Blur는 특정한 곳에 몰려있는 값을 주변에 퍼뜨림
	//  - 해당 예제는 반복횟수가 1,000회로 굉장히 많기 때문에 테스트를 위해 기본값을 크게 설정함

	// texture(x, y) == texture[ x + m_screenWidth * y]
	f32Image[m_screenWidth / 4 + m_screenWidth * m_screenHeight / 2] =
	    Vector4(50000.0f, 0.0f, 0.0f, 1.0f);
	f32Image[m_screenWidth / 2 + m_screenWidth * m_screenHeight / 2] =
	    Vector4(0.0f, 50000.0f, 0.0f, 1.0f);
	f32Image[m_screenWidth / 4 * 3 + m_screenWidth * m_screenHeight / 2] =
	    Vector4(0.0f, 0.0f, 50000.0f, 1.0f);

	// 시작과 끝을 마킹
	f32Image[0] = Vector4(3000.0f);
	f32Image[f32Image.size() - 1] = Vector4(3000.0f);

	// cout << sizeof(Vector4) << endl; // 16 bytes

	// uint8_t (1byte) * 8
	vector<uint8_t> f16Image(m_screenWidth * m_screenHeight * 8);

	// 메모리 시작주소 저장
	uint16_t* f16temp = (uint16_t*)f16Image.data();
	float* f32temp = (float*)f32Image.data();

	// Size는 Vector4의 갯수이므로 * 4, RGBA 각각 별도로 접근하겠다는 것
	for (int i = 0; i < f32Image.size() * 4; i++)
	{
		// fp16_ieee_from_fp32_value() :
		//  - IEEE754 32-bit float을 16-bit half-float으로 변환하는 함수
		f16temp[i] = fp16_ieee_from_fp32_value(f32temp[i]);
	}

	// Staging Texture 만들고 CPU -> GPU 복사
	// Pixel 1개당 2byte(16bit) * 4채널 == 8byte
	m_stagingTexture = D3D11Utils::CreateStagingTexture(m_device,
	                                                    m_context,
	                                                    m_screenWidth,
	                                                    m_screenHeight,
	                                                    f16Image,
	                                                    DXGI_FORMAT_R16G16B16A16_FLOAT,
	                                                    1,
	                                                    1);
}

void Ex1402_Blur::PixelShaderBlur()
{

	ID3D11ShaderResourceView* tempSRV[1] = {NULL};
	ID3D11RenderTargetView* tempRTV[1] = {NULL};

	AppBase::SetMainViewport();
	m_context->PSSetSamplers(0, 1, Graphics::pointClampSS.GetAddressOf());
	m_context->IASetVertexBuffers(0, 1,
	                              m_screenMesh->vertexBuffer.GetAddressOf(),
	                              &m_screenMesh->stride, &m_screenMesh->offset);
	m_context->IASetIndexBuffer(m_screenMesh->indexBuffer.Get(),
	                            DXGI_FORMAT_R32_UINT, 0);

	// A to B
	// SRV : A
	// RTV : B
	AppBase::SetPipelineState(m_blurXPixelPSO);
	m_context->OMSetRenderTargets(1, m_rtvB.GetAddressOf(), NULL);
	m_context->PSSetShaderResources(0, 1, m_srvA.GetAddressOf());
	m_context->DrawIndexed(m_screenMesh->indexCount, 0, 0);

	// B to A
	// SRV : B
	// RTV : A
	AppBase::SetPipelineState(m_blurYPixelPSO);
	m_context->OMSetRenderTargets(1, m_rtvA.GetAddressOf(), NULL);
	m_context->PSSetShaderResources(0, 1, m_srvB.GetAddressOf());
	m_context->DrawIndexed(m_screenMesh->indexCount, 0, 0);
}

void Ex1402_Blur::ComputeShaderBlur(const bool useGroupCache)
{

	m_context->CSSetSamplers(0, 1, Graphics::pointClampSS.GetAddressOf());

	if (useGroupCache)
	{
		// ThreadGroup
		const UINT tgx = UINT(ceil(m_screenWidth / 256.0f));
		const UINT tgy = UINT(ceil(m_screenHeight / 256.0f));

		// Horizontal X-Blur, A to B
		// SRV : A
		// UAV : B
		AppBase::SetPipelineState(m_blurXGroupCacheComputePSO);
		m_context->CSSetShaderResources(0, 1, m_srvA.GetAddressOf());
		m_context->CSSetUnorderedAccessViews(0, 1, m_uavB.GetAddressOf(), NULL);
		m_context->Dispatch(tgx, m_screenHeight, 1);
		AppBase::ComputeShaderBarrier();

		// Vertical Y-Blur, B to A
		// SRV : B
		// UAV : A
		AppBase::SetPipelineState(m_blurYGroupCacheComputePSO);
		m_context->CSSetShaderResources(0, 1, m_srvB.GetAddressOf());
		m_context->CSSetUnorderedAccessViews(0, 1, m_uavA.GetAddressOf(), NULL);
		m_context->Dispatch(m_screenWidth, tgy, 1);
		AppBase::ComputeShaderBarrier();
	}
	else
	{
		// ComputeShader에서 설정한 numthreads에 대응
		const UINT tgx = UINT(ceil(m_screenWidth / 32.0f));
		const UINT tgy = UINT(ceil(m_screenHeight / 32.0f));

		// Horizontal X-Blur, A to B
		AppBase::SetPipelineState(m_blurXComputePSO);
		m_context->CSSetShaderResources(0, 1, m_srvA.GetAddressOf());
		m_context->CSSetUnorderedAccessViews(0, 1, m_uavB.GetAddressOf(), NULL);
		m_context->Dispatch(tgx, tgy, 1); // GroupCahe를 고려하고 만들어진 Dispatch

		// X-Blur이 완전히 끝나고 나서 Y-Blur가 실행해야함. 이를 실행하지 않을 경우 화면 출력이 안됨.
		// Graphics Debugger로 출력창을 확인하면 오류메세지를 확인할 수 있음
		AppBase::ComputeShaderBarrier();

		// Vertical Y-Blur, B to A
		AppBase::SetPipelineState(m_blurYComputePSO);
		m_context->CSSetShaderResources(0, 1, m_srvB.GetAddressOf());
		m_context->CSSetUnorderedAccessViews(0, 1, m_uavA.GetAddressOf(), NULL);
		m_context->Dispatch(tgx, tgy, 1);

		AppBase::ComputeShaderBarrier();
	}
}

void Ex1402_Blur::UpdateGUI() {}

} // namespace hlab