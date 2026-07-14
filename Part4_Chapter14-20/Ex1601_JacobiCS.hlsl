Texture2D<float> pressureTemp : register(t0);
Texture2D<float> divergence : register(t1);

RWTexture2D<float> pressureOut : register(u0);

SamplerState pointWrapSS : register(s0);
SamplerState linearWrapSS : register(s1);

[numthreads(32, 32, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    // Dirichlet boundary condition
    if (dtID.x == 0 && dtID.y == 0)
    {
        pressureOut[dtID.xy] = 0.0;
        return;
    }
    
    uint width, height;
    pressureOut.GetDimensions(width, height);
    // float2 dx = float2(1.0 / width, 1.0 / height);
        
    uint2 left = uint2(dtID.x == 0 ? width - 1 : dtID.x - 1, dtID.y);
    uint2 right = uint2(dtID.x == width - 1 ? 0 : dtID.x + 1, dtID.y);
    uint2 up = uint2(dtID.x, dtID.y == height - 1 ? 0 : dtID.y + 1);
    uint2 down = uint2(dtID.x, dtID.y == 0 ? height - 1 : dtID.y - 1);
    
    // float2 pos_left = (left + 0.5) * dx;
    // float2 pos_right = (right + 0.5) * dx;
    // float2 pos_up = (up + 0.5) * dx;
    // float2 pos_down = (down + 0.5) * dx;
    // float2 pos_center = (dtID.xy + 0.5) * dx;
    // 
    // float2 p_left = pressureTemp.SampleLevel(pointWrapSS, pos_left, 0.0);
    // float2 p_right = pressureTemp.SampleLevel(pointWrapSS, pos_right, 0.0);
    // float2 p_up = pressureTemp.SampleLevel(pointWrapSS, pos_up, 0.0);
    // float2 p_down = pressureTemp.SampleLevel(pointWrapSS, pos_down, 0.0);
    // 
    // float d_center = divergence.SampleLevel(pointWrapSS, pos_center, 0.0);
    //
    // pressureOut[dtID.xy] = (p_right + p_left + p_up + p_down - d_center) * 0.25;
    
    pressureOut[dtID.xy] = (pressureTemp.Load(int3(right, 0))
                          + pressureTemp.Load(int3(left, 0))
                          + pressureTemp.Load(int3(up, 0))
                          + pressureTemp.Load(int3(down, 0))
                          - divergence.Load(int3(dtID.xy, 0))) * 0.25;
    
    // pressureOut[dtID.xy] = (pressureTemp[left]
    //                       + pressureTemp[right]
    //                       + pressureTemp[up]
    //                       + pressureTemp[down]
    //                       - divergence[dtID.xy]) * 0.25;
}

// SampleLevel로 가져오면 안되는 이유
// 셀 기반 연산이기 때문에 연산값이 보간이 되면 안됨