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

struct GeometryShaderInput
{
    float4 pos : SV_POSITION;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION; // not POSITION
    float2 texCoord : TEXCOORD; // 지오메트리 쉐이더에서도 텍스쳐 좌표를 만들어줄 수 있음
    uint primID : SV_PrimitiveID;
};

[maxvertexcount(4)]
void main(point GeometryShaderInput input[1], uint primID : SV_PrimitiveID,
                              inout TriangleStream<PixelShaderInput> outputStream)
{
    float hw = 0.5 * width;
    
    PixelShaderInput output;
    
    // 풀이의 핵심은 점을 기준으로 고정되게 옵셋되던 것을
    // 벡터로 오프셋하겠다는 것
    // 벡터로 오프셋을 하게 될 경우, front가 eyePos의 영향을 받음
    // 이로 인해 실시간으로 front벡터는 input[0].pos에서 eyePos방향을 바라보는 방향이 되고
    // 이를 기준으로 right가 생성되기 때문에 right 또한 항상 front의 직각상태를 유지할 수 있음
    
    float4 up = float4(0.0, 1.0, 0.0, 0.0);
    float4 front = normalize(float4(eyeWorld, 0.0) - input[0].pos);
    front.w = 0.0;
    float4 right = normalize(float4(cross(up.xyz, front.xyz), 0.0));
    
    // 회전행렬 및 쿼터니안으로도 풀 수 있음
    
    output.pos = input[0].pos - hw * right - hw * up;
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.texCoord = float2(0.0, 1.0);
    output.primID = primID;
    
    outputStream.Append(output);

    output.pos = input[0].pos - hw * right + hw * up;
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.texCoord = float2(0.0, 0.0);
    output.primID = primID;
    
    outputStream.Append(output);
    
    output.pos = input[0].pos + hw * right - hw * up;
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.texCoord = float2(1.0, 1.0);
    output.primID = primID;
    
    outputStream.Append(output);
    
    output.pos = input[0].pos + hw * right + hw * up;
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.texCoord = float2(1.0, 0.0);
    output.primID = primID;
    
    outputStream.Append(output);

    // outputStream.RestartStrip();
}
