struct Element
{
    uint key;
    uint value;
};

cbuffer MyBuffer : register(b0)
{
    // https://en.wikipedia.org/wiki/Bitonic_sorter Example Code
    uint k;
    uint j;
}

RWStructuredBuffer<Element> arr : register(u0);

[numthreads(1024, 1, 1)]
void main(int3 gID : SV_GroupID, int3 gtID : SV_GroupThreadID,
          uint3 dtID : SV_DispatchThreadID)
{
	// ^ (bitwise XOR : 같으면 0, 다르면 1)
	// i ^ j
	//	- i의 bit에서 j의 비트 위치만큼 뒤집으면 j 단위의 거리만큼 떨어진 인덱스가 됨
	//  - XOR로 뒤집히게 될 경우 그 bit에 해당하는 값이 더해지거나 빼지기 때문
    
    // for를 병렬처리 한다고 생각하면 됨
    int i = dtID.x;
    
    int l = i ^ j;
    
    if (l > i)
    {
        Element temp_i = arr[i];
        Element temp_l = arr[l];
        
        if (((i & k) == 0) && (arr[i].key > arr[l].key) ||
            ((i & k) != 0) && (arr[i].key < arr[l].key))
        {
            // Element temp = arr[i];
            arr[i] = temp_l;
            arr[l] = temp_i;
        }
    }
}
