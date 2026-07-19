struct PSInput // GS가 있다면 GSInput으로 사용됨
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

// particle 데이터가 out해야할 구조체와 구조가 일치함
struct Particle
{
    float3 position;
    float3 color;
};

// 텍스쳐로 들어옴
StructuredBuffer<Particle> particles : register(t0);

// VSInput이 없이 vertexID만 사용
PSInput main(uint vertexID : SV_VertexID)
{
    // SV_VertexID : Draw를 할 때 m_particles.m_cpu.size()에 맞춰서 index가 들어옴
    // 즉, 0 ~ [m_particles.m_cpu.size() - 1] 만큼 들어온다는 것
    // 그러나 index가 순서대로 들어오진 않음
    // 이렇게 Task를 CS로 우선 처리하고 VS가 받아올 경우 순서와 상관 없게 Shader 코드가 구성되어 있어야함
    
    // Particle의 Array처럼 사용 : SV_VertexID를 기준으로 particles에서 대응하는 데이터를 찾음
    // [] 내부 부분의 경우 어떻게 구성되더라도 상관 없음. vertexID는 일종의 가이드값임.
    // 입출력의 제약이 없기 때문에 구성의 자유도가 상당부분 확보됨
    Particle p = particles[vertexID];
    
    PSInput output;
    
    output.position = float4(p.position.xyz, 1.0);
    
    output.color = p.color;

    return output;
}
