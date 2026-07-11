TextureCube g_textureCube0 : register(t0);
SamplerState g_sampler : register(s0);

struct CubeMappingPixelShaderInput
{
    float4 posProj : SV_POSITION;
    float3 posModel : POSITION;
    float2 texcoord : TEXCOORD0;
    float3 indexColor : INDEXCOLOR;
};

struct PixelShaderOutput
{
    float4 pixelColor : SV_Target0;
    float4 indexColor : SV_Target1;
};

PixelShaderOutput main(CubeMappingPixelShaderInput input)
{
    PixelShaderOutput output;
    output.pixelColor = g_textureCube0.Sample(g_sampler, input.posModel.xyz);
    output.indexColor = float4(input.indexColor, 1.0);
    
    return output;
}