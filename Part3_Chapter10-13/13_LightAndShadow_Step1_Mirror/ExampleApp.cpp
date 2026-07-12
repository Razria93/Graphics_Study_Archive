#include "ExampleApp.h"

#include <DirectXCollision.h> // 구와 광선 충돌 계산에 사용
#include <directxtk/DDSTextureLoader.h>
#include <directxtk/SimpleMath.h>
#include <tuple>
#include <vector>

#include "GeometryGenerator.h"

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

ExampleApp::ExampleApp() : AppBase() {}

bool ExampleApp::Initialize()
{

	if (!AppBase::Initialize())
		return false;

	m_cubeMapping.Initialize(
	    m_device, L"../Assets/Textures/Cubemaps/HDRI/SampleEnvHDR.dds",
	    L"../Assets/Textures/Cubemaps/HDRI/SampleSpecularHDR.dds",
	    L"../Assets/Textures/Cubemaps/HDRI/SampleDiffuseHDR.dds",
	    L"../Assets/Textures/Cubemaps/HDRI/SampleBrdf.dds");

	// 조명 설정
	{
		m_light.position = Vector3(0.0f, 0.5f, 1.7f);
		m_light.radiance = Vector3(5.0f);
		m_light.fallOffEnd = 20.0f;
	}

	// 거울
	{
		auto mesh = GeometryGenerator::MakeSquare(0.48f);
		m_mirror =
		    make_shared<BasicMeshGroup>(m_device, m_context, vector{mesh});
		m_mirror->m_basicPixelConstData.material.albedo = Vector3(0.3f);
		m_mirror->m_basicPixelConstData.material.emission = Vector3(0.0f);
		m_mirror->m_basicPixelConstData.material.metallic = 0.7f;
		m_mirror->m_basicPixelConstData.material.roughness = 0.2f;

		m_mirror->UpdateModelWorld(
		    Matrix::CreateScale(1.0f, 1.5f, 1.0f) *
		    Matrix::CreateRotationY(3.141592f * 0.5f) *
		    Matrix::CreateTranslation(0.5f, 0.25f, 2.0f));

		// HERE : SimpleMath::Plane
		// Plane 위의 점(point) 와 Plane의 법선 벡터(vector) 를 넣어주면 Plane 정의가능
		// Y축 90도 회전했는데 DX에서는 +Y축에서 내려다봤을 때 회전의 양의 방향은 CW라서 시계방향 90회전임
		// 여기 법선방향 및 반사에 대한 질문있음 : 법선의 방향이 맞는지와 법선의 의미
		m_mirrorPlane = SimpleMath::Plane(Vector3(0.5f, 0.25f, 2.0f),
		                                  Vector3(-1.0f, 0.0f, 0.0f));
	}

	// 바닥
	{
		auto mesh = GeometryGenerator::MakeSquare(2.0);
		mesh.albedoTextureFilename =
		    "../Assets/Textures/blender_uv_grid_2k.png";
		m_ground =
		    make_shared<BasicMeshGroup>(m_device, m_context, vector{mesh});
		m_ground->m_basicPixelConstData.material.albedo = Vector3(0.2f);
		m_ground->m_basicPixelConstData.material.emission = Vector3(0.0f);
		m_ground->m_basicPixelConstData.material.metallic = 0.2f;
		m_ground->m_basicPixelConstData.material.roughness = 0.8f;

		m_ground->UpdateModelWorld(
		    Matrix::CreateRotationX(3.141592f * 0.5f) *
		    Matrix::CreateTranslation(0.0f, -0.5f, 2.0f));

		m_basicList.push_back(m_ground); // 리스트에 등록
	}

	// Main Object
	{
		// auto meshes = GeometryGenerator::ReadFromFile(
		//     "../Assets/Models/DamagedHelmet/", "DamagedHelmet.gltf");

		// auto meshes = GeometryGenerator::ReadFromFile(
		//     "../Assets/Models/medieval_vagrant_knights/", "scene.gltf");

		string path = "../Assets/Characters/armored-female-future-soldier/";
		auto meshes = GeometryGenerator::ReadFromFile(path, "angel_armor.fbx");
		meshes[0].albedoTextureFilename = path + "/angel_armor_albedo.jpg";
		meshes[0].emissiveTextureFilename = path + "/angel_armor_e.jpg";
		meshes[0].metallicTextureFilename = path + "/angel_armor_metalness.jpg";
		meshes[0].normalTextureFilename = path + "/angel_armor_normal.jpg";
		meshes[0].roughnessTextureFilename = path + "/angel_armor_roughness.jpg";

		Vector3 center(0.0f, 0.0f, 2.0f);
		m_mainObj = make_shared<BasicMeshGroup>(m_device, m_context, meshes);
		m_mainObj->m_basicPixelConstData.invertNormalMapY =
		    false; // GLTF는 true로
		m_mainObj->m_irradianceSRV = m_cubeMapping.m_irradianceSRV;
		m_mainObj->m_specularSRV = m_cubeMapping.m_specularSRV;
		m_mainObj->m_brdfSRV = m_cubeMapping.m_brdfSRV;
		m_mainObj->UpdateModelWorld(Matrix::CreateTranslation(center));
		m_mainObj->UpdateConstantBuffers(m_device, m_context);

		m_basicList.push_back(m_mainObj); // 리스트에 등록

		// 동일한 크기와 위치에 BoundingSphere 만들기
		m_mainBoundingSphere = BoundingSphere(center, 0.4f);
	}

	// 조명 위치 표시
	{
		MeshData sphere = GeometryGenerator::MakeSphere(0.01f, 10, 10);
		m_lightSphere =
		    make_shared<BasicMeshGroup>(m_device, m_context, vector{sphere});
		m_lightSphere->UpdateModelWorld(
		    Matrix::CreateTranslation(m_light.position));
		m_lightSphere->m_basicPixelConstData.material.albedo = Vector3(0.0f);
		m_lightSphere->m_basicPixelConstData.material.emission =
		    Vector3(1.0f, 1.0f, 0.0f);
		m_lightSphere->UpdateConstantBuffers(m_device, m_context);

		m_basicList.push_back(m_lightSphere); // 리스트에 등록
	}

	// 커서 표시 (Main sphere와의 충돌이 감지되면 월드 공간에 작게 그려지는 구)
	{
		MeshData sphere = GeometryGenerator::MakeSphere(0.01f, 10, 10);
		m_cursorSphere.Initialize(m_device, m_context, vector{sphere});
		m_cursorSphere.UpdateModelWorld(
		    Matrix::CreateTranslation(Vector3(0.0f)));
		m_cursorSphere.m_basicPixelConstData.material.albedo = Vector3(0.0f);
		m_cursorSphere.m_basicPixelConstData.material.emission =
		    Vector3(0.0f, 1.0f, 0.0f);
		m_cursorSphere.UpdateConstantBuffers(m_device, m_context);
	}

	return true;
}

void ExampleApp::Update(float dt)
{

	// 카메라의 이동
	if (m_useFirstPersonView)
	{
		if (m_keyPressed[87]) // W키
			m_camera.MoveForward(dt);
		if (m_keyPressed[83]) // S키
			m_camera.MoveForward(-dt);
		if (m_keyPressed[68]) // D키
			m_camera.MoveRight(dt);
		if (m_keyPressed[65]) // A키
			m_camera.MoveRight(-dt);
		if (m_keyPressed[81]) // Q키
			m_camera.MoveUp(dt);
		if (m_keyPressed[69]) // E키
			m_camera.MoveUp(-dt);
	}

	// HERE : 반사 행렬 추가
	// SimpleMath에서 제공하는 Matrix::CreateReflection 사용
	// 현실세상과 거울세상을 렌더링을 2번해야함
	// VertexBuffer, IndexBuffer는 공유

	// 첫번째 방법은 모델행렬에 ReflectionRow를 곱해줌
	// modelRow * reflectionRow * viewProj
	// 이때 쪼갠다면 reflectionRow는 viewProj와 묶이는게 좋음.
	//
	// 해당 방법이 좋은 첫번째 이유는 모든 물체가 동일하게 적용받기 때문임.
	// 오른쪽에 미리 곱할 경우 모든 모델마다 곱하지 않아도 됨
	// 두번째 이유는 Render에서 매개변수로 CB를 전달해줄 수 있게 구현함
	Vector3 eyeWorld = m_camera.GetEyePos();
	Matrix reflectionRow = Matrix::CreateReflection(m_mirrorPlane);
	Matrix viewRow = m_camera.GetViewRow();
	Matrix projRow = m_camera.GetProjRow();

	AppBase::UpdateEyeViewProjBuffers(eyeWorld, viewRow, projRow,
	                                  reflectionRow);

	// 큐브 매핑 Constant Buffer 업데이트
	m_cubeMapping.UpdateViewProjConstBuffer(m_device, m_context, viewRow,
	                                        projRow, reflectionRow);

	// mainSphere의 회전 계산용
	static float prevRatio = 0.0f;
	static Vector3 prevPos(0.0f);
	static Vector3 prevVector(0.0f);
	Quaternion q =
	    Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), 0.0f);
	Vector3 dragTranslation(0.0f);

	// 마우스 왼쪽 버튼으로 회전
	if (m_leftButton)
	{

		// ViewFrustum에서 가까운 면 위의 커서 위치
		// ViewFrustum에서 먼 면 위의 커서 위치
		Vector3 cursorNdcNear = Vector3(m_cursorNdcX, m_cursorNdcY, 0.0f);
		Vector3 cursorNdcFar = Vector3(m_cursorNdcX, m_cursorNdcY, 1.0f);

		// NDC 커서 위치를 월드 좌표계로 역변환 해주는 행렬
		Matrix inverseProjView = (viewRow * projRow).Invert();

		// ViewFrustum 안에서 PickingRay의 방향 구하기
		Vector3 cursorWorldNear =
		    Vector3::Transform(cursorNdcNear, inverseProjView);
		Vector3 cursorWorldFar =
		    Vector3::Transform(cursorNdcFar, inverseProjView);
		Vector3 dir = cursorWorldFar - cursorWorldNear;
		dir.Normalize();

		// 광선을 만들고 충돌 감지
		SimpleMath::Ray curRay = SimpleMath::Ray(cursorWorldNear, dir);
		float dist = 0.0f;
		m_selected = curRay.Intersects(m_mainBoundingSphere, dist);

		if (m_selected)
		{

			Vector3 pickPoint = cursorWorldNear + dist * dir;

			// 충돌 지점에 작은 구 그리기
			m_cursorSphere.UpdateModelWorld(
			    Matrix::CreateTranslation(pickPoint));
			m_cursorSphere.UpdateConstantBuffers(m_device, m_context);

			// mainSphere를 어떻게 회전시킬지 결정
			if (m_dragStartFlag)
			{ // 드래그를 시작하는 경우
				m_dragStartFlag = false;
				prevVector = pickPoint - m_mainBoundingSphere.Center;
				prevVector.Normalize();
			}
			else
			{
				Vector3 currentVector = pickPoint - m_mainBoundingSphere.Center;
				currentVector.Normalize();
				float theta = acos(prevVector.Dot(currentVector));
				if (theta > 3.141592f / 180.0f * 3.0f)
				{
					Vector3 axis = prevVector.Cross(currentVector);
					axis.Normalize();
					q = SimpleMath::Quaternion::CreateFromAxisAngle(axis,
					                                                theta);
					prevVector = currentVector;
				}
			}
		}
	}

	// 마우스 오른쪽 버튼으로 이동
	if (m_rightButton)
	{

		// ViewFrustum에서 가까운 면 위의 커서 위치
		// ViewFrustum에서 먼 면 위의 커서 위치
		Vector3 cursorNdcNear = Vector3(m_cursorNdcX, m_cursorNdcY, 0.0f);
		Vector3 cursorNdcFar = Vector3(m_cursorNdcX, m_cursorNdcY, 1.0f);

		// NDC 커서 위치를 월드 좌표계로 역변환 해주는 행렬
		Matrix inverseProjView = (viewRow * projRow).Invert();

		// ViewFrustum 안에서 PickingRay의 방향 구하기
		Vector3 cursorWorldNear =
		    Vector3::Transform(cursorNdcNear, inverseProjView);
		Vector3 cursorWorldFar =
		    Vector3::Transform(cursorNdcFar, inverseProjView);
		Vector3 dir = cursorWorldFar - cursorWorldNear;
		dir.Normalize();

		// 광선을 만들고 충돌 감지
		SimpleMath::Ray curRay = SimpleMath::Ray(cursorWorldNear, dir);
		float dist = 0.0f;
		m_selected = curRay.Intersects(m_mainBoundingSphere, dist);

		if (m_selected)
		{

			Vector3 pickPoint = cursorWorldNear + dist * dir;

			// 충돌 지점에 작은 구 그리기
			m_cursorSphere.UpdateModelWorld(
			    Matrix::CreateTranslation(pickPoint));
			m_cursorSphere.UpdateConstantBuffers(m_device, m_context);

			// mainSphere를 어떻게 회전시킬지 결정
			if (m_dragStartFlag)
			{ // 드래그를 시작하는 경우
				m_dragStartFlag = false;
				prevRatio = dist / (cursorWorldFar - cursorWorldNear).Length();
				prevPos = pickPoint;
			}
			else
			{
				Vector3 newPos = cursorWorldNear +
				                 prevRatio * (cursorWorldFar - cursorWorldNear);

				// 마우스가 조금이라도 움직였을 경우에만 회전시키기
				if ((newPos - prevPos).Length() > 1e-3)
				{
					dragTranslation = newPos - prevPos;
					prevPos = newPos;
				}
			}
		}
	}

	// 거울은 따로 처리
	m_mirror->m_basicPixelConstData.lights[1] = m_light;
	m_mirror->UpdateConstantBuffers(m_device, m_context);

	// 조명의 위치 반영
	m_lightSphere->UpdateModelWorld(
	    Matrix::CreateTranslation(m_light.position));

	// 마우스 이동/회전 반영
	Vector3 translation = m_mainObj->m_modelWorldRow.Translation();
	m_mainObj->m_modelWorldRow.Translation(Vector3(0.0f));
	m_mainObj->UpdateModelWorld(
	    m_mainObj->m_modelWorldRow * Matrix::CreateFromQuaternion(q) *
	    Matrix::CreateTranslation(dragTranslation + translation));
	m_mainBoundingSphere.Center = m_mainObj->m_modelWorldRow.Translation();

	// 거울 외의 물체들은 for문으로 처리
	for (auto& i : m_basicList)
	{
		// 조명 설정 (쉐이더의 Light 배열에서 인덱스 1이 포인트 라이트)
		i->m_basicPixelConstData.lights[1] = m_light;
		i->UpdateConstantBuffers(m_device, m_context);
	}
}

void ExampleApp::Render()
{

	SetViewport();

	const float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};

	// renderTargetView가 vector임
	// 이는RTV를 여러개 그리게 될 수도 있다는 것
	// m_float는 PBR에서 사용하기 위한 텍스쳐
	vector<ID3D11RenderTargetView*> renderTargetViews = {m_floatRTV.Get()};
	for (size_t i = 0; i < renderTargetViews.size(); i++)
	{
		m_context->ClearRenderTargetView(renderTargetViews[i], clearColor);
	}

	// OMSetRenderTargets
	// RenderTarget을 여러개 쓴다고 해서 여러개 Set하는게 아닌 덮어쓰고를 반복하는 것
	m_context->OMSetRenderTargets(UINT(renderTargetViews.size()),
	                              renderTargetViews.data(),
	                              m_depthStencilView.Get());

	// 해당 과정은 RenderDoc으로 확인하면서 할 수 있음
	// 근데 기능을 정확히 몰라서 이에 대해서는 엔진 구현하면서 다시한번 복습
	// DepthStencil 표시하는 Window와 Overlay를 확인해보기

	/* 거울 1. 원래 대로 한 번 그림 */

	// 기본 BlendState 사용 (초기화)
	m_context->OMSetBlendState(NULL, NULL, 0xffffffff);

	// DepthStencil Clear
	m_context->ClearDepthStencilView(m_depthStencilView.Get(),
	                                 D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, // Depth, Stencil 모두 초기화
	                                 1.0f, 0);                                // 1.0은 DepthBuffer 초기화값, 0.0은 StencilBuffer 초기화값

	m_context->OMSetDepthStencilState(m_drawDSS.Get(), 1);

	m_context->RSSetState(m_drawAsWire ? m_wireRS.Get() : m_solidRS.Get());

	// 거울 외의 물체들 렌더링
	for (auto& i : m_basicList)
	{
		i->Render(m_context, AppBase::m_eyeViewProjConstBuffer, m_useEnv);
	}

	// 거울은 빼고 그립니다.
	// m_mirror->Render(m_context, AppBase::m_eyeViewProjConstBuffer, m_useEnv);

	// 커서 렌더링
	if ((m_leftButton || m_rightButton) && m_selected)
		m_cursorSphere.Render(m_context, AppBase::m_eyeViewProjConstBuffer, false);

	// 미러 된걸로 그릴지 아닐지
	if (m_useEnv)
	{
		m_cubeMapping.Render(m_context, false);
	}

	/* 거울 2. 거울 위치만 StencilBuffer에 1로 표기 */

	// STENCIL만 클리어
	// 거울을 가리는 물체가 있을 수도 있어서 Depth는 CLEAR 안함
	// 앞 단계의 m_drawDSS에서 모두 KEEP을 사용했기 때문에
	// Stencil도 CLEAR 불필요
	m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_STENCIL, 1.0f, 0);

	// 두 번째 UINT StencilRef = 1 사용
	// ClearDepthStencilView(..., 0)에서는 다른 숫자 0 사용
	m_context->OMSetDepthStencilState(m_maskDSS.Get(), 1);

	// 거울을 그릴 때 색은 필요 없기 때문에 간단한 PS 사용 가능
	// 스텐실 버퍼에만 렌더링할때는 간단한 픽셀쉐이더를 사용하는 방법도 있음
	m_mirror->Render(m_context, AppBase::m_eyeViewProjConstBuffer, m_useEnv);

	/* 거울 3. 거울 위치에 반사된 물체들을 렌더링 */
	m_context->ClearDepthStencilView(m_depthStencilView.Get(),
	                                 D3D11_CLEAR_DEPTH, // Depth, Stencil 모두 초기화
	                                 1.0f, 0);          // 1.0은 DepthBuffer 초기화값, 0.0은 Stencil 초기화값

	m_context->OMSetDepthStencilState(m_drawMaskedDSS.Get(), 1);

	// 반사되면 삼각형 정점들의 순서(Winding)가 반대로 -> 반시계
	m_context->RSSetState(m_drawAsWire ? m_wireCCWRS.Get() : m_solidCCWRS.Get());

	// 반사된 위치에 그려야 함
	// TODO: AppBase::m_mirrorEyeViewProjConstBuffer 사용
	// 행렬의 포인터만 바꿔서 그리기! CPU / GPU에서 데이터를 넘길 필요가 없음
	for (auto& i : m_basicList)
	{
		i->Render(m_context, AppBase::m_mirrorEyeViewProjConstBuffer, m_useEnv);
	}

	// // 환경맵도 뒤집어서 그리기
	if (m_useEnv)
	{
		m_cubeMapping.Render(m_context, true);
	}

	/* 거울 4. 거울 자체의 재질을 "Blend"로 그림 */

	// TODO: m_context->OMSetBlendState(..., ..., 0xffffffff);
	const float blendFactor[4] = {m_mirrorAlpha, m_mirrorAlpha, m_mirrorAlpha, 1.0f};
	m_context->OMSetBlendState(m_mirrorBS.Get(), blendFactor, 0xffffffff);

	// TODO: m_context->RSSetState(...); // 다시 시계 방향
	m_context->RSSetState(m_drawAsWire ? m_wireRS.Get() : m_solidRS.Get());

	// TODO: 거울 그리기
	m_mirror->Render(m_context, AppBase::m_eyeViewProjConstBuffer, m_useEnv);

	// 후처리는 Blend X
	m_context->OMSetBlendState(NULL, NULL, 0xffffffff);

	/* 이후 원래 하던 후처리 */

	m_context->ResolveSubresource(m_resolvedBuffer.Get(), 0,
	                              m_floatBuffer.Get(), 0,
	                              DXGI_FORMAT_R16G16B16A16_FLOAT);

	m_postProcess.Render(m_context);
}

void ExampleApp::UpdateGUI()
{

	ImGui::SetNextItemOpen(false, ImGuiCond_Once);
	if (ImGui::TreeNode("General"))
	{
		ImGui::Checkbox("Use FPV", &m_useFirstPersonView);
		ImGui::Checkbox("Wireframe", &m_drawAsWire);
		if (ImGui::Checkbox("MSAA ON", &m_useMSAA))
		{
			CreateBuffers();
		}
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Env Map"))
	{
		ImGui::Checkbox("Use Env", &m_useEnv);
		int flag = 0;
		flag += ImGui::RadioButton(
		    "Env", &m_cubeMapping.m_pixelConstData.textureToDraw, 0);
		ImGui::SameLine();
		flag += ImGui::RadioButton(
		    "Specular", &m_cubeMapping.m_pixelConstData.textureToDraw, 1);
		ImGui::SameLine();
		flag += ImGui::RadioButton(
		    "Irradiance", &m_cubeMapping.m_pixelConstData.textureToDraw, 2);
		flag += ImGui::SliderFloat(
		    "Mip Level", &m_cubeMapping.m_pixelConstData.mipLevel, 0.0f, 10.0f);
		if (flag)
		{
			m_cubeMapping.UpdatePixelConstBuffer(m_device, m_context);
		}
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(false, ImGuiCond_Once);
	if (ImGui::TreeNode("Post Processing"))
	{
		int flag = 0;
		flag += ImGui::SliderFloat(
		    "Bloom Strength",
		    &m_postProcess.m_combineFilter.m_constData.strength, 0.0f, 1.0f);
		flag += ImGui::SliderFloat(
		    "Exposure", &m_postProcess.m_combineFilter.m_constData.option1,
		    0.0f, 10.0f);
		flag += ImGui::SliderFloat(
		    "Gamma", &m_postProcess.m_combineFilter.m_constData.option2, 0.1f,
		    5.0f);
		// 편의상 사용자 입력이 인식되면 바로 GPU 버퍼를 업데이트
		if (flag)
		{
			m_postProcess.m_combineFilter.UpdateConstantBuffers(m_device,
			                                                    m_context);
		}
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Mirror"))
	{
		int flag = 0;
		flag += ImGui::SliderFloat("Alpha", &m_mirrorAlpha, 0.0f, 1.0f);
		flag += ImGui::SliderFloat(
		    "Metallic", &m_mirror->m_basicPixelConstData.material.metallic,
		    0.0f, 1.0f);
		flag += ImGui::SliderFloat(
		    "Roughness", &m_mirror->m_basicPixelConstData.material.roughness,
		    0.0f, 1.0f);
		if (flag)
		{
			m_mirror->UpdateConstantBuffers(m_device, m_context);
		}
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Point Light"))
	{
		ImGui::SliderFloat3("Position", &m_light.position.x, -5.0f, 5.0f);
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Material"))
	{

		int flag = 0;

		flag += ImGui::SliderFloat(
		    "Metallic", &m_ground->m_basicPixelConstData.material.metallic,
		    0.0f, 1.0f);
		flag += ImGui::SliderFloat(
		    "Roughness", &m_ground->m_basicPixelConstData.material.roughness,
		    0.0f, 1.0f);
		flag += ImGui::CheckboxFlags(
		    "AlbedoTexture", &m_mainObj->m_basicPixelConstData.useAlbedoMap, 1);
		flag += ImGui::CheckboxFlags(
		    "EmissiveTexture", &m_mainObj->m_basicPixelConstData.useEmissiveMap,
		    1);
		flag += ImGui::CheckboxFlags(
		    "Use NormalMapping", &m_mainObj->m_basicPixelConstData.useNormalMap,
		    1);
		flag += ImGui::CheckboxFlags(
		    "Use AO", &m_mainObj->m_basicPixelConstData.useAOMap, 1);
		flag += ImGui::CheckboxFlags(
		    "Use HeightMapping",
		    &m_mainObj->m_basicVertexConstData.useHeightMap, 1);
		flag += ImGui::SliderFloat(
		    "HeightScale", &m_mainObj->m_basicVertexConstData.heightScale, 0.0f,
		    0.1f);
		flag += ImGui::CheckboxFlags(
		    "Use MetallicMap", &m_mainObj->m_basicPixelConstData.useMetallicMap,
		    1);
		flag += ImGui::CheckboxFlags(
		    "Use RoughnessMap",
		    &m_mainObj->m_basicPixelConstData.useRoughnessMap, 1);
		flag += ImGui::Checkbox("Draw Normals", &m_mainObj->m_drawNormals);

		if (flag)
		{
			// GUI 입력이 있을 때만 할 일들 추가
		}

		ImGui::TreePop();
	}
}
} // namespace hlab
