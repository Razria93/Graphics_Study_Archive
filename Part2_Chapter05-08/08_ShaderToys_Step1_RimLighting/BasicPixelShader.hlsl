#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

Texture2D g_texture0 : register(t0);
SamplerState g_sampler : register(s0);

cbuffer BasicPixelConstantBuffer : register(b0)
{
    float3 eyeWorld;
    bool useTexture;
    Material material;
    Light light[MAX_LIGHTS];
    float3 rimColor;
    float rimPower;
    float rimStrength;
    bool useSmoothstep;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
    float3 toEye = normalize(eyeWorld - input.posWorld);

    float3 color = float3(0.0, 0.0, 0.0);
    
    int i = 0;
    
    // https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-for
    // https://forum.unity.com/threads/what-are-unroll-and-loop-when-to-use-them.1283096/
    
    [unroll] // warning X3557: loop only executes for 1 iteration(s), forcing loop to unroll
    for (i = 0; i < NUM_DIR_LIGHTS; ++i)
    {
        color += ComputeDirectionalLight(light[i], material, input.normalWorld, toEye);
    }
    
    [unroll]
    for (i = NUM_DIR_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; ++i)
    {
        color += ComputePointLight(light[i], material, input.posWorld, input.normalWorld, toEye);
    }
    
    [unroll]
    for (i = NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS + NUM_SPOT_LIGHTS; ++i)
    {
        color += ComputeSpotLight(light[i], material, input.posWorld, input.normalWorld, toEye);
    }

    // Rim Lighting
    // OpenGL SuperBible 7th Edition, Ch13. Rendering Techniques
    
    // Smoothstep
    // https://thebookofshaders.com/glossary/?search=smoothstep
    
    // A) center bias
    // color += pow(saturate(dot(toEye, input.normalWorld)), rimPower) * rimColor * rimStrength;

    // B) rim bias (가장자리 강조 = Fresnel 비스듬각 강화) -> 보호막 같은 느낌
    // color += (1.0 - pow(saturate(dot(toEye, input.normalWorld)), rimPower)) * rimColor * rimStrength;
    
    // Rim Effect
    float NdotE = saturate(dot(input.normalWorld, toEye));
    float rimBase = 1.0 - NdotE;
    
    rimBase = max(rimBase, 1e-4);
    float rimPow = max(rimPower, 0.0);
    
    float rim = useSmoothstep ? smoothstep(0.0, 1.0, rimBase)
                              : pow(rimBase, rimPow);
    color += rim * (rimColor * rimStrength);
    
    return useTexture ? float4(color, 1.0) * g_texture0.Sample(g_sampler, input.texcoord) : float4(color, 1.0);
}
