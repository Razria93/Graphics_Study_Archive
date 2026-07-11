#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

TextureCube g_textureCube0 : register(t0);  // 자료형이 텍스쳐큐브임. t임.
SamplerState g_sampler : register(s0);

float4 main(PixelShaderInput input) : SV_TARGET
{
    // 주의: 텍스춰 좌표가 float3 입니다.
    return g_textureCube0.Sample(g_sampler, input.posWorld.xyz); 
    // 텍스쳐 좌표가 2차원이 아니라 3차원임. 이유는 CubeMap에서 색상값을 가져올때 벡터를 기준으로 가져오게 됨
    // Translation은 카메라가 이동하는 것이 아니라 세상이 이동하는 것임. 따라서 카메라는 언제나 중앙에 있음.
    // 그래서 큐브맵도 View의 변화에 따라 회전하게 되는데 카메
}