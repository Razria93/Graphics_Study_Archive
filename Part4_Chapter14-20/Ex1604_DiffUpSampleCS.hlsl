// Advect Velocity and Density

// Low-res
Texture3D<float4> velocityOld : register(t0); 
Texture3D<float4> velocityNew : register(t1); 
Texture3D<float> densityOld : register(t2);
Texture3D<float> densityNew : register(t3);

// High-res
RWTexture3D<float4> velocityUp : register(u0);
RWTexture3D<float> densityUp : register(u1);

SamplerState pointClampSS : register(s0);
SamplerState linearClampSS : register(s1);

cbuffer Consts : register(b4)
{
    float3 dxBase;
    float dt;
    float3 dxUp;
    float time;
}

// Run with Up-resolution
[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    float3 uvw = (dtID + 0.5) * dxUp;
    
    float coeff = 0.99; // 0.0: use interpolated from low-res, 1.0: fully diff-upsample
    
    float4 velOld = velocityOld.SampleLevel(linearClampSS, uvw, 0);
    float4 velNew = velocityNew.SampleLevel(linearClampSS, uvw, 0);
    
    // TODO:
    // velOld는 Projection 연산 이전에 BackUp해둔 저해상도 속도장
    // velNew는 Projection 연산 이후 추출된 저해상도 속도장
    // (velNew - velOld)은 이전 저해상도 속도장과 현재 저해상도 속도장의 차이만큼 고해상도 속도장에 더하여 업데이트 하는 것
    velocityUp[dtID] = lerp(velNew, velocityUp[dtID] + (velNew - velOld), coeff);
    
    float denOld = densityOld.SampleLevel(linearClampSS, uvw, 0);
    float denNew = densityNew.SampleLevel(linearClampSS, uvw, 0);
    
    // TODO:
    densityUp[dtID] = lerp(denNew, densityUp[dtID] + (denNew - denOld), coeff);
}
