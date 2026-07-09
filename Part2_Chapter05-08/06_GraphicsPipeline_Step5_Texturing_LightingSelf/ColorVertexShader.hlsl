








cbuffer ModelViewProjectionConstantBuffer : register(b0) {
    matrix model;
    matrix view;
    matrix projection;
    matrix normalMatrix;
};




struct VertexShaderInput {
    float3 modelPos : POSITION;
    float3 worldPos : WORLDPOSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

struct PixelShaderInput {
    float4 projPos : SV_POSITION;
    float4 worldPos : WORLDPOSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD;
};




PixelShaderInput main(VertexShaderInput input) {

    PixelShaderInput output;
    float4 pos = float4(input.modelPos, 1.0);
    pos = mul(pos, model);
    output.worldPos = pos;
    pos = mul(pos, view);
    pos = mul(pos, projection);
    output.projPos = pos;
    float4 nor = float4(input.normal, 0.0);
    nor = mul(nor, normalMatrix);
    output.normal = nor.xyz;
    output.texcoord = input.texcoord;

    return output;
}
