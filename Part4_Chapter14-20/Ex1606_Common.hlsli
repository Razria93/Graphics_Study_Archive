#define INACTIVE 4294967295U // 0xFFFFFFFF

struct Particle
{
    float3 pos;
    float3 vel;
};

struct SortElement
{
    uint key; // Cell index         [입자가 포함되어 있는 셀의 1차원 인덱스] : 1차원 인덱스에 따라 정렬을 하면 입자가 간접적으로 위치에 따라 정렬하는 것처럼 보임
    uint value; // Particle index   [2차원 격자의 번호이름]
};

static int3 offset[6] =
{
    int3(1, 0, 0), // right
    int3(-1, 0, 0), // left
    int3(0, 1, 0), // up
    int3(0, -1, 0), // down
    int3(0, 0, 1), // back
    int3(0, 0, -1) // front
};

cbuffer Consts : register(b4)
{
    float3 dxBase;
    float dt;
    float3 dxUp;
    float time;
    int upScale = 1;
    int numNewParticles = 0;
    float turbulence = 0.0;
    float sourceStrength = 1.0;
    uint width;
    uint height;
    uint depth;
}