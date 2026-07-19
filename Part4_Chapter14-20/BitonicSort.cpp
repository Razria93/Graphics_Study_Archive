#include "BitonicSort.h"

#include <algorithm>
#include <assert.h>
#include <execution>
#include <random>

namespace hlab
{

using namespace std;

void PrintArray(const vector<BitonicSort::Element>& arr)
{
	cout << "K: ";
	for (const auto& element : arr)
		cout << element.key << " ";
	cout << endl;

	cout << "V: ";
	for (const auto& element : arr)
		cout << element.value << " ";
	cout << endl;
}

bool Compare(const vector<BitonicSort::Element>& a,
             const vector<BitonicSort::Element>& b)
{
	if (a.size() != b.size())
		return false;

	int64_t aSum = 0, bSum = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i].key != b[i].key)
			return false;
		aSum += a[i].value;
		bSum += b[i].value;
	}

	if (aSum != bSum)
		return false;

	return true;
}

void BitonicSort::Initialize(ComPtr<ID3D11Device>& device,
                             const UINT numElements,
                             const wstring shaderFilename)
{

	// 2의 제곱인지 확인
	// https://stackoverflow.com/questions/108318/how-can-i-test-whether-a-number-is-a-power-of-2
	assert(numElements > 0); // 정렬할 데이터의 갯수가 0 이상
	assert((numElements & (numElements - 1)) == 0);
	// [2의 제곱수의 특징]
	// - 2진수로 표현했을 때 항상 1개의 비트만 켜져있음(1)
	// - 이를 수학적으로 검증하는 방법은 다음과 같음
	//
	//   [numElements] 와 [numElements - 1]를 BitwiseAND 연산을 할 경우 같은 비트가 없어야함
	//
	// - 예시 : 8 (2^3)
	//		- numElements		: 1000
	//		- numElements - 1	: 0111
	//		- (numElements & (numElements - 1) == 0

	m_numElements = numElements;

	m_array.Initialize(device, numElements);

	D3D11Utils::CreateComputeShader(device, shaderFilename, m_bitonicSortCS);

	// [비토닉 정렬 핵심 개념]
	// - k: 병합(merge) 그룹의 크기
	// - j: 같은 그룹(k) 내에서 비교할 인덱스 간격(offset)

	// bitonicSort를 사용할 때는 numElements가 반드시 2의 거듭제곱이어야함
	for (uint32_t k = 2; k <= numElements; k *= 2)
		for (uint32_t j = k / 2; j > 0; j /= 2)
		{
			Consts c;

			c.j = j; // 그룹 내부에서 비교할 간격(offset)
			c.k = k; // 현재 병합(merge) 그룹의 전체 크기

			// (j, k) 조합을 저장 → 이후 GPU에서 각 단계별 정렬 수행 시
			// 해당 상수 버퍼를 전달하여 비교/병합 단계를 제어함
			m_constsCpu.push_back(c);
		}

	// - GPU 상수 버퍼 배열 생성 (CPU 데이터 → GPU ConstantBuffer로 변환)
	//
	// - GPU가 실제로 비토닉 정렬을 수행하기 전에,
	//   필요한 모든(j, k) 조합이 이미 ConstantBuffer로 GPU에 업로드되어 있음
	//
	// - 비토닉 정렬은 ComputeShader 내에서 numthreads(1024,1,1) 단위로 병렬 실행됨
	//		- 즉, 한 번의 Dispatch당 최대 1024개 요소를 병렬 처리
	//		- 하지만 실제 정렬 단계(k,j)는 알고리즘 논리적으로 제어되며
	//        numElements가 1024보다 작아도 정상 동작함 (남는 스레드는 idle 처리)

	m_constsGpu.resize(m_constsCpu.size());
	for (size_t i = 0; i < m_constsCpu.size(); i++)
	{
		D3D11Utils::CreateConstBuffer(device, m_constsCpu[i], m_constsGpu[i]);
	}
}

void BitonicSort::SortGPU(ComPtr<ID3D11Device>& device,
                          ComPtr<ID3D11DeviceContext>& context)
{
	// j, k는 CPU에서 돌림
	// 또한 j,k에 대해서는 이미 m_constsGpu에 세팅을 해두었기 때문에 여기서는 for문을 돌리는 데만 사용함
	size_t constCount = 0;
	for (uint32_t k = 2; k <= m_numElements; k *= 2)
		for (uint32_t j = k / 2; j > 0; j /= 2)
		{
			context->CSSetConstantBuffers(0, 1, m_constsGpu[constCount++].GetAddressOf());
			context->CSSetShader(m_bitonicSortCS.Get(), 0, 0);
			context->CSSetUnorderedAccessViews(0, 1, m_array.GetAddressOfUAV(), NULL);
			context->Dispatch(UINT(ceil(m_numElements / 1024.0f)), 1, 1);
		}

	// UAV Barrier
	ID3D11ShaderResourceView* nullSRV[2] = {0, 0};
	context->CSSetShaderResources(0, 2, nullSRV);
	ID3D11UnorderedAccessView* nullUAV[2] = {0, 0};
	context->CSSetUnorderedAccessViews(0, 2, nullUAV, NULL);
}

void BitonicSort::SortCPU(vector<Element>& arr)
{

	const size_t numElements = arr.size();

	for (uint32_t k = 2; k <= numElements; k *= 2)
		for (uint32_t j = k / 2; j > 0; j /= 2)
		{

#pragma omp parallel for

			for (int32_t i = 0; i < int32_t(numElements); i++)
			{
				// ^ (bitwise XOR : 같으면 0, 다르면 1)
				// i ^ j
				//	- i의 bit에서 j의 비트 위치만큼 뒤집으면 j 단위의 거리만큼 떨어진 인덱스가 됨
				//  - XOR로 뒤집히게 될 경우 그 bit에 해당하는 값이 더해지거나 빼지기 때문
				int32_t l = i ^ j;	
				if (l > i)
				{
					if (((i & k) == 0) && (arr[i].key > arr[l].key) ||
					    ((i & k) != 0) && (arr[i].key < arr[l].key))
						std::swap(arr[i], arr[l]);
				}
			}

			// cout << j << endl;
			// PrintArray(arr);
		}
}

void BitonicSort::TestBitonicSort(ComPtr<ID3D11Device>& device,
                                  ComPtr<ID3D11DeviceContext>& context)
{

	Timer timer(device);

	// Random Number Generator
	// 1. rd는 진짜 랜덤한 시드 (운영체제, 하드웨어 수준의 예측 불가능한 값)
	// 2. gen은 위 시드를 기반으로 결정론적인 의사난수 시퀀스를 만듦
	//		- mt19937은 시드가 같으면 언제 실행해도 같은 난수 순서를 반환함 (결정론적(deterministic) 알고리즘)
	// 3. dc는 그 시퀀스를 0 ~99 사이의 균등 확률로 매핑함
	//		- uniform_int_distribution 또한 결정론적 매핑 함수

	std::random_device rd;                                       // 시드 생성기
	std::mt19937 gen(rd());                                      // 난수 엔진
	std::uniform_int_distribution<uint32_t> dc(0, uint32_t(99)); // “0~99 정수 균등분포” 생성기
	                                                             // 세 개를 합쳐서 dc(gen) 호출 시 0~99 사이 균등한 난수를 얻음

	for (uint32_t numElements = 1024; numElements <= 1024 * pow(2, 10); numElements *= 2) // pow(2, 10)는 실험을 위해 요소의 숫자를 2의 거듭제곱 형태로 늘려주는 것
	{
		cout << "Test Num Elements " << numElements << endl;

		// 1. 실험 데이터 준비
		// std::generate(arr.begin(), arr.end(), lambda)
		//	- 지정된 범위([first, last))의 모든 원소를 함수 결과값으로 채워 넣는 함수
		vector<Element> arr(numElements);
		std::generate(arr.begin(), arr.end(),
		              [&]() -> Element                 // [] : 외부변수를 가져오는 방식 / () : 입력 파라미터 (매개변수) / -> Element : 반환자료형 명시 / {} : 함수 본문
		              { return {dc(gen), dc(gen)}; }); // Element 컨테이너의 모든 요소의 key,value값을 0~99 사이의 임의 값으로 초기화함
		vector<Element> arrCopy1(arr);                 // 사본
		vector<Element> arrCopy2(arr);                 // 사본

		// 2. std::sort() 사용
		{
			timer.Start(context, false);

			// 1. std::sort(begin, end, 비교함수)
			//	- begin 부터 end까지의 원소를 [비교함수]의 기준에 따라 오름차순으로 정렬

			// 2. std::execution::par
			//	- 병렬 실행 (여러 스레드)을 지정하는 기능
			// [참고] std::execution::seq
			//	- 기본값. 순차 실행 (단일 스레드)

			// 3. std::sort의 세 번째 인자는 “Compare”라는 함수 객체로, 형태도 아래와 같이 고정
			//	- bool comp(const T& a, const T& b)
			//	- 해당 함수의 내용을 람다함수 형태로 지정해서 넘겨줌
			//		- 캡쳐가 없다면 함수 포인터처럼 '시작주소를 넘기는 것과 동일함'
			//		- 캡쳐가 있다면 내부적으로 operator()를 가진 함수 객체의 인스턴스 주소를 넘기는 구조
			//
			// 4. 반환된 불값에 따라 a, b가 sort 됨
			std::sort(std::execution::par, arrCopy1.begin(), arrCopy1.end(),
			          [](const Element& a, const Element& b) -> bool
			          {
				          return a.key < b.key;
			          });
			timer.End(context);
		}

		// 3. Wikipedia 구현
		{
			timer.Start(context, false);
			SortCPU(arr);
			timer.End(context);
			cout << (Compare(arr, arrCopy1) ? "OK" : "NOT OK") << endl;
		}

		// 4. GPU 구현
		{
			BitonicSort sort(device, UINT(arrCopy2.size()),
			                 L"Ex1408_BitonicSortCS.hlsl");
			sort.m_array.Upload(context, arrCopy2);	// 난수로 초기화된 Element 컨테이너 복사

			timer.Start(context, true);
			sort.SortGPU(device, context);
			timer.End(context);

			sort.m_array.Download(context, arrCopy2);
			cout << (Compare(arr, arrCopy2) ? "OK" : "NOT OK") << endl;

			// PrintArray(arrCopy2);
		}

		// 제 PC 기준 메모리 복사를 제외하고 std::sort()와 비슷합니다.
		// sort() 자체가 빠르지 않더라도 CPU-GPU 복사를 피할 수 있다는 것은
		// 장점입니다.

		// 추가 최적화 참고: MS Sample에서는 j 루프를 쉐이더 안으로 옮겼습니다.
		// https://github.com/microsoft/DirectX-Graphics-Samples/blob/master/MiniEngine/Core/Shaders/Bitonic32InnerSortCS.hlsl
	}

	exit(0);
}

} // namespace hlab