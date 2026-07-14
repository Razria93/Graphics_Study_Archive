#include "SphSimulation.h"

#include "SphKernels.h"
#include <iostream>

namespace hlab
{

using namespace std;

void SphSimulation::Update(float dt)
{

	UpdateDensity();

	UpdateForces();

	for (int i = 0; i < m_particlesCpu.size(); i++)
	{

		if (m_particlesCpu[i].life < 0.0f)
			continue;

		// 힘으로 속도 업데이트
		// 속도로 위치 업데이트
		m_particlesCpu[i].velocity += m_particlesCpu[i].force * dt / m_mass;
		m_particlesCpu[i].position += m_particlesCpu[i].velocity * dt;
	}
}

void SphSimulation::UpdateDensity()
{

#pragma omp parallel for
	for (int i = 0; i < m_particlesCpu.size(); i++)
	{

		if (m_particlesCpu[i].life < 0.0f)
			continue;

		m_particlesCpu[i].density = 0.0f; // 주변 입자들이 많을경우 높음 (여왕)

		// the summation over j includes all particles
		// i와 j가 같을 경우에도 고려한다는 의미
		// https://en.wikipedia.org/wiki/Smoothed-particle_hydrodynamics

		for (size_t j = 0; j < m_particlesCpu.size(); j++)
		{

			if (m_particlesCpu[j].life < 0.0f)
				continue;

			// 주변입자와의 거리
			const float dist =
			    (m_particlesCpu[i].position - m_particlesCpu[j].position)
			        .Length();

			// 반지름보다 크면 영향력 == 0 -> 계산 필요 X
			// 해당 조건에 걸러질 입자들을 미리 걸러낼 수 있다면
			// 반지름 내의 입자들만 연산할 수 있게 가속할 수 있음
			// 이때 자료구조를 사용함 [추후 소개]
			if (dist >= m_radius)
				continue;

			// 해당 입자가 주변 입자에 미칠 수 있는 영향력을 누적으로 더하는 식
			// 부드럽게 내려가는 함수 이름이 CubicSpline
			m_particlesCpu[i].density +=
			    m_mass * SphKernels::CubicSpline(dist * 2.0f / m_radius);
		}

		// density를 기반으로 압력을 계산하는 식
		m_particlesCpu[i].pressure =
		    m_pressureCoeff *
		    (pow(m_particlesCpu[i].density / m_density0, 7.0f) - 1.0f);
	}
}

void SphSimulation::UpdateForces()
{

#pragma omp parallel for
	for (int i = 0; i < m_particlesCpu.size(); i++)
	{
		// 유체의 특정지점 i에 대한 데이터를 입자화
		// 질량은 1로 일반화하고 연산하는 듯
		if (m_particlesCpu[i].life < 0.0f)
			continue;

		Vector3 pressureForce(0.0f);
		Vector3 viscosityForce(0.0f);

		const float& rho_i = m_particlesCpu[i].density;
		const float& p_i = m_particlesCpu[i].pressure;
		const Vector3& x_i = m_particlesCpu[i].position;
		const Vector3& v_i = m_particlesCpu[i].velocity;

		// i의 물리량 계산
		for (size_t j = 0; j < m_particlesCpu.size(); j++)
		{

			if (m_particlesCpu[j].life < 0.0f)
				continue;

			if (i == j)
				continue;

			const float& rho_j = m_particlesCpu[j].density;
			const float& p_j = m_particlesCpu[j].pressure;
			const Vector3& x_j = m_particlesCpu[j].position;
			const Vector3 x_ij = x_i - x_j;
			const Vector3& v_j = m_particlesCpu[j].velocity;

			const float dist = (x_i - x_j).Length();

			if (dist >= m_radius)
				continue;

			if (dist < 1e-3f) // 수치 오류 방지
				continue;

			// 힌트: SphKernels::CubicSplineGrad() 사용

			float q = 2.0f * dist / m_radius;

			// 여기서 A는 압력(p)
			// 방향이 (x_i - x_j) 인 이유는 CubieSpline이 j가 i에 영향을 주는 것이기 때문임
			const Vector3 gradPressure = 
				rho_i * m_mass * 
				(p_i / (rho_i * rho_i) + p_j / (rho_j * rho_j)) * 
				SphKernels::CubicSplineGrad(q) * 
				(x_i - x_j) / dist; // 정규화 (방향이기 때문에 정규화, dist가 너무 가까우면 안됨. 해당 예제에서는 if정도로 막아둠)

			// 여기서 A는 속도(v)
			const Vector3 laplacianVelocity =
			    2.0f * (m_mass / rho_j) * (v_i - v_j) /
			    (x_ij.LengthSquared() + 0.01f * m_radius * m_radius) *
			    SphKernels::CubicSplineGrad(q) *
				x_ij.Dot(x_ij / dist);
			    

			pressureForce -= m_mass / rho_i * gradPressure;
			viscosityForce += m_mass * m_viscosity * laplacianVelocity;
		}

		m_particlesCpu[i].force = pressureForce + viscosityForce;
	}
}

} // namespace hlab

/*
            float q = 2.0f * (dist / m_radius);

            const Vector3 gradPressure =
                rho_i * m_mass *
                ((p_i / (rho_i * rho_i)) + (p_j / (rho_j * rho_j))) *
                SphKernels::CubicSpline(q) * x_ij;

            const Vector3 laplacianVelocity = ((v_j - v_i) / rho_j) * SphKernels::CubicSplineGrad(q);

            pressureForce -= m_mass / rho_i * gradPressure;
            viscosityForce += m_mass * m_viscosity * laplacianVelocity;
        }

        m_particlesCpu[i].force = pressureForce + viscosityForce;
*/