#include "Common.hlsli"

Texture2D g_texture0 : register(t0);
SamplerState g_sampler : register(s0);

cbuffer PixelConstantBuffer : register(b0)
{
    float3 eyeWorld;
    bool useTexture;
    Material material;
    Light lights[MAX_LIGHTS];
    uint useBlinnPhong;
    float3 padding;
};

float3 EvaluateSurface(float3 lightStrength, float3 lightVec, float3 normal,
                       float3 toEye, Material mat)
{
    float3 specular = float3(0.0f, 0.0f, 0.0f);

    if (useBlinnPhong != 0)
    {
        float3 halfwaySum = toEye + lightVec;
        float halfwayLength = length(halfwaySum);
        if (halfwayLength > 0.00001f)
        {
            float3 halfway = halfwaySum / halfwayLength;
            float hdotn = max(dot(halfway, normal), 0.0f);
            specular = mat.specular
                     * pow(hdotn, mat.shininess * 2.0f);
        }
    }
    else
    {
        float3 reflected = reflect(-lightVec, normal);
        float rdotv = max(dot(reflected, toEye), 0.0f);
        specular = mat.specular * pow(rdotv, mat.shininess);
    }

    return (mat.diffuse + specular) * lightStrength;
}

float3 EvaluateDirectionalComparison(Light light, Material mat,
                                     float3 normal, float3 toEye)
{
    float3 lightVec = normalize(-light.direction);
    float ndotl = max(dot(lightVec, normal), 0.0f);
    float3 lightStrength = light.strength * ndotl;

    return EvaluateSurface(lightStrength, lightVec, normal, toEye, mat);
}

float CalculateComparisonAttenuation(float distanceToLight,
                                     float falloffStart,
                                     float falloffEnd)
{
    float range = max(falloffEnd - falloffStart, 0.00001f);
    return saturate((falloffEnd - distanceToLight) / range);
}

float3 EvaluatePointComparison(Light light, Material mat, float3 position,
                               float3 normal, float3 toEye)
{
    float3 lightVec = light.position - position;
    float distanceToLight = length(lightVec);
    float3 result = float3(0.0f, 0.0f, 0.0f);

    if (distanceToLight <= light.fallOffEnd
        && distanceToLight > 0.00001f)
    {
        lightVec /= distanceToLight;

        float ndotl = max(dot(lightVec, normal), 0.0f);
        float3 lightStrength = light.strength * ndotl;
        lightStrength *= CalculateComparisonAttenuation(
            distanceToLight, light.fallOffStart, light.fallOffEnd);

        result = EvaluateSurface(
            lightStrength, lightVec, normal, toEye, mat);
    }

    return result;
}

float3 EvaluateSpotComparison(Light light, Material mat, float3 position,
                              float3 normal, float3 toEye)
{
    float3 lightVec = light.position - position;
    float distanceToLight = length(lightVec);
    float3 result = float3(0.0f, 0.0f, 0.0f);

    if (distanceToLight <= light.fallOffEnd
        && distanceToLight > 0.00001f)
    {
        lightVec /= distanceToLight;

        float ndotl = max(dot(lightVec, normal), 0.0f);
        float3 lightStrength = light.strength * ndotl;
        lightStrength *= CalculateComparisonAttenuation(
            distanceToLight, light.fallOffStart, light.fallOffEnd);

        float spotFactor = pow(
            max(-dot(lightVec, normalize(light.direction)), 0.0f),
            light.spotPower);
        lightStrength *= spotFactor;

        result = EvaluateSurface(
            lightStrength, lightVec, normal, toEye, mat);
    }

    return result;
}

float4 main(PixelShaderInput input) : SV_TARGET
{
    float3 toEye = normalize(eyeWorld - input.posWorld);
    float3 color = material.ambient;

    [unroll]
    for (int i = 0; i < NUM_DIR_LIGHTS; ++i)
    {
        color += EvaluateDirectionalComparison(
            lights[i], material, input.normalWorld, toEye);
    }

    [unroll]
    for (int j = NUM_DIR_LIGHTS;
         j < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS;
         ++j)
    {
        color += EvaluatePointComparison(
            lights[j], material, input.posWorld, input.normalWorld, toEye);
    }

    [unroll]
    for (int k = NUM_DIR_LIGHTS + NUM_POINT_LIGHTS;
         k < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS + NUM_SPOT_LIGHTS;
         ++k)
    {
        color += EvaluateSpotComparison(
            lights[k], material, input.posWorld, input.normalWorld, toEye);
    }

    float4 surfaceColor = useTexture
        ? g_texture0.Sample(g_sampler, input.texcoord)
        : float4(1.0f, 1.0f, 1.0f, 1.0f);

    return float4(color, 1.0f) * surfaceColor;
}
