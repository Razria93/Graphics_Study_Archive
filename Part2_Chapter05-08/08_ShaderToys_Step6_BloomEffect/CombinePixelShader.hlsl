Texture2D g_texture0 : register(t0);    // 필터
Texture2D g_texture1 : register(t1);    // 원본
SamplerState g_sampler : register(s0);

cbuffer SamplingPixelConstantData : register(b0)
{
    float dx;
    float dy;
    float threshold;
    float strength;
    float4 options;
};

struct SamplingPixelShaderInput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

float4 main(SamplingPixelShaderInput input) : SV_TARGET
{
    return strength * g_texture0.Sample(g_sampler, input.texcoord) + g_texture1.Sample(g_sampler, input.texcoord);
}