#pragma once

#include <directxtk/SimpleMath.h>
#include <vector>

namespace hlab {

using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;

struct Vertex {
    Vector3 position;
    Vector3 normalModel;
    Vector2 texcoord;
    Vector3 tangentModel;
    // HERE : 중요!
    // Vector3 biTangentModel;
    // biTangent는 쉐이더에서 계산
    
    // 텍스쳐는 2D 이미지임
    // 텍스쳐 좌표만 있으면 색상을 샘플링해올 수 있음
    // 노멀맵은 텍스쳐 좌표에 따른 노멀값을 반환함
    // 노멀벡터는 텍스쳐 좌표계에 정의가 되어 있음 (3차원 텍스쳐 좌표계)
    // 왼손좌표계인 DX / 오른손 좌표계인 GL 모두 해당되는 이야기
    // 텍스쳐의 전면방향이 노멀의 +방향이 되게 하기 위해서는
    // DX는 Y가 아래로, GL은 Y가 위로 가야함
    // 아 이거떄문에 텍스쳐 좌표가 반대구나?
    // 노멀맵에서 샘플링한 노멀값을 렌더링에 사용하기 위해서는 해당 노멀값을 월드변환을 해주어야함
    // 해당 변환을 시켜주기 위해서는 노멀값이 원래 어떤 좌표계에 대해서 정의되어 있는지 알고 있어야함
    // 모델링 소프트웨어 & 디자이너가 만들어주는 것들은 일반적으로 탄젠트벡터가 있음
    // 근데 그렇지 않을 경우 직접 구해야함
};

} // namespace hlab