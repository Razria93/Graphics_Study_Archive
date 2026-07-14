RWTexture2D<float4> densityField : register(u0);

[numthreads(32, 32, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    const float dissipation = 0.1f;
    // 원래는 시간이 많이 지날수록 사라짐의 정도가 커지기 때문에 시간을 곱함

    float3 color = densityField[dtID.xy].rgb - dissipation;
    color = max(0, color);
    
    densityField[dtID.xy] = float4(color, 1.0);
}
