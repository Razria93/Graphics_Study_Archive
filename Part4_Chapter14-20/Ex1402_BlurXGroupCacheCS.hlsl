Texture2D<float4> inputTex : register(t0);
RWTexture2D<float4> outputTex : register(u0);

// 참고 자료: Luna DX11 교재 Ch. 12

static const float weights[11] =
{
    0.05f, 0.05f, 0.1f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f,
};

static const int blurRadius = 5;

#define N 256
#define CACHE_SIZE (N + 2*blurRadius) 
// [N + 2*blurRadius인 이유]
//  - 그룹의 양 끝단 쪽에 위치한 픽셀들은 샘플링할 때 끝단 너머의 색값 데이터도 필요하기 때문임

// Groupshared memory is limited to 16KB per group.
// A single thread is limited to a 256 byte region of groupshared memory for writing.
// https://learn.microsoft.com/en-us/windows/win32/direct3d11/direct3d-11-advanced-stages-compute-shader

// 그룹 내에서 공유하는 메모리
//  - 크기제한[16KB]가 있기 때문에 주의해서 사용
groupshared float4 groupCache[CACHE_SIZE];

// GroupCahe의 변동성을 위하여 numthread의 값을 하드코딩하지 않음
[numthreads(N, 1, 1)]
void main(uint3 gID : SV_GroupID, uint3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    uint width, height;
    outputTex.GetDimensions(width, height);

    // Task01_[Update GroupCache]
    // 01-01_범위 밖의 데이터 캐싱
    //  - GroupCache에 사용될 색상값을 캐싱하는 과정에서 양 끝단에 있는 값들은 Radius만큼 추가적으로 값을 가져와야함
    //  - 이를 맨 끝의 Thread 혼자 부담하지 않고 끝에 있는 스레드들이 분담하여 가져옴
    //  - 어짜피 GroupMemoryBarrierWithGroupSync에서 싱크를 하기 때문에 끝단의 Thread 작업이 늦어지면 전체 작업속도도 느려지기 때문에 분담하는 것
    if (gtID.x < blurRadius)
    {
        int x = max(int(dtID.x) - blurRadius, 0);
        groupCache[gtID.x] = inputTex[int2(x, dtID.y)];
    }
    
    if (gtID.x >= N - blurRadius)
    {
        int x = min(dtID.x + blurRadius, width - 1);
        groupCache[gtID.x + 2 * blurRadius] = inputTex[int2(x, dtID.y)];
    }
    
    // 01-01_범위 내의 데이터 캐싱
    groupCache[gtID.x + blurRadius] =
        inputTex[min(dtID.xy, uint2(width, height) - 1)];

    // 모든 스레드들의 작업 싱크를 맞추기 위한 함수
    //  - 작업이 끝난 스레드들도 다른 스레드들이 작업이 끝나기 전까지 이 부분에서 기다림
    //  - 데이터 캐싱이 완전히 끝나고 나서 작업
    GroupMemoryBarrierWithGroupSync();
    
    // Task02_[Update Color]
    float4 blurColor = float4(0, 0, 0, 0);

    [unroll]
    for (int i = -blurRadius; i <= blurRadius; ++i)
    {
        int k = gtID.x + blurRadius + i;
        blurColor += weights[i + blurRadius] * groupCache[k];
    }

    outputTex[dtID.xy] = blurColor;
}
