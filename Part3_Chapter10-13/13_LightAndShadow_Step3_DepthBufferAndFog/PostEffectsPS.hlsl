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

    // DepthMap.z와 NDC.z는 같은 비선형 깊이 값
    // 엄밀히 말하면 ScreenSpace에서 작성된 DepthMap과 NDC에서 작성된 값은 동일하다 볼 순 없으나 z값은 동일함
    // 그러나 DepthMap을 사용하는 결정적인 이유는 프리미티브 단위의 데이터만 알 수 있는 렌더링 파이프라인의 한계를 극복하기 위한 것
    // 즉, 실시간으로 병렬처리 되고 있는 수많은 파이프라인이 공유하고 사용하는 공유메모리 라는 것
    
    // ScreenSpace -> NDC(Normalized Device Coordinates)
    // [0, 1]x[0, 1] -> [-1, 1]x[-1, 1]
    posProj.xy = texcoord * 2.0 - 1.0;
    posProj.y *= -1; // 주의: y 방향을 뒤집어줘야 합니다.
    
    // NDC + Depth -> Homogeneous Clip Space (동차 좌표 공간)
    posProj.z = depthOnlyTex.Sample(linearClampSampler, texcoord).r;
    posProj.w = 1.0;

    // ProjectSpace -> ViewSpace
    float4 posView = mul(posProj, invProj);
    
    // 동차로 나눔
    posView.xyz /= posView.w;
    
    return posView;
}

float4 main(SamplingPixelShaderInput input) : SV_TARGET
{
    if (mode == 1)
    {
        // TODO: Fog
        float3 fogColor = float3(1, 1, 1);
        float fogMin = 0.0;
        float fogMax = 5.0;
 
        // posView 해당 픽셀이 렌더링하고 있는 텍스쳐의 물리적 위치
        // dist는 그 위치까지의 거리
        float4 posView = TexcoordToView(input.texcoord);
        float dist = length(posView.xyz); // 눈의 위치가 원점인 좌표계
        float distFog = saturate((dist - fogMin) / (fogMax - fogMin));
        float3 renderColor = renderTex.Sample(linearClampSampler, input.texcoord).rgb;
        
        renderColor = lerp(renderColor, fogColor, distFog);
        
        return float4(renderColor, 1.0);
    }
    else // if (mode == 2)
    {
        // 여기서 z값은 view좌표계의 Z값
        float z = TexcoordToView(input.texcoord).z * depthScale;
        return float4(z, z, z, 1);
    }
}
