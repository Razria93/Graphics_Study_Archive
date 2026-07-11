#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

TextureCube g_diffuseCube : register(t0);
TextureCube g_specularCube : register(t1);

Texture2D g_albedoTexture : register(t2);
Texture2D g_normalTexture : register(t3); // HERE : 텍스쳐가 2개 늘어남
Texture2D g_aoTexture : register(t4); // HERE : 텍스쳐가 2개 늘어남 (Ambient Occlution)

SamplerState g_sampler : register(s0);

cbuffer BasicPixelConstantData : register(b0)
{
    float3 eyeWorld;
    float mipmapLevel;
    Material material;
    Light light[MAX_LIGHTS];
    float4 indexColor; // 피킹(Picking)에 사용
    int useAlbedoTexture;
    int useNormalMap;
    int useAOMap; // Ambient Occlusion
    int dummy;
};

// Schlick approximation: Eq. 9.17 in "Real-Time Rendering 4th Ed."
// fresnelR0는 물질의 고유 성질
// Water : (0.02, 0.02, 0.02)
// Glass : (0.08, 0.08, 0.08)
// Plastic : (0.05, 0.05, 0.05)
// Gold: (1.0, 0.71, 0.29)
// Silver: (0.95, 0.93, 0.88)
// Copper: (0.95, 0.64, 0.54)
float3 SchlickFresnel(float3 fresnelR0, float3 normal, float3 toEye)
{
    // 참고 자료들
    // THE SCHLICK FRESNEL APPROXIMATION by Zander Majercik, NVIDIA
    // http://psgraphics.blogspot.com/2020/03/fresnel-equations-schlick-approximation.html

    float normalDotView = saturate(dot(normal, toEye));

    float f0 = 1.0f - normalDotView; // 90도이면 f0 = 1, 0도이면 f0 = 0

    // 1.0 보다 작은 값은 여러 번 곱하면 더 작은 값이 됩니다.
    // 0도 -> f0 = 0 -> fresnelR0 반환
    // 90도 -> f0 = 1.0 -> float3(1.0) 반환
    // 0도에 가까운 가장자리는 Specular 색상, 90도에 가까운 안쪽은 고유
    // 색상(fresnelR0)
    return fresnelR0 + (1.0f - fresnelR0) * pow(f0, 5.0);
}

struct PixelShaderOutput
{
    float4 pixelColor : SV_Target0;
    float4 indexColor : SV_Target1;
};

PixelShaderOutput main(PixelShaderInput input)
{
    float3 toEye = normalize(eyeWorld - input.posWorld);

    float3 color = float3(0.0, 0.0, 0.0);

    int i = 0;

    float3 normalWorld = input.normalWorld;
    
    if (useNormalMap) // NormalWorld를 교체
    {
        float3 normalTex = g_normalTexture.SampleLevel(g_sampler, input.texcoord, 0.0).rgb;
        normalTex = 2.0 * normalTex - 1.0; // 범위 조절 [-1.0, 1.0]
        // UNORM : Unsigned Integer 형식 (0 ~ 255)를 0.0 ~ 1.0 의 floatPoint로 변환해서 사용함
        // 해당 방식은 각 요소 값이 0.0 ~ 1.0 까지라 음수가 없어 360도 노멀방향을 표현할 수 없음
        // 그래서 샘플링한 값에 2배를 해서 -1.0을 하면 범위가 [-1.0, 1.0] 이 됨
        // 이렇게 변환된 값을 노멀로 사용하자는 약속이 되어 있음
        // 이미 정의가 되어 있는 것들은 텍스쳐 좌표계에 맞춰서 정의를 해둔 것
        
        // 이때 텍스쳐 좌표계의 XYZ(TBN)가 모델에 붙을 때 어떤 방향으로 좌표계변환이 되는지 알면 텍스쳐 좌표계에 있는 노멀 벡터도 머델에 맞춰서 변환 가능

        // 반지름이 0.3이고 원점이 (0.5, 0.5, 0.3)인 구의 normal만 이용해서 렌더링 해보기
        // x가 u이고 y가 v라면 z는 sqrt(0.3*0.3 - x*x - y*y)
        // z의 방향 주의
        
        // 텍스쳐 좌표계의 tangent, bi-tangent, normal방향이 월드에서 어떤 방향과 매칭되는지를 정의
        // 여기서는 벡터 변환용이라 Translation이 필요가 없어서 3x3
        // 이를 기반으로 텍스쳐에서 얻은 노멀을 변환하면 됨
        // 텍스쳐에서 (1.0, 0.0, 0.0) 은 (1.0, 0.0, 0.0);
        // 텍스쳐에서 (0.0, 1.0, 0.0) 은 (0.0, -1.0, 0.0);
        // 텍스쳐에서 (0.0, 0.0, 1.0) 은 (0.0, 0.0, -1.0);
        float3 T = float3(1.0, 0.0, 0.0);
        float3 B = float3(0.0, -1.0, 0.0);
        float3 N = float3(0.0, 0.0, -1.0);
        
        float3x3 TBN = float3x3(T, B, N);
        normalWorld = normalize(mul(normalTex, TBN));
        
        // 3개의 벡터를 기반으로 변환행렬을 만들어야함
        // DX는 표준 기저 벡터를 각각 변환해서 행단위로 행렬에 기입함 (여기서는 TBN 순) Row Major
        // | T_x T_y T_z |
        // | B_x B_y B_z |   
        // | N_x N_y N_z |  
        {
        // float3 center = float3(0.5f, 0.5f, 0.3f);                                       // 1) 구의 중심을 텍스쳐좌표계 관점에서 정의
        // float2 point_fromCenter = input.texcoord - center.xy;                           // 2) texcoord를 center 기준으로 해석하거나 
        //                                                                                 //    texcoord값에서 center값을 뺌으로서 원점을 기준으로 연산한다는 의도로 해석해도 됨
        // float dist_Square_PfromC = dot(point_fromCenter, point_fromCenter);             // 
        // if (dist_Square_PfromC < 0.3 * 0.3)                                             // 3) 단면 원 내부인지 판단
        // {
        //     float z = sqrt(0.3 * 0.3 - dist_Square_PfromC);                             // 4) 원점기준 z값이 어떻게 되는지 연산
        //     float3 pointLocation = float3(point_fromCenter.x, -point_fromCenter.y, -z); // 5) y값에 -가 붙은 이유 : 빛과의 상호작용을 계산하는건 월드기준임
        //                                                                                 //    그런데 현재 연산한 내용은 모두 텍스쳐 좌표계 위에서 계산한 내용이므로 y축이 반전이 되어 있다는 점을 반영하여
        //                                                                                 //    해당 좌표의 위치를 월드기준으로 변환한 것 (같은 위치여도 y축의 양수방향이 바뀌면 값이 달라짐. 정확히는 부호가 반전이 됨)
        //                                                                                 //    z값에 -가 붙은 이유 : 위와 마찬가지임.
        //                                                                                 //    텍스쳐 좌표는 오른쪽이 +u, 아래쪽이 +v 이고 이를 왼손좌표계를 기반으로 w 방향을 구하면 화면을 뚫고 나오는 방향임
        //                                                                                 //    따라서 월드 기준으로 해석할 수 있게 변환할 때 부호를 붙이는 것
        //                                                                                 //    결과적으로 텍스쳐좌표계 -> 월드좌표계로 변환한 것임
        //     normalWorld = normalize(pointLocation);
        // }
        // else
        // {
        //     normalWorld = float3(0, 0, -1);
        // }
        //
        // 근데 이건 표현을 위한 예제인거고
        // 실질적으로 노멀맵은 TBN 공간에서 기록되며, 이는 각 픽셀마다 그 픽셀의 지점이 0,0,0 이라는 가정하에 벡터의 방향요소를 RGB 값으로 기록한것임
        // 그렇기 때문에 0,0,0 기준의 TBN 공간에서 Y값의 방향이 GL과 DX가 반대이기 때문에 상호간의 노멀맵을 사용하기 위해서는 값을 뒤집어줘야함
        // TBN 공간이 텍스쳐좌표계의 Y방향과 일치시키고자 Y방향은 서로 다르지만 X방향과 매시의 정면부분이 N의 양수라는 것은 환경 상관없이 똑같음
        //
        // 이번 예제를 굳이 해석하자면 픽셀단위로도 노말을 가질 수 있다는 것
        // 그리고 그 노멀은 구(Sphere)일 경우 Point - Center 방향의 정규화 값이므로 사실상 center가 원점일 경우 point값의 정규화 값이 노멀 방향이라는 것
        // 그런데 우리가 Square 위에 구의 노멀을 구하기 위해 사용한 값이 texcoord 이고, 해당 값은 Square의 좌상단이 0,0 우하단이 1,1 인 텍스쳐 좌표계 에서의 값이라,
        // Y와 Z의 양수방향이 월드에서의 양수방향과 반대임
        // 따라서 월드에 있는 조명과 상호작용하기 위해 [방향은 유지하고 그 방향에 맞는 값으로 변환]한 것이며, 그 값은 Y와 Z값의 부호가 반대로 된 값임
        // 다만 이는 샘플링된 대상이 회전 스케일 변환이 되지 않은 것을 근거로 하여 부호만 반대로 달아준 것이기 때문에 회전과 스케일까지 고려하려면 해당 노멀값에 모델행렬의 invpose를 적용시켜야함
        }
    }
    
    // 이제 위 연산에서 구한 노멀맵 기반의 노멀을 가지고 연산을 다함
    // 버텍스 쉐이더로 구한 노멀을 사용하지 않음
    // 이 뜻은 버텍스에서 가져와 보간한 노멀을 사용하지 않는다는 것이며 즉 Geometry의 노멀을 사용하지 않는다는 것임
    // 텍스쳐에서 지정한 픽셀단위의 노멀값을 기반으로 해당 픽셀에 맞는 노멀값을 가지게 됨
    // 이렇게 될 경우 픽셀 단위의 상세도가 적용됨
    [unroll] 
    for (i = 0; i < NUM_DIR_LIGHTS; ++i)
    {
        color += ComputeDirectionalLight(light[i], material, normalWorld,
                                         toEye);
    }

    [unroll]
    for (i = NUM_DIR_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS;
                  ++i)
    {
        color += ComputePointLight(light[i], material, input.posWorld,
                                   normalWorld, toEye);
    }

    [unroll]
    for (i = NUM_DIR_LIGHTS + NUM_POINT_LIGHTS;
                  i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS + NUM_SPOT_LIGHTS;
                  ++i)
    {
        color += ComputeSpotLight(light[i], material, input.posWorld,
                                  normalWorld, toEye);
    }

    // 쉽게 이해할 수 있는 간단한 구현입니다.
    // IBL과 다른 쉐이딩 기법(예: 퐁 쉐이딩)을 같이 사용할 수도 있습니다.

    // IBL (Image Based Lighting) 에 PointLight에 의해 결정되는 색상값을 반영하기 위해 color값을 더함
    // IBL : 
    // 가장 단순한 IBL: 월드 노멀 N을 방향으로 해서 환경맵(cubemap) 을 샘플 → “노멀 방향에서 들어오는 평균 빛”처럼 쓰는 ambient/sky 느낌.
    // PBR 에서는 이중으로 함
    
    float4 diffuse = g_diffuseCube.Sample(g_sampler, normalWorld) + float4(color, 1.0);
    float4 specular =
        g_specularCube.Sample(g_sampler, reflect(-toEye, normalWorld));

    diffuse *= float4(material.diffuse, 1.0);
    specular *=
        pow(abs(specular.r + specular.g + specular.b) / 3.0, material.shininess);
    specular *= float4(material.specular, 1.0);

    // 참고: https://www.shadertoy.com/view/lscBW4
    float3 f = SchlickFresnel(material.fresnelR0, normalWorld, toEye);
    specular.xyz *= f;

    float dist = length(eyeWorld - input.posWorld);
    float distMin = 5.0;
    float distMax = 20.0;
    float lod = 10.0 * saturate(dist / (distMax - distMin));
    
    if (useAlbedoTexture)
    {
        //diffuse *= g_albedoTexture.SampleLevel(g_sampler, input.texcoord, lod);
        // 이번 예제에서는 가장 높은 해상도 사용
        diffuse *= g_albedoTexture.SampleLevel(g_sampler, input.texcoord, 0.0);
    }
    
    // 참고 https://github.com/microsoft/DirectXTK/blob/main/Src/Shaders/PBRCommon.fxh#L132
    if (useAOMap)
        diffuse *= g_aoTexture.SampleLevel(g_sampler, input.texcoord, lod);

    PixelShaderOutput output;
    output.pixelColor = diffuse + specular;
    output.indexColor = indexColor;
    
    return output;
}
