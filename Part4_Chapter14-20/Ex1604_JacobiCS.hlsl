Texture3D<float> pressureTemp : register(t0);
Texture3D<float> divergence : register(t1);

// boundary conditions
// -1: Dirichlet condition
// -2: Neumann condition
//  0: Full cell
Texture3D<int> bc : register(t2);

RWTexture3D<float> pressure : register(u0);

SamplerState pointClampSS : register(s0);
SamplerState linearClampSS : register(s1);

static int3 offset[6] =
{
    int3(1, 0, 0), // right
    int3(-1, 0, 0), // left
    int3(0, 1, 0), // up
    int3(0, -1, 0), // down
    int3(0, 0, 1), // back
    int3(0, 0, -1) // front
};

[numthreads(16, 16, 4)]
void main(uint3 dtID : SV_DispatchThreadID)
{
    if (bc[dtID.xyz] >= 0)
    {
        float temp = 0.0;

        for (int i = 0; i < 6; i++)
        {
            if (bc[dtID.xyz + offset[i]] == -1) // Dirichlet
            {
                // 정확하게 하려는 경우 ApplyPressureCS와 같이 경계조건에 맞는 압력값을 넣어주어야함
                temp += -pressureTemp[dtID.xyz];
            }
            else if (bc[dtID.xyz + offset[i]] == -2) // Neumann
            {
                temp += pressureTemp[dtID.xyz];
            }
            else
                temp += pressureTemp[dtID.xyz + offset[i]];
        }
        // TODO:
        // 인접 픽셀이 6개이기 때문에 6.0으로 나누어줌
        pressure[dtID.xyz] = (-divergence[dtID.xyz] + temp) / 6.0;
    }
}
