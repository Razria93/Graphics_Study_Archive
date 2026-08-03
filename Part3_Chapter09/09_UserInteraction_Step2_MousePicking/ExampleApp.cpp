#include "ExampleApp.h"

#include <directxtk/DDSTextureLoader.h> // 큐브맵 읽을 때 필요
#include <tuple>
#include <vector>

#include "GeometryGenerator.h"

namespace hlab
{

using namespace std;
using namespace DirectX;

ExampleApp::ExampleApp() : AppBase() {}

bool ExampleApp::Initialize()
{

	if (!AppBase::Initialize())
		return false;

	m_cubeMapping.Initialize(
	    m_device, L"../Assets/Textures/Cubemaps/skybox/cubemap_bgra.dds",
	    L"../Assets/Textures/Cubemaps/skybox/cubemap_diffuse.dds",
	    L"../Assets/Textures/Cubemaps/skybox/cubemap_specular.dds");

	MeshData ground = GeometryGenerator::MakeSquare(2.0f);
	ground.textureFilename = "../Assets/Textures/blender_uv_grid_2k.png";
	m_meshGroupGround.Initialize(m_device, {ground});
	m_meshGroupGround.m_diffuseResView = m_cubeMapping.m_diffuseResView;
	m_meshGroupGround.m_specularResView = m_cubeMapping.m_specularResView;

	// 바닥으로 사용하기 위해 회전
	Matrix modelMat = Matrix::CreateRotationX(DirectX::XM_PIDIV2);
	Matrix invTransposeRow = modelMat;
	invTransposeRow.Translation(Vector3(0.0f));
	invTransposeRow = invTransposeRow.Invert().Transpose();

	// ConstantBuffer 초기화 (바닥은 변경 없음)
	m_meshGroupGround.m_basicVertexConstantData.model = modelMat.Transpose();
	m_meshGroupGround.m_basicVertexConstantData.invTranspose =
	    invTransposeRow.Transpose();
	m_meshGroupGround.m_basicPixelConstantData.useTexture = true;
	m_meshGroupGround.m_basicPixelConstantData.material.diffuse = Vector3(1.0f);
	m_meshGroupGround.UpdateConstantBuffers(m_device, m_context);

	// 물체 1
	{
		MeshData sphere = GeometryGenerator::MakeSphere(0.1f, 20, 20);
		m_meshGroupSphere.Initialize(m_device, {sphere});
		m_meshGroupSphere.m_diffuseResView = m_cubeMapping.m_diffuseResView;
		m_meshGroupSphere.m_specularResView = m_cubeMapping.m_specularResView;
		Matrix modelMat = Matrix::CreateTranslation({-0.2f, 0.1f, 0.6f});
		Matrix invTransposeRow = modelMat;
		invTransposeRow.Translation(Vector3(0.0f));
		invTransposeRow = invTransposeRow.Invert().Transpose();
		m_meshGroupSphere.m_basicVertexConstantData.model =
		    modelMat.Transpose();
		m_meshGroupSphere.m_basicVertexConstantData.invTranspose =
		    invTransposeRow.Transpose();
		m_meshGroupGround.m_basicPixelConstantData.isPickingSphere = false;
		m_meshGroupSphere.m_basicPixelConstantData.useTexture = false;
		m_meshGroupSphere.m_basicPixelConstantData.material.diffuse =
		    Vector3(0.5f, 0.5f, 0.5f);
		m_meshGroupSphere.m_basicPixelConstantData.material.specular =
		    Vector3(0.0f);
		m_meshGroupSphere.UpdateConstantBuffers(m_device, m_context);
	}

	// 물체 2
	{
		// TODO:
	}

	BuildFilters();

	return true;
}

void ExampleApp::Update(float dt)
{

	// 카메라의 이동
	if (m_useFirstPersonView)
	{
		if (m_keyPressed[87])
			m_camera.MoveForward(dt);
		if (m_keyPressed[83])
			m_camera.MoveForward(-dt);
		if (m_keyPressed[68])
			m_camera.MoveRight(dt);
		if (m_keyPressed[65])
			m_camera.MoveRight(-dt);
	}

	Matrix viewRow = m_camera.GetViewRow();
	Matrix projRow = m_camera.GetProjRow();
	Vector3 eyeWorld = m_camera.GetEyePos();

	// 큐브 매핑 Constant Buffer 업데이트
	m_cubeMapping.UpdateConstantBuffers(
	    m_device, m_context, viewRow.Transpose(), projRow.Transpose());

	// 바닥 매핑 Constant Buffer 업데이트
	m_meshGroupGround.m_basicPixelConstantData.eyeWorld = eyeWorld;
	m_meshGroupGround.m_basicVertexConstantData.view = viewRow.Transpose();
	m_meshGroupGround.m_basicVertexConstantData.projection =
	    projRow.Transpose();
	m_meshGroupGround.UpdateConstantBuffers(m_device, m_context);


	// 다른 물체들 Constat Buffer 업데이트
	
	// picking
	if (m_meshGroupSphere.m_pickingDirtyFlag)
	{
		m_meshGroupSphere.m_basicPixelConstantData.isPickingSphere = m_meshGroupSphere.m_pickingFlag;
		std::cout << "'m_meshGroupSphere.m_basicPixelConstantData.isPickingSphere' is Update" << std::endl;
		std::cout << "isPickingSphere is " << m_meshGroupSphere.m_basicPixelConstantData.isPickingSphere << std::endl;
		m_meshGroupSphere.m_pickingDirtyFlag = 0;
	}

	m_meshGroupSphere.m_basicPixelConstantData.eyeWorld = eyeWorld;
	m_meshGroupSphere.m_basicVertexConstantData.view = viewRow.Transpose();
	m_meshGroupSphere.m_basicVertexConstantData.projection =
	    projRow.Transpose();

	// TODO:

	m_meshGroupSphere.UpdateConstantBuffers(m_device, m_context);

	// TODO:

	if (m_dirtyflag && m_filters.size() > 1)
	{
		m_filters[1]->m_pixelConstData.threshold = m_threshold;
		m_filters[1]->UpdateConstantBuffers(m_device, m_context);
		m_filters.back()->m_pixelConstData.strength = m_strength;
		m_filters.back()->UpdateConstantBuffers(m_device, m_context);
		m_dirtyflag = 0;
	}
}

void ExampleApp::Render()
{

	// RS: Rasterizer stage
	// OM: Output-Merger stage
	// VS: Vertex Shader
	// PS: Pixel Shader
	// IA: Input-Assembler stage

	SetViewport();

	float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};

	m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);

	// 마우스 피킹에 사용할 indexRenderTarget도 초기화
	m_context->ClearRenderTargetView(m_indexRenderTargetView.Get(), clearColor);

	m_context->ClearDepthStencilView(m_depthStencilView.Get(),
	                                 D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
	                                 1.0f, 0);
	// Multiple render targets
	// 인덱스를 저장할 RenderTarget을 추가
	// 여기서 m_indexRenderTargetView 하기 때문에
	// m_indexTexture 에는 1번째로 내보내는 값들이 그려질 것임

	// 안그려지고 있던 것이 아니라, m_renderTargetView는 swapChain의 backBuffer 이기 때문에 swapChain에 그려졌었던 것이고
	// m_indexRenderTargetView는 RenderTargetView에 별도로 그려지고 있었던 것
	// 이렇게 한다면 swapChain에는 안그려지고 RTV에만 그려질 것임
	//
	// backBuffer는 SwapChain 생성 당시 지정한 갯수만큼 swapChain 객체 내에 생성되어 포함되어 있는 Buffer임
	// OMSetRTV는 GPU에서 기록할 Texture의 RTV를 Set하여 해당 Texture에 GPU가 기록할 수 있게 해주는 것
	// 그렇기 때문에 어떠한 Texture가 와도 상관없음
	// 그러나 화면에 출력되기 위해서는 Present() 호출 이전에 반드시 backBuffer에 Copy가 되어 있어야함
	// m_renderTargetView.Get()을 없앨 경우 m_indexRenderTargetView에 기록은 되나 결과적으로 출력이 안됨
	//
	//

	ID3D11RenderTargetView *targets[] = {m_renderTargetView.Get(),
	                                     m_indexRenderTargetView.Get()};
	m_context->OMSetRenderTargets(2, targets, m_depthStencilView.Get());
	m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

	if (m_drawAsWire)
	{
		m_context->RSSetState(m_wireRasterizerSate.Get());
	}
	else
	{
		m_context->RSSetState(m_rasterizerSate.Get());
	}

	m_meshGroupGround.Render(m_context);
	m_meshGroupSphere.Render(m_context);
	// TODO:

	// 물체 렌더링 후 큐브매핑
	m_cubeMapping.Render(m_context);

	// 후처리 필터 시작하기 전에 Texture2DMS에 렌더링 된 결과를 Texture2D로 복사
	// MSAA Texture2DMS to Texture2D
	// https://stackoverflow.com/questions/24269813/directx-newb-multisampled-texture2d-with-depth-on-a-billboard
	ComPtr<ID3D11Texture2D> backBuffer;
	m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	m_context->ResolveSubresource(m_tempTexture.Get(), 0, backBuffer.Get(), 0,
	                              DXGI_FORMAT_R8G8B8A8_UNORM);

	// 후처리 필터
	if (m_usePostProcessing)
	{
		for (auto &f : m_filters)
		{
			f->Render(m_context);
		}
	}

	// Picking
	{
		// TODO: m_pickColor 업데이트
		//  GPU->CPU는 화면 캡쳐 코드 참고

		if (m_screenWidth <= 0 || m_screenHeight <= 0)
			return;

		D3D11_TEXTURE2D_DESC indexTextureDesc{};
		m_indexTempTexture->GetDesc(&indexTextureDesc);
		if (m_cursorX < 0 || m_cursorY < 0 ||
		    static_cast<UINT>(m_cursorX) >= indexTextureDesc.Width ||
		    static_cast<UINT>(m_cursorY) >= indexTextureDesc.Height)
			return;

		// 여기서 Get되는 backBuffer는 위에 RTV로 지정하여 기록이 되었던 _m_indexTexture
		// swapchain의 backBuffer는 main RTV로 사용하고 있던 것 1개임
		// 즉, ResolveSubresource의 대상이 되어야하는건 백버퍼가 아니라 m_indexTexture
		// 해결! 이제 해당 staging을 CPU로 넘겨서 색상데이터와 일치하면 특정 텍스쳐 혹은 색을 자체적으로 표시하거나, 그 정보를 GPU한테 넘겨서 처리시켜도 될듯

		// ComPtr<ID3D11Texture2D> backBuffer_m_indexTexture;
		// m_swapChain->GetBuffer(1,
		//                        IID_PPV_ARGS(backBuffer_m_indexTexture.GetAddressOf()));

		// MSAA 데이터를 일반 텍스쳐 버퍼로 복사
		m_context->ResolveSubresource(m_indexTempTexture.Get(), 0,
		                              m_indexTexture.Get(), 0,
		                              DXGI_FORMAT_R8G8B8A8_UNORM);
		// Copy계열 함수
		// CopyResource :
		// 단순히 GPU 리소스끼리 bitwise copy. (비트단위로 카피)
		// MSAA ↔ Non - MSAA 사이에는 직접 사용할 수 없음
		// ResolveSubresource :
		// MSAA → Non-MSAA로 변환할 때 전용.
		// 각 픽셀의 여러 샘플들을 평균내서 1픽셀로 합침.
		// MSAA의 경우 픽셀 1개에 여러 개의 샘플 데이터를 가지고 있음
		// GPU 출력단계 (Rasterizer -> RenderTarget)에서는 샘플별로 데이터가 유지됨
		// Resolve(평균)는 화면에 최종 출력하거나
		// ResolveSubresource를 호출하여 일반 텍스처로 복사하려 할 때 합쳐짐

		// 참고: 전체 복사할 때
		// context->CopyResource(stagingTexture.Get(), pTemp.Get());

		D3D11_BOX box;
		box.left = m_cursorX;
		box.right = m_cursorX + 1; // write 해갈 영역을 지정 left ~ right
		box.top = m_cursorY;
		box.bottom = m_cursorY + 1; // write 해갈 영역을 지정 top ~ bottom
		box.front = 0;
		box.back = 1;
		m_context->CopySubresourceRegion(m_indexStagingTexture.Get(), // 목적지 리소스 (write 대상)
		                                 0,                           // 목적지 서브리소스 인덱스
		                                 0, 0, 0,                     // 목적지 리소스 안에서 "복사 시작 좌표"
		                                 m_indexTempTexture.Get(),    // 소스 리소스	(read 대상)
		                                 0,                           // 소스 서브리소스 인덱스
		                                 &box);                       // 소스에서 가져올 영역 (nullptr이면 전체)

		size_t boxWidth = box.right - box.left;
		size_t boxHeight = box.bottom - box.top;

		// R8G8B8A8 이라고 가정
		std::vector<uint8_t> pixels(boxWidth * boxHeight * 4);

		// stagingTexture를 Read할 수 있는 ms COM 객체를 만듦
		D3D11_MAPPED_SUBRESOURCE ms;
		m_context->Map(m_indexStagingTexture.Get(),
		               NULL,
		               D3D11_MAP_READ, // D3D11_MAP_READ 주의
		               NULL,
		               &ms);

		// 텍스춰가 작을 경우에는
		// ms.RowPitch가 width * sizeof(uint8_t) * 4보다 클 수도 있어서
		// for문으로 가로줄 하나씩 복사

		// ms.pData 안에는 CPU 쪽에서 접근할 수 있는 포인터가 저장되는 변수이며, Map 호출 시 채워짐
		// Map : 어떤 집합의 원소를 다른 집합의 원소로 대응시킴 (연결지음, 대응 관계를 만듦)
		// 해당 포인터는 사실상 “GPU 리소스 메모리(또는 그에 대응하는 메모리)”에 대응되는 CPU 주소

		// 각 배열번호는 해당 행의 시작 바이트 오프셋
		// uint8_t*로 캐스팅한 이유는, 텍스처 데이터가 바이트 단위(R8G8B8A8_UNORM 같은 RGBA 8bit × 4) 로 저장돼 있기 때문

		// GPU 메모리는 행(row) 단위로 정렬(alignment) 됨
		//
		// 예를 들어 픽셀 포맷이 R8G8B8A8(4바이트) 이고,
		// width가 5라면 :
		// 한 줄 유효 데이터 크기 = 5 × 4 = 20 bytes
		// 
		// 하지만 GPU는 메모리 효율성과 SIMD 최적화를 위해 보통 256바이트 단위로 행을 정렬함.
		// 그래서 실제 RowPitch는 20이 아니라 256바이트가 될 수 있음
		// 즉, 한 줄마다 “20바이트 유효데이터 + 236바이트 패딩” 식으로 저장됨.
		// 따라서 패딩 값이 다음 데이터가 저장될 공간에 들어가는걸  막기 위해 box와 cpy의 규격을 일치시켜줘야함
		

		uint8_t *pData = (uint8_t *)ms.pData;
		for (unsigned int h = 0; h < boxHeight; h++)
		{
			memcpy(&pixels[h * boxWidth * 4],
			       &pData[h * ms.RowPitch],
			       boxWidth * sizeof(uint8_t) * 4);
		}

		m_context->Unmap(m_indexStagingTexture.Get(), NULL);

		// here_picking
		m_curPickingColor = Vector3((float)pixels[0] / 255, (float)pixels[1] / 255, (float)pixels[2] / 255);
		if (m_curPickingColor != m_prePickingColor)
		{
			m_prePickingColor = m_curPickingColor;
			std::cout << "[m_curPickingColor] : [" << m_curPickingColor.x << ", " << m_curPickingColor.y << ", " << m_curPickingColor.z << "]" << std::endl;

				if (m_curPickingColor == m_meshGroupSphere.m_indexColor)
				{
					m_meshGroupSphere.m_pickingFlag = true;
					m_meshGroupSphere.m_pickingDirtyFlag = true;
				    std::cout << "m_meshGroupSphere is picking [m_pickingFlag(ON)]" << std::endl;
				}
				else
				{
					m_meshGroupSphere.m_pickingFlag = false;
					m_meshGroupSphere.m_pickingDirtyFlag = true;
					std::cout << "m_meshGroupSphere is Not picking [m_pickingFlag(OFF)]" << std::endl;
				}
		}
		

	}
}

void ExampleApp::BuildFilters()
{

	m_filters.clear();

	// 해상도를 낮춰서 다운 샘플링
	auto copyFilter =
	    make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"Sampling",
	                             m_screenWidth, m_screenHeight);
	copyFilter->SetShaderResources({m_shaderResourceView});
	m_filters.push_back(copyFilter);

	for (int down = 2; down <= m_down; down *= 2)
	{
		auto downFilter = make_shared<ImageFilter>(
		    m_device, m_context, L"Sampling", L"Sampling", m_screenWidth / down,
		    m_screenHeight / down);

		if (down == 2)
		{
			downFilter->SetShaderResources({m_shaderResourceView});
		}
		else
		{
			downFilter->SetShaderResources(
			    {m_filters.back()->m_shaderResourceView});
		}

		downFilter->m_pixelConstData.threshold = 0.0f;
		downFilter->UpdateConstantBuffers(m_device, m_context);
		m_filters.push_back(downFilter);
	}

	for (int down = m_down; down >= 1; down /= 2)
	{
		for (int i = 0; i < m_repeat; i++)
		{
			auto &prevResource = m_filters.back()->m_shaderResourceView;
			m_filters.push_back(make_shared<ImageFilter>(
			    m_device, m_context, L"Sampling", L"BlurX",
			    m_screenWidth / down, m_screenHeight / down));
			m_filters.back()->SetShaderResources({prevResource});

			auto &prevResource2 = m_filters.back()->m_shaderResourceView;
			m_filters.push_back(make_shared<ImageFilter>(
			    m_device, m_context, L"Sampling", L"BlurY",
			    m_screenWidth / m_down, m_screenHeight / m_down));
			m_filters.back()->SetShaderResources({prevResource2});
		}

		if (down > 1)
		{
			auto upFilter = make_shared<ImageFilter>(
			    m_device, m_context, L"Sampling", L"Sampling",
			    m_screenWidth / down * 2, m_screenHeight / down * 2);
			upFilter->SetShaderResources(
			    {m_filters.back()->m_shaderResourceView});
			upFilter->m_pixelConstData.threshold = 0.0f;
			upFilter->UpdateConstantBuffers(m_device, m_context);
			m_filters.push_back(upFilter);
		}
	}

	auto combineFilter =
	    make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"Combine",
	                             m_screenWidth, m_screenHeight);
	combineFilter->SetShaderResources({copyFilter->m_shaderResourceView,
	                                   m_filters.back()->m_shaderResourceView});
	combineFilter->SetRenderTargets(
	    {this->m_renderTargetView}); // 렌더타겟 교체
	combineFilter->m_pixelConstData.strength = m_strength;
	combineFilter->UpdateConstantBuffers(m_device, m_context);
	m_filters.push_back(combineFilter);
}

void ExampleApp::OnResizeBegin()
{
	m_filters.clear();
}

void ExampleApp::OnResizeEnd()
{
	BuildFilters();
}

void ExampleApp::UpdateGUI()
{

	ImGui::Checkbox("Use FPV", &m_useFirstPersonView);
	ImGui::Checkbox("Use PostProc", &m_usePostProcessing);

	m_dirtyflag = 0;
	// m_dirtyflag +=
	//     ImGui::SliderFloat("Bloom Threshold", &m_threshold, 0.0f, 1.0f);
	// m_dirtyflag +=
	//     ImGui::SliderFloat("Bloom Strength", &m_strength, 0.0f, 3.0f);

	ImGui::Checkbox("Wireframe", &m_drawAsWire);
}

} // namespace hlab
