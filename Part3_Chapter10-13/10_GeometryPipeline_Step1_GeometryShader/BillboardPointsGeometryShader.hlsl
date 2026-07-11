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

//TODO: PointStream -> TriangleStream
[maxvertexcount(100)]
void main(point GeometryShaderInput input[1], uint primID : SV_PrimitiveID,
                              inout TriangleStream<PixelShaderInput> outputStream)
{
    // 최대 출력 Vertex 갯수 제한 있음 (32bit 값을 1024개)
    // 반환 자료형이 void -> <>은 템플릿
    // GS 는 선택적 파이프라인이라서 매개변수로 받고 매개변수로 반환하나봄
    // input은 토폴로지가 point라 점 1개씩 들어옴
    // SV_PrimitiveID를 붙여서 GS가 프리미티브 ID를 받아올 수 있음
    
    // float hw = 0.5 * width;
    
    PixelShaderInput output;
    
    output.pos = input[0].pos;
    
    // for 문을 없애고 위의 hw를 이용해서 별도로 지정해주는 거이 정답
    // 시작하는 위치 기준으로 0.003씩 늘어남
    for (int i = 0; i < 6; i++)
    {
        float4 vec;
       
        // {
        //     // TRIANGLE STRIP
        //     if (i == 0)
        //         vec = float4(0.0, 0.05, 0.0, 0.0);
        //     else if (i == 1)
        //         vec = float4(0.05, 0.05, 0.0, 0.0);
        //     else if (i == 2)
        //         vec = float4(0.0, 0.0, 0.0, 0.0);
        //     else if (i == 3)
        //         vec = float4(0.05, 0.0, 0.0, 0.0);
        // }

        {
            // TRIANGLE LIST
            if (i == 0)
                vec = float4(0.0, 0.05, 0.0, 0.0);
            else if (i == 1)
                vec = float4(0.05, 0.05, 0.0, 0.0);
            else if (i == 2)
                vec = float4(0.0, 0.0, 0.0, 0.0);
            
            
            
            if (i == 3)
                vec = float4(0.05, 0.05, 0.0, 0.0);
            else if (i == 4)
                vec = float4(0.05, 0.0, 0.0, 0.0);
            else if (i == 5)
                vec = float4(0.0, 0.0, 0.0, 0.0);
            
        }

        
        // 지오메트리에서 view, proj를 설정 
        // output.pos = input[0].pos + float4(0.0, 0.003, 0.0, 0.0) * float(i);
        output.pos = input[0].pos + vec;
        output.pos = mul(output.pos, view);
        output.pos = mul(output.pos, proj);
        output.primID = primID;

        // 해당 스트림에 출력할 것은 하나하나씩 추가해주는 방식
        // 프리미티브 단위로 채워서 내보냄
        
        
        // TriangleStream으로 바꾸고 output에 Vertex를 4개 넣으면 됨    (TRIANGLE STRIPS : Vertex 4개) -> 순서 중요!! 0,1,2 하고 나머지 1개를 3
        // OR TriangleStream으로 바꾸고 output에 Vertex를 6개 넣으면 됨 (TRIANGLE LIST : Vertex 6개)
        outputStream.Append(output);
    }
 
    // 주의: GS는 Triangle Strips으로 출력합니다.
    // https://learn.microsoft.com/en-us/windows/win32/direct3d9/triangle-strips

    // Vertex 6개로 만들려 하면 새로 스트립을 만든다는 의미로 아래 코드를 넣어야함
    // outputStream.RestartStrip(); // Strip을 다시 시작
}
