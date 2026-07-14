// RW       : ReadWrite    (텍스쳐 타입)
// <float4> : Pixel Format (RGBA 각각 float)
// u0       : Unordered Access View
RWTexture2D<float4> gOutput : register(u0);

cbuffer MyBuffer : register(b0)
{
    float scale;
}

// numthreads 공식 문서
// https://learn.microsoft.com/ko-kr/windows/win32/direct3dhlsl/sm5-attributes-numthreads
// numthreads : 하나의 그룹 안에서 실행되는 스레드 개수 (x, y, z)
// numthreads의 총합이 1024를 넘어가서는 안됨 (위 문서 참고)
// 해당 값은 유연하게 바꿀 수 없음
[numthreads(32, 32, 1)]
void main(int3 gID : SV_GroupID, uint3 tID : SV_DispatchThreadID)
// HLSL 파일 - (좌클릭) - Properties - HLSL Compiler - EntyPoint Name : main (기본)
{
    // [스레드 식별자]
    //   - SV_GroupID           : 어떤 그룹에 속했는지
    //   - SV_GroupThreadID     : 그룹 내 로컬 스레드 좌표
    //   - SV_DispatchThreadID  : 전체 스레드 기준 1D 인덱스
    //   - SV_GroupIndex        : 그룹 내부 스레드 기준 1D 인덱스
      
    // if ((gID.x + gID.y) % uint(2) == 0) // 결과값은 동일함
    if ((gID.x % uint(2) == 0) ^ (gID.y % uint(2) == 0))
    {
        gOutput[tID.xy] = float4(1.0, 1.0, 1.0, 1.0);
        // gOutput[tID.xy] = gOutput[tID.xy] + 0.001; // 읽기 + 연산 = 쓰기 
    }
    else
    {
        gOutput[tID.xy] = float4(0.5, 0.5, 0.5, 1.0);
    }
    
    // 원그리기
    // float radius = 50.0;
    // float3 center = float3(1280.0 / 2, 720.0 / 2, 0.0);
    // 
    // float x = tID.x - center.x;
    // float y = tID.y - center.y;
    // 
    // if ((radius * radius)   > (x * x + y * y))
    // {
    //     gOutput[tID.xy] = float4(0.5, 0.5, 0.5, 1.0);
    // }
    // else
    // {
    //     gOutput[tID.xy] = float4(1, 1, 1, 1) * scale;
    // }
}
