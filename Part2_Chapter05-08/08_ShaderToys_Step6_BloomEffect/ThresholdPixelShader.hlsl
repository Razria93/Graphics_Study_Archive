Texture2D g_texture0 : register(t0);
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
    float4 smapling = g_texture0.Sample(g_sampler, input.texcoord);
    
    // return all(g_texture0.Sample(g_sampler, input.texcoord).xyz > threshold) ? g_texture0.Sample(g_sampler, input.texcoord) : float4(0.0, 0.0, 0.0, 1.0);
    return ((smapling.x + smapling.y + smapling.z) / 3) > threshold ?
    smapling :
    float4(0.0, 0.0, 0.0, 1.0);
}