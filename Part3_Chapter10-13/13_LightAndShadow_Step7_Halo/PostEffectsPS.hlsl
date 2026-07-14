#include "Common.hlsli" 

// t20에서부터 시작
Texture2D renderTex : register(t20); // Rendering results
Texture2D depthOnlyTex : register(t21); // DepthOnly

cbuffer PostEffectsConstants : register(b3)
{
    int mode; // 1: Rendered image, 2: DepthOnly
    float depthScale;
    float fogStrength;
};

struct SamplingPixelShaderInput
{
    float4 posProj : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

float4 TexcoordToView(float2 texcoord)
{
    float4 posProj;

    // ScreenSpace 라는 2차원 좌표계로 압축된 데이터를 가지고 3차원으로 되돌리는 함수
    // DepthMap 필요함
    
    // 이전
    // 0. 과거에는 모든 오브젝트의 픽셀을 3차원적으로 직접 계산
    //  - 각 오브젝트마다 조명 계산 수행
    //  - 뷰에 보이지 않는 영역도 (Z Test 전까지) 셰이더 실행
    //  - 조명, 반사, 그림자 등 대부분을 World Space 기준으로 연산
    
    // 현재
    // 1. 요즘 렌더링은 모든 공간을 처음부터 3D로 계산하지 않음
    // 2. 먼저 기본 렌더링으로 Depth, Normal 등 최소한의 데이터를 확보 (2차원 데이터의 형태로 여러개)
    // 3. 확보한 2차원 데이터들을 기반으로 보이는 표면만 3차원적으로 복원
    // 4. 해당 값을 기반으로 추가적인 광학 효과나 디테일 향상을 수행
    
    // [0, 1]x[0, 1] -> [-1, 1]x[-1, 1]
    posProj.xy = texcoord * 2.0 - 1.0;
    posProj.y *= -1; // y 좌표 뒤집기
    posProj.z = depthOnlyTex.Sample(linearClampSampler, texcoord).r;
    posProj.w = 1.0;
    
    // ProjectSpace -> ViewSpace
    //float4 posView = mul(posProj, lights[0].invProj);
    float4 posView = mul(posProj, invProj);
    posView.xyz /= posView.w;
    
    return posView;
}

// 충돌 유무 판단 함수
int RaySphereIntersection(in float3 start, in float3 dir, in float3 center, in float radius,
                            out float t1, out float t2)
{
    float3 p = start - center;
    float pdotv = dot(p, dir);
    float p2 = dot(p, p);
    float r2 = radius * radius;
    float m = pdotv * pdotv - (p2 - r2);
    
    if (m < 0.0)
    {
        t1 = 0;
        t2 = 0;
        return 0;
    }
    else
    {
        m = sqrt(m);
        t1 = -pdotv - m;
        t2 = -pdotv + m;
        return 1;
    }
}

// "Foundations of Game Engine Development" by Eric Lengyel, V2 p319
float HaloEmission(float3 posView, float radius)
{
    // posView : 렌더링 픽셀 위치
    // light[1].position : 헤일로 중심 위치
    
    // Halo
    // float3 rayStart = float3(0, 0, 0); // View space
    float3 rayStart = mul(float4(eyeWorld, 1.0), view).xyz;
    
    // 시점에서 렌더링 포인트 방향으로 색상탐색하는 방식
    float3 dir = normalize(posView - rayStart);

    // view 공간에서의 조명의 위치를 계산해야함
    float3 center = mul(float4(lights[1].position, 1.0), view).xyz; // View 공간으로 변환

    float t1 = 0.0;
    float t2 = 0.0;
    
    // Halo(광원)의 위치가 물체보다 뒤쪽에 있다면 반영하면 안됨. 이는 Depth 가지고 구현할 수 있음.
    if (RaySphereIntersection(rayStart, dir, center, radius, t1, t2))
    {
        // t1, t2 음수판정을 하지 않으면, 뒤쪽에서 hit 되었음에도 전면에 헤일로를 렌더링하는 버그가 발생하게 됨
        if (t2 < 0.0)
            return 0.0;
        
        if (t1 < 0.0)
            t1 = 0.0;
        
        if (posView.z < t1)
            return 0.0;
        
        if (posView.z < t2)
            t2 = posView.z;
        
        // 고려하지 못한 부분_1
        // point는 center로부터 시작됨
        float3 p = rayStart - center;
        
        float p2 = dot(p, p);
        float pdotv = dot(p, dir);
        float d2 = dot(dir, dir); // dir이 유닛벡터이기 때문에 사실상 1.0임
        float r2 = radius * radius;
        float inv_r2 = 1.0 / r2;
        
        float emission = (1.0 - p2 * inv_r2) * (t2 - t1)
                        - pdotv * inv_r2 * (t2 * t2 - t1 * t1)
                        - d2 / (3.0 * r2) * (t2 * t2 * t2 - t1 * t1 * t1);
        
        // 구의 반경에 상관없이 전체적인 에너지를 보존하기 위해 구의 부피를 기반으로 보정한 상수
        // 에너지 보존을 정확하게 구현한 것은 아니나, 단일 구 내에서는 부피에 상관없이 에너지가 보존됨
        // 물리기반 보정계수 : 1/R³ 
        // 부피기반 보정계수 : 4R³/3
        // 경험기반 보정계수 : 4R/3
        emission /= (4.0 * radius / 3.0);
        
        return emission;
    }
    else
    {
        return 0.0;
    }
}

float4 main(SamplingPixelShaderInput input) : SV_TARGET
{
    if (mode == 1)
    {
        float3 color = clamp(renderTex.Sample(linearClampSampler, input.texcoord).rgb, 0, 1);
        
        float4 posView = TexcoordToView(input.texcoord);

        // Halo
        float3 haloColor = float3(0.96, 0.94, 0.82);
        float radius = lights[1].haloRadius;
        color += HaloEmission(posView.xyz, radius) * haloColor * lights[1].haloStrength;

        // Fog
        float dist = length(posView.xyz); // 눈의 위치가 원점인 좌표계
        float3 fogColor = float3(1, 1, 1);
        float fogMin = 1.0;
        float fogMax = 10.0;
        float distFog = saturate((dist - fogMin) / (fogMax - fogMin));
        float fogFactor = exp(-distFog * fogStrength);

        color = lerp(fogColor, color, fogFactor);
        
        return float4(color, 1.0);
    }
    else // if (mode == 2)
    {
        float z = TexcoordToView(input.texcoord).z * depthScale;
        return float4(z, z, z, 1);
    }
}
