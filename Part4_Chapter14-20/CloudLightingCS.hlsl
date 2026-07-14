Texture3D<float> densityTex : register(t0);
RWTexture3D<float> lightingTex : register(u0);

SamplerState linearClampSampler : register(s1);

cbuffer Consts : register(b0)
{
    float3 uvwOffset;
    float lightAbsorptionCoeff = 5.0;
    float3 lightDir = float3(0, 1, 0);
    float densityAbsorption = 10.0;
    float3 lightColor = float3(1, 1, 1) * 40.0;
    float aniso = 0.3;
}

// https://wallisc.github.io/rendering/2020/05/02/Volumetric-Rendering-Part-2.html
float BeerLambert(float absorptionCoefficient, float distanceTraveled)
{
    // 얼마나 흡수되어야하는지 (비율)
    return exp(-absorptionCoefficient * distanceTraveled);
}

// 박스 가장자리 좌표로부터 3D 텍스춰 좌표 계산
float3 GetUVW(float3 posModel)
{
    return (posModel.xyz + 1.0) * 0.5;
}

// posModel : 3D 텍스쳐를 감싸고 있는 박스의 좌표계에서 연산
float LightRay(float3 posModel, float3 lightDir)
{
    // 근처만 탐색
    int numSteps = 128 / 4; // 많으면 퀄리티가 높아지지만 느려짐
    float stepSize = 2.0 / float(numSteps); // 스탭별 거리 (2.0은 박스의 한 변의 길이 및 light 추적의 최대 길이)
    // float absorptionCoeff = 5.0;

    float alpha = 1.0; // visibility 1.0으로 시작 (최대체력 -> 연산해나가며 alpha값이 줄어들고, 최종적으로 남은 alpha값이 렌더링에 사용됨)

    [loop] // [unroll] 사용 시 쉐이더 생성이 너무 느림
    for (int i = 0; i < numSteps; i++)
    {
        float prevAlpha = alpha;
        float density = densityTex.SampleLevel(linearClampSampler, GetUVW(posModel), 0).r;
        
        if (density > 1e-3)
            alpha *= BeerLambert(lightAbsorptionCoeff * density, stepSize);     // 비율이기 때문에 곱해줌

        posModel += lightDir * stepSize;                                        // 스탭 전진

        if (abs(posModel.x) > 1 || abs(posModel.y) > 1 || abs(posModel.z) > 1)  // 박스 범위 바깥으로 나갔는지 (박스의 중심이 O이고 절반길이가 1이기 때문에 해당 조건 가능)
            break;
        
        if (alpha < 1e-3)                                                       // alpha 값이 0.0에 근사한지 (에너지 모두 사용)
            break;
    }
    
    // alpha가 0에 가까울 수록 조명으로부터 빛을 잘 못 받음
    return alpha;
}

[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    // float3 lightDir = float3(0, 1, 0);
    
    uint width, height, depth;
    lightingTex.GetDimensions(width, height, depth);
    
    // dtID [0 ~ width -1], [0 ~ height -1], [0 ~ depth -1]
    float3 uvw = dtID / float3(width, height, depth); //+ uvwOffset; 라이트맵은 주어진 밀도장에 대해 계산하는 것이라서 uvwOffset 미사용

    // [0, 1] -> [-1, +1]의 좌표계 변환
    // uvw는 [0, 1]x[0, 1]x[0, 1]
    // 모델 좌표계는 [-1,1]x[-1,1]x[-1,1]
    lightingTex[dtID] = LightRay((uvw - 0.5) * 2.0, lightDir);
}
