struct Particle
{
    float3 pos;
    float3 color;
};

static float dt = 1 / 60.0; // ConstBuffer로 받아올 수 있음

static int radius = 10; // 픽셀 단위 반지름

RWStructuredBuffer<Particle> outputParticles : register(u0);
RWTexture2D<float4> densityOutput : register(u1);

// https://en.wikipedia.org/wiki/Smoothstep
float smootherstep(float x, float edge0 = 0.0f, float edge1 = 1.0f)
{
  // Scale, and clamp x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0, 1);

    return x * x * x * (3 * x * (2 * x - 5) + 10.0f);
}

[numthreads(256, 1, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    // Advect 기능
    Particle p = outputParticles[dtID.x]; // Read
    
    float3 velocity = float3(-p.pos.y, p.pos.x, 0.0) * 0.5;

    p.pos += velocity * dt;
    
    outputParticles[dtID.x].pos = p.pos; // Write

    // PS에서 동그라미 그리는걸 CS에서 어떻게 구현할지
    // 즉, 렌더링 파이프라인(VS - GS - PS) 과정을 실행시키지 않고 CS에서 구현하면 어떻게 할 수 있을지에 대한 내용임
    // DrawSprites()를 비활성화 시키고 보면 됨
    // CS로 그리면 노이즈가 발생함
    
    // 문제가 발생하는 원인 : 멀티스레딩
    // 픽셀마다 색상을 정하는데 이게 그룹간의 소통이 안되기 때문에 색상값을 경정하는 과정에서 충돌이 일어난거 같음
    // 그런데 이걸 해결하기위해 싱크로나이징을 할 경우 상당히 느려지며 병렬처리를 하는 메리트가 사라질 정도일수도 있음
    
    // 렌더링 파이프라인은 각각의 작업을 분리해서 순차적으로 진행함
    // PS는 이미 그릴 곳을 딱 정한 뒤 해당 픽셀의 색상을 정하는 것
    // CS의 경우 칠하는 곳을 직접 지정하는 형식이기 때문에 칠하는 곳이 중복될 수 있으나,
    // PS의 경우는 특정 픽셀의 색상을 결정하는 과정이 PS이기 때문에 겹칠일이 없음
    
    /*
    uint width, height;
    densityOutput.GetDimensions(width, height);
    
    float2 posScreen = float2(p.pos.x, -p.pos.y);
    posScreen = (posScreen + 1) * 0.5;
    posScreen *= float2(width, height);
    posScreen -= 0.5;

    // 출력에 임의 접근 가능 (Bounding Box)
    // 주의: ThreadSafe 하지 않음
    for (int j = max(0, posScreen.y - radius); j <= min(height - 1, posScreen.y + radius); j++)
        for (int i = max(0, posScreen.x - radius); i <= min(width - 1, posScreen.x + radius); i++)
        {
            int2 idx = uint2(i, j);
            idx.x = clamp(idx.x, 0, width - 1);
            idx.y = clamp(idx.y, 0, height - 1);

            float dist = length(idx - posScreen);
            float density = smootherstep(radius - dist, 0.0, radius);

            densityOutput[idx] += float4(p.color.rgb * density, 1.0) * 0.5; // Write
        }
    */
}
