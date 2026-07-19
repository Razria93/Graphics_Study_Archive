Texture3D<float4> velocity : register(t0);

// boundary conditions
// -1: Dirichlet condition
// -2: Neumann condition
//  0: Full cell
Texture3D<int> bc : register(t2);

RWTexture3D<float> divergence : register(u0);
RWTexture3D<float> pressure : register(u1);
RWTexture3D<float> pressureTemp : register(u2);

cbuffer Consts : register(b4)
{
    float3 dxBase;
    float dt;
    float3 dxUp;
    float time;
}

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
    if (bc[dtID.xyz] >= 0) // 가장자리 조건 주의
    {
        float div = 0.0;
        // Divergence
        //  - 셀 중심에서 6방향(±x, ±y, ±z) 속도의 차이를 합산하는 것
        //  - 주변에 비해서 해당 셀의 속도가 높은지 낮은지를 표시하는 값이며, 해당 셀이 압축되고 있는지 혹은 팽창되고 있는지를 나타내는 값
        
        [unroll]
        for (int i = 0; i < 6; i++)
        {
            if (bc[dtID.xyz + offset[i]] == -1) 
            {
                // Dirichlet
                // 의미 : Open Boundary (외부와 맞닿은 개방 경계, 압력=0)
                // 따로 처리해야하는 이유 : 외부 셀이 존재하지 않음 → ghost cell을 사용해야 함
                // 코드 동작 : 인접한 셀의 속도를 “현재 셀 속도”로 대체하여 보정
                // 추가설명
                //  1. 유체는 경계를 넘어 나갈 수 있음 (개방경계, Open boundary)
                //  2. 경계 밖은 유체가 없는 “공기/진공” 영역 
                //  3. 저항이 없으므로 등속도 운동
                
                // TODO:
                div += dot(velocity[dtID.xyz].xyz, float3(offset[i]));
            }
            if (bc[dtID.xyz + offset[i]] == -2) 
            {
                // Neumann
                // 의미 : Closed Boundary (벽, 법선 속도=0)
                // 따로 처리해야하는 이유 : 벽을 통과하지 않도록 속도 반사(reflection) 필요
                // 코드 동작 : “반사 속도” 계산으로 벽면 속도 0 보정
                // 추가설명
                // [ fluid cell ] | [ wall boundary ] | [ ghost cell ]
                //  1. 위와 같을 때 중앙차분으로 벽 중심에서의 속도를 근사하면 [ u_wall = (u_fluid + u_ghost) / 2.0 ] 
                //  2. 이를 u_ghost에 대하여 풀면 [ u_ghost = 2.0 * u_wall - u_fluid ] 
                // 왜 이렇게 되어야하는가
                //  1. 벽 통과 불과(No-Pentration) 조건의 핵심은 속도 연속(Velocity Continuity)
                //  2. 이는 '벽에 바로 초근접으로 붙어 있는 유체의 속도는 벽의 속도와 같아야 한다' 임
                //  3. 해당 벽은 유체셀과 내부(고스트)셀이 접하는 면으로 위의 중앙차분을 이용하여 중심에서의 속도를 근사하게 되면, 
                //     선형보간으로 인해 양쪽셀의 속성값으로 시작한 속도가 점점 벽에 가까워지며, 초근접 거리의 유체와 ghost에서는 벽의 속도와 같아지게 될 거임
                //  4. 그러나 우리가 알고 있는 것은 유체의 속도이며, 희망하는 벽의 속도가 있기 때문에, 이를 기반으로 ghost셀의 속도 속성값을 역산하고자 하는 것
                
                // TODO:
                div += dot(2 * velocity[dtID.xyz + offset[i]].xyz - velocity[dtID.xyz].xyz, float3(offset[i]));
            }
            else
            {
                // 의미 : 일반 유체 셀
                // 따로 처리해야하는 이유 : 내부 유체 간 정상적인 차분 계산
                // 코드 동작 : 인접 셀의 속도 사용
                
                // TODO:
                div += dot(velocity[dtID.xyz + offset[i]].xyz, float3(offset[i]));
            }
        }

        divergence[dtID.xyz] = 0.5 * div;
        pressure[dtID.xyz] = 0.0;
        pressureTemp[dtID.xyz] = 0.0;
    }
}
