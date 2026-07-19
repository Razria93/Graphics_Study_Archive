Texture3D<float> pressure : register(t0);

// boundary conditions
// -1: Dirichlet condition
// -2: Neumann condition
//  0: Full cell
Texture3D<int> bc : register(t2);

RWTexture3D<float4> velocity : register(u0);

static int3 offset[6] =
{
    int3(1, 0, 0), // right
    int3(-1, 0, 0), // left
    int3(0, 1, 0), // up
    int3(0, -1, 0), // down
    int3(0, 0, 1), // back
    int3(0, 0, -1) // front
};

[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    // 가장자리 조건 주의
    // Sourcing에서 설정한 bc (바운더리맵)에서 음수(바운더리 부분)인 경우 연산을 진행하지 않음
    // 즉, 해당 부분의 압력값에 대하여 초기값 이후 갱신을 진행하지 않음
    if (bc[dtID.xyz] >= 0)
    {
        // offset 지점들의 압력을 캐싱해두는 배열변수
        float p[6];

        [unroll]
        for (int i = 0; i < 6; i++)
        {
            /* 해당 for문은 PressureProjection에 사용할 인접한 셀의 압력값을 캐싱하는 단계*/
            //  - 0 ~ 6라는 인덱스를 기반으로 offset[6]의 요소의 순서에 맞게 캐싱함
            //  - 만약 인접한 셀이 바운더리라면 바운더리의 속성값이 아닌 아래 규칙에 맞는 속성값을 캐싱함
            
            // 해당 지점의 근처 셀이 바운더리에 해당하는 경우
            // 경계조건 (Boundary Condtion) : 시뮬레이션 공간의 가장자리
            if (bc[dtID.xyz + offset[i]] == -1)
            {
                // TODO:
                p[i] = -pressure[dtID.xyz];
                
                // Dirichlet
                // 목적:
                //   외부와 맞닿은 경계(시뮬레이션 도메인의 가장자리)에 대해
                //   압력을 0으로 고정(Open Boundary)하여 유체가 자유롭게
                //   나가거나 들어올 수 있도록 함.
                //
                // 배경:
                //   경계면과 맞닿아 있는 셀의 압력값을 직접 0으로 설정할 수도 있으나,
                //   인접한 셀 간의 평균압력이 0이 되면 경계압력이 자연스럽게 0으로 수렴하게 됨.
                //   따라서 경계 근처 셀의 압력합이 0이 되도록 보정하는 것이 더 정확한(2차 정밀도) 접근임.
                //
                // 수학적 근거:
                //   (p_center + p_boundary) / 2 = 0  →  p_boundary = -p_center
                //
                // 구현:
                //   경계 방향의 셀 값을 -p_center로 설정하여 평균압력 0을 만족시킴.
                //   이렇게 하면 경계면에서 압력이 0으로 근사되며, 외부 대기압(기준압력)과의 균형이 유지됨.
                //
                // 결과:
                //   개방형(Open) 경계 → 유체가 외부로 빠져나가거나 유입될 수 있음.
            }
            else if (bc[dtID.xyz + offset[i]] == -2)
            { 
                // TODO:
                p[i] = pressure[dtID.xyz];
                
                // Neumann
                // 목적:
                //   내부 오브젝트(고체 벽) 표면에서 유체가 벽을 통과하지 못하도록, 벽 방향으로의 압력 변화(기울기)를 0으로 유지함
                //   즉, 벽면의 양쪽 압력이 동일하도록 만들어 유체가 물체 내부로 유입/유출하는 흐름을 원천차단
                //
                // 배경:
                //   해당 셀로 속성(유체)이 이동하려면 [압력차이가 발생하여 속도가 해당 셀 쪽으로 발생]해야함
                //   따라서 이동을 막기위해서는 해당 셀 근처에서 방향으로 속도가 발생해서는 안되며 이를 위해서는 압력차이가 발생해서는 안됨
                //   Neumann Boundary Condition은 ∂p/∂n = 0 을 의미함. [법선 방향으로 압의 변화량이 0]
                //   (n은 벽 표면의 법선 방향)
                //
                //   이 조건은 “법선 방향으로 압력이 일정하다(gradient = 0)”는 뜻이며, 따라서 벽을 향한 압력 변화가 없어 그 방향으로 힘이 작용하지 않음
                //   결과적으로 유체가 벽을 뚫고 나가거나 들어오지 못함
                //
                // 수학적 근거:
                //   ∂p/∂n = 0  →  (p_boundary - p_center) / Δx = 0  →  p_boundary = p_center
                //
                // 구현:
                //   경계면 방향의 압력값을 중심셀 압력과 동일하게 복사.
                //   즉, p[i] = pressure[center] 로 설정.
                //
                // 결과:
                //   - 벽 방향으로 압력차(∇p)가 0이 되므로, 힘(?∇p)이 0.
                //   - 벽을 통과하는 속도 성분(u?)이 0으로 유지됨.
                //   - 즉, 벽 표면을 따라 미끄러질 수는 있지만 침투는 없음.
                //
                // 요약:
                //   “압력 변화가 없는 폐쇄 경계(Closed Boundary)”로,
                //   유체의 침투를 막고 안정된 물체 표면 효과를 형성.
            }
            else
            {
                // 둘 다 아닌경우 압력장에 기록된 값을 그대로 사용
                p[i] = pressure[dtID.xyz + offset[i]];
            }
        }

        // Gradient
        //  - 이웃끼리의 압력 차(기울기)를 구하는 것 (P_1 - P_0) / 2 * Δx
        //  - 한 지점의 압력이 주변보다 높으면 높은쪽에서 낮은 쪽으로 힘이 작용하며, 
        //    이 때 힘 밀도(단위 체적당 힘)은 압력의 기울기(단위 구간 당 압력의 차)로 주어짐
        
        //  - Navier Stokes Equation : 속도변화는 밀도에 반비례, 압력 구배는 역방향으로 비례
        //    f_pressure =  - 1/ρ * ∇p
        
        velocity[dtID.xyz] -= 0.5 * float4(p[0] - p[1], p[2] - p[3], p[4] - p[5], 0);
    }
}
// Dirichlet : 외곽 위치에 압력이 0 (Open Boundary, 압력차가 0)
// Neumann : 물체 내부의 대류를 막음 (Close Boundary, Gradinent가 0)