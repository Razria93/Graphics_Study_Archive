#include "TileableNoise.hlsli"

RWTexture3D<float> densityTex : register(u0);

cbuffer Consts : register(b0)
{
    float3 uvwOffset;
    float lightAbsorptionCoeff = 5.0;
    float3 lightDir = float3(0, 1, 0);
    float densityAbsorption = 10.0;
    float3 lightColor = float3(1, 1, 1) * 40.0;
    float aniso = 0.3;
}

float cloudDensity(float3 uvw)
{
    //밀도 계산
    float freq = 4.0f;
    
    float pfbm = lerp(1., perlinfbm(uvw, 4., 7), .5);
    pfbm = abs(pfbm * 2.f - 1.f); // billowy perlin noise

    float g = worleyFbm(uvw, freq);
    float r = remap(pfbm, 0.f, 1.f, g, 1.f); // perlin-worley 방식 (노이즈 기반)
    float b = worleyFbm(uvw, freq * 2.0f);
    float a = worleyFbm(uvw, freq * 4.0f);

    float perlinWorley = r;
    float wfbm = g * .625f + b * .125f + a * .25f;

    // cloud shape modeled after the GPU Pro 7 chapter
    float cloud = remap(perlinWorley, wfbm - 1., 1., 0., 1.);
    cloud = remap(cloud, .85, 1., 0., 1.); // fake cloud coverage
    
    return saturate(cloud);
}

[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    uint width, height, depth;
    densityTex.GetDimensions(width, height, depth);
    
    // 기본 좌표 + 애니메이션을 위한 offset 까지 고려한 uvw 좌표
    float3 uvw = dtID / float3(width, height, depth) + uvwOffset; // 노이즈 생성을 위해 uvwOffset 사용
    // float3 uvw = dtID / float3(width, height, depth);
    
    // uvw로 3차원 텍스쳐좌표에서 샘플링해옴
    // 좀 더 정확히는 3차원 배열로써 사용하고 있는 것
    //  - 텍스쳐라기엔 16bit float 형태이기 때문에
    //  - 또한 dtID는 3차원 인덱스 (위치)
    
    // float3 center = (0.5, 0.5, 0.5);
    // float c = abs(length(uvw - center)) < 0.5 ? 1.0 : 0.0;
    
    densityTex[dtID] = cloudDensity(uvw);
}

// 텍스쳐 샘플링을 할 경우 주변의 픽셀들을 참고하여 Linear Interpolation을 함
//  - 3차원일 경우 8개의 픽셀위치에서 샘플링을 해오기 때문에 더 느림
//  - 또한 같은 픽셀위치가 여러번 호출되기 때문에 데이터가 중복됨
//  - 따라서 별도로 CS를 기반으로 계산하고 운용하는 식으로