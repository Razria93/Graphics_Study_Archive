#include "Ex1401_Basic.h"
#include "GeometryGenerator.h"
#include "GraphicsCommon.h"

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Ex1401_Basic::Ex1401_Basic() : AppBase() {}

bool Ex1401_Basic::Initialize()
{
	// [디버깅 용도]
	cout << "Ex1401_Basic::Initialize()" << endl;

	// [CS 이용 렌더링]
	// CS를 이용하여 연산을 한 값을 렌더링에 사용하기 위해서는 backbuffer의 형식이 float여야함
	//	- GPU의 ALU(연산유닛)은 대부분 32bit float(Full-precision) 연산단위로 처리하며 ComputeShader 또한 마찬가지
	//	- 따라서 결과물을 저장할 렌더타깃 또한 float 형식이여야함
	//	- 그러나 채널의 크기가 일치할 필요는 없으며, 저장단계에서 정밀도 절삭이 일어나더라도 효율성을 위해 16bit float(Half-precision)으로 저장하겠다는 의도
	AppBase::m_backBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;

	// 여기서 backbuffer 초기화
	if (!AppBase::Initialize())
		return false;

	// 백버퍼의 텍스춰 가져오기 (백버퍼도 FLOAT 사용)
	ComPtr<ID3D11Texture2D> backBuffer;
	ThrowIfFailed(
	    m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

	// 백버퍼의 UAV 생성 [ComputeShader용 COM 객체]
	// UAV (Unordered Access View)
	//  - 비순차적 접근(Unordered Access)		: 스레드마다 다른 좌표(x, y, z)에 자유롭게 접근 가능
	//  - 랜덤 액세스(Random Access)			: 임의의 위치에 데이터를 읽기(Read) 및 쓰기(Write) 가능
	//  - GPU 메모리(View) 객체로, Compute Shader나 Pixel Shader(DX11.1+) 등에서 사용됨
	//  - 단, 여러 스레드가 동시에 같은 위치를 쓸 경우 데이터 충돌(Race Condition)이 발생할 수 있으므로
	//    필요 시 원자적(atomic) 연산을 사용해야 함 (예: InterlockedAdd 등)
	D3D11_TEXTURE2D_DESC desc;
	backBuffer->GetDesc(&desc);

	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	ZeroMemory(&uavDesc, sizeof(uavDesc));
	uavDesc.Format = desc.Format;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	uavDesc.Texture2D.MipSlice = 0;
	ThrowIfFailed(m_device->CreateUnorderedAccessView(
	    backBuffer.Get(), &uavDesc, m_backUAV.GetAddressOf()));

	// CS에서 사용할 Consts 버퍼
	D3D11Utils::CreateConstBuffer(m_device, m_constsCPU, m_constsGPU);

	// CS 만들기
	D3D11Utils::CreateComputeShader(m_device, L"Ex1401_CS.hlsl", m_testCS);

	// ComputeShader Test
	m_testComputePSO.m_computeShader = m_testCS;

	return true;
}

void Ex1401_Basic::Update(float dt)
{
	D3D11Utils::UpdateBuffer(m_context, m_constsCPU, m_constsGPU);
}

void Ex1401_Basic::Render()
{

	AppBase::SetPipelineState(m_testComputePSO);

	m_context->CSSetConstantBuffers(0, 1, m_constsGPU.GetAddressOf());
	m_context->CSSetUnorderedAccessViews(0, 1, m_backUAV.GetAddressOf(), NULL);	// UAV : Read / Write 모두 됨

	// TODO: ThreadGroupCount를 쉐이더의 numthreads에 따라 잘 바꿔주기
	// TODO: ceil() 사용하는 이유 이해하기

	// [Dispatch]
	//  - GPU에 일감을 나눠주는 함수 (Draw와 같은 역할)
	//  - [Compute Shader 스레드 그룹들을 실행하라]고 GPU에 명령함
	//
	//  - GPU의 스레드(코어) 수는 매우 많지만, 스크린의 모든 픽셀(수백만)을 
	//	  '1픽셀:1스레드'로 처리할 만큼 많지는 않기 때문에,
	//    [스크린 전체 픽셀을 일정한 규격의 그룹 단위로 나누어 병렬 연산]을 수행함
	//
	//  - 매개변수 (x, y, z)는 [스레드 그룹(Thread Group)의 개수]를 의미함
	//    → 한 그룹당 스레드 개수는 HLSL의 [numthreads(nx, ny, nz)] 속성에서 정의됨
	//    → 따라서 총 스레드 개수 = (x * nx, y * ny, z * nz)
	// 
	// [Dispatch(x,y,z)]
	//  - Ex1401_CS.hlsl : [numthreads(256, 1, 1)]
	//  - 즉, 256 x 1 x 1 Pixels 를 기본단위로 렌더링하고 있음
	//  - 해당 부분은 Width와 Height, 그리고 의도에 맞게 [스레드 그룹 내부의 픽셀 구조]와 [스레드 개수]를 조절
	//
	// [ceil]
	//	- 값을 올리는 함수
	//	- 각 축에 대한 그룹의 개수이기 때문에 버리게 되면 렌더링이 되지 않음
	//  - 따라서 올림을 하여 그룹의 형태가 온전치 않더라도 카운트를 하고 연산을 해주어야함
	// m_context->Dispatch(UINT(ceil(m_screenWidth / 256.0f)), m_screenHeight, 1);
	m_context->Dispatch(UINT(ceil(m_screenWidth / 32.0f)), UINT(ceil(m_screenHeight / 32.0f)), 1);

	// 컴퓨터 쉐이더가 하던 일을 끝내게 만들고 Resources 해제
	AppBase::ComputeShaderBarrier();
}

void Ex1401_Basic::UpdateGUI()
{
	ImGui::SliderFloat("Scale", &m_constsCPU.scale, 0.0f, 1.0f);
}

} // namespace hlab