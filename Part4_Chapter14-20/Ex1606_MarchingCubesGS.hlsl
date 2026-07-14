#include "Common.hlsli"
#include "Ex1606_Common.hlsli"

// dual cell centers -> [VERTEX SHADER] -> [GEOMETRY SHADER] -> PixelShaderInput -> [PIXEL SHADER]

// 참고 https://github.com/Tsarpf/MarchingCubesGPU/blob/master/GPUMarchingCubes/GPUMarchingCubes/GeometryShader.hlsl

Texture3D<float> density : register(t0);
Texture3D<float> signedDistance : register(t1);
Texture2D<int> triTableTex : register(t2);

struct GeometryShaderInput
{
    float4 pos : SV_POSITION;
};

uint3 Index3(in uint i1)
{
    uint3 i3;
    i3.z = i1 / (width * height);
    i1 -= i3.z * (width * height);
    i3.y = i1 / width;
    i1 -= i3.y * width;
    i3.x = i1;
    
    return i3;
}

float3 vertexInterp(float isoLevel, float3 v0, float l0, float3 v1, float l1)
{
    // sdf일 경우 가정 (isoLevel = 0.0)
    float lerper = abs(l0) / (abs(l1) + abs(l0));
    return lerp(v0, v1, lerper);
}

int triTableValue(int i, int j)
{
    if (i >= 256 || j >= 16)
        return -1;
    else
        return triTableTex[uint2(j, i)];
}

static int3 decal[8] =
{
    int3(0, 0, 0),
    int3(1, 0, 0),
    int3(1, 1, 0),
    int3(0, 1, 0),
    int3(0, 0, 1),
    int3(1, 0, 1),
    int3(1, 1, 1),
    int3(0, 1, 1)
};

// 노말 계산
// Signed Distance의 Gradient가 Normal이 됨 (미분)
float4 ComputeNormal(float3 pos)
{
    float3 uvw = (pos * 0.5) + 0.5;
    float3 normal;
    normal.x = signedDistance.SampleLevel(linearClampSampler, uvw + float3(dxBase.x * 0.5, 0, 0), 0)
               - signedDistance.SampleLevel(linearClampSampler, uvw - float3(dxBase.x * 0.5, 0, 0), 0);
    normal.y = signedDistance.SampleLevel(linearClampSampler, uvw + float3(0, dxBase.y * 0.5, 0), 0)
               - signedDistance.SampleLevel(linearClampSampler, uvw - float3(0, dxBase.y * 0.5, 0), 0);
    normal.z = signedDistance.SampleLevel(linearClampSampler, uvw + float3(0, 0, dxBase.z * 0.5), 0)
               - signedDistance.SampleLevel(linearClampSampler, uvw - float3(0, 0, dxBase.z) * 0.5, 0);
    return float4(normalize(normal), 0);
}

// PS로 넘김
PixelShaderInput MakeOutput(float3 pos)
{
    PixelShaderInput output;
    
    output.posModel = pos.xyz;
    output.posWorld = mul(float4(output.posModel, 1), world).xyz;
    output.normalWorld = mul(ComputeNormal(pos), worldIT).xyz;
    output.posProj = mul(float4(output.posWorld, 1), viewProj);
    output.texcoord.xy = 0; // dummy
    output.tangentWorld.xyz = 0; // dummy
   
    return output;
}

[maxvertexcount(18)]
void main(point GeometryShaderInput input[1], uint primID : SV_PrimitiveID,
	      inout TriangleStream<PixelShaderInput> outputStream)
{
    uint3 i3 = Index3(primID);

    if (i3.x < width - 1 && i3.y < height - 1 && i3.z < depth - 1)
    {
        float isolevel = 0.0;
        
        float cubeVals[8];
        float3 cubePoses[8];
        for (int i = 0; i < 8; i++)
        {
            cubeVals[i] = signedDistance[i3 + decal[i]];                // SignedDistance값을 미리 저장
            cubePoses[i] = (dxBase * (i3 + decal[i] + 0.5) - 0.5) * 2;  // 픽셀 중심(큐브의 모서리)의 Pos를 저장
        }
        
        // Flag : Bite Mask (각각의 버텍스가 물 안인지, 밖인지 표현하는 cubeindex)
        int cubeindex = 0;
        cubeindex = int(cubeVals[0] <= isolevel);
        cubeindex += int(cubeVals[1] <= isolevel) * 2;
        cubeindex += int(cubeVals[2] <= isolevel) * 4;
        cubeindex += int(cubeVals[3] <= isolevel) * 8;
        cubeindex += int(cubeVals[4] <= isolevel) * 16;
        cubeindex += int(cubeVals[5] <= isolevel) * 32;
        cubeindex += int(cubeVals[6] <= isolevel) * 64;
        cubeindex += int(cubeVals[7] <= isolevel) * 128;
        
        // 해당 인덱스를 기반으로 판단하는 부분
        // index가 0인 경우 어느 버텍스도 내부에 해당하지 않는 All_Out 이며, 255인 경우는 모든 버텍스가 내부에 해당하는 All_In의 경우임
        // 따라서 두 경우에는 경계선이 지나갈 필요가 없으며, 삼각형도 만들 필요가 없음 -> 넘어감
        if (cubeindex != 0 && cubeindex != 255)
        {
            float3 vertlist[12];

		    //Find the vertices where the surface intersects the cube
            // 만들어지는 엣지위의 버텍스에 대한 인덱스
            vertlist[0] = vertexInterp(isolevel, cubePoses[0], cubeVals[0], cubePoses[1], cubeVals[1]);
            vertlist[1] = vertexInterp(isolevel, cubePoses[1], cubeVals[1], cubePoses[2], cubeVals[2]);
            vertlist[2] = vertexInterp(isolevel, cubePoses[2], cubeVals[2], cubePoses[3], cubeVals[3]);
            vertlist[3] = vertexInterp(isolevel, cubePoses[3], cubeVals[3], cubePoses[0], cubeVals[0]);
            vertlist[4] = vertexInterp(isolevel, cubePoses[4], cubeVals[4], cubePoses[5], cubeVals[5]);
            vertlist[5] = vertexInterp(isolevel, cubePoses[5], cubeVals[5], cubePoses[6], cubeVals[6]);
            vertlist[6] = vertexInterp(isolevel, cubePoses[6], cubeVals[6], cubePoses[7], cubeVals[7]);
            vertlist[7] = vertexInterp(isolevel, cubePoses[7], cubeVals[7], cubePoses[4], cubeVals[4]);
            vertlist[8] = vertexInterp(isolevel, cubePoses[0], cubeVals[0], cubePoses[4], cubeVals[4]);
            vertlist[9] = vertexInterp(isolevel, cubePoses[1], cubeVals[1], cubePoses[5], cubeVals[5]);
            vertlist[10] = vertexInterp(isolevel, cubePoses[2], cubeVals[2], cubePoses[6], cubeVals[6]);
            vertlist[11] = vertexInterp(isolevel, cubePoses[3], cubeVals[3], cubePoses[7], cubeVals[7]);
            
            for (int j = 0; triTableValue(cubeindex, j) != -1; j += 3)
            {
                // 마지막 더하는 숫자가 역순
                outputStream.Append(MakeOutput(vertlist[triTableValue(cubeindex, j + 2)]));
                outputStream.Append(MakeOutput(vertlist[triTableValue(cubeindex, j + 1)]));
                outputStream.Append(MakeOutput(vertlist[triTableValue(cubeindex, j + 0)]));
                outputStream.RestartStrip();
            }
        }
        else
        {
            /* Nothing */
        }
    }
    else
    {
           /* Nothing */
    }
}