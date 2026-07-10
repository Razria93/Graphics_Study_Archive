#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

Texture2D g_texture0 : register(t0);
TextureCube g_textureCube0 : register(t1);

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
    bool useRelfection;
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

    // reflect(광선이 들어오는 방향, 노멀 벡터)
    // https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-reflect
    
    // color = g_textureCube0.Sample(g_sampler, input.normalWorld);
    
    // 내가 작성한 코드
    // CubeMap은 배경이므로 pos값은 무시되어야함. 이는 hit 지점도 마찬가지
    // hitPoint의 변화정도는 배경 입장에선 정말 미미한 변화이나, 샘플링 관점에서는 엄청 크게 변할 수 있는 수치임
    // 따라서 pos값은 더하면 안됨. CubeMap은 무조건 원점기준 방향벡터만
    // float3 reflectDir = normalize(2.0 * max(dot(input.normalWorld, toEye), 0.0) * input.normalWorld - toEye);
    // float3 toSkybox = input.posWorld + reflectDir;
    // float k = max(abs(toSkybox.x), max(abs(toSkybox.y), abs(toSkybox.z)));
    // float3 hitPoint = toSkybox / k;
    // 
    // color = g_textureCube0.Sample(g_sampler, hitPoint);
    
    // 올바른 코드_1
    // float3 reflectDir = normalize(2.0 * max(dot(input.normalWorld, toEye), 0.0) * input.normalWorld - toEye);
    // color = g_textureCube0.Sample(g_sampler, reflectDir);
    
    // 올바른 코드_2 : 자체적으로 reflect를 계산해주는 함수가 있음
    color = g_textureCube0.Sample(g_sampler, reflect(-toEye, input.normalWorld));
    
    return useTexture ? float4(color, 1.0) * g_texture0.Sample(g_sampler, input.texcoord) : float4(color, 1.0);
}
