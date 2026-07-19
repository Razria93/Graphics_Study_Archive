Texture2D inputTex : register(t0);
SamplerState pointClampSS : register(s0);

static const float weights[11] =
{
    // 가중치
    0.05f, 0.05f, 0.1f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f,
};

static const int blurRadius = 5;

struct SamplingPixelShaderInput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
};

float4 main(SamplingPixelShaderInput input) : SV_TARGET
{
    // texture의 해상도 가져오기
    // 해상도가 가변적인 경우, 쉐이더 내에서 GetDimensions
    uint width, height;
    inputTex.GetDimensions(width, height);
    
    const float2 dx = float2(1.0 / width, 0.0);
    
    float3 blurColor = float3(0, 0, 0);
    
    [unroll]
    for (int i = -blurRadius; i <= blurRadius; ++i)
    {
        // No need to clamp index manually thanks to the sampler
        //  - pointSampler라서 interpolation(보간)을 하지 않고 배열처럼 값을 가져옴
        //  - 인덱스가 이미지가 밖으로 벗어나더라도 clamp 사용할 필요 없음
        float3 inputColor = inputTex.SampleLevel(pointClampSS, input.texcoord + float(i) * dx, 0.0).rgb;
        blurColor += weights[i + blurRadius] * inputColor;
    }
    
    return float4(blurColor, 1.0f);
}