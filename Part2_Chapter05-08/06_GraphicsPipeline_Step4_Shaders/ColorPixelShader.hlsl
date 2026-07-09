

cbuffer PSConstantBuffer : register(b1)
{
    float4 leftColor;
    float4 rightColor;
    float xSplitPoint;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float2 texcoord : TEXCOORD;
    
};

float4 main(PixelShaderInput input) : SV_TARGET
{
    float4 returnColor;
    
    if (input.texcoord.x < xSplitPoint)
    {
        if (input.texcoord.y < xSplitPoint)
            returnColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
        else
            returnColor = float4(0.0f, 1.0f, 0.0f, 1.0f);

    }
    else
    {
        if (input.texcoord.y < xSplitPoint)
            returnColor = float4(0.0f, 0.0f, 1.0f, 1.0f);
        else
            returnColor = float4(1.0f, 1.0f, 0.0f, 1.0f);
    }
    
    
    return returnColor;
}
