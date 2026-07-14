#include "Common.hlsli"
#include "Ex1606_Common.hlsli"

struct GeometryShaderInput
{
    float4 pos : SV_POSITION;
};

// 자체기능은 없고 GS 호출용도로 작성됨
// 해상도(vertexID)만큼 호출되며 해상도 당 큐브를 구성하여 몇개의 버텍스를 만들지는 GS를 어떻게 작성하느냐에 따라 다름 
GeometryShaderInput main(uint vertexID : SV_VertexID)
{
    GeometryShaderInput output;
    
    output.pos = float4(0, 0, 0, 0); // dummy
    
    return output;
}