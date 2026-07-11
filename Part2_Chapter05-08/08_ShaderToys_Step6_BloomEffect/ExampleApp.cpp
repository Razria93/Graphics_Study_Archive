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

	m_cubeMapping.Initialize(m_device, L"./CubemapTextures/Stonewall_diffuseIBL.dds", L"./CubemapTextures/Stonewall_specularIBL.dds");

	MeshData sphere = GeometryGenerator::MakeSphere(0.3f, 100, 100);
	sphere.textureFilename = "ojwD8.jpg";
	m_meshGroupSphere.Initialize(m_device, {sphere});

	// 해당 객체의 렌더링된 텍스쳐에 접근할 수 있게 객체마다 자체적으로 가지고 있으며,
	// 해당 예제에서 접근하기 용이하게 멤버 포인터 변수로 뺴두는 작업
	// SRV는 대상의 렌더링 결과를 "읽기"할 수 있는 View
	m_meshGroupSphere.m_diffuseResView = m_cubeMapping.m_diffuseResView;
	m_meshGroupSphere.m_specularResView = m_cubeMapping.m_specularResView;

	m_meshGroupCharacter.Initialize(m_device, "f3d-data/zelda/", "zeldaPosed001.fbx");
	m_meshGroupCharacter.m_diffuseResView = m_cubeMapping.m_diffuseResView;
	m_meshGroupCharacter.m_specularResView = m_cubeMapping.m_specularResView;

	BuildFilters();

	return true;
}

void ExampleApp::Update(float dt)
{

	using namespace DirectX;

	auto &visibleMeshGroup = m_visibleMeshIndex == 0 ? m_meshGroupSphere : m_meshGroupCharacter;

	auto modelRow = Matrix::CreateScale(m_modelScaling) * Matrix::CreateRotationY(m_modelRotation.y) * Matrix::CreateRotationX(m_modelRotation.x) * Matrix::CreateRotationZ(m_modelRotation.z) *
	                Matrix::CreateTranslation(m_modelTranslation);

	auto invTransposeRow = modelRow;
	invTransposeRow.Translation(Vector3(0.0f));
	invTransposeRow = invTransposeRow.Invert().Transpose();

	auto viewRow = Matrix::CreateRotationY(m_viewRot.y) * Matrix::CreateRotationX(m_viewRot.x) * Matrix::CreateTranslation(0.0f, 0.0f, 2.0f);

	const float aspect = AppBase::GetAspectRatio();
	Matrix projRow = m_usePerspectiveProjection ? XMMatrixPerspectiveFovLH(XMConvertToRadians(m_projFovAngleY), aspect, m_nearZ, m_farZ)
	                                            : XMMatrixOrthographicOffCenterLH(-aspect, aspect, -1.0f, 1.0f, m_nearZ, m_farZ);

	auto eyeWorld = Vector3::Transform(Vector3(0.0f), viewRow.Invert());

	// MeshGroup의 ConstantBuffers 업데이트

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		// 다른 조명 끄기
		if (i != m_lightType)
		{
			visibleMeshGroup.m_basicPixelConstantData.lights[i].strength *= 0.0f;
		}
		else
		{
			visibleMeshGroup.m_basicPixelConstantData.lights[i] = m_lightFromGUI;
		}
	}

	visibleMeshGroup.m_basicVertexConstantData.model = modelRow.Transpose();
	visibleMeshGroup.m_basicVertexConstantData.view = viewRow.Transpose();
	visibleMeshGroup.m_basicVertexConstantData.projection = projRow.Transpose();

	visibleMeshGroup.m_basicPixelConstantData.eyeWorld = eyeWorld;

	visibleMeshGroup.m_basicPixelConstantData.material.diffuse = Vector3(m_materialDiffuse);
	visibleMeshGroup.m_basicPixelConstantData.material.specular = Vector3(m_materialSpecular);
	visibleMeshGroup.UpdateConstantBuffers(m_device, m_context);

	// 큐브 매핑 Constant Buffer 업데이트
	m_cubeMapping.UpdateConstantBuffers(m_device, m_context, (Matrix::CreateRotationY(m_viewRot.y) * Matrix::CreateRotationX(m_viewRot.x)).Transpose(), projRow.Transpose());

	// 각 필요한 부분의 컨스턴트 버퍼에 저장해주고 있는데,
	// 차라리 변화가 생길떄마다 예제 내의 변수를 변화시키고 업데이트 시키는게 나을듯
	if (m_dirtyflag)
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

	// CPU에서 GPU쪽 설정값을 Setting하는 Context 객체를 넘겨주며 초기화함
	// RTV는 여기서 설정한 RTV에함
	float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
	m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// 백버퍼 RTV
	m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
	m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);

	if (m_drawAsWire)
	{
		m_context->RSSetState(m_wireRasterizerSate.Get());
	}
	else
	{
		m_context->RSSetState(m_rasterizerSate.Get());
	}

	// 큐브매핑
	m_cubeMapping.Render(m_context);

	// 물체들
	if (m_visibleMeshIndex == 0)
	{
		m_meshGroupSphere.Render(m_context);
	}
	else
	{
		m_meshGroupCharacter.Render(m_context);
	}

	// 후처리 필터 시작하기 전에 back buffer에 렌더링 된 결과를 Texture2D로 복사
	ComPtr<ID3D11Texture2D> backBuffer;
	m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	m_context->CopyResource(m_tempTexture.Get(), backBuffer.Get());

	// 후처리 필터
	// Filter들은 위의 Mesh들과는 다르게 별도의 RTV를 가지고 있음
	// 현재 얘네 초기화 안된거 같은데
	for (auto &f : m_filters)
	{
		f->Render(m_context);
	}

	// RTV BackBuffer로 수정 (ImGui)
	m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
	m_context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
}

void ExampleApp::BuildFilters()
{
	m_filters.clear();

	// 해상도를 조절하면 업/다운 샘플링도 가능

	// 자기 자신을 복사하는 필터
	auto copyFilter = std::make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"Sampling", this->m_screenWidth, this->m_screenHeight);
	copyFilter->SetShaderResources({this->m_shaderResourceView});
	m_filters.push_back(copyFilter);
	// std::vector<ComPtr<ID3D11ShaderResourceView>> srvs;
	// srvs.push_back(this->m_shaderResourceView);
	// copyFilter->SetShaderResources(srvs);


	// 일정이상 횟수를 올리면 터지거나 릴리즈에서는 안정적이지 못함

	bool reverseFlag = false;
	bool completeFlag = false;
	int curlevel_Sampling = 0;
	int maxlevel_Sampling = 5;
	int width = m_screenWidth;
	int height = m_screenHeight;

	while (completeFlag == false)
	{
		if (!reverseFlag)
		{
			width /= 2;
			height /= 2;
			curlevel_Sampling++;
		}
		else
		{
			width *= 2;
			height *= 2;
			curlevel_Sampling--;
		}

		std::cout << "reverseFlag : " << reverseFlag << " / completeFlag : " << completeFlag << std::endl;
		std::cout << "curlevel_Sampling : " << curlevel_Sampling << " / maxlevel_Sampling : " << maxlevel_Sampling << std::endl;
		std::cout << "width : " << width << " / height : " << height << std::endl;

		// 일정 수치 이상의 색상들만 남기는 필터
		auto thresholdFilter = std::make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"Threshold", width, height);
		thresholdFilter->SetShaderResources({m_filters.back()->m_shaderResourceView});
		m_filters.push_back(thresholdFilter);

		if (!reverseFlag && (maxlevel_Sampling - curlevel_Sampling <= 0))
		{
			reverseFlag = true;

			std::cout << "reverse" << std::endl;
		}

		if (reverseFlag)
		{
			// 가우시안효과를 X방향에 주는 필터
			auto blurXFilter = std::make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"BlurX", width, height);
			blurXFilter->SetShaderResources({m_filters.back()->m_shaderResourceView});
			m_filters.push_back(blurXFilter);

			// 가우시안효과를 Y방향에 주는 필터
			auto blurYFilter = std::make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"BlurY", width, height);
			blurYFilter->SetShaderResources({m_filters.back()->m_shaderResourceView});
			m_filters.push_back(blurYFilter);

			std::cout << "blur" << std::endl;
		}

		if (reverseFlag && (curlevel_Sampling <= 0))
		{
			completeFlag = true;

			std::cout << "complete" << std::endl;
		}
	}

	// SRV에 들어온 texture2개의 색상을 합쳐주는 필터
	auto combineFilter = std::make_shared<ImageFilter>(m_device, m_context, L"Sampling", L"Combine", this->m_screenWidth, this->m_screenHeight);
	combineFilter->SetShaderResources({m_filters.back()->m_shaderResourceView, this->m_shaderResourceView});
	combineFilter->SetRenderTargets({this->m_renderTargetView});
	m_filters.push_back(combineFilter);
}

void ExampleApp::UpdateGUI()
{

	auto &meshGroup = m_visibleMeshIndex == 0 ? m_meshGroupSphere : m_meshGroupCharacter;

	if (ImGui::RadioButton("Sphere", m_visibleMeshIndex == 0))
	{
		m_visibleMeshIndex = 0;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Character", m_visibleMeshIndex == 1))
	{
		m_visibleMeshIndex = 1;
	}

	m_dirtyflag += ImGui::SliderFloat("Bloom Threshold", &m_threshold, 0.0f, 1.0f);
	m_dirtyflag += ImGui::SliderFloat("Bloom Strength", &m_strength, 0.0f, 3.0f);

	ImGui::Checkbox("Use Texture", &meshGroup.m_basicPixelConstantData.useTexture);
	ImGui::Checkbox("Wireframe", &m_drawAsWire);
	ImGui::Checkbox("Draw Normals", &meshGroup.m_drawNormals);
	if (ImGui::SliderFloat("Normal scale", &meshGroup.m_normalVertexConstantData.scale, 0.0f, 1.0f))
	{
		meshGroup.m_drawNormalsDirtyFlag = true;
	}

	ImGui::SliderFloat3("m_modelRotation", &m_modelRotation.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("m_viewRot", &m_viewRot.x, -3.14f, 3.14f);
	ImGui::SliderFloat3("Material FresnelR0", &meshGroup.m_basicPixelConstantData.material.fresnelR0.x, 0.0f, 1.0f);

	ImGui::SliderFloat("Material Diffuse", &m_materialDiffuse, 0.0f, 3.0f);
	ImGui::SliderFloat("Material Specular", &m_materialSpecular, 0.0f, 3.0f);
	ImGui::SliderFloat("Material Shininess", &meshGroup.m_basicPixelConstantData.material.shininess, 0.01f, 20.0f);
}

} // namespace hlab
