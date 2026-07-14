#include "Ex1403_MatVecMult.h"
#include "GeometryGenerator.h"
#include "GraphicsCommon.h"
#include "Texture2D.h"

#include <random>

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Ex1403_MatVecMult::Ex1403_MatVecMult() : AppBase() {}

float DotProduct(float* a, float* b, int N)
{

	float sum = 0.0f;

	for (int i = 0; i < N; i++)
	{
		sum += a[i] * b[i];
	}

	return sum;
}

bool Ex1403_MatVecMult::Initialize()
{

	cout << "Ex1403_MatVecMult::Initialize()" << endl;

	// ComputeShader에서 BackBuffer를 사용하기 위해서 FLOAT로 설정
	// 이 예제에서는 렌더링하지 않고 계산만 하고 종료
	AppBase::m_backBufferFormat = DXGI_FORMAT_R16G16B16A16_FLOAT;

	if (!AppBase::Initialize())
		return false;

	m_repeat = 1;
	m_numRows = 1024; //    *16;
	m_numCols = 2048; //    *8;

	PrepareForData();

	TestCPU();

	TestGPU();

	// 7. 결과 비교

	float errorGPUSum = 0.0f;
	for (int i = 0; i < m_myResult.size(); i++)
	{
		errorGPUSum += abs(m_myResult[i] - m_myResultGPU[i]);

		// 하나하나 다 출력해서 확인해보고 싶은 경우
		// cout << "Diff " << m_myResult[i] << " " << myResultGPU[i] << " "
		//    << abs(m_myResult[i] - myResultGPU[i])
		//    << endl;
	}
	cout << "Error GPU " << errorGPUSum << endl;

	cout << "GPU Result "
	     << DotProduct(m_myResultGPU.data(), m_myResultGPU.data(), m_numRows)
	     << endl;

	exit(0); // 렌더링 하지 않고 바로 종료

	return true;
}

void Ex1403_MatVecMult::Update(float dt) {}

void Ex1403_MatVecMult::Render() {}

// 사용할 데이터 준비
void Ex1403_MatVecMult::PrepareForData()
{

	// (m_numRows by m_numCols) Matrix 곱하기 m_numCols Vector
	// -> m_numRows Vector

	m_myMat = vector<float>(m_numRows * m_numCols); // m_numRows
	m_myVec = vector<float>(m_numCols);
	m_myResult = vector<float>(m_numRows, 0.0f); // 결과 저장용

	// 랜덤 넘버 생성기 (숫자가 클 경우 정밀도 문제 발생 -> floor로 절삭)
	// std::random_device rd;		// 난수 시드
	// std::mt19937 gen(rd());		// 랜덤한 난수 시드를 기반으로 매 실행마다 서로 다른 난수엔진을 매번 생성함
	std::mt19937 gen(0); // 일정한 난수 시드를 기반으로 매 실행마다 동일한 난수엔진을 매번 생성함

	std::uniform_real_distribution<float> dist(0, 10); // 0 ~ 10 사이 float 기반 균등분포 생성
	// [균등분포]
	//  - 모든 값이 나올 확률이 동일한 확률분포.
	//	- [a,b) 안에서 모든 값이 같은 확률로 등장
	//  - 그 밖에서는 확률이 0

	std::generate(m_myMat.begin(), m_myMat.end(),
	              [&]()
	              { return floor(dist(gen)); });
	std::generate(m_myVec.begin(), m_myVec.end(),
	              [&]()
	              { return floor(dist(gen)); });
	// std::generate(first, last, generator)
	//	- 지정한 범위 [first, last)의 모든 원소를 'generator 함수의 반환값으로 채움
	//	- 순서는 다음과 같이 동작함 (m_myMat 기준으로 설명)
	//		1. m_myMat의 각 요소를 begin부터 end까지 하나씩 순회함
	//
	//		2. 매번 dist(gen)으로 랜덤 실수를 하나 생성
	//			- [0, 10) 구간 안의 모든 실수 중에서, 동일한 확률로 선택된 하나의 난수를 반환하라는 것
	//
	//			- gen이 내부 상태를 바탕으로 다음 난수(정수) 를 하나 생성함
	//			  (비유 : 무작위 번호표를 뽑아주는 기계 / 예시: 3859039201 같은 32비트 정수)
	//
	//			- dist는 그 숫자를 받아서 [0 이상 10 미만의 균등분포 실수(float)]로 변환시킴
	//			  (비유: 그 번호표를 실제 숫자 범위(0~10) 로 스케일링해주는 함수 / 예: 3.48572f, 9.123f, 0.237f)
	//
	//		3. 그 값을 floor()로 내림해서 정수 형태로 변환
	//
	//		4. 그 결과를 해당 인덱스의 원소로 저장
	//
	//		5. 결과: m_myMat 전체가 0~9 사이의 난수(float 형태)로 채워짐

	// 디버깅용 데이터 (숫자가 클 경우 정밀도 문제 발생)
	// for (size_t i = 0; i < m_myMat.size(); i++)
	//    m_myMat[i] = float(i % 10);
	// for (int i = 0; i < m_myVec.size(); i++)
	//    m_myVec[i] = float(i % 10);
}

void Ex1403_MatVecMult::TestCPU()
{

	Timer timer(m_device);
	timer.Start(m_context, false);


	for (int i = 0; i < m_repeat; i++) // 반복횟수
	{
		size_t offset = 0;                  // 행의 시작 index
		for (int r = 0; r < m_numRows; r++) // 각 행마다 실행 (m_numRows가 행의 개수이기 때문)
		{
			// 행렬 벡터 곱하기 테스트
			// m_myResult[r] = DotProduct(&m_myMat[offset], &m_myVec[0],
			// m_numCols));

			// 반복 누적 테스트 용도 (+= 사용)
			m_myResult[r] += DotProduct(&m_myMat[offset],	// r번째 행 시작주소
			                            &m_myVec[0],		// 행렬곱 대상 벡터의 시작주소
			                            m_numCols);			// 열의 개수 (내적 길이)

			offset += m_numCols;	// 다음 행 연산을 위한 시작 index 위치변경
		}
	}
	// [TestCPU]
	//	- m_myResult의 각 요소에 [r번째 행 * 벡터]의 내적값 저장
	//  - 궁극적인 목표는 행렬과 벡터의 연산
	//  - 내적은 행렬연산과 같은 연산방식을 가지고 있기 때문에 사용하는 것

	timer.End(m_context);

	cout << "Result CPU: "
	     << DotProduct(m_myResult.data(), m_myResult.data(), m_numRows) << endl;
}

void Ex1403_MatVecMult::TestGPU()
{

	// 1. Texture 초기화

	Texture2D matTex, vecTex, outputTex;

	matTex.Initialize(m_device, m_numCols / 4, m_numRows,
	                  DXGI_FORMAT_R32G32B32A32_FLOAT);
	vecTex.Initialize(m_device, m_numCols / 4, 1,
	                  DXGI_FORMAT_R32G32B32A32_FLOAT);
	outputTex.Initialize(m_device, m_numRows,       // 주의: m_numRows
	                     1, DXGI_FORMAT_R32_FLOAT); // 주의: R32

	// 2. 데이터 업로드 (내부적으로 Staging texture 사용)

	// 주의: RGBA 사용으로 m_numCols/4
	std::vector<uint8_t> buffer;

	// uint8_t 자료형 buffer에 float 자료형 데이터들을 memcpy
	buffer.resize(m_myMat.size() * sizeof(float) / sizeof(uint8_t));
	memcpy(buffer.data(), m_myMat.data(), buffer.size());

	// CPU에서 작성된 데이터를 stagingTexture를 통해 GPU에서 사용가능한 COM객체로 Upload
	matTex.Upload(m_device, m_context, buffer);

	// buffer 재사용
	buffer.resize(m_myVec.size() * sizeof(float) / sizeof(uint8_t));
	memcpy(buffer.data(), m_myVec.data(), buffer.size());

	vecTex.Upload(m_device, m_context, buffer);

	// 결과값을 저장할 COM객체 생성을 위하여 일정 크기의 빈 벡터를 생성
	vector<float> myResultZero(m_numRows, 0.0f);

	buffer.resize(myResultZero.size() * sizeof(float) / sizeof(uint8_t));
	memcpy(buffer.data(), myResultZero.data(), buffer.size());

	outputTex.Upload(m_device, m_context, buffer);

	// 3. 쉐이더 호출
	ComPtr<ID3D11ComputeShader> matVecMultCS;
	D3D11Utils::CreateComputeShader(m_device, L"Ex1403_MatVecMultCS.hlsl",
	                                matVecMultCS);

	Timer timer(m_device);
	timer.Start(m_context, true);

	// 컴퓨터 쉐이더만 사용하는 특별한 상황
	m_context->CSSetShader(matVecMultCS.Get(), 0, 0);

	// 주의: R32라서 numRows를 4로 나눠주지 않음
	for (int i = 0; i < m_repeat; i++)
	{
		ID3D11ShaderResourceView* srvs[2] = {matTex.GetSRV(), vecTex.GetSRV()};
		m_context->CSSetShaderResources(0, 2, srvs);
		m_context->CSSetUnorderedAccessViews(0, 1, outputTex.GetAddressOfUAV(),
		                                     NULL);
		m_context->Dispatch(UINT(ceil(m_numRows / 256.0f)), 1, 1);
		AppBase::ComputeShaderBarrier(); // 이 예제에서는 생략 가능
	}

	/* 실험 결과는 여러 가지 요소에 따라 많이 달라집니다.

	1회 반복
	GPU : 0.064832, CPU : 3.1

	10회 반복
	GPU: 0.521728, CPU: 3.5592 <- CPU 오버헤드가 10배로 증가하지는 않음

	100회 반복
	GPU: 5.09747, CPU: 8.1159 <- CPU 오버헤드가 100배로 증가하지는 않음

	// CPU Time은 GPU 작업시간까지 포함된 것이 때문에 CPU 오버헤드는 일정하게 유지가 됨
	// 즉, CPU가 GPU에게 작업시키는 시간은 동일하다는 거
	// 따라서 시행횟수가 많아질수록 CPU단일 작업보다 GPU로 작업하는게 압도적으로 빠름

	*/

	timer.End(m_context);

	// 4. GPU 계산 결과를 CPU로 복사 (중간에 Staging texture 사용)
	buffer.resize(m_numRows * sizeof(float) / sizeof(uint8_t));
	std::fill(buffer.begin(), buffer.end(), 0);

	// GPU -> CPU로 결과값 Download
	outputTex.Download(m_context, buffer);

	// uint8_t -> float 복사
	m_myResultGPU = vector<float>(m_myResult.size());
	memcpy(m_myResultGPU.data(), buffer.data(), buffer.size());
}

void Ex1403_MatVecMult::UpdateGUI() {}

} // namespace hlab