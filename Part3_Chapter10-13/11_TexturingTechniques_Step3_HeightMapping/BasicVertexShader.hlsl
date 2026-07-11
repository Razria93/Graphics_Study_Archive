#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

// Vertex Shader에서도 텍스춰 사용
Texture2D g_heightTexture : register(t0);
SamplerState g_sampler : register(s0);

cbuffer BasicVertexConstantData : register(b0)
{
    matrix modelWorld;
    matrix invTranspose;
    matrix view;
    matrix projection;
    int useHeightMap;
    float heightScale;
    float2 dummy;
};

PixelShaderInput main(VertexShaderInput input)
{
    // 모델(Model) 행렬은 모델 자신의 원점에서 
    // 월드 좌표계에서의 위치로 변환을 시켜줍니다.
    // 모델 좌표계의 위치 -> [모델 행렬 곱하기] -> 월드 좌표계의 위치
    // -> [뷰 행렬 곱하기] -> 뷰 좌표계의 위치 -> [프로젝션 행렬 곱하기]
    // -> 스크린 좌표계의 위치
    
    // 뷰 좌표계는 NDC이기 때문에 월드 좌표를 이용해서 조명 계산
    
    PixelShaderInput output;
    
    // Normal 벡터 먼저 변환 (Height Mapping)
    float4 normal = float4(input.normalModel, 0.0f);
    output.normalWorld = mul(normal, invTranspose).xyz;
    output.normalWorld = normalize(output.normalWorld);
    
    // Tangent 벡터는 modelWorld로 변환
    float4 tangentWorld = float4(input.tangentModel, 0.0f);
    tangentWorld = mul(tangentWorld, modelWorld);

    // 월드 상의 VertexPos는 하단의 pos와 같음
    float4 pos = float4(input.posModel, 1.0f);
    pos = mul(pos, modelWorld);
    
    if (useHeightMap)
    {
        // 지금 CreateTexture에 Mipmap을 생성하는 코드가 있어서 텍스쳐마다 모두 LOD 적용가능
        // float4 heightMap = g_heightTexture.SampleLevel(g_sampler, input.texcoord, 0.0);
        // float height = length(heightMap.xyz);
        float height = g_heightTexture.SampleLevel(g_sampler, input.texcoord, 0.0).r;
        height = 2.0 * height - 1.0; // 스케일링 [0, 1] -> [-1, +1]
        // VertexShader에서는 SampleLevel 사용
        pos += float4(output.normalWorld * height * heightScale, 0.0);
        // 노멀맵을 끄면 밋밋하게 렌더링이 되는데 이는 버텍스 위치만 옮겨주고 노멀값은 변경시키지 않기 때문에 Sphere의 노멀로 렌더링이 됨
        // 바닥의 경우 디테일이 떨어지면 (버텍스 숫자가 별로 없으면) 티가 안남
        // 결과적으로 버텍스의 위치를 옮겨주는 것이기 때문
    }

    output.posWorld = pos.xyz; // 월드 위치 따로 저장

    pos = mul(pos, view);
    pos = mul(pos, projection);

    output.posProj = pos;
    output.texcoord = input.texcoord;
    output.tangentWorld = tangentWorld.xyz;

    output.color = float3(0.0f, 0.0f, 0.0f);

    return output;
}
