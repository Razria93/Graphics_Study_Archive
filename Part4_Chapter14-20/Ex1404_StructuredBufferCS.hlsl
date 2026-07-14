struct Particle
{
    float3 pos;
    float3 color;
};

static float dt = 1 / 600.0; // ConstBuffer로 받아올 수 있음

//StructuredBuffer<Particle> inputParticles : register(t0);     // SRV : SRV로 텍스쳐에 접근할 경우 읽기만 가능
RWStructuredBuffer<Particle> outputParticles : register(u0);    // UAV : UAV로 텍스쳐에 접근할 경우 읽기/쓰기 모두 가능
                                                                // - VertexShader는 SRV로만 Texture를 읽을 수 있으며, 
                                                                //   UAV로 텍스쳐를 Shader에게 넘겨줄 수 있는 것은 CS뿐임
                                                                // - GS를 이용하여 연산하고 스트림아웃으로 메모리에 저장하는 방법도 있으나 CS활용이 늘어나고 있는 추세

[numthreads(256, 1, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    Particle p = outputParticles[dtID.x]; // Read
    // 각 스레드(dtID.x)는 outputParticles 배열의 고유한 요소를 담당.
    // 즉, Thread ID와 데이터 인덱스를 1:1로 매핑함으로써
    // GPU의 비결정적 실행 순서(병렬 스케줄링)에도 결과가 일관되게 유지됨.
    
    // 컴퓨터 그래픽스에서는 시간간격이 이산적으로 끊어져있음 (dt 간격으로 일정하게 호출된다는 것)
    // (P_{t+1} - P_{t}) / delta{t} = V_{t} [단위시간(delta{t}) 기준 위치의 변화 정도(P_{t+1} - P_{t}) = 속도(V_{t})]
    // 여기서는 V_{t}를 기반으로 P_{t+1}을 계산하는 것이기 때문에 
    
    // P_{t+1} = P_{t} + V_{t} * delta{t}
    // P_{t}는 CPU에서 결정하며, delta{t}는 위에서 1 / 60.0 으로 고정 됨
    
    // V_{t}는 'P_{t} - O' 에 수직인 벡터로 설정할 수 있음 (O는 원점)
    // 회전 방정식을 이용하여 구한 V_{t}는 다음과 같음
    // V_{t} = (- P_y, P_x, 0)
    
    // 속력은 속도의 절대값 (방향이 없는 크기이기 때문)
    // velocity를 정규화할 경우에는 속도가 모두 같아지므로 
    // 이동거리가 짧은 가운데는 빨리도는 것처럼 보이고,이동거리가 긴 바깥은 느리게 도는 것처럼 보임
    float3 velocity = float3(-p.pos.y, p.pos.x, 0.0);
    p.pos += velocity * dt;
    
    outputParticles[dtID.x].pos = p.pos; // Write
}
