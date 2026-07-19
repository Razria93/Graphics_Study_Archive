#include "Ex1501_ParticleSystem.h"
#include "GeometryGenerator.h"
#include "GraphicsCommon.h"

#include <numeric>
#include <random>

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Ex1501_ParticleSystem::Ex1501_ParticleSystem() : AppBase() {}

bool Ex1501_ParticleSystem::Initialize()
{

	cout << "Ex1501_ParticleSystem::Initialize()" << endl;

	// ComputeShader에서 Backbuffer를 사용
	AppBase::m_backBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;

	m_screenWidth = 1024;
	m_screenHeight = 1024;

	if (!AppBase::Initialize())
		return false;

	// 1. 데이터 초기화 (최대 Particle 수가 정해져있는 구조)
	//  - 새로운 파티클을 생성할 때는 죽어있는 파티클을 살리는(life를 양수로 바꾸는) 방식으로 구현함
	//	- 메모리 밀집도가 높고 규모가 크지 않은 파티클과 같은 것들은 메모리가 100% 사용되지 않더라도 미리 확보 후 on / off로 사용
	m_particlesCPU.resize(2048 * 2);
	// m_particlesCPU.resize(100);

	vector<Vector3> rainbow = {
	    {1.0f, 0.0f, 0.0f},  // Red
	    {1.0f, 0.65f, 0.0f}, // Orange
	    {1.0f, 1.0f, 0.0f},  // Yellow
	    {0.0f, 1.0f, 0.0f},  // Green
	    {0.0f, 0.0f, 1.0f},  // Blue
	    {0.3f, 0.0f, 0.5f},  // Indigo
	    {0.5f, 0.0f, 1.0f}   // Violet/Purple
	};

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> dp(-1.0f, 1.0f);
	uniform_int_distribution<size_t> dc(0, rainbow.size() - 1);
	for (auto& p : m_particlesCPU)
	{
		p.position = Vector3(dp(gen), dp(gen), 1.0f);
		p.color = rainbow[dc(gen)];
		p.radius = (dp(gen) + 1.3f) * 0.02f;
		p.life = -1.0f; // 일단 파티클을 다 죽어있는 상태로 만듦 (2048개 메모리만 확보해둠)
	}

	// GPU에도 메모리를 잡아줌
	// Dynamic을 활용하는 방식도 있음 (이러면 Staging이 없어도 됨)
	D3D11Utils::CreateStructuredBuffer(
	    m_device, UINT(m_particlesCPU.size()), sizeof(Particle),
	    m_particlesCPU.data(), m_particlesGPU, m_particlesSRV, m_particlesUAV);

	// CPU -> GPU로 복사 (CPU에서 랜덤넘버, 생성, 업데이트를 해주고 GPU로 넘기고 있음)
	// 최적화하려면 파티클 애니메이션을 CS에서 알고리듬을 구현
	D3D11Utils::CreateStagingBuffer(m_device, UINT(m_particlesCPU.size()),
	                                sizeof(Particle), m_particlesCPU.data(),
	                                m_particlesStagingGPU);

	// 주의: Vertex Shader에서 Vertex 정보 미사용

	// VS는 이전 예제와 동일
	const vector<D3D11_INPUT_ELEMENT_DESC> inputElements = {
	    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	     D3D11_INPUT_PER_VERTEX_DATA, 0}}; // Dummy
	D3D11Utils::CreateVertexShaderAndInputLayout(
	    m_device, L"Ex1501_ParticleSystemVS.hlsl", inputElements,
	    m_vertexShader, m_inputLayout);
	D3D11Utils::CreatePixelShader(m_device, L"Ex1501_ParticleSystemPS.hlsl",
	                              m_pixelShader);
	D3D11Utils::CreateGeometryShader(m_device, L"Ex1501_ParticleSystemGS.hlsl",
	                                 m_spriteGS);

	return true;
}

void Ex1501_ParticleSystem::Update(float dt)
{
	// 해당 예제는 GPU 파티클 연산을 실습하기 위한 2D 좌표계 기반 예제
	// 따라서 월드-뷰-프로젝션(WVP) 변환을 수행하지 않음
	// 즉, WVP 행렬은 항등행렬(Identity Matrix)로 취급되며,
	// 결과적으로 CPU에서 설정한 파티클의 position 값이 그대로 NDC 좌표로 사용되어
	// 래스터라이저(Rasterizer) 단계로 전달됨

	dt *= 0.5f; // 느리게 진행하고 싶을 경우 가상의 시간 사용 가능

	random_device rd;
	mt19937 gen(rd());

	// 임의설정
	uniform_real_distribution<float> randomTheta(-3.141592f, 3.141592f);
	// uniform_real_distribution<float> randomTheta(0.0f, 0.0f);
	uniform_real_distribution<float> randomSpeed(1.5f, 3.0f);
	uniform_real_distribution<float> randomLife(0.0f, 1.0f);

	const float wallWidth_left = -0.9f; // 벽 충돌너비 (left)
	const float wallWidth_right = 0.9f; // 벽 충돌너비 (right)
	const float groundHeight = -0.9f;   // 바닥 충돌높이

	// 마우스 클릭시 추가
	int newCount = 10; // 한 프레임에 새로 만들어질 수 있는 파티클 개수
	for (auto& p : m_particlesCPU)
	{
		if (AppBase::m_leftButton && p.life < 0.0f && newCount > 0)
		{
			// cout << "Click" << endl;
			// cout << "m_mouseNdcX : " << m_mouseNdcX << " / m_mouseNdcY : " << m_mouseNdcY << endl;

			if (m_mouseNdcX > wallWidth_right || m_mouseNdcX < wallWidth_left || m_mouseNdcY < groundHeight)
				continue;

			const float theta = randomTheta(gen);

			p.position = Vector3(m_mouseNdcX, m_mouseNdcY, 0.0);

			p.velocity = Vector3(cos(theta), -sin(theta), 0.0) * randomSpeed(gen);
			p.life = randomLife(gen) * 1.5f;
			newCount--;
		}
	}

	// 항상 추가하는 Source
	newCount = 10; // 추가 가능 카운트
	for (auto& p : m_particlesCPU)
	{
		// 비활성화되어 있는 입자를 찾으면 활성화하는 방식
		if (p.life < 0.0f && newCount > 0)
		{
			const float theta = randomTheta(gen);
			// const float theta = 0.0f;
			p.position =
			    Vector3(cos(theta), -sin(theta), 0.0) * randomLife(gen) * 0.1f + // 여기서 randomLife는 Life의 의미로 쓰인 것이 아닌,
			    Vector3(0.9f, 0.9f, 0.0f);                                       // 생성좌표값인 Vector3(cos(theta), -sin(theta), 0.0)에 랜덤성을 주기 위하여 사용된 것
			                                                                     // 즉, 중심좌표가 Vector3(0.0f, -0.3f, 0.0f)에 반지름이 0.1f인 원 내부의 임의의 지점에서 생성 되도록 함
			                                                                     // 임의 생성은 theta에 의한 랜덤성으로 인해 방향이 임의로 지정되며, randomLife(gen)으로 인해 길이가 임의지정 됨
			                                                                     // 또한 cos(theta), -sin(theta)인 이유는 NDC -> Viewport 변환과정에서 Y축 반전이 일어나
			                                                                     // theta의 진행방향이 CCW에서 CW로 바뀜. 즉, 의도한 증가방향과 화면에 보이는 증가방향이 반대가 된다는 것
			                                                                     // 따라서 애초에 입력할 때 반대인 -theta를 넣어줌으로서 theta의 진행방향이 의도한 방향으로 진행되게 하기 위함이며,
			                                                                     // 이를 cos, sin에 대입했을 경우, cos(−θ)=cos(θ), sin(−θ)=−sin(θ) 가 되는 것

			// p.position = Vector3(cos(theta), -sin(theta), 0.0) + Vector3(-0.5f, 0.0f, 0.0f);

			p.velocity = Vector3(-1.0f, 0.0f, 0.0) * randomSpeed(gen); // 입자들마다 다르게 생성 됨 (velocity가 서로 다름)
			p.life = randomLife(gen) * 1.5f;                           // life 추가
			newCount--;

			// 만약 consume / append Buffer를 사용할 경우 활성화된 파티클 카운트까지 가능함
			// consume / append가 동적으로 보이지만 메모리는 미리 확보하고 사용하는 방식 (정적)
		}
	}

	const Vector3 gravity = Vector3(0.0f, -9.8f, 0.0f);
	const float cor = 0.95f; // Coefficient Of Restitution (충돌/반발계수) : 부딫히고 나서 속도를 얼마나 잃을것인가

	for (auto& p : m_particlesCPU)
	{

		if (p.life < 0.0f) // 수명이 다했다면 무시
			continue;

		p.velocity = p.velocity + gravity * dt; // 중력가속도를 사용하여 속도를 업데이트 하고 있음
		p.position += p.velocity * dt;
		p.life -= dt;

		// 충돌검사
		if (p.position.y < groundHeight && p.velocity.y < 0.0f)
		{
			const float theta = randomTheta(gen);
			float random_x = clamp(cos(theta), -1.0f, 1.0f);
			float random_y = clamp(abs(-sin(theta)), 0.0f, 1.0f);

			// cor을 randomLife(gen) 으로 주어 다이나믹하게 설정할 수도 있음
			// 또는 크기에 따라서도 다르게 해줄 수도 있을듯
			// 예제에서는 position을 경계로 고정시키고 있음 (경계밖으로 못나가게)

			p.position.y = groundHeight;
			p.velocity = Vector3(p.velocity.x * random_x, -p.velocity.y * random_y * cor, 0.0);
		}

		if (p.position.x < wallWidth_left && p.velocity.x < 0.0f)
		{
			const float theta = randomTheta(gen);
			float random_x = clamp(abs(cos(theta)), 0.0f, 1.0f);
			float random_y = clamp(-sin(theta), -1.0f, 1.0f);

			p.position.x = wallWidth_left;
			p.velocity = Vector3(-p.velocity.x * random_x * cor, p.velocity.y * random_y, 0.0);
		}

		if (p.position.x > wallWidth_right && p.velocity.x > 0.0f)
		{
			const float theta = randomTheta(gen);
			float random_x = clamp(abs(cos(theta)), 0.0f, 1.0f);
			float random_y = clamp(-sin(theta), -1.0f, 1.0f);

			p.position.x = wallWidth_right;
			p.velocity = Vector3(-p.velocity.x * random_x * cor, p.velocity.y * random_y, 0.0);

			// p.life = -1.0; // 이렇게 설정할 경우 삭제됨
		}
	}

	D3D11Utils::CopyToStagingBuffer(
	    m_context, m_particlesStagingGPU,
	    UINT(sizeof(Particle) * m_particlesCPU.size()), m_particlesCPU.data());
	m_context->CopyResource(m_particlesGPU.Get(), m_particlesStagingGPU.Get());
}

void Ex1501_ParticleSystem::Render()
{

	// Timer timer(m_device);
	// timer.Start(m_context, true);

	DrawSprites();

	// timer.End(m_context);
}

void Ex1501_ParticleSystem::DrawSprites()
{

	// Geometry Shader로 Particle Sprites 그리기

	AppBase::SetMainViewport();

	const float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	m_context->ClearRenderTargetView(m_backBufferRTV.Get(), clearColor);
	m_context->OMSetRenderTargets(1, m_backBufferRTV.GetAddressOf(), NULL);
	m_context->VSSetShader(m_vertexShader.Get(), 0, 0);
	m_context->GSSetShader(m_spriteGS.Get(), 0, 0);
	m_context->PSSetShader(m_pixelShader.Get(), 0, 0);
	m_context->CSSetShader(NULL, 0, 0);

	// 색을 모두 더하면서 그리는 accumulateBS 사용
	const float blendColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	m_context->OMSetBlendState(Graphics::accumulateBS.Get(), blendColor,
	                           0xffffffff);

	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	m_context->VSSetShaderResources(0, 1, m_particlesSRV.GetAddressOf());
	m_context->Draw(UINT(m_particlesCPU.size()), 0);
}

void Ex1501_ParticleSystem::UpdateGUI() {}

} // namespace hlab