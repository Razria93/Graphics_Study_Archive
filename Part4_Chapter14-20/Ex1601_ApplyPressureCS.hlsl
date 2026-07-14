Texture2D<float> pressure : register(t0);
RWTexture2D<float2> velocity : register(u0);

[numthreads(32, 32, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    uint width, height;
    velocity.GetDimensions(width, height);
    float2 dx = float2(1.0 / width, 1.0 / height); // 이번 예제에서는 안쓰임. 1로 되어 있음
    
    // cell들의 인덱싱
    // 반복되는 구조를 만들기 위해 가장자리 부분에 반복되는 구조를 만들어둠
    uint2 left = uint2(dtID.x == 0 ? width - 1 : dtID.x - 1, dtID.y);
    uint2 right = uint2(dtID.x == width - 1 ? 0 : dtID.x + 1, dtID.y);
    uint2 up = uint2(dtID.x, dtID.y == height - 1 ? 0 : dtID.y + 1);
    uint2 down = uint2(dtID.x, dtID.y == 0 ? height - 1 : dtID.y - 1);
    
    // TODO: 압력의 gradient 계산
    float p_left = pressure.Load(float3(left, 0.0));
    float p_right = pressure.Load(float3(right, 0.0));
    float p_up = pressure.Load(float3(up, 0.0));
    float p_down = pressure.Load(float3(down, 0.0));
    
    // // 구해야할 것은 x방향 성분들의 x방향으로의 차이, y방향 성분들의 y방향으로의 차이
    float2 dp = float2((p_right - p_left) * 0.5, (p_up - p_down) * 0.5);
    float2 u = velocity[dtID.xy];
    velocity[dtID.xy] = u - dp;
    
    // 약식
    // float2 dp = float2(pressure[right] - pressure[left], pressure[up] - pressure[down]);
    // velocity[dtID.xy] -= dp * 0.5;
    
}

// 기본적으로 SRV는 dtID 기준 가져오고 싶을 경우 Load가 표준
// UAV는 무조건 dtID 기준으로