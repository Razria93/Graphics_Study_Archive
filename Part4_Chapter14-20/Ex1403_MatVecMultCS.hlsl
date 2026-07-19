Texture2D<float4> matTex : register(t0); // (width, height) = (numCols/4, numRows)
Texture2D<float4> vecTex : register(t1); // (width, height) = (numCols/4, 1)
RWTexture2D<float> outputTex : register(u0); // (width, height) = (numRows, 1)

// float4 자료형을 사용함으로서 픽셀 1개에 
// 출력 벡터의 차원(numRows / 4)에 대해 여러 쓰레드로 나눠서 계산

// 	- SV_GroupID : (2, 1, 0) 
// 		- 수많은 그룹 중에서 어떤 그룹에 속해있는지 알 수 있는 ID
// 		  
// 	- SV_GroupThreadID : (7, 5, 0) 
// 		- 그룹 내의 수많은 스레드들 중 에서 어떤 스레드인지 알 수 있는 ID
// 		  
// 	- SV_DispatchThreadID : (2, 1, 0) * (10, 8 , 3) + (7, 5, 0) = (27, 13, 0) 
// 		- 그룹 구분없이 전체 스레드 기준으로 봤을 때 어떤 스레드인지 알 수 있는 ID

// 디버깅할 때는 (1, 1, 1)로도 테스트
[numthreads(256, 1, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
    // matrix 기준 width, height
    uint width, height;
    matTex.GetDimensions(width, height);

    uint r = dtID.x;                    // 행 인덱스
    float sum = 0.0;                    // 결과 누적용 변수 (행과 벡터의 내적 결과)
    for (uint i = 0; i < width; i++)    // 행의 모든 열 순회 (i는 [연산되고 있는 행의 몇번째 열(몇번째 float4 묶음)인지]에 대한 값)
    {
        // TODO:
        float4 m = matTex[uint2(i, r)]; // 행렬의 [i번째 float4 묶음, r번째 행]을 읽음
        float4 v = vecTex[uint2(i, 0)]; // 벡터의 [i번째 float4 묶음]을 읽음
        
        // 행렬을 행단위로 연산하는 방식이며,
        // 행을 이루는 각각의 요소별로 곱해야하는 벡터와 1:1로 대응하고 연산하는 방식
        // 따라서 행의 모든 요소가 벡터와 연산이 끝나고 합산되어야 비로소 하나의 행과 벡터가 연산이 된 값이 도출이 됨
        sum += dot(m, v);
    }

    // outputTex[dtID.xy].r = sum; // 행렬 벡터 곱하기

    // 2D 텍스쳐 좌표이기 때문에 xy로 지정하지만 사실상 y방향 스레드는 1개이기 때문에 항상 0(0번째 열)임
    outputTex[dtID.xy].r += sum; // 반복 누적 테스트
}
