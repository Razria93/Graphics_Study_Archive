#include "Common.hlsli"

cbuffer BasicVertexConstantData : register(b0)
{
    matrix modelWorld;
    matrix invTranspose;
    matrix view;
    matrix projection;
};

cbuffer NormalVertexConstantData : register(b1)
{
    float scale; // 그려지는 선분의 길이 조절
};

PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput output;
    float4 pos = float4(input.posModel, 1.0f);

    // Normal 먼저 변환
    float4 normal = float4(input.normalModel, 0.0f);
    output.normalWorld = mul(normal, invTranspose).xyz;
    //output.normalWorld = mul(normal, modelWorld).xyz;
    output.normalWorld = normalize(output.normalWorld);
        
    // 노멀의 끝부분 버텍스가 넘어가고 있음
    // 근데 이럴게 아니라 점과 노멀은 여기서 변환을 해서 넘기고
    // 지오메트리 쉐이더에서 오프셋 후 선분을 그리는게 맞는듯
    // float t = input.texcoord.x;
    // pos.xyz += output.normalWorld * t * scale;

    pos = mul(pos, modelWorld);
    output.posWorld = pos.xyz;
    
    pos = mul(pos, view);                   // [현재 의미없음] GS에서 재계산
    pos = mul(pos, projection);             // [현재 의미없음] GS에서 재계산

    output.posProj = pos;                   // [현재 의미없음] GS에서 재계산
    output.texcoord = input.texcoord;       // [현재 의미없음]
    output.color = float3(1.0, 0.0, 0.0);   // [현재 의미없음] GS에서 재지정 

    return output;
}
