#include "Ex1606_Common.hlsli"

Texture3D<float4> noiseTex : register(t0);
StructuredBuffer<uint> numActiveParticles : register(t1);

RWStructuredBuffer<Particle> particles : register(u0);
RWStructuredBuffer<SortElement> sortElements : register(u1);

bool IsInside(float3 uvw)
{
    if (uvw.x <= dxBase.x)
        return false;
    else if (uvw.y <= dxBase.y)
        return false;
    else if (uvw.z <= dxBase.z)
        return false;
    else if (uvw.x >= 1.0 - dxBase.x)
        return false;
    else if (uvw.y >= 1.0 - dxBase.y)
        return false;
    else if (uvw.z >= 1.0 - dxBase.z)
        return false;
    else
        return true;
}

float3 SphericalToCartesial(in float3 sph)
{
    // x: phi, y: theta, z: radius
    sph.xy *= 3.141592 * 2.0; // 0~360 degrees
    
    return float3(sin(sph.x) * cos(sph.y), sin(sph.x) * sin(sph.y), cos(sph.x)) * sph.z;
}

uint MinCornerCell(float3 particlePos)
{
    int3 i3 = int3(floor(particlePos - 0.5));
    return i3.x + i3.y * width + i3.z * width * height;
}

[numthreads(1024, 1, 1)] // Particle 대상
void main(uint3 gId : SV_GroupID, uint3 dtID : SV_DispatchThreadID)
{
    // 아까 만든 자료구조
    SortElement ref = sortElements[dtID.x];
    
    if (ref.key != INACTIVE) // Active particle
    {
        Particle p = particles[ref.value];  // value는 해당 파티클의 particle 배열 내 인덱스
   
        float3 uvw = p.pos.xyz * dxBase;    // 파티클의 좌표계는 Grid의 해상도 Scale (0.0 ~ 1.0 으로 변환)

        // 시뮬레이션 공간 밖으로 나갔는지를 평가함
        // GPU 프로그래밍을 할때는 메모리 동적할당보단 초기화 후 활성화 비활성화 하는 방식으로 사용함
        if (IsInside(uvw))
        {
            // 밖으로 나가지 않았다면
            // 속도의 기준은 BaseGrid이지만 입자 좌표계는 UpGrid라서 upScale을 곱해줍니다.
            p.vel += float3(0, -0.2, 0) * dt * float3(width, height, depth); // 중력 적용과 해상도 scaling (-0.2 임의의 값)
                                                                             // 이미 유체처럼 움직이도록 움직임이 값이 앞단계에서 들어가있는 상태에서 중력만 적용하는 것
            p.pos += p.vel * dt; // 포지션 업데이트

            // 물체와 유체(입자)의 충돌
            // Object collision 
            /*float3 objCenter = float3(0.15, 0.3, 0.5) / dxBase;
            float objRadius = 0.1 / dxBase.y;
            float sqrDist = dot((p.pos - objCenter), (p.pos - objCenter)) - objRadius * objRadius;
            if (sqrDist <= 0.0)
            {
                float dist = sqrt(sqrDist);
                p.pos = objCenter + (p.pos - objCenter) / dist * (objRadius + 1e-2);
            }*/

            sortElements[dtID.x].key = MinCornerCell(particles[ref.value].pos); // MinCornerCell : 입자가 들어있는 셀의 인덱스를 찾아줌 (근처의 4개의 셀중 가장 작은 인덱스를 저장함) 
            particles[ref.value] = p; // 파티클 업데이트
        }
        else
        {
            // 밖으로 나갔다면
            sortElements[dtID.x].key = INACTIVE; // 비활성화 시키기 (INACTIVE : uint 최대값) -> 이유 : 정렬할 때 비활성화 된 값이 뒤로 정렬되도록 최대값으로
        }
    }
    else if (dtID.x < numActiveParticles[0] + numNewParticles) // 멀티스레딩 (dtID.x 가 추가할 인덱스인지 아닌지만 판단하여 실행)
    {
        // 파티클 추가하는 부분
        // Add a new particle

        uint width, height, depth;
        noiseTex.GetDimensions(width, height, depth); // 노이즈 텍스쳐에서 같은 자리의 값을 샘플링하지 않게 하도록 함 (주로 사용하는게 시간, 스레드 ID)

        // Source 1 
        if (dtID.x % 2 == 0) // ID 짝수
        {
            float3 sourceCenter = float3(0.02, 0.6, 0.5) / dxBase;
            float sourceRadius = 0.1 / dxBase.y;
            float3 randomPos = noiseTex[uint3(int(time * 654.321) % width, int(time * 123 + dtID.x * 1.73) % height, (time * 456 + gId.x) % depth)].xyz;
            randomPos = randomPos * 2 - 1;  // 노이즈 범위
            float radius = sqrt(dot(randomPos, randomPos));
            if (radius <= 1)    // 입자 추가
            {
                float3 pos = sourceRadius * randomPos + sourceCenter;

                if (pos.x >= 0.5)
                {
                    particles[ref.value].pos = pos;
                    particles[ref.value].vel = float3(32 * sourceStrength / 64.0, 0, 0) / dxBase;   // 초기속도
                    sortElements[dtID.x].key = MinCornerCell(particles[ref.value].pos);
                }
            }
        }
        else // Source 2  // ID 홀수 (예제 실행해보면 양쪽에서 나옴. 이를 짝홀수로 나눈 것
        {
            float3 sourceCenter = float3(1.0 - 0.02, 0.6, 0.5) / dxBase;
            float sourceRadius = 0.1 / dxBase.y;
            float3 randomPos = noiseTex[uint3(int(time * 654.321) % width, int(time * 123 + dtID.x * 1.73) % height, (time * 456 + gId.x * 7) % depth)].xyz;
            randomPos = randomPos * 2 - 1;
            float radius = sqrt(dot(randomPos, randomPos));
            if (radius <= 1)
            {
                float3 pos = sourceRadius * randomPos + sourceCenter;

                if (pos.x < 1.0 / dxBase.x - 0.5)
                {
                    particles[ref.value].pos = pos;
                    particles[ref.value].vel = float3(-32 * sourceStrength / 64.0, 0, 0) / dxBase;  // 속도가 반대
                    sortElements[dtID.x].key = MinCornerCell(particles[ref.value].pos);
                }
            }
        }
    }
}
