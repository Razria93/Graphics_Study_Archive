#include "Common.hlsli"

cbuffer BasicVertexConstantBuffer : register(b0)
{
    matrix model;
    matrix invTranspose;
    matrix view;
    matrix projection;
};

PixelShaderInput main(VertexShaderInput input)
{
    // 불필요한 멤버들도 VertexShaderInput을 통일시켰기 때문에 채워줘야 합니다.
    // 캐릭터가 돌때는 Cube가 움직이면 안되고,
    // 시점이 옮길때만 움직여야함
    // 따라서 cube 자체의 모델행렬은 별도로 있을 필요가 없음. 큐브가 자체적으로, 그리고 월드 내에서 움직일 일은 없음
    // 그래서 view, projection만 적용 (CPU에서 view - projection 행렬만 만들어서 넘겨서 적용시켜도 됨)
    
    PixelShaderInput output;
    float4 pos = float4(input.posModel, 1.0f);

    pos = mul(pos, model); // Identity

    output.posWorld = pos.xyz;
    
    float4 normal = float4(input.normalModel, 0.0f);
    output.normalWorld = mul(normal, invTranspose).xyz;
    output.normalWorld = normalize(output.normalWorld);

    pos = mul(pos, view);
    
    pos = mul(pos, projection);
    output.posProj = pos;

    output.texcoord = input.texcoord;
    output.color = float3(1.0, 1.0, 0.0);

    return output;
}
