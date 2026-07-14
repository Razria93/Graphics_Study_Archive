#define _CRT_SECURE_NO_WARNINGS // stb_image_write compile error fix

#include "D3D11Utils.h"

#include <directxtk/DDSTextureLoader.h> // 큐브맵 읽을 때 필요
#include <dxgi.h>                       // DXGIFactory
#include <dxgi1_4.h>                    // DXGIFactory4
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

namespace hlab
{

using namespace std;
using namespace DirectX;

void CheckResult(HRESULT hr, ID3DBlob* errorBlob)
{
	if (FAILED(hr))
	{
		// 파일이 없을 경우
		if ((hr & D3D11_ERROR_FILE_NOT_FOUND) != 0)
		{
			cout << "File not found." << endl;
		}

		// 에러 메시지가 있으면 출력
		if (errorBlob)
		{
			cout << "Shader compile error\n"
			     << (char*)errorBlob->GetBufferPointer() << endl;
		}
	}
}

bool D3D11Utils::CreateDepthBuffer(
    ComPtr<ID3D11Device>& device, int screenWidth, int screenHeight,
    UINT& numQualityLevels, ComPtr<ID3D11DepthStencilView>& depthStencilView)
{

	D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
	depthStencilBufferDesc.Width = screenWidth;
	depthStencilBufferDesc.Height = screenHeight;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	if (numQualityLevels > 0)
	{
		depthStencilBufferDesc.SampleDesc.Count = 4; // how many multisamples
		depthStencilBufferDesc.SampleDesc.Quality = numQualityLevels - 1;
	}
	else
	{
		depthStencilBufferDesc.SampleDesc.Count = 1; // how many multisamples
		depthStencilBufferDesc.SampleDesc.Quality = 0;
	}
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0;
	depthStencilBufferDesc.MiscFlags = 0;

	ComPtr<ID3D11Texture2D> depthStencilBuffer;

	if (FAILED(device->CreateTexture2D(&depthStencilBufferDesc, 0,
	                                   depthStencilBuffer.GetAddressOf())))
	{
		std::cout << "CreateTexture2D() failed." << std::endl;
	}
	if (FAILED(device->CreateDepthStencilView(
	        depthStencilBuffer.Get(), 0, depthStencilView.GetAddressOf())))
	{
		std::cout << "CreateDepthStencilView() failed." << std::endl;
	}
	return true;
}

void D3D11Utils::CreateVertexShaderAndInputLayout(
    ComPtr<ID3D11Device>& device, const wstring& filename,
    const vector<D3D11_INPUT_ELEMENT_DESC>& inputElements,
    ComPtr<ID3D11VertexShader>& m_vertexShader,
    ComPtr<ID3D11InputLayout>& m_inputLayout)
{

	ComPtr<ID3DBlob> shaderBlob;
	ComPtr<ID3DBlob> errorBlob;

	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	// 쉐이더의 시작점의 이름이 "main"인 함수로 지정
	// D3D_COMPILE_STANDARD_FILE_INCLUDE 추가: 쉐이더에서 include 사용
	HRESULT hr = D3DCompileFromFile(
	    filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
	    "vs_5_0", compileFlags, 0, &shaderBlob, &errorBlob);

	CheckResult(hr, errorBlob.Get());

	device->CreateVertexShader(shaderBlob->GetBufferPointer(),
	                           shaderBlob->GetBufferSize(), NULL,
	                           &m_vertexShader);

	device->CreateInputLayout(inputElements.data(), UINT(inputElements.size()),
	                          shaderBlob->GetBufferPointer(),
	                          shaderBlob->GetBufferSize(), &m_inputLayout);
}

void D3D11Utils::CreatePixelShader(ComPtr<ID3D11Device>& device,
                                   const wstring& filename,
                                   ComPtr<ID3D11PixelShader>& m_pixelShader)
{
	ComPtr<ID3DBlob> shaderBlob;
	ComPtr<ID3DBlob> errorBlob;

	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	// 쉐이더의 시작점의 이름이 "main"인 함수로 지정
	// D3D_COMPILE_STANDARD_FILE_INCLUDE 추가: 쉐이더에서 include 사용
	HRESULT hr = D3DCompileFromFile(
	    filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
	    "ps_5_0", compileFlags, 0, &shaderBlob, &errorBlob);

	CheckResult(hr, errorBlob.Get());

	device->CreatePixelShader(shaderBlob->GetBufferPointer(),
	                          shaderBlob->GetBufferSize(), NULL,
	                          &m_pixelShader);
}

void D3D11Utils::CreateIndexBuffer(ComPtr<ID3D11Device>& device,
                                   const std::vector<uint32_t>& indices,
                                   ComPtr<ID3D11Buffer>& indexBuffer)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE; // 초기화 후 변경X
	bufferDesc.ByteWidth = UINT(sizeof(uint32_t) * indices.size());
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0; // 0 if no CPU access is necessary.
	bufferDesc.StructureByteStride = sizeof(uint32_t);

	D3D11_SUBRESOURCE_DATA indexBufferData = {0};
	indexBufferData.pSysMem = indices.data();
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;

	device->CreateBuffer(&bufferDesc, &indexBufferData,
	                     indexBuffer.GetAddressOf());
}

void D3D11Utils::CreateGeometryShader(
    ComPtr<ID3D11Device>& device, const wstring& filename,
    ComPtr<ID3D11GeometryShader>& geometryShader)
{

	ComPtr<ID3DBlob> shaderBlob;
	ComPtr<ID3DBlob> errorBlob;

	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	// 쉐이더의 시작점의 이름이 "main"인 함수로 지정
	// D3D_COMPILE_STANDARD_FILE_INCLUDE 추가: 쉐이더에서 include 사용
	HRESULT hr = D3DCompileFromFile(
	    filename.c_str(), 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main",
	    "gs_5_0", compileFlags, 0, &shaderBlob, &errorBlob);

	// CheckResult(hr, errorBlob.Get());

	device->CreateGeometryShader(shaderBlob->GetBufferPointer(),
	                             shaderBlob->GetBufferSize(), NULL,
	                             &geometryShader);
}

void ReadImage(const std::string filename, std::vector<uint8_t>& image,
               int& width, int& height)
{

	int channels;

	unsigned char* img =
	    stbi_load(filename.c_str(), &width, &height, &channels, 0);

	// assert(channels == 4);

	// 4채널로 만들어서 복사
	image.resize(width * height * 4);

	if (channels == 3)
	{
		for (size_t i = 0; i < width * height; i++)
		{
			for (size_t c = 0; c < 3; c++)
			{
				image[4 * i + c] = img[i * channels + c];
			}
			image[4 * i + 3] = 255;
		}
	}
	else if (channels == 4)
	{
		for (size_t i = 0; i < width * height; i++)
		{
			for (size_t c = 0; c < 4; c++)
			{
				image[4 * i + c] = img[i * channels + c];
			}
		}
	}
	else
	{
		std::cout << "Read 3 or 4 channels images only. " << channels
		          << " channels" << endl;
	}
}

void D3D11Utils::CreateTexture(
    ComPtr<ID3D11Device>& device, const std::string filename,
    ComPtr<ID3D11Texture2D>& texture,
    ComPtr<ID3D11ShaderResourceView>& textureResourceView)
{

	int width, height, channels;

	unsigned char* img =
	    stbi_load(filename.c_str(), &width, &height, &channels, 0);

	// assert(channels == 4);

	// 4채널로 만들어서 복사
	std::vector<uint8_t> image;
	image.resize(width * height * 4);
	for (size_t i = 0; i < width * height; i++)
	{
		for (size_t c = 0; c < 3; c++)
		{
			image[4 * i + c] = img[i * channels + c];
		}
		image[4 * i + 3] = 255;
	}

	// Create texture.
	D3D11_TEXTURE2D_DESC txtDesc = {};
	txtDesc.Width = width;
	txtDesc.Height = height;
	txtDesc.MipLevels = txtDesc.ArraySize = 1;
	txtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	txtDesc.SampleDesc.Count = 1;
	txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
	txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = image.data();
	initData.SysMemPitch = txtDesc.Width * sizeof(uint8_t) * 4;
	// initData.SysMemSlicePitch = 0;

	device->CreateTexture2D(&txtDesc, &initData, texture.GetAddressOf());
	device->CreateShaderResourceView(texture.Get(), nullptr,
	                                 textureResourceView.GetAddressOf());
}

// HERE
void D3D11Utils::CreateTextureArray(ComPtr<ID3D11Device>& device, const std::vector<std::string> filenames,
                                    ComPtr<ID3D11Texture2D>& texture,
                                    ComPtr<ID3D11ShaderResourceView>& textureResourceView)
{

	// 모든 이미지의 width와 height가 같다고 가정합니다. (해상도가 동일하다는 것)
	// 다르다면 다른걸 이미지 자체의 해상도를 조정하거나 여기서 변경하거나
	int width = 0, height = 0;
	std::vector<uint8_t> imageArray;
	for (const auto& f : filenames)
	{
		// 각각의 이미지를 for문으로 image라는 벡터에 ReadImage로 저장 후,
		// 저장된 image 벡터를 insert를 통해 데이터를 imageArray라는 벡터에 누적시키고 있음

		cout << f << endl;

		std::vector<uint8_t> image;

		ReadImage(f, image, width, height);

		// std::vector::begin()은 첫 요소(인덱스 0)를 가리키는 이터레이터(iterator)를 반환합니다.
		
		// ============================================================
		// [TL;DR]
		// - 이터레이터 = 컨테이너 요소를 가리키는 "일반화된 포인터" 커서.
		// - "일반화"란 컨테이너가 달라도 *같은 패턴*(*it, ++it 등)으로 다루게 한 제너릭 추상화.
		// - std::vector는 재할당(capacity 초과 시)하면 메모리 블록을 갈아끼우므로
		//   기존 이터레이터/포인터/참조가 전부 무효(댕글링)됨.
		// - 재할당이 없어도 (같은 버퍼 내에서) 삽입/삭제 지점부터 끝까지는 요소 이동으로 무효 가능.
		// - 대량 추가 전 reserve(), 변동 후 이터레이터 다시 얻기, 인덱스 캐싱 등을 권장.
		// ============================================================
		//
		// [이터레이터(Iterator)]
		// - 컨테이너 요소를 가리키고 순회하는 "일반화된 포인터" 인터페이스.
		// - 목적: 서로 다른 내부 구조(vector/list/map 등)를 같은 사용 패턴으로 다룰 수 있게 함.
		//   * 사용 패턴 예: *it, ++it, it == end, (vector의 경우) it + n, it[i] 등
		// - 실제 작업(정렬/복사/탐색)은 표준 알고리즘이 수행하고, 이터레이터는 그 알고리즘이
		//   요구하는 '가리키기/이동/비교' 연산만 제공합니다. (컴파일타임 제너릭 규약)
		//
		// [일반화(Generalization)의 의미]
		// - 컨테이너마다 내부 구조/접근 방식이 달라도 동일한 패턴으로 접근 가능하게 추상화.
		// - 이터레이터 "범주(category)"에 따라 가능한 연산이 달라짐:
		//   Input → Forward → Bidirectional → RandomAccess → Contiguous (vector는 RandomAccess/Contiguous)
		//   (예: list는 it + n 불가, vector는 가능)
		//
		// [std::vector에서의 무효화(Invalidation) 규칙 요약]
		// 1) 재할당(Reallocation) 발생 시 (size > capacity가 되는 삽입 등):
		//    - 새 메모리 블록으로 모든 요소 이동/복사 → 이전 블록 해제
		//    - 기존 이터레이터/포인터/참조 "전부 무효(댕글링)"
		// 2) 재할당 없이 같은 버퍼 내에서 재배치하는 경우:
		//    - insert(pos, ...) : 재할당이 없더라도 'pos부터 끝까지'의 이터레이터/참조 무효
		//      (이전 구간은 보통 유효)
		//    - erase(first, last): 지워진 구간 '이후부터 끝까지' 무효
		//    - push_back/emplace_back: 재할당 없으면 기존 요소 참조는 대개 유효하나 end()는 변경
		// 3) clear/assign/shrink_to_fit/(대부분의) swap: 모두 무효로 보는 것이 안전
		// 4) reserve(n): n > capacity()이면 재할당 → 모두 무효, 아니면 영향 없음
		//
		// [안전 사용 팁]
		// - 대량 추가 전에 v.reserve(예상 최대)로 재할당을 예방합니다.
		// - 변동 이후 이터레이터를 다시 얻습니다. (필요 시 인덱스 캐싱 → 변동 후 재계산)
		// - 순서/주소 안정성이 중요하고 중간 삽입/삭제가 잦다면 list/deque/객체 풀 등 구조 재검토.
		// - 맨 뒤 한 개 추가는 push_back/emplace_back, 뒤에 범위 붙이기는 insert(v.end(), first, last).
		//
		// [요약 문구(의미 정리)]
		// - '일반화된 포인터'라는 말은 "다른 인터페이스지만 동일한 사용 패턴으로
		//   사용자가 의도한 요소에 접근하도록 해주는 추상화"라는 뜻입니다.
		// - 벡터의 재할당은 "메모리 블록 교체"이므로, 이전 블록을 가리키던 커서는 모두 댕글링이 됩니다.
		
		// 맨앞 붙이기 (프리펀드) 형식
		// 뒷 요소부터 역순으로 Shift 하여 옮기고 맨앞에 새로운 값(<T>)을 추가하는 형식
		imageArray.insert(imageArray.begin(), image.begin(), image.end());
	}

	// Create texture.
	D3D11_TEXTURE2D_DESC txtDesc;
	ZeroMemory(&txtDesc, sizeof(txtDesc));
	txtDesc.Width = UINT(width);					// 텍스쳐의 하나의 width
	txtDesc.Height = UINT(height);					// 텍스쳐의 하나의 height
	txtDesc.MipLevels = 1;
	txtDesc.ArraySize = UINT(filenames.size());		// 그 텍스쳐가 모두 몇개인지
	txtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	txtDesc.SampleDesc.Count = 1;
	txtDesc.SampleDesc.Quality = 0;
	txtDesc.Usage = D3D11_USAGE_IMMUTABLE;
	txtDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	// SUBRESOURCE_DATA를 배열로 만들어야함 (vector)
	// D3D11_SUBRESOURCE_DATA
	// 버퍼/텍스쳐를 생성할 때 초기 데이터를 넘겨주는 구조체
	
	// 벡터를 초기화
	// 벡터를 v(size)로 초기화할 경우 벡터요소의 초기값들이 size 갯수만큼 실제로 생성됨
	std::vector<D3D11_SUBRESOURCE_DATA> initData(filenames.size());
	// std::vector<D3D11_SUBRESOURCE_DATA> initData;  // 기본 생성: "빈 벡터"
	//
	// - initData 객체(컨트롤 블록/메타데이터)는 지금 이 변수 자리에 생성되어 있음.
	//   (내부적으로 data 포인터, size, capacity 같은 필드를 가짐 ? 구현 의존)
	// - 하지만 요소는 1개도 없으므로
	//     initData.size()    == 0
	//     initData.capacity()== 0  (대부분의 구현; 표준이 0을 강제하진 않음)
	//     initData.data()    == 유의미한 버퍼 없음(역참조 금지)
	//   → 요소 저장용 "연속 버퍼"는 아직 할당되지 않은 상태.
	//
	// - 이후 아래와 같은 시점에 요소 버퍼(연속 메모리)가 힙에 할당되고, 메타데이터가 업데이트됨:
	//     ? reserve(N):  용량(capacity)만 ≥ N으로 확보 (size는 그대로 0)
	//     ? resize(N):   요소 N개를 실제로 생성 (POD는 0 초기화, 객체는 디폴트 생성자 호출)
	//     ? push_back / insert: 요소 추가; capacity 부족하면 재할당 발생
	//
	// - 주의(무효화):
	//     ? size + 삽입수 > capacity → 재할당(새 버퍼로 이사) → 기존 이터레이터/포인터/참조 "전부 무효"
	//     ? 재할당이 없어도 insert/erase 구간부터 끝까지는 주소 재배치로 무효 가능
	//
	// - 팁:
	//     ? 대량 추가 전 reserve(예상치)로 재할당을 줄일 것
	//     ? 주소가 필요할 때는 표준 API 사용: initData.data() / &*it
	//     ? 빈 벡터에서 data()는 유의미한 메모리를 보장하지 않으므로 역참조 금지

	size_t offset = 0;
	for (auto& i : initData)
	{
		// 벡터로 생성한 서브리소스를 초기화하는 중
		// 여기서 뭉텅이로 저장했던 imageArray를 해석할 수 있는 가이드를 만드는 것
		i.pSysMem = imageArray.data() + offset;										// 데이터의 시작주소
		i.SysMemPitch = txtDesc.Width * sizeof(uint8_t) * 4;						// 데이터의 행 간격 (어디서 줄바꿈을 해야하는지) / 가로줄 데이터의 크기
		i.SysMemSlicePitch = txtDesc.Width * txtDesc.Height * sizeof(uint8_t) * 4;	// 데이터의 슬라이스 간격 (어디까지가 한 페이지의 내용인지) / 슬라이스 데이터의 크기
		offset += i.SysMemSlicePitch;
	}
	
	// Desc vs SubresourceData 요약
	// - D3D11_TEXTURE2D_DESC(Desc): "목표 리소스"의 스펙 정의
	//   * 차원/크기: Width, Height / (MipLevels, ArraySize)
	//   * 포맷/용도: DXGI_FORMAT, Usage, BindFlags, CPUAccessFlags, MiscFlags 등
	//
	// - D3D11_SUBRESOURCE_DATA: "초기 업로드 소스 메모리"의 배치 정보
	//   * pSysMem: 시작 포인터
	//   * SysMemPitch: 행(row) 간 바이트 간격
	//   * SysMemSlicePitch: 슬라이스(3D 면) 간 바이트 간격
	//
	// 즉, Desc = 목적지(텍스처 형태/의미), SubresourceData = 출발지(바이트 배열 배치/주소).
	// 초기 데이터 나중에 채울 경우: CreateTexture2D(&desc, nullptr, …) 후 UpdateSubresource 사용.
	// 쉽게 이야기하면 Desc은 저장할 버퍼에 대한 정보를 설정 및 저장
	// D3D11_SUBRESOURCE_DATA는 버퍼에 저장할 소스에 대한 정보를 설정 및 저장

	// 이미지 파일로 가져온 데이터가 texture에 복사가 됨
	// txtDesc에서 정의한 서브리소스 갯수만큼 각 항목을 사용해 모든 서브리소스를 즉시 초기화함
	device->CreateTexture2D(&txtDesc, initData.data(), texture.GetAddressOf());

	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Format = txtDesc.Format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;	// 디멘전
	desc.Texture2DArray.MostDetailedMip = 0;
	desc.Texture2DArray.MipLevels = txtDesc.MipLevels;			
	desc.Texture2DArray.FirstArraySlice = 0;
	desc.Texture2DArray.ArraySize = txtDesc.ArraySize;			// 사이즈 설정

	device->CreateShaderResourceView(texture.Get(), &desc,
	                                 textureResourceView.GetAddressOf());
}

void D3D11Utils::CreateCubemapTexture(
    ComPtr<ID3D11Device>& device, const wchar_t* filename,
    ComPtr<ID3D11ShaderResourceView>& textureResourceView)
{

	ComPtr<ID3D11Texture2D> texture;

	// https://github.com/microsoft/DirectXTK/wiki/DDSTextureLoader
	auto hr = CreateDDSTextureFromFileEx(
	    device.Get(), filename, 0, D3D11_USAGE_DEFAULT,
	    D3D11_BIND_SHADER_RESOURCE, 0,
	    D3D11_RESOURCE_MISC_TEXTURECUBE, // 큐브맵용 텍스춰
	    DDS_LOADER_FLAGS(false), (ID3D11Resource**)texture.GetAddressOf(),
	    textureResourceView.GetAddressOf(), nullptr);

	if (FAILED(hr))
	{
		std::cout << "CreateDDSTextureFromFileEx() failed" << std::endl;
	}
}

void D3D11Utils::WriteToFile(ComPtr<ID3D11Device>& device,
                             ComPtr<ID3D11DeviceContext>& context,
                             ComPtr<ID3D11Texture2D>& textureToWrite,
                             const std::string filename)
{

	D3D11_TEXTURE2D_DESC desc;
	textureToWrite->GetDesc(&desc);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = 0;
	desc.MiscFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ; // CPU에서 읽기 가능
	desc.Usage = D3D11_USAGE_STAGING;            // GPU에서 CPU로 보낼 데이터를 임시 보관

	ComPtr<ID3D11Texture2D> stagingTexture;
	if (FAILED(device->CreateTexture2D(&desc, nullptr,
	                                   stagingTexture.GetAddressOf())))
	{
		cout << "Failed()" << endl;
	}

	// 참고: 전체 복사할 때
	// context->CopyResource(stagingTexture.Get(), pTemp.Get());

	// 일부만 복사할 때 사용
	D3D11_BOX box;
	box.left = 0;
	box.right = desc.Width;
	box.top = 0;
	box.bottom = desc.Height;
	box.front = 0;
	box.back = 1;
	context->CopySubresourceRegion(stagingTexture.Get(), 0, 0, 0, 0,
	                               textureToWrite.Get(), 0, &box);

	// R8G8B8A8 이라고 가정
	std::vector<uint8_t> pixels(desc.Width * desc.Height * 4);

	D3D11_MAPPED_SUBRESOURCE ms;
	context->Map(stagingTexture.Get(), NULL, D3D11_MAP_READ, NULL,
	             &ms); // D3D11_MAP_READ 주의

	// 텍스춰가 작을 경우에는
	// ms.RowPitch가 width * sizeof(uint8_t) * 4보다 클 수도 있어서
	// for문으로 가로줄 하나씩 복사
	uint8_t* pData = (uint8_t*)ms.pData;
	for (unsigned int h = 0; h < desc.Height; h++)
	{
		memcpy(&pixels[h * desc.Width * 4], &pData[h * ms.RowPitch],
		       desc.Width * sizeof(uint8_t) * 4);
	}

	context->Unmap(stagingTexture.Get(), NULL);

	stbi_write_png(filename.c_str(), desc.Width, desc.Height, 4, pixels.data(),
	               desc.Width * 4);

	cout << filename << endl;
}

} // namespace hlab