struct Particle
{
    float3 pos;
    float3 color;
};

static float dt = 1 / 60.0; // ConstBuffer로 받아올 수 있음

//StructuredBuffer<Particle> inputParticles : register(t0); // SRV로 사용 가능
//RWStructuredBuffer<Particle> outputParticles : register(u0);

ConsumeStructuredBuffer<Particle> inputParticles : register(u0);    // consume  : 소모 
AppendStructuredBuffer<Particle> outputParticles : register(u1);    // append   : 붙여넣기

// Consume에서 꺼내서 처리하고 Append에 붙여넣는 방식
// 메모리 크기가 가변적으로 변하는 것은 아니며, 초기화 당시의 크기를 유지하되, Counter만 변화하는 것임

[numthreads(256, 1, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    Particle p = inputParticles.Consume();  // Read
                                            // 당장 사용 가능한 것을 inputParticles에서 하나씩 가져와서 계산함
    
    float3 velocity = float3(-p.pos.y, p.pos.x, 0.0) * 0.1;
    p.pos += velocity * dt;
    
    outputParticles.Append(p);  // Write
                                // 다른 thread에서 몇개나 저장했는지 모르겠으니 outputParticles의 맨끝에다가 Append
                                // 멀티 스레딩의 경우에도 어디서 가져오고 어디에 저장할지를 명확히 했어야함 [dtID.x]
                                // Consume, Append는 내부적으로 알아서 처리해줌
}
