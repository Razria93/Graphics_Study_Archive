#include "Common.hlsli"

cbuffer VertexConstantBuffer : register(b0) { matrix viewProj; };

struct CubeMappingPixelShaderInput 
    {
    float4 posProj : SV_POSITION;
    float3 posModel : POSITION;
    float2 texcoord : TEXCOORD0;
    float3 indexColor : INDEXCOLOR;
};

CubeMappingPixelShaderInput main(VertexShaderInput input) {

    CubeMappingPixelShaderInput output;
    output.posModel = input.posModel;
    output.posProj = mul(float4(input.posModel, 1.0f), viewProj);
    output.texcoord = input.texcoord; // 근데 텍스쳐 코드가 없는데.. 아 큐브맵 매핑
    output.indexColor = input.indexColor;
    
    return output;
}
