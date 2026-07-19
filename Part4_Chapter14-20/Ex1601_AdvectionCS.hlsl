// Advect Velocity and Density

Texture2D<float2> velocityTemp : register(t0);
Texture2D<float4> densityTemp : register(t1);

RWTexture2D<float2> velocity : register(u0);
RWTexture2D<float4> density : register(u1);

// Repeated Boundary
SamplerState pointWrapSS : register(s0);
SamplerState linearWrapSS : register(s1);

cbuffer Consts : register(b0)
{
    float dt;
    float viscosity;
    float alpha;
}

[numthreads(32, 32, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    uint width, height;
    velocity.GetDimensions(width, height);
    float2 dx = float2(1.0 / width, 1.0 / height);
    float2 pos = (dtID.xy + 0.5) * dx; // 이 쓰레드가 처리하는 셀의 중심
    
    // TODO: 1. velocityTemp로부터 현재속도 샘플링해오기
    // 속도장으로부터 Advection 되어야 하기 때문
    float2 vel = velocityTemp.SampleLevel(pointWrapSS, pos, 0.0).xy;
    
    // TODO: 2. 그 속도를 이용해서 역추적 위치 계산
    float2 posBack = pos - vel * dt;
    
    float2 velBack = velocityTemp.SampleLevel(linearWrapSS, posBack, 0.0);
    float4 densityBack = densityTemp.SampleLevel(linearWrapSS, posBack, 0.0);
    
    // Load 사용버전
    // float2 pixelCoord = posBack * float2(width, height);
    // pixelCoord = clamp(pixelCoord, float2(0.0f, 0.0f), float2(width - 1, height - 1));
    // float4 colorBack = densityTemp.Load(int3(pixelCoord, 0.0));
    
    // TODO: 3. 그 위치에서 샘플링 해오기
    velocity[dtID.xy] = velBack;
    density[dtID.xy] = densityBack;
}

// 셀값이 어디서 왔는지 역추적하는 단계
// 대부분이 셀 중심이 아닌 중간좌표에서 옴
// 샘플을 하지 않을 경우 계단현상이 생김