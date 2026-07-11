struct PixelShaderInput
{
    float4 posProj : SV_POSITION; // Screen position
    uint primID : SV_PrimitiveID;
};

struct PixelShaderOutput
{
    float4 pixelColor : SV_Target0;
};

PixelShaderOutput main(PixelShaderInput input)
{
    PixelShaderOutput output;
    
    // 프리미티브 ID에 따라 색상을 다르게
    output.pixelColor = (input.primID % 2 == 0) ?
        float4(1.0f, 1.0f, 1.0f, 1.0f) : float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    return output;
}
