struct PixelShaderInput
{
    float4 pos : SV_POSITION; // not POSITION
    float2 texCoord : TEXCOORD;
    float3 color : COLOR;
    uint primID : SV_PrimitiveID;
};

// https://en.wikipedia.org/wiki/Smoothstep
float smootherstep(float x, float edge0 = 0.0f, float edge1 = 1.0f)
{
  // Scale, and clamp x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0, 1);

    return x * x * x * (3 * x * (2 * x - 5) + 10.0f);
}

// 일반적으로 Sprite는 텍스춰를 많이 사용합니다.
// 이 예제처럼 수식으로 패턴을 만들 수도 있습니다.
// 난수가 들어간 복잡한 함수도 많이 사용함
float4 main(PixelShaderInput input) : SV_TARGET
{
    // Geometry Shader(GS)가 각 사각형 단위로 새로운 텍스처 좌표(texCoord)를 재설정하고,
    // Pixel Shader(PS)는 그 재설정된 texCoord를 기준으로 사각형 내부의 원형 패턴을 계산하고 있음
    // scale을 지우면 사각형의 형태로 렌더링이 되는 것을 볼 수 있음
    
    float dist = length(float2(0.5, 0.5) - input.texCoord) * 2;
    float scale = smootherstep(1 - dist);
    return float4(input.color.rgb * scale, 1);
    // return float4(input.color.rgb, 1);
}
