#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

// 참고자료
// https://github.com/Nadrin/PBR/blob/master/data/shaders/hlsl/pbr.hlsl

// Enviroment Texture
TextureCube specularIBLTex : register(t0); // Specular 연산용 환경광(IBL) 텍스쳐
TextureCube irradianceIBLTex : register(t1); // Diffuse 연산용 환경광(IBL) 텍스쳐
Texture2D brdfTex : register(t2); // BRDF의 연산에 필요한 A,B 값을 미리 연산하여 저장해둔 텍스쳐

// Object Texture
Texture2D albedoTex : register(t3);
Texture2D normalTex : register(t4);
Texture2D aoTex : register(t5);
Texture2D metallicTex : register(t6);
Texture2D roughnessTex : register(t7);

// Sampler
SamplerState linearSampler : register(s0); //
SamplerState clampSampler : register(s1); // 가장자리의 값을 샘플링. BRDF를 사용할 때는 정확한 값을 가져와야하기 때문에 clamp를 사용함

static const float3 Fdielectric = 0.04; // 비금속(Dielectric) 재질의 F0 (최소값)
static const float PI = 3.141592;

cbuffer BasicPixelConstData : register(b0)
{
    float3 eyeWorld;
    float mipmapLevel;
    Material material;
    Light light[MAX_LIGHTS];
    int useAlbedoMap;
    int useNormalMap;
    int useAOMap; // Ambient Occlusion
    int invertNormalMapY;
    int useMetallicMap;
    int useRoughnessMap;
    float exposure;
    float gamma;
};

float3 SchlickFresnel(float3 F0, float NdotV)
{
    // Fresnel : Specular 에너지 비율 연산식
    // satuate : clamp[0, 1]
    float fc = pow(1.0 - saturate(NdotV), 5.0);
    return F0 + (1 - F0) * fc;
}

struct PixelShaderOutput
{
    float4 pixelColor : SV_Target0;
};

float3 GetNormal(PixelShaderInput input)
{
    float3 normalWorld = input.normalWorld;
    
    if (useNormalMap) // NormalWorld를 교체
    {
        float3 normal = normalTex.SampleLevel(linearSampler, input.texcoord, 0.0).rgb;
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

// Diffuse : 물체의 고유 색을 정의 (재질의 색)
// “표면이 투사된 빛을 받아, 표면 고유의 색상 비율로 반사해 내보내는 것”
float3 DiffuseIBL(float3 albedo, float3 normalWorld, float3 pixelToEye, float metallic)
{
    // Fresnel [동적 반사율]
    // - 정의 : 빛이 표면에 부딪혔을 때 표면에서 반사되는 비율(Specular 반사율)
    // - 물리적 의미 : 빛은 표면에 닿을 때 전체 에너지 1.0이 두 경로로 나뉩
    //      - 반사된 빛 (Specular) → 비율: F
    //      - 내부로 들어간 빛 (Diffuse) → 비율: (1 - F)
    //      - 즉, Fresnel은 입사된 에너지의 보존을 구현하기 위해 연산되는 값이며, 더 정확히는
    //      - [Fresnel] 은 표면 근처에서 바로 반사되는(specular) 에너지비율, 
    //      - [1 - Fresnel] 은 내부로 흡수되어 확산되는(diffuse) 에너지비율.
    
    // F0 [기준 반사율]
    // - 빛이 표면에 정면(0°) 으로 입사할 때 반사되는 비율 (정면 반사율, base reflectivity)
    // - F₀를 기준으로 입사각이 커질수록 동적반사율이 점점커지게 됨 [ F(θ) = F₀ ​+ pow((1−F₀​) * (1−cosθ), 5.0) ]
    // - 정면으로 입사할 경우 빛의 진행 방향이 표면 법선과 일치하므로, 대부분의 빛이 내부를 통과하게 되므로, 반사되는 비율이 가장 낮음.
    // - 반대로 측면으로 입사하는 각이 커질수록 빛의 진행 방향과 표면 법선과의 방향과 유사성이 떨어지게 되므로, 내부로 들어가기 힘들어져 반사되는 비율이 늘어남.
    
    // Albedo [RGB 채널별 반사율(빛의 파장별 반사 비율)]
    // ‘표면에서 반사되어 나오는 빛의 비율(반사율)’을 색상별로 표현한 값
    
    // F0 를 구하는 이유 : 
    // 해당 재질의 각 색상별 반사의 [기본]비율 metallic을 반영해서 구하기 위함 
    // (metallic이 높을수록 해당 색상을 albedo에 설정한 값 그대로 반사할 확률이 높음)
    float3 F0 = lerp(Fdielectric, albedo, metallic);
    
    // F 를 구하는 이유 :
    // 입반사 방향에 따라 달라지는 반사율을 구하기 위함
    float3 F = SchlickFresnel(F0, max(0.0, dot(normalWorld, pixelToEye)));
    
    // lerp(A, B, x) = A * (1.0 - x) + B * x
    // metallic 값에 따라 diffuse와 specular의 비율이 정해짐
    // 즉, metallic 값의 존재가 diffuse와 specular의 표현을 주어진 빛 에너지 내에서 구현하도록 한 것 (두 값이 연동되어 있음)
    
    // kd를 구하는 이유와 해당 형태를 가지게 된 이유
    // 1. 금속과 비금속은 이원적(binary)이고, metallic은 금속/비금속을 구분하는 성질이기 때문에 금속일 때 Diffuse 항이 아에 사라져야함 (kd == 0.0)
    // 2. 금속(metallic == 1.0)과 비금속(metallic == 0.0) 일때는 에너지 보존이 됨
    
    // Q. F와 (1 - F)면 충분히 표현 가능하지 않나? 
    // A. 불가능. 금속이여도 F값이 0.0이 아니기 때문에(0.1 ~ 0.02) 이원적이 될 수가 없음
    
    // Q. 0.0 < metallic < 1.0 일 때는 에너지 보존이 안되는 것 아닌가?
    // A. 맞음. 에너지 보존이 되지 않음. (ex. metallic == 0.5 일 경우, 에너지는 0.52배)
    // 그러나 시각적 자연스러움과 효율성을 위한 물리적 사실성을 지키는 선에서 일부 타협한 것이라 생각하면 됨
    
    // Q. 뭘 위해서?
    // 현실의 표면들은 대부분 금속과 비금속이 복합적으로 존재하고 있는 복합 재질(mixed Material)
    // ex. 자동차 외장 (알루미늄  금속 + 페인트 + 코팅 + 먼지) / 석재 장식(비금속 + 일부 금속) / 기계부품 (금속 + 플라스틱 + 녹)
    // 이러한 복합 재질을 하나하나 분리해서 구현하는 것이 아닌 하나의 텍스쳐로 잡고 금속과 비금속의 성질을 블랜딩하여 시각적 연속성과 자연스러움을 구현한 것
    // 해당 방식을 통해 완전비금속, 복합재질, 완전금속을 같은 파라미터로 구현이 가능하게 하며, 물리적 구조 분리 없이 연속적으로 표현가능하게 됨
    // ex. 페인트된 철 표면
    // [페인트층]
    // BaseColor    : (0.8, 0.1, 0.1)
    // Roughness    : 0.5
    // Metallic     : 0.0
    // 
    // [벗겨진 금속]
    // BaseColor    : (0.7, 0.6, 0.5)
    // Roughness    : 0.2
    // Metallic     : 1.0
    // 
    // [녹슨 영역]
    // BaseColor    : (0.6, 0.25, 0.1)
    // Roughness    : 0.7
    // Metallic     : 0.3
    float3 kd = lerp(1.0 - F, 0.0, metallic);
    
    // Normal 방향으로 샘플링
    float3 irradiance = irradianceIBLTex.Sample(linearSampler, normalWorld).rgb;
    
    // return irradiance * kd * albedo / PI;
    return irradiance * kd * albedo;
}

// Specular : 빛이 반사되어 보이는 하이라이트/환경 반사 (빛의 반사 표현)
// “Specular는 투사되는 환경광이 표면에서 어떻게 반사되어 보일지를 결정하는 것”
float3 SpecularIBL(float3 albedo, float3 normalWorld, float3 pixelToEye, float metallic, float roughness)
{
    // Environment BRDF
    
    // [Look Up Table]
    // LUT : 이미지가 아니라 데이터가 저장된 2차원 표
    // 가로축 : NdotV
    // 세로축 : roughness
    // IBL Baker가 만들어준 BRDF 텍스쳐를 사용할때는 Roughness를 [1 - Roughness] 값을 사용해야함 (뒤집혀있음)
    float NdotV = dot(normalWorld, pixelToEye);
    // clampSampler 가 아닐경우 끝 부분에서 이상해보임 (linerSampler의 경우 반대쪽의 값을 가져와서 깜빡임이 발생함)
    float2 specularBRDF = brdfTex.Sample(clampSampler, float2(NdotV, 1 - roughness)).rg;
    
    // roughness : 높아지면 표면이 거칠어지면 스페큘러가 뭉개지면서 부드럽게 나타남
    // SampleLevel에서 roughness가 높아지게 되면 Level값이 올라가 해상도가 낮은 Mipmap 텍스쳐가 선택됨
    // float3 vec_Light = 2 * NdotV * normalWorld - pixelToEye;
    float3 specularIrradiance = specularIBLTex.SampleLevel(linearSampler,
                                                           reflect(-pixelToEye, normalWorld), roughness * 10.0).rgb;
    
    // Dielectric : 비금속(Fdielectric)의 기본 반사율
    const float3 Fdielectric = 0.04;
    float3 F0 = lerp(Fdielectric, albedo, metallic);
    
    float LUT = F0 * specularBRDF.x + specularBRDF.y;

    return specularIrradiance * LUT;
}

// 환경광(Ambient) 계산
float3 AmbientLightingByIBL(float3 albedo, float3 normalW, float3 pixelToEye, float ao,
                            float metallic, float roughness)
{
    float3 diffuseIBL = DiffuseIBL(albedo, normalW, pixelToEye, metallic);
    float3 specularIBL = SpecularIBL(albedo, normalW, pixelToEye, metallic, roughness);
    
    // IBL를 기반으로 한 AmbientLight에만 곱해주고 있음
    // 손전등 같은 것으로 비추면 구석진 곳도 밝아져야하기 때문
    return (diffuseIBL + specularIBL) * ao;
}

// GGX/Towbridge-Reitz normal distribution function.
// Uses Disney's reparametrization of alpha = roughness^2.
float NdfGGX(float NdotH, float roughness)
{
    float alpha = roughness * roughness;
    float alphaSq = alpha * alpha;
    float dneom = max(1e-5, (NdotH * NdotH) * (alphaSq - 1.0) + 1.0);
    float ndf = alphaSq / (PI * dneom * dneom);
    
    return ndf;
}

float SchlickG1(float NdotX, float k)
{
    return NdotX / (NdotX * (1 - k) + k);
}

// TODO: 방정식 (4)
float SchlickGGX(float NdotL, float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    
    float geo = SchlickG1(NdotL, k) * SchlickG1(NdotV, k);
    
    return geo;
}

// Diffuse, Specular, light 모두 분리시켜서 렌더링해보기
PixelShaderOutput main(PixelShaderInput input)
{
    float3 pixelToEye = normalize(eyeWorld - input.posWorld);
    float3 normalWorld = GetNormal(input);

    // Object Texture
    // 픽셀단위로 해당 texcoord에 매핑되는 샘플갑을 가져옴
    float3 albedo = useAlbedoMap ? albedoTex.Sample(linearSampler, input.texcoord).rgb 
                                 : material.albedo;
    
    float ao = useAOMap ? aoTex.SampleLevel(linearSampler, input.texcoord, 0.0).r 
                        : 1.0;
    
    float metallic = useMetallicMap ? metallicTex.Sample(linearSampler, input.texcoord).r 
                                    : material.metallic;
    
    float roughness = useRoughnessMap ? roughnessTex.Sample(linearSampler, input.texcoord).r 
                                      : material.roughness;

    float3 ambientLighting = AmbientLightingByIBL(albedo, normalWorld, pixelToEye, ao,
                                                  metallic, roughness);

    float3 directLighting = float3(0, 0, 0);

    // Analytical Light Source
    // 분석적 광원 / 수학적 광원 : 이미지가 아닌 데이터를 기반으로 구현되는 광원
    // 포인트 라이트만 먼저 구현
    [unroll]
    for (int i = NUM_DIR_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; ++i)
    {
        float3 lightVec = light[i].position - input.posWorld;
        float3 halfway = normalize(pixelToEye + lightVec);
        
        float NdotL = max(0.0, dot(normalWorld, lightVec));
        float NdotH = max(0.0, dot(normalWorld, halfway));
        float NdotV = max(0.0, dot(normalWorld, pixelToEye));
        
        const float3 Fdielectric = 0.04; // 비금속(Dielectric) 재질의 F0
        float3 F0 = lerp(Fdielectric, albedo, metallic);
        float3 F = SchlickFresnel(F0, max(0.0, dot(halfway, pixelToEye)));
        float3 kd = lerp(float3(1, 1, 1) - F, float3(0, 0, 0), metallic);
        float3 diffuseBRDF = kd * albedo;

        float D = NdfGGX(NdotH, roughness);
        float3 G = SchlickGGX(NdotL, NdotV, roughness);
        
        // 방정식 (2), 0으로 나누기 방지
        float3 specularBRDF = (F * D * G) / max(1e-5, 4.0 * NdotL * NdotV);
        
        // 거리에 따라서 달라짐
        float3 radiance = light[i].radiance * saturate((light[i].fallOffEnd - length(lightVec)) / (light[i].fallOffEnd - light[i].fallOffStart));

        // diffuse + specular
        directLighting += (diffuseBRDF + specularBRDF) * radiance * NdotL;
    }
    
    PixelShaderOutput output;
    // IBL 기반으로 쉐이딩된 값이 ambientLighting
    // pointLight 값을 기반으로 계산한 것이 directLighting
    output.pixelColor = float4(ambientLighting + directLighting, 1.0);
    output.pixelColor = clamp(output.pixelColor, 0.0, 1000.0);
    
    return output;
}
