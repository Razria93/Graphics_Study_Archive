// Advect Velocity and Density

Texture3D<float4> velocityUp : register(t0);
Texture3D<float> densityUp : register(t1);

RWTexture3D<float4> velocity : register(u0);
RWTexture3D<float> density : register(u1);

cbuffer Consts : register(b4)
{
    float3 dxBase;
    float dt;
    float3 dxUp;
    float time;
    int upScale;
}

static int3 offset[6] =
{
    int3(1, 0, 0), // right
    int3(-1, 0, 0), // left
    int3(0, 1, 0), // up
    int3(0, -1, 0), // down
    int3(0, 0, 1), // back
    int3(0, 0, -1) // front
};


// Run with Down-resolution
// 해당 CS는 저해상도(Low-Resolution)를 기준으로 쓰레드를 실행하며, 각 저해상도 셀 하나가 고해상도(High-Res)의 여러 셀을 평균 내는 역할을 함
[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    float4 velocitySum = float4(0, 0, 0, 0);
    float densitySum = 0.0;
    
    // [기준]
    // dtID : 저해상도 텍셀의 좌표 (예: 64x32x32 해상도)
    // dtIdUp : 고해상도 텍셀의 좌표 (예: 128x64x64 해상도)
    //  - '저해상도 공간의 1개 셀에 대응되는 고해상도 영역의 시작 인덱스'를 찾기 위해 사용함
    uint3 dtIdUp = dtID * upScale;
    
    // [loop]
    for (int k = 0; k < upScale; k++)
        for (int j = 0; j < upScale; j++)
            for (int i = 0; i < upScale; i++)
            {
                // TODO:
                // 다운샘플링 : 모두 더하고 평균값
                velocitySum += velocityUp[dtIdUp + int3(i, j, k)];
                densitySum += densityUp[dtIdUp + int3(i, j, k)];
            }
    
    float scale = 1.0 / (upScale * upScale * upScale);
    
    velocity[dtID] = velocitySum * scale;
    density[dtID] = densitySum * scale;
}
