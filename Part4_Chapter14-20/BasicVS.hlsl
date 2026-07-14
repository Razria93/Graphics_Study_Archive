#include "Common.hlsli" // 쉐이더에서도 include 사용 가능

// Vertex Shader에서도 텍스춰 사용
Texture2D g_heightTexture : register(t0);

PixelShaderInput main(VertexShaderInput input)
{
    // 뷰 좌표계는 NDC이기 때문에 월드 좌표를 이용해서 조명 계산
    
    PixelShaderInput output;

#ifdef SKINNED
    
    // 참고 자료: Luna DX 12 교재
    
    float weights[8];
    weights[0] = input.boneWeights0.x;
    weights[1] = input.boneWeights0.y;
    weights[2] = input.boneWeights0.z;
    weights[3] = input.boneWeights0.w;
    weights[4] = input.boneWeights1.x;
    weights[5] = input.boneWeights1.y;
    weights[6] = input.boneWeights1.z;
    weights[7] = input.boneWeights1.w;
    
    uint indices[8]; // 힌트: 꼭 사용!
    indices[0] = input.boneIndices0.x;
    indices[1] = input.boneIndices0.y;
    indices[2] = input.boneIndices0.z;
    indices[3] = input.boneIndices0.w;
    indices[4] = input.boneIndices1.x;
    indices[5] = input.boneIndices1.y;
    indices[6] = input.boneIndices1.z;
    indices[7] = input.boneIndices1.w;

    // 연산용 float3
    float3 posModel = float3(0.0f, 0.0f, 0.0f);
    float3 normalModel = float3(0.0f, 0.0f, 0.0f);
    float3 tangentModel = float3(0.0f, 0.0f, 0.0f);
    
    // Uniform Scaling 가정
    // (float3x3)boneTransforms 캐스팅으로 Translation 제외
    for (int i = 0; i < 8; ++i)
    {
        // TODO:
        // 해당 부분은 BindPos로 구성된 Model의 개별 Vertex에 대하여 영향을 주는 bone들의 변환의 정도를 가중치에 맞게 더하여 반영하는 부분임
        
        // input.posModel   : skinnedVertices
        // boneTransforms   : Animation 중 한 frame의 동작을 표현하는 bone들의 transform데이터
        //                    각 bone들의 최종적인 변환행렬인 M_{i}이 bone의 idx에 맞춰 저장되어 있음
        // weight[i] * mul(v_BindPos, boneTransforms[i])의 형태인 이유
        //  - boneTransforms[i]은 변환행렬이기 때문에 여기에 상수인 weight를 그대로 곱해버리면 변환행렬이 뒤틀려버림 (변환행렬은 이동/회전/스케일 이라는 행렬의 복합체이기 때문)
        //  - 따라서 이미 적용된 결과값에 가중치를 부여하여 누적하는 것이 맞음
        
        posModel += weights[i] * mul(float4(input.posModel, 1.0f), boneTransforms[indices[i]]).xyz;
        normalModel += weights[i] * mul(input.normalModel, (float3x3)boneTransforms[indices[i]]);      // 벡터 (rotation만)
        tangentModel += weights[i] * mul(input.tangentModel, (float3x3)boneTransforms[indices[i]]);    // 벡터 (rotation만)
    
        // weight의 합은 항상 1.0 이기에 정규화는 필요없음
    }

    input.posModel = posModel;
    input.normalModel = normalModel;
    input.tangentModel = tangentModel;

#endif

    //참고: windTrunk, windLeaves 옵션도 skinnedMesh처럼 매크로 사용 가능
    // 잔디 애니메이션에도 사용
    if (windTrunk != 0.0)   // 줄기가 얼마나 흔들릴지 (나무 전체 기준)
    {
        float2 rotCenter = float2(0.0f, -0.5f);
        float2 temp = (input.posModel.xy - rotCenter);                              // Center로부터의 높이
        float coeff = windTrunk * pow(max(0, temp.y), 2.0) * sin(globalTime);       // 높이 제곱에 비례, globalTime을 기반으로한 sin 패턴
        
        float2x2 rot = float2x2(cos(coeff), sin(coeff), -sin(coeff), cos(coeff));   // 회전 행렬
        
        input.posModel.xy = mul(temp, rot);
        input.posModel.xy += rotCenter;
    }
    
    if (windLeaves != 0.0)  // 나뭇잎이 얼마나 흔들릴지
    {
        float3 windVel = float3(sin(input.posModel.x * 100.0 + globalTime * 0.1)        // 나뭇잎의 x좌표에 따라 영향력이 달라짐
                                * cos(input.posModel.y * 100 + globalTime * 0.1), 0, 0) // 나뭇잎의 y좌표에 따라 영향력이 달라짐
                                * sin(globalTime * 10.0);                               // 높이 제곱에 비례, globalTime을 기반으로한 sin 패턴
                                                                                        // 나뭇잎의 움직임이 불규칙하게 움직이길 원한다면 Noise를 활용
                                                                                        // 언리얼, 유니티, 모델링 프로그램 : Noise 제공을 많이 함
        
        // 이거 난수를 이용하면 훨씬 나을듯
        float3 coeff = (1.0 - input.texcoord.y) * windLeaves * dot(input.normalModel, windVel) * input.normalModel;
        // dot(input.normalModel, windVel) : 면에 수직으로 들어올수록 흔들림이 커짐 [즉, windVel값이 Normal을 구성하는 값의 정도(면의방향)에 따라 재구성되는 부분]
        // input.normalModel ; 위 상수값은 노멀의 값에 비례하여 감가됨 (노멀방향으로 움직임)
        
        input.posModel.xyz += coeff;
    }
    
    output.posModel = input.posModel;
    output.normalWorld = mul(float4(input.normalModel, 0.0f), worldIT).xyz;
    output.normalWorld = normalize(output.normalWorld);
    output.posWorld = mul(float4(input.posModel, 1.0f), world).xyz;

    if (useHeightMap)
    {
        float height = g_heightTexture.SampleLevel(linearClampSampler, input.texcoord, 0).r;
        height = height * 2.0 - 1.0;
        output.posWorld += output.normalWorld * height * heightScale;
    }

    output.posProj = mul(float4(output.posWorld, 1.0), viewProj);
    output.texcoord = input.texcoord;
    output.tangentWorld = mul(float4(input.tangentModel, 0.0f), world).xyz;

    return output;
}
