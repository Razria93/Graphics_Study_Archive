RWTexture3D<float4> velocity : register(u0);
RWTexture3D<float> density : register(u1);

// boundary conditions
// -1: Dirichlet condition
// -2: Neumann condition
//  0: Full cell
RWTexture3D<int> bc : register(u2); // 경계조건 맵 (각 셀이 어떤 종류의 경계에 속하는지를 표시하는 역할)

cbuffer Consts : register(b4)
{
    float3 dxBase;
    float dt;
    float3 dxUp;
    float time;
    int upScale = 1;
    int numNewParticles = 0;
    float turbulence = 0.0;
    float sourceStrength = 1.0;
    float buoyancy = 0.0;
}

// https://en.wikipedia.org/wiki/Smoothstep
float smootherstep(float x, float edge0 = 0.0f, float edge1 = 1.0f)
{
  // Scale, and clamp x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0, 1);

    return x * x * x * (3 * x * (2 * x - 5) + 10.0f);
}

[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    uint width, height, depth;
    bc.GetDimensions(width, height, depth);
    
    bc[dtID] = 0;
    
    if (dtID.x == 0 || dtID.y == 0 || dtID.z == 0
        || dtID.x == width - 1 || dtID.y == height - 1 || dtID.z == depth - 1)
    {
        bc[dtID] = -1; // Dirichlet boundary condition, 바운더리 컨디션 기록
        density[dtID.xyz] = 0.0;
    }

    // Source
    float3 center = float3(0.02, 0.3, 0.5) / dxBase;
    int radius = 0.2 * height;

    float dist = length(float3(dtID.xyz) - center) / radius;
    
    if (dist < 1.0)
    {
        velocity[dtID.xyz] = float4(32 * sourceStrength, 0, 0, 0) / 64.0 * float(width);
        // scale up velocity
        // float(width) : width에 상관없이, 전체 도메인 대비 유체의 이동 거리(비율)가 일정하도록 보정하기 위한 스케일링 항 (해상도 보정)
        // 32, 64       : 경험적 상수 보정
        
        density[dtID.xyz] = max(smootherstep(1.0 - dist), density[dtID.xyz]);
        // density를 구형으로 적당히 뿌려주는 코드
        // max는 지속적으로 갱신하되, 기존 것이 더 높다면 기존 것을 유지하겠다는 것
        
        //bc[dtID.xyz] = -2; // Neumann
    }

    // Object
    // 물체 하드코딩
    center = float3(0.15, 0.3, 0.5) / dxBase;
    radius = 0.1 * height;
    
    dist = length(float3(dtID.xyz) - center) / radius;
    
    if (dist < 1.0)
    {
        velocity[dtID.xyz] = float4(0, 0, 0, 0) / 64.0 * width; // 멈춰있는 물체 : 물체 자체가 멈춰있으므로 속도는 0
        // density[dtID.xyz] = 0.0;
        bc[dtID.xyz] = -2; // Neumann, 바운더리 컨디션 기록 (-1은 외곽 경계, -2는 물체 경계)
    }

    // -----------------------------------------------------------------------------
    // Buoyancy (부력)
    // -----------------------------------------------------------------------------
    //
    // 부력은 밀도 차이에 의해 발생하는 중력의 반대방향 힘으로,
    // 유체 내부의 특정 셀을 위쪽(y축)으로 밀어올리는 형태로 작용함.
    //
    // 물리적 정의:
    //     f_buoyancy = - (ρ_object - ρ_fluid) * g * y^
    //   - ρ_object, ρ_fluid : 물체와 주변 유체의 밀도
    //   - g    : 중력가속도
    //   - y^   : y축 단위 벡터(위쪽 방향)
    //
    // F = ma 로부터 체적당(force per volume)으로 나눈 형태이며,
    // 유체 시뮬레이션에서는 실제 질량밀도 대신 ‘상대적 밀도(density field)’를 사용함.
    // 즉, density[dtID.xyz]는 0~1 범위의 무차원 스칼라로
    // “부력을 유발하는 상대적 강도”를 의미.
    //
    // velocity += (가속도 * Δt)
    //   → 힘(F/m)을 시간(dt) 동안 적분하여 속도 변화(Δv)를 계산.
    //   → dt는 시간 스텝 보정, width는 격자 해상도 보정(도메인 크기에 따른 속도 스케일링)
    //
    // buoyancy  : -g * y^ 항에 해당하는 계수 (가속도 크기)
    // density   : 부력의 세기에 비례하는 상대적 밀도값 ([유체의 단위 부피당 질량]이 밀도)
    // dt        : 시간 적분 항 (가속 → 속도)
    // width     : 공간 해상도 보정 항
    //
    // 결과적으로, 아래 식은 “유체의 밀도장에 따라 위쪽(y축) 방향으로
    // 부력에 해당하는 속도 증가를 적용하는 단계”를 의미함.
    
    velocity[dtID.xyz] += float4(0, buoyancy, 0, 0) * density[dtID.xyz] * dt * width;
}
