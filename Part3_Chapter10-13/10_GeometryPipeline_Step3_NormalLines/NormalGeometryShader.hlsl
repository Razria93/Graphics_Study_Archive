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

struct GeometryShaderInput
{
    float4 posProj : SV_POSITION;
    float3 posWorld : POSITION;
    float3 normalWorld : NORMAL;
    float2 texcoord : TEXCOORD;
    float3 color : COLOR;
};

struct PixelShaderInput
{
    float4 posProj : SV_POSITION;
    float3 posWorld : POSITION;
    float3 normalWorld : NORMAL;
    float2 texcoord : TEXCOORD;
    float3 color : COLOR;
};

[maxvertexcount(2)]
void main(point GeometryShaderInput input[1],
	      inout LineStream<PixelShaderInput> outputStream)
{
    PixelShaderInput output;
    
    float4 startPoint_Normal = float4(input[0].posWorld, 1.0);
    
    output.posWorld = startPoint_Normal.xyz;
    
    startPoint_Normal = mul(startPoint_Normal, view);
    startPoint_Normal = mul(startPoint_Normal, projection);
    
    output.posProj = startPoint_Normal;
    output.normalWorld = input[0].normalWorld;
    output.texcoord = float2(0.0, 0.0); // 의미없음
    output.color = float3(1.0, 0.0, 0.0);
    
    outputStream.Append(output);
    
    
    float4 endPoint_Normal = float4(input[0].posWorld + output.normalWorld *scale, 1.0);
    
    output.posWorld = endPoint_Normal.xyz;
    
    endPoint_Normal = mul(endPoint_Normal, view);
    endPoint_Normal = mul(endPoint_Normal, projection);
    
    output.posProj = endPoint_Normal;
    output.normalWorld = input[0].normalWorld;
    output.texcoord = float2(1.0, 1.0); // 의미없음
    output.color = float3(1.0, 1.0, 0.0);
    
    outputStream.Append(output);
}