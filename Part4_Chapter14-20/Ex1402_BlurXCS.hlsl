Texture2D<float4> inputTex : register(t0);      // SRV
RWTexture2D<float4> outputTex : register(u0);   // UAV

SamplerState pointClampSS : register(s0);       // PS 처럼 샘플러 사용 가능
                                                // 대신 CS는 샘플링할 texCoord를 임의로 지정해주어야 함
// 참고 자료: Luna DX11 교재 Ch. 12

// 가중치 설정
static const float weights[11] =
{
    0.05f, 0.05f, 0.1f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f,
};

static const int blurRadius = 5;

[numthreads(32, 32, 1)] // 32 * 32 = 1024 [DX11 에서는 1024가 최대]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    // 해상도를 받아와서 사용
    // uint width, height;
    // outputTex.GetDimensions(width, height);           
    // float2 dx = float2(1.0 / width, 1.0 / height);
    
    // 해상도 고정
    float dx = 1.0 / 1280;
    float dy = 1.0 / 768;
    // 또는 float2 dx = float2(1.0 / 1280, 1.0 / 768)
    
    // Sampling할 texCoord
    // Pixel 중심의 좌표를 구할 때는 +0.5, +0.5
    float2 uv = float2((dtID.x + 0.5) * dx, (dtID.y + 0.5) * dy);
    // float2 uv = float2((dtID.x + 0.5) * dx.x, (dtID.y + 0.5) * dx.y);

    float3 blurColor = float3(0, 0, 0);

    [unroll]
    for (int i = -blurRadius; i <= blurRadius; ++i)
    {
        // Sampler를 사용하지 않을 경우 (pointSampler)
        // uint clamped = uint(clamp(i + int(dtID.x), 0, int(width) - 1)); // 범위를 벗어나지 않게 수동 클램핑 처리 코드
        // float3 color = inputTex[uint2(clamped, dtID.y)].xyz;
        
        float3 color = inputTex.SampleLevel(pointClampSS, uv + float2(float(i) * dx, 0.0), 0.0).rgb;

        blurColor += weights[i + blurRadius] * color;
    }

    // PS의 경우 임의의 Pixel에 대한 색값을 구하는 과정이기 때문에 이미 위치가 정해져있고 거기에 맞는 color값을 반환하는 형태
    // CS의 경우 계산한 color값을 저장할 Pixel 또한 지정해 주어야함
    outputTex[dtID.xy] = float4(blurColor, 1);
}
