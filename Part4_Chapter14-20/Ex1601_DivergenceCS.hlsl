Texture2D<float2> velocity : register(t0);
RWTexture2D<float> divergence : register(u0);
RWTexture2D<float> pressure : register(u1);
RWTexture2D<float> pressureTemp : register(u2);

SamplerState pointWrapSS : register(s0);
SamplerState linearWrapSS : register(s1);

[numthreads(32, 32, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    uint width, height;
    divergence.GetDimensions(width, height);
    float2 dx = float2(1.0 / width, 1.0 / height);

    // idnex
    uint2 left = uint2(dtID.x == 0 ? width - 1 : dtID.x - 1, dtID.y);
    uint2 right = uint2(dtID.x == width - 1 ? 0 : dtID.x + 1, dtID.y);
    uint2 up = uint2(dtID.x, dtID.y == height - 1 ? 0 : dtID.y + 1);
    uint2 down = uint2(dtID.x, dtID.y == 0 ? height - 1 : dtID.y - 1);

    // float2 pos_left = (left + 0.5) * dx;
    // float2 pos_right = (right + 0.5) * dx;
    // float2 pos_up = (up + 0.5) * dx;
    // float2 pos_down = (down + 0.5) * dx;
    // 
    // float2 u_left = velocity.SampleLevel(pointWrapSS, pos_left, 0.0);
    // float2 u_right = velocity.SampleLevel(pointWrapSS, pos_right, 0.0);
    // float2 u_up = velocity.SampleLevel(pointWrapSS, pos_up, 0.0);
    // float2 u_down = velocity.SampleLevel(pointWrapSS, pos_down, 0.0);
    // 
    // float2 du = (u_right - u_left) + (u_up - u_down);

    // divergence[dtID.xy] = du * 0.5;
    
    // 规过 1
    float2 du = float2((velocity[right].x - velocity[left].x), (velocity[up].y - velocity[down].y));
    divergence[dtID.xy] = 0.5 * dot(du, float2(1, 1));
    
    // 规过 2
    // divergence[dtID.xy] = ((velocity[right] - velocity[left]) + (velocity[up] - velocity[down])) * 0.5;
    
    pressure[dtID.xy] = 0.0;
    pressureTemp[dtID.xy] = 0.0;
}
