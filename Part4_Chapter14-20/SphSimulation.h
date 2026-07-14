#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>

namespace hlab
{

using DirectX::SimpleMath::Vector3;
using std::vector;

// 좀더 정확한 산식은 나중에 개인 프로젝트 하면서 해보자
class SphSimulation
{
  public:
	struct Particle
	{
		Vector3 position = Vector3(0.0f);
		Vector3 velocity = Vector3(0.0f);
		Vector3 force = Vector3(0.0f); // 이걸 물리식을 기반으로 정교하게 계산하기 위해 density, pressure 가 필요함
		float density = 0.0f;
		float pressure = 0.0f;

		Vector3 color = Vector3(1.0f);
		float life = 0.0f; // 입자가 활성화되어있는지 구분용
		float size = 1.0f;
	};

	void Update(float dt);
	void UpdateDensity();
	void UpdateForces();

	vector<Particle> m_particlesCpu;
	float m_radius = 1.0f / 16.0f; // 입자 크기
	float m_mass = 1.0f;           // 질량
	float m_pressureCoeff = 1.0f;  // 입자의 척력 : 커지면 자기 공간을 확보를 잘하기 때문에 부피가 커짐.
	float m_density0 = 1.0f;		// 밀도
	float m_viscosity = 0.1f;		// 점성

	// 현재 입자들에 작용하는 힘이 중력과 바닥과 벽이 힘을 받을 때 발생하는 척력 (m_pressureCoeff)
	// 이 힘들이 균형을 이루는 시점에서 안정화가 됨
	// 압력이 높을경우 미는 힘이 강해져서 일렁임이 커짐
	// 일렁임이 커질 경우 안정이 되지 않는 것이기에 정밀도가 떨어지는 것
	// SPH에서는 점성은 압력에 의한 움직임을 안정화 시킬 때 사용함
	// 진짜 점성의 높은 액체는 다른 기술로 구현

  private:
};
} // namespace hlab