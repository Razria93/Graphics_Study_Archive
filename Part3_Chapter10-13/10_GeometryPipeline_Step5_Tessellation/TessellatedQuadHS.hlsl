cbuffer ConstantData : register(b0)
{
    float3 eyeWorld;
    float width;
    Matrix model;
    Matrix view;
    Matrix proj;
    uint tessellationMode;
    float distanceMin;
    float distanceMax;
    float modePadding;
    float4 edges;
    float2 inside;
    float2 padding2;
};

struct VertexOut
{
    float4 pos : POSITION;
};

struct HullOut
{
    float3 pos : POSITION;
};

struct PatchConstOutput
{
    float edges[4] : SV_TessFactor;
    float inside[2] : SV_InsideTessFactor;
};

PatchConstOutput MyPatchConstantFunc(InputPatch<VertexOut, 4> patch,
                                     uint patchID : SV_PrimitiveID)
{
    PatchConstOutput pt;

    if (tessellationMode == 0)
    {
        pt.edges[0] = edges.x;
        pt.edges[1] = edges.y;
        pt.edges[2] = edges.z;
        pt.edges[3] = edges.w;
        pt.inside[0] = inside.x;
        pt.inside[1] = inside.y;
    }
    else
    {
        float3 patchCenter =
            (patch[0].pos + patch[1].pos + patch[2].pos + patch[3].pos).xyz * 0.25;
        float3 patchCenterWorld = mul(float4(patchCenter, 1.0), model).xyz;
        float distanceToPatch = length(patchCenterWorld - eyeWorld);
        float distanceRange = max(distanceMax - distanceMin, 0.0001);
        float ratio = saturate((distanceMax - distanceToPatch) / distanceRange);
        float tess = lerp(1.0, 64.0, ratio);

        pt.edges[0] = tess;
        pt.edges[1] = tess;
        pt.edges[2] = tess;
        pt.edges[3] = tess;
        pt.inside[0] = tess;
        pt.inside[1] = tess;
    }

    return pt;
}
// 아래 []에 있는걸 Attributes 라고 함
[domain("quad")] // 그릴 도형의 모양 [quad 사각형]
[partitioning("integer")] // 어떻게 쪼갤지 [integer, fractional_even, fractional_odd, pow] 가 있음. 나중에 넣어보기
[outputtopology("triangle_cw")] // 분항해서 시계방향 삼각형으로 만들어줌
[outputcontrolpoints(4)] // 스레드 1개당 사용할 컨트롤 포인트 (뭐지?)
[patchconstantfunc("MyPatchConstantFunc")] // 사용할 함수 이름
[maxtessfactor(64.0f)] // 요소 갯수 (총 몇등분까지 가능하게 할지)
HullOut main(InputPatch<VertexOut, 4> p,
           uint i : SV_OutputControlPointID,
           uint patchId : SV_PrimitiveID)
{
    HullOut hout;
	
    // 버텍스로부터 받아온 좌표를 그대로 반환하고 있음
    // P는 4개씩 넣어주는, VS의 Output의 4개의 배열
    // i는 각 컨트롤 포인트의 번호 (0, 1, 2, 3 이 바꿔가면서 들어오게 됨) - 컨트롤 포인트가 4개이기 때문
    hout.pos = p[i].pos.xyz; // 따라서 i로 인덱싱을 하고 있음
    // 이렇게 될 경우 VS에서 넣어준 순서대로 컨트롤 포인트를 부여받게 되는 것
    // 결과적으로 해당 메인도 버텍스 1번당 1번 실행되는 것으로 볼 수 있음
    // 그리고 버텍스를 그냥 넣어주는 것이 아닌 버텍스에 컨트롤포인트 ID를 붙여서 반환함
    return hout;
}

// HS는 두단계로 작동함
// ControlPoint 단계 (HS main)
// 1. [outputcontrolpoints(4)] : 패치 당 컨트롤포인트 4개를 출력함 (Quad 도메인과 일치함)
// 2. VertexOutput가 4개 있는 입력패치의 i번째 버텍스(컨트롤포인트)를 받아서 HullOut으로 그대로 전달함
// 3. 즉, 패치의 꼭지점들을 ID를 기반으로 정리하고 HullOut에 입력하는 단계
//  
// Patch Constant 단계 (patchconstantfunc)
// 1. [patchconstantfunc("MyPatchConstantFunc")]가 패치마다 1번 호출됨
// 2. 반환구조체인 PatchConstOutput에 모서리 4개의 테셀레이션 팩터, 사각형 내부의 방향 테셀 펙터를 채움