#include "Ex1606_Common.hlsli"

StructuredBuffer<Particle> particles : register(t0);
StructuredBuffer<SortElement> sortElements : register(t1);
Texture3D<uint> firstIndex : register(t2);

RWTexture3D<float4> velocity : register(u0);
RWTexture3D<float> density : register(u1);
RWTexture3D<float> signedDistance : register(u2);

float CubicSpline(const float q)
{
    float coeff = 3.0f / (2.0f * 3.141592f);

    if (q < 1.0f)
        return coeff * (2.0f / 3.0f - q * q + 0.5f * q * q * q);
    else if (q < 2.0f)
        return coeff * pow(2.0f - q, 3.0f) / 6.0f;
    else // q >= 2.0f
        return 0.0f;
}

// https://en.wikipedia.org/wiki/Smoothstep
float smootherstep(float x, float edge0 = 0.0f, float edge1 = 1.0f)
{
    // Scale, and clamp x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0), 0, 1);

    return x * x * x * (3 * x * (2 * x - 5) + 10.0f);
}

float ZhuKernel(float s)
{
    float temp = 1 - s * s;
    return max(0, temp * temp * temp);
}

[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    uint width, height, depth;
    firstIndex.GetDimensions(width, height, depth);
    
    uint numStructs, stride;
    sortElements.GetDimensions(numStructs, stride);
    
    density[dtID] = 0.0;
    signedDistance[dtID] = 1.0;
    velocity[dtID] = float4(0, 0, 0, 0);
    
    float3 posTemp = float3(0, 0, 0);
    
    if (dtID.x > 0 && dtID.y > 0 && dtID.z > 0
        && dtID.x < width - 1 && dtID.y < height - 1 && dtID.z < depth - 1)
    {
        float3 cellCenter = dtID + 0.5;
        
        // 주변의 가까운 입자들만 찾아서 for문을 돌리기 위한 구조
        for (int k = -1; k < 1; k++)
            for (int j = -1; j < 1; j++)
                for (int i = -1; i < 1; i++)
                {
                    uint firstId = firstIndex[dtID + int3(i, j, k)];
                    
                    if (firstId != INACTIVE)
                    {
                        int p = 0;

                        [loop]
                        while (true)
                        {
                            SortElement ref = sortElements[firstId + p];
                        
                            if (ref.key == INACTIVE)
                                break;

                            if (ref.key != sortElements[firstId].key)
                                break;
                        
                            float dist = length(particles[ref.value].pos - cellCenter);
                            float weight = CubicSpline(dist * 2.0);
                            //float weight = ZhuKernel(dist);
                            density[dtID] += weight;                                            // 가까이 있는 입자들만 가중치를 더해서 그리드의 밀도를 올림 (입자의 분포를 density로 샘플링)
                            velocity[dtID] += weight * float4(particles[ref.value].vel, 0.0);   // 입자들의 속도들도 가중치를 더해서 그리드의 속도로 옮김   (입자의 속도를 속도장(격자 텍스쳐 메모리)으로 샘플링)
                            posTemp += weight * particles[ref.value].pos;                       // 주변 파티클들의 위치를 가중치를 반영하여 모두 더함
                            
                            p++;
                        
                            if (firstId + p == numStructs)
                                break;
                        }
                    }
                }

        if (density[dtID] > 1e-6)
        {
            // 평균을 냄
            // 가중치에 의한 평균을 냄 (가까운 입자들에 더 영향을 크게 받도록)
            // density가 위에서 weight의 합이기 때문
            velocity[dtID] /= density[dtID];
            posTemp /= density[dtID];   // 그리고 그 포지션의 대표 평균을 만듦
            
            signedDistance[dtID] = length(posTemp - cellCenter) - 1;    // SDF : 거리값
                                                                        // 그리고 그 셀에 대표입자 1개 있다고 생각하고 SDF를 추출함
        }
    }
}
