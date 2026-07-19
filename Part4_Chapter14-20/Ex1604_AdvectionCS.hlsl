// Advect Velocity and Density
// Advection에는 Temp 텍스쳐도 같이 필요함

Texture3D<float4> velocityTemp : register(t0);
Texture3D<float> densityTemp : register(t1);

RWTexture3D<float4> velocity : register(u0);
RWTexture3D<float> density : register(u1);

SamplerState pointClampSS : register(s0);
SamplerState linearClampSS : register(s1);
SamplerState linearMirrorSS : register(s2);
SamplerState pointWrapSS : register(s3);
SamplerState linearWrapSS : register(s4);

cbuffer Consts : register(b4)
{
    float3 dxBase;
    float dt;
    float3 dxUp;
    float time;
    int upScale;
    int numNewParticles;
    float turbulence;
}

[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    uint width, height, depth;
    velocity.GetDimensions(width, height, depth);
    float3 dx = float3(1.0 / width, 1.0 / height, 1.0 / depth);
    float3 uvw = (dtID.xyz + 0.5) * dx; // 픽셀 중심

    // TODO:
    // 주의: velocityTemp에는 이미 해상도 단위(격자 단위, cell/s)로 정규화된 속도가 저장되어 있음.
    //       즉, 실제 물리 속도(거리/시간)를 격자 단위(cell/second)로 변환해 보관하고 있으므로,
    //       여기서 다시 dx를 곱해줌으로써 물리 단위(거리/시간)의 속도로 환산함.
    //
    // 정리하자면:
    //       - velocityTemp [격자단위 속도] = velocity / dx
    //       - velocity     [물리단위 속도] = velocityTemp * dx
    //       위 관계를 일관되게 유지해야 단위 일관성과 수치 안정성을 확보할 수 있음.
    float3 vel = velocityTemp[dtID.xyz].xyz * dx;
   
    // TODO:
    // semi-Lagrangian advection (반-라그랑지안 이동)
    //  - 현재 셀 중심에서 속도장을 따라 과거 위치(uvwBack)를 추적하여, Temp 텍스처에서 샘플링한 값을 현재 텍스처에 저장함.
    //  - velocityTemp는 BaseGrid 해상도 기준으로 정의되어 있으며, Advection은 더 세밀한 UpGrid에서 수행되므로,
    //    동일한 물리적 거리 이동량을 유지하기 위해 속도에 upScale을 곱함.
    //    (BaseGrid 대비 UpGrid의 해상도 비율 보정)
    float3 uvwBack = uvw - (vel * dt * upScale);
    
    // TODO:
    // Advection (운반 단계)
    //  - 유체 속의 물리량(속도, 온도, 밀도 등)이 유체의 흐름에 따라 함께 이동하는 현상
    //  - uvwBack은 현재 셀의 중심에서 과거로 역추적한 좌표이며, 여기서 샘플링된 값을 현재 프레임의 density 및 velocity에 저장함
    //  - 0.999는 서서히 약해지는 것(소실)을 구현하기 위함
    density[dtID.xyz] = densityTemp.SampleLevel(linearWrapSS, uvwBack, 0.0) * 0.999;    
    velocity[dtID.xyz] = velocityTemp.SampleLevel(linearWrapSS, uvwBack, 0.0) * 0.999;  
}
