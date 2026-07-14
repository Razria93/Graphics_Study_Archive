#include "AppBase.h"

#include <algorithm>

#include "D3D11Utils.h"

// imgui_impl_win32.cpp에 정의된 메시지 처리 함수에 대한 전방 선언
// Vcpkg를 통해 IMGUI를 사용할 경우 빨간줄로 경고가 뜰 수 있음
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

namespace hlab
{

using namespace std;

AppBase* g_appBase = nullptr;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return g_appBase->MsgProc(hWnd, msg, wParam, lParam);
}

AppBase::AppBase()
    : m_screenWidth(1280), m_screenHeight(720), m_mainWindow(0),
      m_screenViewport(D3D11_VIEWPORT())
{

	g_appBase = this;

	m_camera.SetAspectRatio(this->GetAspectRatio());
}

AppBase::~AppBase()
{
	g_appBase = nullptr;

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(m_mainWindow);
	// UnregisterClass(wc.lpszClassName, wc.hInstance);//생략

	// COMPtr에서 알아서 release
	// ComPtr automatically maintains a reference count for the underlying
	// interface pointer and releases the interface when the reference count
	// goes to zero.
	// https:learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170
	// 예시: m_d3dDevice.Reset(); 생략
}

float AppBase::GetAspectRatio() const
{
	return float(m_screenWidth - m_guiWidth) / m_screenHeight;
}

int AppBase::Run()
{

	// Main message loop
	MSG msg = {0};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();

			ImGui::NewFrame();
			ImGui::Begin("Scene Control");

			// ImGui가 측정해주는 Framerate 출력
			ImGui::Text("Average %.3f ms/frame (%.1f FPS)",
			            1000.0f / ImGui::GetIO().Framerate,
			            ImGui::GetIO().Framerate);

			UpdateGUI(); // 추가적으로 사용할 GUI

			m_guiWidth = 0;

			ImGui::End();
			ImGui::Render();

			Update(ImGui::GetIO().DeltaTime);

			Render(); // <- 중요: 우리가 구현한 렌더링

			// GUI 렌더링
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			// GUI 렌더링 후에 Present() 호출
			m_swapChain->Present(1, 0);
		}
	}

	return 0;
}

bool AppBase::Initialize()
{

	if (!InitMainWindow())
		return false;

	if (!InitDirect3D())
		return false;

	if (!InitGUI())
		return false;

	// 콘솔창이 렌더링 창을 덮는 것을 방지
	SetForegroundWindow(m_mainWindow);

	return true;
}

void AppBase::OnMouseMove(int mouseX, int mouseY)
{

	// 마우스 커서의 위치를 NDC로 변환
	// 마우스 커서는 좌측 상단 (0, 0), 우측 하단(width-1, height-1)
	// NDC는 좌측 하단이 (-1, -1), 우측 상단(1, 1)
	m_cursorNdcX = mouseX * 2.0f / m_screenWidth - 1.0f;
	m_cursorNdcY = -mouseY * 2.0f / m_screenHeight + 1.0f;

	// 커서가 화면 밖으로 나갔을 경우 범위 조절
	// 게임에서는 클램프를 안할 수도 있습니다.
	m_cursorNdcX = std::clamp(m_cursorNdcX, -1.0f, 1.0f);
	m_cursorNdcY = std::clamp(m_cursorNdcY, -1.0f, 1.0f);

	// 카메라 시점 회전
	if (m_useFirstPersonView)
	{
		m_camera.UpdateMouse(m_cursorNdcX, m_cursorNdcY);
	}
}

LRESULT AppBase::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		// 화면 해상도가 바뀌면 SwapChain을 다시 생성
		if (m_swapChain)
		{

			m_screenWidth = int(LOWORD(lParam));
			m_screenHeight = int(HIWORD(lParam));
			m_guiWidth = 0;

			m_backBufferRTV.Reset();
			m_swapChain->ResizeBuffers(0,                    // 현재 개수 유지
			                           (UINT)LOWORD(lParam), // 해상도 변경
			                           (UINT)HIWORD(lParam),
			                           DXGI_FORMAT_UNKNOWN, // 현재 포맷 유지
			                           0);
			CreateBuffers();

			SetViewport();
			m_camera.SetAspectRatio(this->GetAspectRatio());
		}
		break;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONDOWN:
		if (!m_leftButton)
		{
			m_dragStartFlag = true; // 드래그를 새로 시작하는지 확인
		}
		m_leftButton = true;
		break;
	case WM_LBUTTONUP:
		m_leftButton = false;
		break;
	case WM_RBUTTONDOWN:
		if (!m_rightButton)
		{
			m_dragStartFlag = true; // 드래그를 새로 시작하는지 확인
		}
		m_rightButton = true;
		break;
	case WM_RBUTTONUP:
		m_rightButton = false;
		break;
	case WM_KEYDOWN:
		m_keyPressed[wParam] = true;
		if (wParam == 27)
		{ // ESC키 종료
			DestroyWindow(hwnd);
		}
		break;
	case WM_KEYUP:
		if (wParam == 70)
		{ // f키 일인칭 시점
			m_useFirstPersonView = !m_useFirstPersonView;
		}

		if (wParam == 67)
		{ // c키 화면 캡쳐
			ComPtr<ID3D11Texture2D> backBuffer;
			m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
			D3D11Utils::WriteToFile(m_device, m_context, backBuffer,
			                        "captured.png");
		}

		m_keyPressed[wParam] = false;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

// 여러 물체들이 공통적으료 사용하는 Const 업데이트
void AppBase::UpdateEyeViewProjBuffers(const Vector3& eyeWorld,
                                       const Matrix& viewRow,
                                       const Matrix& projRow,
                                       const Matrix& refl = Matrix())
{
	m_eyeViewProjConstData.eyeWorld = eyeWorld;
	m_eyeViewProjConstData.viewProj = (viewRow * projRow).Transpose();
	m_mirrorEyeViewProjConstData.eyeWorld = eyeWorld;
	m_mirrorEyeViewProjConstData.viewProj =
	    (refl * viewRow * projRow).Transpose();

	D3D11Utils::UpdateBuffer(m_device, m_context, m_eyeViewProjConstData,
	                         m_eyeViewProjConstBuffer);
	D3D11Utils::UpdateBuffer(m_device, m_context, m_mirrorEyeViewProjConstData,
	                         m_mirrorEyeViewProjConstBuffer);
}

void AppBase::CreateDepthBuffers()
{

	// DepthStencilView 만들기
	// Depth : 여러 물체 중 화면에 그릴 것을 정할 때 사용함 (24bit == 3byte)
	// Stencil : 렌더링할 부분을 정할 때 사용함 (8bit == 1byte)
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = m_screenWidth;
	desc.Height = m_screenHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	// RTV가 MSAA를 활성화를 시켰을 경우, DepthBuffer도 MSAA를 활성화 시켜줘야함
	if (m_useMSAA && m_numQualityLevels > 0)
	{
		desc.SampleDesc.Count = 4;
		desc.SampleDesc.Quality = m_numQualityLevels - 1;
	}
	else
	{
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
	}

	// [Depth & Stencil]
	// Format : DXGI_FORMAT_D24_UNORM_S8_UINT (Depth : 24bit / Stencil : 8bit)
	//
	// [Depth]
	// Depth는 NDC 단계에서 정규화된 깊이값 (0 ~ 1)을 정수화(quantization, 양자화)를 통해서 정수로 저장함
	// z_stored ​= round(z_ndc​×(2^N−1))
	// 2^N-1은 저장공간의 크기 (지정한 UINT 정수의 범위)
	// ex) D24UNORM : [0, 16,777,215]
	// 이후 필요에 의해 다시 정규값이 필요할 경우 [ Depth값 (UINT)/2^N - 1 ] 을 하면 됨
	// ex) 8,388,608 / 16,777,215 ≈ 0.5
	// 해당 방식으로 정밀도 손실이 있을 수는 있으나 대부분의 장면 깊이 분포에서는 충분히 정밀함
	// 문제는 1/z 의 형태로 정규화 되었기 때문에 깊이값이 선형적이지 않고, 0에 가까워질수록 무한대에 가까워지는 수준으로 급격하게 커지며, 값이 커질수록 0에 수렴하는 수준으로 급격하게 작아짐
	// 이로인해 Z-Fighting 이 발생하며, (far - near) 값이 크면 클수록 심해짐
	//
	// [Stencil]
	// Stencil은 렌더링 결과에 대하여 특정 영역만 필요할 때, 그 영역을 식별하거나 제한하는데 사용하는 [공간적 마스크] 역할
	// 즉, 렌더링된 값에 대하여 [이부분이 거울에 사용될 값이다] 라고 마스킹[표시] 하는 것과 같음
	// ex)
	// 1차 Pass에서 World의 거울 부분을 stencil = 1로 기록,
	// 2차 Pass에서 ReflectionWorld의 렌더링 결과값 중에서 1차 때 stencil == 1로 기록한 부분만 렌더
	//
	// 주로 사용되는 곳
	// Portals / Mirrors	    : 특정 영역에서만 장면을 반전 렌더        [ex) stencil = 1 영역만 반사]
	// Outline / Silhouette     : 오브젝트 외곽선 강조                   [ex) 오브젝트보다 살짝 큰 영역을 만들어 stencil = 1 / 오브젝트 + 이외의 부분을 stencil =0 로 설정하고 stencil = 1 부분만 렌더]
	// UI Mask / Clipping       : UI 이미지가 특정 형태 안에만 보이게 함  [ex) stencil = 1인 픽셀만 표시]
	// Deferred Rendering Layer : 특정 G-buffer pass에만 효과 적용       [ex) stencil bit로 pass 식별]
	//
	// 여기서는 D3D11_DEPTH_STENCIL_DESC 를 만들어 더 상세하게 설정할 것임

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	ThrowIfFailed(m_device->CreateTexture2D(
	    &desc, 0, m_depthStencilBuffer.GetAddressOf()));
	ThrowIfFailed(m_device->CreateDepthStencilView(
	    m_depthStencilBuffer.Get(), NULL, m_depthStencilView.GetAddressOf()));

	/* D3D11_DEPTH_STENCIL_DESC 옵션 정리
	 * https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_depth_stencil_desc
	 * StencilRead/WriteMask: 예) uint8 중 어떤 비트를 사용할지
	 */

	/* D3D11_DEPTH_STENCILOP_DESC 옵션 정리
	 * https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_depth_stencilop_desc
	 * Depth와 Stencil이 같이 다니기 때문에 둘 다 생각해줘야함
	 *
	 * 렌더링 시 GPU는 픽셀을 그리기 전에 아래 두단계를 수행함
	 * Depth Test   : 이 픽셀이 기존 픽셀보다 앞인가 뒤인가?        | Less, Greater, Equal 등의 비교 연산으로 결과를 판단
	 * Stencil Test : 이 픽셀이 스텐실 조건(ref 값)과 일치하는가?   | qual, NotEqual, Always 등의 비교로 결과를 판단
	 * Depth와 Stencil 값에 대하여 판정을 할 수가 있고 그 결과가 pass / fail로 나옴

	 * StencilPassOp : 둘 다 pass일 때 할 일
	 * StencilDepthFailOp : Stencil pass, Depth fail 일 때 할 일
	 * StencilFailOp : 둘 다 fail 일 때 할 일
	 */

	// 하나의 버퍼에 3가지 상태 (state)를 만들어 사용하는 것이지,
	// StencilBuffer를 여러개 만드는 것이 아님

	// 들어가기 전에 알아둬야할 것
	// ============================================================================
	//  [Depth / Stencil Test 동작 요약]
	// ----------------------------------------------------------------------------
	// 1. GPU 파이프라인에서 픽셀이 실제로 그려질지 여부는
	//    Output-Merger(OM) 단계의 Depth / Stencil Test에서 결정된다.
	//    Depth의 Test는 현재 픽셀의 깊이 값(SV_Position.z 또는 HW Depth)과 DepthBuffer에 저장된 기존 픽셀 깊이값을 비교함
	//      - 정규화된 실수(float, 0~1 범위) 형태로 비교함
	//      - DepthBuffer에서 값을 읽을 때는 자동으로 24bit UINT값을 0~1 사이 float로 복원함
	//    Stencil의 Test는 OMSetDepthStencilState(pDSState, 1) 에서 1이 ref값이며, StencilFunc( bufferStencil, ref )의 형태로 판정함
	//
	// 2. Test의 핵심 구성 요소
	//    - DepthFunc     : 새 픽셀의 깊이(Z)와 DepthBuffer에 기록된 Z를 비교하여 통과 여부 결정
	//    - StencilFunc   : 스텐실 버퍼 값과 참조값(ref)을 비교하여 통과 여부 결정
	//                      (예: D3D11_COMPARISON_EQUAL → bufferStencil == ref인 경우 통과)
	//
	// [중요]
	// 3. StencilFunc / DepthFunc의 테스트 결과가 모두 "Pass"일 때만 픽셀 셰이더 출력값이 컬러 버퍼에 기록됨
	//    테스트에서 하나라도 Fail되면 픽셀은 그려지지 않음
	//    즉, 버퍼에 남기는 것과 상관없이 해당 렌더링 결과값은 Test All Pass에 의해 결정된다는 것
	//    또한 각 Buffer는 후속 작업을 위해 해당 작업에서 메모를 해두는 용도일 뿐, 해당 작업에는 영향을 주지 않음
	//
	// 4. 이후 결과에 따라 StencilOp(연산자)가 실행됨
	//    각 조건에 따라 별도로 Buffer에 메모할 수 있게 실행 옵션을 다양하게 뒀음
	//    - StencilFailOp       : 스텐실 테스트 자체 실패 시 실행
	//    - StencilDepthFailOp  : 스텐실 Pass, Depth Fail 시 실행
	//    - StencilPassOp       : 스텐실 + 깊이 테스트 모두 Pass 시 실행
	//
	// 5. StencilOp은 스텐실 버퍼의 값을 갱신할지 유지할지 결정함
	//    즉, 특정 조건의 옵션이 실행되었을 때, 각 Buffer에 어떤 행동을 할지 정하는 것
	//    - KEEP     : 기존 스텐실 값 유지
	//    - REPLACE  : 참조값(ref)으로 덮어씀
	//    - INCR_SAT / DECR_SAT : 스텐실 값 증감
	//
	// 6. 반사변환을 한 물체는 Winding 순서가 바뀜. (같은 A-B-C순서이지만 배치가 바뀌면서 CW->CCW, CCW->CW가 됨)
	// ----------------------------------------------------------------------------
	// [요약 정리]
	// ----------------------------------------------------------------------------
	// - StencilFunc / DepthFunc : "렌더링 가능한지" 판정하는 테스트 단계
	// - StencilOp               : "테스트 이후 버퍼를 수정할지" 결정하는 연산단계
	// - KEEP                    : 테스트는 수행하지만 버퍼는 수정하지 않음
	// - StencilEnable = false    : 테스트 자체를 비활성화 (모든 픽셀 렌더링)
	//
	// - [그릴지 여부는 Func에서 결정]되고, [버퍼는 후속 패스를 위해 값만 남겨두는 용도]로 사용됨
	// ============================================================================

	// m_drawDSS: 지금까지 사용해온 기본적으로 적용되는 DSS [Null, Default 시
	// 적용되던 값]
	// 해당 DSS를 가지고 1차 렌더
	// 이때 거울은 제외하고 렌더링함

	// [Depth]
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.DepthEnable = true;                          // 깊이 테스트(Depth Test)의 활성화 여부               [true → 깊이 비교 사용 / false → 무시하고 항상 그리기]
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 깊이 버퍼에 값 쓸지 여부                            [ALL → 깊이 통과 픽셀은 Z값 기록 / ZERO → 깊이 읽기만 하고 기록 안 함(투명 오브젝트 등)]
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;           // 깊이 비교 방식 (새 pixel vs 기존 pixel)             [LESS → 새 픽셀이 기존보다 '가까우면' 통과]

	// [Stencil]
	dsDesc.StencilEnable = false;                               // 스텐실 테스트 기능 활성화 여부                       [true → 스텐실 비교/연산 수행 / false → 스텐실 관련 설정 전부 무시]
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;   // 읽을 때 적용되는 비트마스크                          [0xFF(255,기본값) → 모든 비트 사용. 테스트할 때 어떤 비트를 대상으로 테스트할지]
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK; // 쓸 때 적용되는 비트마스크                            [0xFF(255,기본값) → 모든 비트 사용. 비트를 갱신할 때 어떤 비트를 대상으로 갱신할지]

	// 스텐실은 폴리곤의 앞면(front)과 뒷면(back) 각각에 대해 테스트 실패 / 통과시 어떤 연산을 할지를 개별적으로 정의할 수 있음
	// 해당 State에는 false이므로 설정값이 사용되지 않음
	// 앞면에 대해서 어떻게 작동할지 설정
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;      // 스텐실 테스트가 실패했을 때 수행할 연산               [KEEP → 기존 값 유지 / REPLACE → 새 ref 값으로 덮어씀 / INCR & DECR → 값 증가/감소]
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; // 스텐실은 통과했지만 깊이 테스트 실패 시 수행할 연산    [KEEP → 그대로 둠 (기본 설정)]
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;      // 두 테스트(스텐실+깊이) 모두 통과 시 수행할 연산        [KEEP → 유지 / REPLACE → 스텐실 값 덮어쓰기]
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;      // 스텐실 비교 연산 방식                                [ALWAYS → 항상 통과 / EQUAL → ref와 같을 때만 통과 / NOTEQUAL → ref와 다를 때만 통과]

	// 뒷면에 대해 어떻게 작동할지 설정 (뒷면도 그릴 경우)
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	ThrowIfFailed(
	    m_device->CreateDepthStencilState(&dsDesc, m_drawDSS.GetAddressOf()));

	// Stencil에 1(임의)로 표기해주는 DSS
	// - 1이라는 특정 값은 OMSetDepthStencilState의 2번째 인수로 넣음
	// - 해당 DSS가 적용된 상태로 거울만 그림
	// - 그러면 거울 부분만 Stencil = 1 이 설정됨
	// - Stencil을 기록하기 위해 그리는 것으로 뒤에서 거울 렌더를 제대로 그릴 때 DepthWriteMask를 All로 설정
	dsDesc.DepthEnable = true;                           // 이미 그려진 물체 유지
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // ALL로 해도 결과값에는 차이가 없음. 그러나 성능면에서는 있을 수 있으므로 ZERO로 Depth 기록은 꺼두는 것을 권장함
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = true;    // Stencil 필수
	dsDesc.StencilReadMask = 0xFF;  // 모든 비트 다 사용
	dsDesc.StencilWriteMask = 0xFF; // 모든 비트 다 사용

	// 앞면에 대해서 어떻게 작동할지 설정
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;      // Depth가 Fail인 경우 의도대로라면 Stencil 구간이였더라도 1로 기록하지 않고 기존값을 유지함 (그려지면 안되기 때문)
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; // 위와 동일
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;   // 둘다 Pass인 경우에만 기록
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;      // PASS 조건[Render/Buffer] : Stencil 값 내에서는 따로 비교하지 않음 (어짜피 0, 1 밖에 없음)

	ThrowIfFailed(
	    m_device->CreateDepthStencilState(&dsDesc, m_maskDSS.GetAddressOf()));

	// Stencil에 1로 표기된 경우에"만" 그리는 DSS
	// DepthBuffer는 초기화된 상태로 가정 (거울 안에 새로운 세상을 그려야 하기 때문에 DepthTest를 다시함)
	// 거울보다 앞에있는 물체가 있는 경우, 앞선 State에 의해 결러짐
	// 거울 속 세상을 거울 위치에만 그림. 즉, Reflection 되어 있는 물체들을 Stencil = 1 인 부분에만 렌더링함

	// D3D11_COMPARISON_EQUAL 이미 1로 표기된 경우에만 그리기
	// OMSetDepthStencilState(..., 1); <- 여기의 1

	dsDesc.DepthEnable = true;                          // 깊이 테스트 기능 전체 활성화   | 거울 속을 다시 그릴때 필요
	dsDesc.StencilEnable = true;                        // 스텐실 테스트 기능 전체 활성화 | Stencil 사용
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 깊이 값 기록 허용             | 새 DepthBuffer 기준으로 깊이값을 다시 써야 하므로 기록을 허용
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;     // 깊이 비교 방식                | 반사 시점에서의 Z-Test를 수행할 때, 기존 깊이값과 동일한 픽셀도 통과시키기 위함 (EQUAL 포함) <- 주의
	                                                    // 해당 예시는 거울에 맞대고 있는 손가락을 예시로 들 수 있음. 즉, 거울과 거의 같은 깊이를 가진 것도 렌더링을 해야한다는 의미

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;      // Stencil Buffer를 읽기전용으로 쓰겠다는 의미
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP; // Stencil Buffer를 읽기전용으로 쓰겠다는 의미
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;      // Stencil Buffer를 읽기전용으로 쓰겠다는 의미
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;       // PASS 조건[Render/Buffer] : ref(1)과 stencil 값이 같아야함

	ThrowIfFailed(m_device->CreateDepthStencilState(
	    &dsDesc, m_drawMaskedDSS.GetAddressOf()));

	/* "이미 그려져있는 화면"과 어떻게 섞을지를 결정
	 * Dest: 이미 그려져 있는 값들을 의미
	 * Src: 픽셀 쉐이더가 계산한 값들을 의미 (여기서는 마지막 거울)
	 * 여기서 설정한 값대로 블랜딩해서 그려짐
	 *
	 * 해당 예제에서는
	 * 1차 렌더링에서 “비치지 않는 거울 표면”이 그려져 있기 때문에
	 * [거울 표면 픽셀이 Destination(기존값)]
	 *
	 * 그리고 2차렌더링에서 그려지는
	 * [반사된 월드가 Source(새 픽셀)]
	 */

	D3D11_BLEND_DESC mirrorBlendDesc;
	ZeroMemory(&mirrorBlendDesc, sizeof(mirrorBlendDesc));
	mirrorBlendDesc.AlphaToCoverageEnable = true;   // MSAA
	mirrorBlendDesc.IndependentBlendEnable = false; // RTV마다 따로따로 설정하고 싶을 경우 true로 변경하고 설정해주면 됨
	// 개별 RenderTarget에 대해서 설정 (최대 8개)
	mirrorBlendDesc.RenderTarget[0].BlendEnable = true; // 블렌딩 여부

	// FACTOR는 OMSetBlendState에 인자로 전달된 값
	// 첫번째 : BlendState
	// 두번째 : 얼마나 섞어줄지 (BLEND FACTOR)
	// 세번째 : MSAA 시 어떤걸 업데이트할지 설정하는 값(잘 사용하는지는 모름)
	mirrorBlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_INV_BLEND_FACTOR; // INV_FACTOR은 1-FACTOR값으로 사용함
	mirrorBlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_BLEND_FACTOR;    // FACTOR값 그대로 사용함
	mirrorBlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;            // 두개를 더함

	mirrorBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; // 알파값을 바꿀 때 사용함. 투명한 물체가 누적되어 있을 경우에는 중요함
	mirrorBlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	mirrorBlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	// 필요하면 RGBA 각각에 대해서도 출력을 조절 가능
	mirrorBlendDesc.RenderTarget[0].RenderTargetWriteMask =
	    D3D11_COLOR_WRITE_ENABLE_ALL;

	ThrowIfFailed(m_device->CreateBlendState(&mirrorBlendDesc,
	                                         m_mirrorBS.GetAddressOf()));
}

bool AppBase::InitMainWindow()
{

	WNDCLASSEX wc = {sizeof(WNDCLASSEX),
	                 CS_CLASSDC,
	                 WndProc,
	                 0L,
	                 0L,
	                 GetModuleHandle(NULL),
	                 NULL,
	                 NULL,
	                 NULL,
	                 NULL,
	                 L"HongLabGraphics", // lpszClassName, L-string
	                 NULL};

	if (!RegisterClassEx(&wc))
	{
		cout << "RegisterClassEx() failed." << endl;
		return false;
	}

	RECT wr = {0, 0, m_screenWidth, m_screenHeight};
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, false);
	m_mainWindow = CreateWindow(wc.lpszClassName, L"HongLabGraphics Example",
	                            WS_OVERLAPPEDWINDOW,
	                            100,                // 윈도우 좌측 상단의 x 좌표
	                            100,                // 윈도우 좌측 상단의 y 좌표
	                            wr.right - wr.left, // 윈도우 가로 방향 해상도
	                            wr.bottom - wr.top, // 윈도우 세로 방향 해상도
	                            NULL, NULL, wc.hInstance, NULL);

	if (!m_mainWindow)
	{
		cout << "CreateWindow() failed." << endl;
		return false;
	}

	ShowWindow(m_mainWindow, SW_SHOWDEFAULT);
	UpdateWindow(m_mainWindow);

	return true;
}

bool AppBase::InitDirect3D()
{

	const D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	const D3D_FEATURE_LEVEL featureLevels[2] = {
	    D3D_FEATURE_LEVEL_11_0, // 더 높은 버전이 먼저 오도록 설정
	    D3D_FEATURE_LEVEL_9_3};
	D3D_FEATURE_LEVEL featureLevel;

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferDesc.Width = m_screenWidth;
	sd.BufferDesc.Height = m_screenHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferCount = 2;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = m_mainWindow;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; //ImGui 폰트가 두꺼워짐
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.SampleDesc.Count = 1; // _FLIP_은 MSAA 미지원
	sd.SampleDesc.Quality = 0;

	ThrowIfFailed(D3D11CreateDeviceAndSwapChain(
	    0, driverType, 0, createDeviceFlags, featureLevels, 1,
	    D3D11_SDK_VERSION, &sd, m_swapChain.GetAddressOf(),
	    m_device.GetAddressOf(), &featureLevel, m_context.GetAddressOf()));

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		cout << "D3D Feature Level 11 unsupported." << endl;
		return false;
	}

	CreateBuffers();

	SetViewport();

	D3D11_RASTERIZER_DESC rastDesc;
	ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
	rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	rastDesc.FrontCounterClockwise = false; // CounterClockWise == CCW (반시계방향)
	rastDesc.DepthClipEnable = true;
	rastDesc.MultisampleEnable = true;

	ThrowIfFailed(
	    m_device->CreateRasterizerState(&rastDesc, m_solidRS.GetAddressOf()));

	// 거울에 반사되면 삼각형의 Winding이 바뀌기 때문에 CCW로 그려야함 (같은 A-B-C순서이지만 배치가 바뀌면서 CW->CCW, CCW->CW가 됨)
	// 따라서 FrontCounterClockwise를 true로 바꿔야함
	rastDesc.FrontCounterClockwise = true;

	// Reflection 물체 용도 RasterizeState를 하나 더 만듦
	ThrowIfFailed(m_device->CreateRasterizerState(&rastDesc,
	                                              m_solidCCWRS.GetAddressOf()));

	rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	ThrowIfFailed(
	    m_device->CreateRasterizerState(&rastDesc, m_wireCCWRS.GetAddressOf()));

	rastDesc.FrontCounterClockwise = false;
	ThrowIfFailed(
	    m_device->CreateRasterizerState(&rastDesc, m_wireRS.GetAddressOf()));

	// 공통으로 쓰이는 ConstBuffers
	D3D11Utils::CreateConstBuffer(m_device, m_eyeViewProjConstData,
	                              m_eyeViewProjConstBuffer);
	D3D11Utils::CreateConstBuffer(m_device, m_mirrorEyeViewProjConstData,
	                              m_mirrorEyeViewProjConstBuffer);

	return true;
}

bool AppBase::InitGUI()
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.DisplaySize = ImVec2(float(m_screenWidth), float(m_screenHeight));
	ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	if (!ImGui_ImplDX11_Init(m_device.Get(), m_context.Get()))
	{
		return false;
	}

	if (!ImGui_ImplWin32_Init(m_mainWindow))
	{
		return false;
	}

	return true;
}

void AppBase::SetViewport()
{

	static int previousGuiWidth = -1;

	if (previousGuiWidth != m_guiWidth)
	{

		previousGuiWidth = m_guiWidth;

		// Set the viewport
		ZeroMemory(&m_screenViewport, sizeof(D3D11_VIEWPORT));
		m_screenViewport.TopLeftX = float(m_guiWidth);
		m_screenViewport.TopLeftY = 0;
		m_screenViewport.Width = float(m_screenWidth - m_guiWidth);
		m_screenViewport.Height = float(m_screenHeight);
		m_screenViewport.MinDepth = 0.0f;
		m_screenViewport.MaxDepth = 1.0f;

		m_context->RSSetViewports(1, &m_screenViewport);
	}
}

void AppBase::CreateBuffers()
{

	// 레스터화 -> float/depthBuffer(MSAA) -> resolved -> backBuffer

	// BackBuffer는 화면으로 최종 출력 (SRV는 불필요)
	ComPtr<ID3D11Texture2D> backBuffer;
	ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));
	ThrowIfFailed(m_device->CreateRenderTargetView(backBuffer.Get(), NULL, m_backBufferRTV.GetAddressOf()));

	// FLOAT MSAA RenderTargetView/ShaderResourceView
	ThrowIfFailed(m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R16G16B16A16_FLOAT, 4, &m_numQualityLevels));

	D3D11_TEXTURE2D_DESC desc;
	backBuffer->GetDesc(&desc);
	desc.MipLevels = desc.ArraySize = 1;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	desc.Usage = D3D11_USAGE_DEFAULT; // 스테이징 텍스춰로부터 복사 가능
	desc.MiscFlags = 0;
	desc.CPUAccessFlags = 0;
	if (m_useMSAA && m_numQualityLevels)
	{
		desc.SampleDesc.Count = 4;
		desc.SampleDesc.Quality = m_numQualityLevels - 1;
	}
	else
	{
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
	}

	ThrowIfFailed(
	    m_device->CreateTexture2D(&desc, NULL, m_floatBuffer.GetAddressOf()));

	ThrowIfFailed(m_device->CreateShaderResourceView(m_floatBuffer.Get(), NULL, m_floatSRV.GetAddressOf()));

	ThrowIfFailed(m_device->CreateRenderTargetView(m_floatBuffer.Get(), NULL, m_floatRTV.GetAddressOf()));

	// FLOAT MSAA를 Relsolve해서 저장할 SRV/RTV
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	ThrowIfFailed(m_device->CreateTexture2D(&desc, NULL,
	                                        m_resolvedBuffer.GetAddressOf()));
	ThrowIfFailed(m_device->CreateShaderResourceView(
	    m_resolvedBuffer.Get(), NULL, m_resolvedSRV.GetAddressOf()));
	ThrowIfFailed(m_device->CreateRenderTargetView(
	    m_resolvedBuffer.Get(), NULL, m_resolvedRTV.GetAddressOf()));

	CreateDepthBuffers();

	m_postProcess.Initialize(m_device, m_context, {m_resolvedSRV},
	                         {m_backBufferRTV}, m_screenWidth, m_screenHeight,
	                         4);
}

} // namespace hlab