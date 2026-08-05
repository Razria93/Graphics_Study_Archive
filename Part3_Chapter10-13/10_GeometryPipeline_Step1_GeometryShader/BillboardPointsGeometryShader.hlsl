// Geometry-Shader Object
// https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-geometry-shader

// Stream-Output Object
// https://learn.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-so-type

cbuffer BillboardPointsConstantData : register(b0)
{
    float3 eyeWorld;
    float width;
    Matrix model; // For vertex shader
    Matrix view; // For vertex shader
    Matrix proj; // For vertex shader
};

// VS 에서 내보낸 것
struct GeometryShaderInput
{
    float4 pos : SV_POSITION;
};

// GS 출력 -> PS 입력
struct PixelShaderInput
{
    float4 pos : SV_POSITION; // not POSITION
    uint primID : SV_PrimitiveID; // Primitive : 렌더링의 최소 단위. 이를 기반으로 PS에서 색상 지정
};

// Point input -> triangle-strip quad output
[maxvertexcount(4)]
void main(point GeometryShaderInput input[1], uint primID : SV_PrimitiveID,
          inout TriangleStream<PixelShaderInput> outputStream)
{
    static const float4 offsets[4] =
    {
        float4(0.00, 0.05, 0.0, 0.0), // top-left
        float4(0.05, 0.05, 0.0, 0.0), // top-right
        float4(0.00, 0.00, 0.0, 0.0), // bottom-left
        float4(0.05, 0.00, 0.0, 0.0)  // bottom-right
    };

    [unroll]
    for (int i = 0; i < 4; ++i)
    {
        PixelShaderInput output;
        output.pos = input[0].pos + offsets[i];
        output.pos = mul(output.pos, view);
        output.pos = mul(output.pos, proj);
        output.primID = primID;
        outputStream.Append(output);
    }

    outputStream.RestartStrip();
}