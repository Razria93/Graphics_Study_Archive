cbuffer ConstantData : register(b0)
{
    float3 eyeWorld;
    float width;
    Matrix model;
    Matrix view;
    Matrix proj;
    float time = 0.0f;
    float3 padding;
};
// HullShader Output 1
struct PatchConstOutput
{
    float edges[4] : SV_TessFactor;
    float inside[2] : SV_InsideTessFactor;
};
// HullShader Output 2
struct HullOut
{
    float3 pos : POSITION;
};

struct DomainOut
{
    float4 pos : SV_POSITION;
};

// 도메인 쉐이더는 TS를 거치면서 컨트롤 포인트와 텍스쳐 좌표를 받아옴
// 도메인 쉐이더는 분할 된 뒤의 모든 버텍스의 좌표를 출력해줘야함
// 예를들면 4개의 버텍스로 시작했지만
// 분할 갯수가 엣지 4번씩하게 될 경우 총 버텍스가 25개가 발생하게 됨
// 이 25개를 반환해야함

[domain("quad")]
DomainOut main(PatchConstOutput patchConst,
             float2 uv : SV_DomainLocation,
             const OutputPatch<HullOut, 4> quad)
{
    DomainOut dout; 
    // 도메인 아웃은 좌표만 출력하면 됨
    // 이는 uv와 쿼드로부터 계산해줘야함
    
	// Bilinear interpolation.
    // 선형보간 
    // U방향 보간 2점, 이 2점을 가지고 V방향 보간
    // 하나의 패치를 구현하기 위해 헐쉐이더와 도메인 쉐이더가 여러번 실행이 됨
    // 도메인 쉐이더는 쪼개진 버텍스 수만큼 실행됨
    float3 v1 = lerp(quad[0].pos, quad[1].pos, uv.x);
    float3 v2 = lerp(quad[2].pos, quad[3].pos, uv.x);
    float3 p = lerp(v1, v2, uv.y);
    
    dout.pos = float4(p, 1.0);
    dout.pos = mul(dout.pos, view);
    dout.pos = mul(dout.pos, proj);
	
    return dout;
}

// Hull에서 모서리의 컨트롤 포인트 4개를 받아옴
// 안쪽에 쪼개진 각 버텍스의 텍스쳐 좌표도 받아옴
// 가장자리의 4개의 콘트롤 포인트 + 텍스쳐 좌표 => 쪼개진 버텍스의 좌표를 출력해줘야함
// 도메인에 대해서 쪼개진 버텍스의 좌표를 구하는 것이 도메인쉐이더
