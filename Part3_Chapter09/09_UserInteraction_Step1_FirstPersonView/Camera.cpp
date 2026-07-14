#include <iostream>
#include "Camera.h"

namespace hlab
{

using namespace std;
using namespace DirectX;

Matrix Camera::GetViewRow()
{
	// m_pitch는 Y축 회전이기 때문에 각도의 양 회전방향과 우리가 의도하는 회전방향이 서로 반대임
	// 따라서 우리가 의도한 회전을 하려면 음의 회전방향으로 회전을 해야하므로 -theta여야 함
	// 
	// 이와는 별개로 View변환의 경우 World가 우리가 회전을 의도한 방향의 반대방향으로 움직여야 하기 때문에 
	// Translation과 Rotation을 의도한 각도 및 방향을 반대값으로 변환해서 World에 적용해야 함
	//
	// 해당 View행렬은 ExampleApp에서 호출하여 ConstantsBuffer에 들어가 World에 적용됨

	// 곱셈순서 조심!!
	return Matrix::CreateTranslation(-m_position) * Matrix::CreateRotationY(-m_yaw) * Matrix::CreateRotationX(-(-m_pitch));
}

Vector3 Camera::GetEyePos() { return m_position; }

void Camera::UpdateMouse(float mouseNdcX, float mouseNdcY)
{
	// 얼마나 회전할지 계산
	// https://en.wikipedia.org/wiki/Aircraft_principal_axes
	m_yaw = mouseNdcX * DirectX::XM_PI;      // 좌우 360도
	m_pitch = mouseNdcY * DirectX::XM_PIDIV2; // 위 아래 90도

	// 방향벡터는 해당방향으로 정상적으로 회전을 해야함
	// 방향벡터는 표현을 위해 존재하는 것이 아닌, 모델의 전후좌우상하를 표현해야하는 '진짜 방향' 이기 때문에 정상적으로 translate와 rotate가 되어야하는 것
	// 또한 뱡향값이기 때문에 translate의 영향을 받아서도 안됨
	// 따라서 ViewDir은 Rotate의 정방향에 대한 영향만 받음
	
	m_viewDir = Vector3::Transform(Vector3(0.0f, 0.0f, 1.0f), Matrix::CreateRotationY(m_yaw));
	m_viewDir.Normalize();
	
	m_rightDir = m_upDir.Cross(m_viewDir);
	m_rightDir.Normalize();
}

// 이미 dt에서 부호를 바꿔서 들어옴
void Camera::MoveForward(float dt)
{
	// 이동후의_위치 = 현재_위치 + 이동방향 * 속도 * 시간차이;
	m_position += m_viewDir * m_speed * dt;
}

void Camera::MoveRight(float dt)
{
	// 이동후의_위치 = 현재_위치 + 이동방향 * 속도 * 시간차이;
	m_position += m_rightDir * m_speed * dt;
}

void Camera::SetAspectRatio(float aspect) { m_aspect = aspect; }

Matrix Camera::GetProjRow()
{
	return m_usePerspectiveProjection
	           ? XMMatrixPerspectiveFovLH(XMConvertToRadians(m_projFovAngleY),
	                                      m_aspect, m_nearZ, m_farZ)
	           : XMMatrixOrthographicOffCenterLH(-m_aspect, m_aspect, -1.0f,
	                                             1.0f, m_nearZ, m_farZ);
}
} // namespace hlab