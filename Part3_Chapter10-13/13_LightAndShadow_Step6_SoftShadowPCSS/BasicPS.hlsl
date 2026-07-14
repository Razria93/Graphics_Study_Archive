#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

// 참고자료
// https://github.com/Nadrin/PBR/blob/master/data/shaders/hlsl/pbr.hlsl

// 메쉬 재질 텍스춰들 t0 부터 시작
Texture2D albedoTex : register(t0);
Texture2D normalTex : register(t1);
Texture2D aoTex : register(t2);
Texture2D metallicRoughnessTex : register(t3);
Texture2D emissiveTex : register(t4);

static const float3 Fdielectric = 0.04; // 비금속(Dielectric) 재질의 F0

cbuffer MaterialConstants : register(b0)
{
    float3 albedoFactor; // baseColor
    float roughnessFactor;
    float metallicFactor;
    float3 emissionFactor;

    int useAlbedoMap;
    int useNormalMap;
    int useAOMap; // Ambient Occlusion
    int invertNormalMapY;
    int useMetallicMap;
    int useRoughnessMap;
    int useEmissiveMap;
    float dummy;
};

float3 SchlickFresnel(float3 F0, float NdotH)
{
    return F0 + (1.0 - F0) * pow(2.0, (-5.55473 * NdotH - 6.98316) * NdotH);
    //return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

struct PixelShaderOutput
{
    float4 pixelColor : SV_Target0;
};

float3 GetNormal(PixelShaderInput input)
{
    float3 normalWorld = normalize(input.normalWorld);
    
    if (useNormalMap) // NormalWorld를 교체
    {
        float3 normal = normalTex.SampleLevel(linearWrapSampler, input.texcoord, lodBias).rgb;
        normal = 2.0 * normal - 1.0; // 범위 조절 [-1.0, 1.0]

        // OpenGL 용 노멀맵일 경우에는 y 방향을 뒤집어줍니다.
        normal.y = invertNormalMapY ? -normal.y : normal.y;
        
        float3 N = normalWorld;
        float3 T = normalize(input.tangentWorld - dot(input.tangentWorld, N) * N);
        float3 B = cross(N, T);
        
        // matrix는 float4x4, 여기서는 벡터 변환용이라서 3x3 사용
        float3x3 TBN = float3x3(T, B, N);
        normalWorld = normalize(mul(normal, TBN));
    }
    
    return normalWorld;
}

float3 DiffuseIBL(float3 albedo, float3 normalWorld, float3 pixelToEye,
                  float metallic)
{
    float3 F0 = lerp(Fdielectric, albedo, metallic);
    float3 F = SchlickFresnel(F0, max(0.0, dot(normalWorld, pixelToEye)));
    float3 kd = lerp(1.0 - F, 0.0, metallic);
    float3 irradiance = irradianceIBLTex.SampleLevel(linearWrapSampler, normalWorld, 0).rgb;
    
    return kd * albedo * irradiance;
}

float3 SpecularIBL(float3 albedo, float3 normalWorld, float3 pixelToEye,
                   float metallic, float roughness)
{
    float2 specularBRDF = brdfTex.SampleLevel(linearClampSampler, float2(dot(normalWorld, pixelToEye), 1.0 - roughness), 0.0f).rg;
    float3 specularIrradiance = specularIBLTex.SampleLevel(linearWrapSampler, reflect(-pixelToEye, normalWorld),
                                                            2 + roughness * 5.0f).rgb;
    const float3 Fdielectric = 0.04; // 비금속(Dielectric) 재질의 F0
    float3 F0 = lerp(Fdielectric, albedo, metallic);

    return (F0 * specularBRDF.x + specularBRDF.y) * specularIrradiance;
}

float3 AmbientLightingByIBL(float3 albedo, float3 normalW, float3 pixelToEye, float ao,
                            float metallic, float roughness)
{
    float3 diffuseIBL = DiffuseIBL(albedo, normalW, pixelToEye, metallic);
    float3 specularIBL = SpecularIBL(albedo, normalW, pixelToEye, metallic, roughness);
    
    return (diffuseIBL + specularIBL) * ao;
}

// GGX/Towbridge-Reitz normal distribution function.
// Uses Disney's reparametrization of alpha = roughness^2.
float NdfGGX(float NdotH, float roughness)
{
    float alpha = roughness * roughness;
    float alphaSq = alpha * alpha;
    float denom = (NdotH * NdotH) * (alphaSq - 1.0) + 1.0;

    return alphaSq / (3.141592 * denom * denom);
}

// Single term for separable Schlick-GGX below.
float SchlickG1(float NdotV, float k)
{
    return NdotV / (NdotV * (1.0 - k) + k);
}

// Schlick-GGX approximation of geometric attenuation function using Smith's method.
float SchlickGGX(float NdotI, float NdotO, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    return SchlickG1(NdotI, k) * SchlickG1(NdotO, k);
}

// 참고: https://github.com/opengl-tutorials/ogl/blob/master/tutorial16_shadowmaps/ShadowMapping.fragmentshader
float random(float3 seed, int i)
{
    float4 seed4 = float4(seed, i);
    float dot_product = dot(seed4, float4(12.9898, 78.233, 45.164, 94.673));
    return frac(sin(dot_product) * 43758.5453);
}

// NdcDepthToViewDepth
float N2V(float ndcDepth, matrix invProj)
{
    float4 pointView = mul(float4(0, 0, ndcDepth, 1), invProj);
    return pointView.z / pointView.w;
}

#define NEAR_PLANE 0.1
// #define LIGHT_WORLD_RADIUS 0.001
#define LIGHT_FRUSTUM_WIDTH 0.34641 // <- 계산해서 찾은 값

// Assuming that LIGHT_FRUSTUM_WIDTH == LIGHT_FRUSTUM_HEIGHT
// #define LIGHT_RADIUS_UV (LIGHT_WORLD_RADIUS / LIGHT_FRUSTUM_WIDTH)

float PCF_Filter(float2 uv, float zReceiverNdc, float filterRadiusUV, Texture2D shadowMap)
{
    float sum = 0.0f;
    for (int i = 0; i < 64; ++i)
    {
        float2 offset = diskSamples64[i] * filterRadiusUV;
        sum += shadowMap.SampleCmpLevelZero(
            shadowCompareSampler, uv + offset, zReceiverNdc);
    }
    return sum / 64;
}

// void Func(out float a) <- c++의 void Func(float& a) 처럼 출력값 저장 가능
// out 가 붙어있는 매개변수로 넘어온 인수는 내부에서 값 조절 가능함
void FindBlocker(out float avgBlockerDepthView, out float numBlockers, float2 uv,
                 float zReceiverView, Texture2D shadowMap, matrix invProj, float lightRadiusWorld)
{
    // lightRadiusWorld 는 월드 좌표에서 봤을 때 조명의 크기
    // 광원의 실제 크기(World 공간)를 그림자맵의 좌표계(UV 공간)로 변환
    float lightRadiusUV = lightRadiusWorld / LIGHT_FRUSTUM_WIDTH;
    
    // near 평면위의 lightRadius를 구함
    // lightRadiusUV는 UV 좌표평면으로 변환된 '실제' 조명의 길이
    // searchRadius는 near평면에 투영된 lightRadiusUV의 길이. near평면은 ShadowMap을 기록하는 평면
    // P는 색상을 찾고자 하는 대상인 픽셀로 P지점에서 light의 영향범위를 측정하고 그 범위 내에서 그림자가 얼마나 발생하는지의 비율을 찾고자 하는 것
    float searchRadius = lightRadiusUV * (zReceiverView - NEAR_PLANE) / zReceiverView;

    float blockerSum = 0;
    numBlockers = 0;
    for (int i = 0; i < 64; ++i)
    {
        // UV위치 기준 i번째 SamplingPoint의 searchRadius배 멀리 있는 위치의 깊이값을 가져오는 것
        float shadowMapDepth =
            shadowMap.SampleLevel(shadowPointSampler, float2(uv + diskSamples64[i] * searchRadius), 0).r;

        // ndc에서 가지고 있던 Depth값는 비선형이기 때문에 View공간의 선형인 실제 길이로 변경함
        shadowMapDepth = N2V(shadowMapDepth, invProj);
        
        if (shadowMapDepth < zReceiverView)
        {
            blockerSum += shadowMapDepth;
            numBlockers++;
        }
    }
    avgBlockerDepthView = blockerSum / numBlockers;
}

float PCSS(float2 uv, float zReceiverNdc, Texture2D shadowMap, matrix invProj, float lightRadiusWorld)
{
    // lightRadius : 실제 물리적 light 반지름 길이
    // LIGHT_FRUSTUM_WIDTH : 실제 물리적 프로스텀 길이
    // 결과적으로 얻고자 하는 것은 [원점을 기준으로 하는 radius의 LIGHT_FRUSTUM_WIDTH에 대한 상대적 비율 x 2]
    // 엄밀하게 따지면 프러스텀 폭은 전체 길이이므로, 반지름(radius)과 비교하기 위해서는 /2를 적용해야 같은 기준 (중심기준 거리)으로 비교할 수 있음
    // 그러나 해당 값을 의도적으로 누락함으로서 실제의 길이비율보다 2배인 값을 사용하게 됨
    // 결과적으로 샘플링 반경이 2배 커져, 동일 깊이 평면 내에서 더 넓은 주변 픽셀을 평균하게 되므로 시각적으로 부드러워짐
    // LIGHT_FRUSTUM_WIDTH는 원근 투영(Perspective Light)에서는 z(Depth)에 따라 선형적으로 커지지만,  [점광, 스포트라이트]
    // 직교 투영(Directional Light)에서는 일정하게 유지됨                                            [태양광]

    // UV 좌표공간 내에서의 Radius 길이 (정규화된 비율)
    float lightRadiusUV = lightRadiusWorld / LIGHT_FRUSTUM_WIDTH;
    
    float zReceiverView = N2V(zReceiverNdc, invProj);
    
    // STEP 1: blocker search
    float avgBlockerDepthView = 0;
    float numBlockers = 0;

    FindBlocker(avgBlockerDepthView, numBlockers, uv, zReceiverView, shadowMap, invProj, lightRadiusWorld);

    // FindBlocker에 의해 변경된 값으로 사용함
    if (numBlockers < 1)
    {
        // There are no occluders so early out(this saves filtering)
        return 1.0f;
    }
    else
    {
        // 내일 한번 다시보자
        // 조명의 크기에 따라 pnumbra 크기가 달라짐
        
        // STEP 2: penumbra size
        // penumbraRatio : penumbra의 상대적 길이
        float penumbraRatio = (zReceiverView - avgBlockerDepthView) / avgBlockerDepthView;
        
        // filterRadiusUV : Sampling 반경
        // near평면 위에서의 pnumbra의 길이
        float filterRadiusUV = penumbraRatio * lightRadiusUV * NEAR_PLANE / zReceiverView; 

        // STEP 3: filtering
        // filterRadiusUV가 클수록 샘플링 범위가 커짐
        return PCF_Filter(uv, zReceiverNdc, filterRadiusUV, shadowMap);
    }
}

float3 LightRadiance(Light light, float3 posWorld, float3 normalWorld, Texture2D shadowMap)
{
    // Directional light
    float3 lightVec = light.type & LIGHT_DIRECTIONAL
                      ? -light.direction
                      : light.position - posWorld;
        
    float lightDist = length(lightVec);
    lightVec /= lightDist;

    // Spot light
    float spotFator = light.type & LIGHT_SPOT
                     ? pow(max(-dot(lightVec, light.direction), 0.0f), light.spotPower)
                      : 1.0f;
        
    // Distance attenuation
    float att = saturate((light.fallOffEnd - lightDist)
                         / (light.fallOffEnd - light.fallOffStart));

    // Shadow map
    float shadowFactor = 1.0;

    if (light.type & LIGHT_SHADOW)
    {
        const float nearZ = 0.01; // 카메라 설정과 동일
        
        // 1. Project posWorld to light screen    
        float4 lightScreen = mul(float4(posWorld, 1.0), light.viewProj);
        lightScreen.xyz /= lightScreen.w;
        
        // 2. 카메라(광원)에서 볼 때의 텍스춰 좌표 계산
        float2 lightTexcoord = float2(lightScreen.x, -lightScreen.y);
        lightTexcoord += 1.0;
        lightTexcoord *= 0.5;
        
        // 3. 쉐도우맵에서 값 가져오기
        //float depth = shadowMap.Sample(shadowPointSampler, lightTexcoord).r;
        
        // 4. 가려져 있다면 그림자로 표시
        //if (depth + 0.001 < lightScreen.z)
          //  shadowFactor = 0.0;
        
        uint width, height, numMips;
        shadowMap.GetDimensions(0, width, height, numMips);
        
        // Texel size
        float dx = 5.0 / (float) width;
       // shadowFactor = PCF_Filter(lightTexcoord.xy, lightScreen.z - 0.001, dx, shadowMap);
        shadowFactor = PCSS(lightTexcoord, lightScreen.z - 0.01, shadowMap, light.invProj, light.radius);
    }

    float3 radiance = light.radiance * spotFator * att * shadowFactor;

    return radiance;
}

float3 LightRadiance(in Light light, in float3 posWorld, in float3 normalWorld)
{
    // Directional light
    float3 lightVec = light.type & LIGHT_DIRECTIONAL
                      ? -light.direction
                      : light.position - posWorld;
        
    float lightDist = length(lightVec);
    lightVec /= lightDist;

    // Spot light
    float spotFator = light.type & LIGHT_SPOT
                     ? pow(max(-dot(lightVec, light.direction), 0.0f), light.spotPower)
                      : 1.0f;
        
    // Distance attenuation
    float att = saturate((light.fallOffEnd - lightDist)
                         / (light.fallOffEnd - light.fallOffStart));

    // Shadow map
    float shadowFactor = 1.0;
    float3 radiance = light.radiance * spotFator * att * shadowFactor;

    return radiance;
}

PixelShaderOutput main(PixelShaderInput input)
{
    float3 pixelToEye = normalize(eyeWorld - input.posWorld);
    float3 normalWorld = GetNormal(input);
    
    float3 albedo = useAlbedoMap ? albedoTex.SampleLevel(linearWrapSampler, input.texcoord, lodBias).rgb * albedoFactor
                                 : albedoFactor;
    float ao = useAOMap ? aoTex.SampleLevel(linearWrapSampler, input.texcoord, lodBias).r : 1.0;
    float metallic = useMetallicMap ? metallicRoughnessTex.SampleLevel(linearWrapSampler, input.texcoord, lodBias).b * metallicFactor
                                    : metallicFactor;
    float roughness = useRoughnessMap ? metallicRoughnessTex.SampleLevel(linearWrapSampler, input.texcoord, lodBias).g * roughnessFactor
                                      : roughnessFactor;
    float3 emission = useEmissiveMap ? emissiveTex.SampleLevel(linearWrapSampler, input.texcoord, lodBias).rgb
                                     : emissionFactor;

    float3 ambientLighting = AmbientLightingByIBL(albedo, normalWorld, pixelToEye, ao, metallic, roughness) * strengthIBL;
    
    float3 directLighting = float3(0, 0, 0);

    // 임시로 unroll 사용
    [unroll] // warning X3550: sampler array index must be a literal expression, forcing loop to unroll
    for (int i = 0; i < MAX_LIGHTS; ++i)
    {
        if (lights[i].type)
        {
            float3 lightVec = lights[i].position - input.posWorld;
            float lightDist = length(lightVec);
            lightVec /= lightDist;
            float3 halfway = normalize(pixelToEye + lightVec);
        
            float NdotI = max(0.0, dot(normalWorld, lightVec));
            float NdotH = max(0.0, dot(normalWorld, halfway));
            float NdotO = max(0.0, dot(normalWorld, pixelToEye));
        
            const float3 Fdielectric = 0.04; // 비금속(Dielectric) 재질의 F0
            float3 F0 = lerp(Fdielectric, albedo, metallic);
            float3 F = SchlickFresnel(F0, max(0.0, dot(halfway, pixelToEye)));
            float3 kd = lerp(float3(1, 1, 1) - F, float3(0, 0, 0), metallic);
            float3 diffuseBRDF = kd * albedo;

            float D = NdfGGX(NdotH, roughness);
            float3 G = SchlickGGX(NdotI, NdotO, roughness);
            float3 specularBRDF = (F * D * G) / max(1e-5, 4.0 * NdotI * NdotO);

            float3 radiance = 0.0f;
            
            radiance = LightRadiance(lights[i], input.posWorld, normalWorld, shadowMaps[i]);
            
            /*if (i == 0)
                radiance = LightRadiance(lights[i], input.posWorld, normalWorld, shadowMap0);
            if (i == 1)
                radiance = LightRadiance(lights[i], input.posWorld, normalWorld, shadowMap1);
            if (i == 2)
                radiance = LightRadiance(lights[i], input.posWorld, normalWorld, shadowMap2);*/
                
            directLighting += (diffuseBRDF + specularBRDF) * radiance * NdotI;
        }
    }
    
    PixelShaderOutput output;
    output.pixelColor = float4(ambientLighting + directLighting + emission, 1.0);
    output.pixelColor = clamp(output.pixelColor, 0.0, 1000.0);
    
    return output;
}
