#pragma once

#include <directxtk/SimpleMath.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace hlab
{

using DirectX::SimpleMath::Matrix;
using DirectX::SimpleMath::Quaternion;
using DirectX::SimpleMath::Vector3;
using std::map;
using std::string;
using std::vector;

struct AnimationClip
{

	struct Key
	{
		// fbx 데이터가 아래처럼 구성이 되어 있음
		//  변환행렬의 구성요소
		Vector3 pos = Vector3(0.0f);   // translate
		Vector3 scale = Vector3(1.0f); // scale
		Quaternion rot = Quaternion(); // rotate

		Matrix GetTransform() // 해당 정보를 가지고 Matrix를 만들어서 반환
		{
			return Matrix::CreateScale(scale) * // 해당 예제에서는 사용 안함
			       Matrix::CreateFromQuaternion(rot) *
			       Matrix::CreateTranslation(pos);
		}
	};

	string name;              // Name of this animation clip
	vector<vector<Key>> keys; // m_key[boneIdx][frameIdx]
	int numChannels;          // Number of bones
	int numKeys;              // Number of frames of this animation clip
	double duration;          // Duration of animation in ticks
	double ticksPerSec;       // Frames per second
};

struct AnimationData
{

	map<string, int32_t> boneNameToId; // 뼈 이름과 인덱스 정수
	vector<string> boneIdToName;       // boneNameToId의 Id 순서대로 뼈 이름 저장
	vector<int32_t> boneParents;       // 부모 뼈의 인덱스
	vector<Matrix> offsetMatrices;
	vector<Matrix> boneTransforms;
	vector<AnimationClip> clips;
	Matrix defaultTransform;
	Matrix rootTransform = Matrix();
	Matrix accumulatedRootTransform = Matrix();
	Vector3 prevPos = Vector3(0.0f);

	Matrix Get(int clipId, int boneId, int frame)
	{

		return defaultTransform.Invert() * offsetMatrices[boneId] *
		       boneTransforms[boneId] * defaultTransform;

		// - defaultTransform.Invert() : 엔진좌표계 -> FBX 좌표계
		// - defaultTransform : FBX 좌표계 -> 엔진자표계

		// - offsetMatrices[boneId], boneTransforms[boneId]는 FBX에서 가져온 데이터
		//	 따라서 연산을 하고 싶다면 FBX 좌표계에서 사용해야함
		// 
		// - offsetMatrices : 
		//		- 메시 좌표	= 바인드 포즈 기준
		//		  본 변환	= 현재 포즈 기준
		//		- 따라서 메시 좌표에서 바인드 포즈를 제거하여 아무런 변환이 적용되어 있지 않은 상태로 돌려야함
		//	
		//		- 비교를 하자면 가위질을 하기 위해 가위를 샀음
		//		- 근데 가위가 날을 잘 보여주기 위해서 날이 벌려진 상태에서 출고 됨
		//		- 가위질을 하기 위해서는 손가락을 벌렸다가 모았다가 하는 애니메이션을 취해야하는데 
		//		  이미 벌려진 상태에서 애니메이션을 적용할 경우 원치 않는 형태로 동작하게 됨
		//		- 따라서 벌려진 가위 날을 다문 기본 상태로 돌려야함
		//		- offsetMatrices 이 [기본 상태로 되돌리는 행렬]
		//		- boneTransforms 이 [기본으로 돌린 상태에서 적용되는 애니메이션 행렬]

		// defaultTransform은 모델을 읽어들일때 GeometryGenerator::Normalize()
		// 에서 계산 defaultTransform.Invert() * offsetMatrices[boneId]를 미리
		// 계산해서 합치고 defaultTransform * rootTransform을 미리 계산해놓을
		// 수도 있습니다. 여기는 교육용 예제라서 좌표계 변환 사례로 참고하시라고
		// 남겨놨습니다.
	}

	void Update(int clipId, int frame)	// 매프레임 갱신
	{
		// 저장된 clips 중에서 clipId 번째 AnimationClip을 레퍼런스로 캐싱함
		auto& clip = clips[clipId];

		// if (clipId != 0)
		// {
		// 	std::cout << "clipId : " << clipId << " / frame : " << frame << std::endl;
		// }

		// 모든 본에 대하여 어떻게 변화시켜야할지를 정하는 for문
		// boneTransforms 는 bone의 갯수와 일치
		// bone의 순서가 트리구조로 정렬되었기 때문에 Root부터 시작해서 부모 -> 자식 순으로 for문이 실행됨
		// 자식이 부모의 transform에 영향을 받기 때문
		for (int boneId = 0; boneId < boneTransforms.size(); boneId++)
		{
			// m_key[boneIdx][frameIdx]에서 m_key[boneIdx]를 사용했으므로 keys는 해당 본의 frameIdx를 배열번호로 사용하여 데이터를 가져올 수 있음
			auto& keys = clip.keys[boneId];

			// 주의: 모든 채널(뼈)이 frame 개수가 동일하진 않음

			const int parentIdx = boneParents[boneId]; // 뼈의 순서를 부모->자식 순으로 정렬함 (트리구조, 최상단이 root, root는 index가 0번)
			                                           // 해당 코드는 각 bone의 부모가 누군지 저장해둔 배열로 자신의 idx를 넣으면 부모의 idx를 반환해줌
			                                           // parentIdx가 음수일 경우는 Root

			const Matrix parentMatrix = parentIdx >= 0					// M_{i-1}
			                                ? boneTransforms[parentIdx]
			                                : accumulatedRootTransform;	// Root인 경우, 캐릭터의 이동, 회전이 반영된 트랜스폼을 부모 트랜스폼으로 반영함 (게임 내 캐릭터의 월드이동변환(움직임)을 반영하는 것)
																		// Root bone일 경우 이전 프레임에서 누적한 월드상의 움직임을 부모로 삼아서 연속성을 구현하겠다는 것임

			// key : 해당 클립의 해당 본의 해당 프레임의 정보값을 가지고 있음 (위치, 스케일, 회전값)
			// 만약, keys.size()가 0일 경우에는 Identity 변환 -> 멈춰있음 (위치,스케일,회전 변한 것 없음)
			// frame은 tick 처럼 누적 증가하는 전역 카운터 (궁금하면 아래 코드)
			// std::cout << "frame : " << frame << std::endl;
			// 따라서 Loop의 경우 애니메이션을 반복적으로 실행해야하기 때문에 일정 패턴을 가지고 실행되어야함
			// 이를 현재 frame값을 animation의 전체 key값으로 나누어 적절한 데이터를 찾는 것

			// key : pos, rotate, scale 등 클립의 각 프레임별 애니메이션에 대한 뼈 정보를 저장하고 있는 구조체
			// key 복사 : 아래서 key의 pos를 0.0으로 만들어도 복사값이라 다음 클립때는 아래과정을 또 거침 (accumulatedRootTransform 누적 후 key.pos 제거 등등)
			auto key = keys.size() > 0					// 여기서 key값으로 반환되는건 Key 구조체 값으로 내부에 fbx에서 가져온 pos, rotate, scale값이 저장되며, 내부 함수를 통해 Matrix로 반환이 가능함
			               ? keys[frame % keys.size()]
			               : AnimationClip::Key();		// key가 reference 아님 (변환이 없음. 항등행렬 반환. 가만히 있음)

			
			// 루트 본의 transform은 항상 가장 먼저 계산해야 함
			if (parentIdx < 0) // parentIdx < 0 : Root 본일 경우 (Root는 부모가 없으므로 인덱스가 음수)
			{
				// RootMotion이 포함된 애니메이션의 경우
				//  - Root 본의 translation이 실제로 이동을 포함함
				//  - 하지만 애니메이션은 루프 재생되므로, 0프레임으로 돌아올 때 다시 원래 위치로 돌아가게 됨
				//  - 또한, 외부 이동 로직과 RootMotion이 동시에 적용되면 실제 의도보다 2배로 전진했다가 되돌아오는 현상이 발생함
				//  → 따라서 RootMotion을 분리(InPlace 처리)하거나, 누적 방식으로 처리해야 함

				// RootMotion을 누적 방식으로 처리하는 경우:
				//  - 각 프레임 간의 위치 변화량 (key.pos - prevPos)을 누적 변환 행렬에 곱함
				//  - 이렇게 하면 루프 재생 시에도 실제 이동이 계속 이어짐

				if (frame != 0) // 현재 프레임이 첫프레임이 아닐 경우
				{
					// 이전 프레임과의 위치 차이를 누적 이동으로 변환
					accumulatedRootTransform =
					    Matrix::CreateTranslation(key.pos - prevPos) *
					    accumulatedRootTransform;
				}
				else // 현재 프레임이 첫프레임일 경우
				{
					// 초기 높이값만 보정
					// 회전하는 것이 있을 경우 accumulatedRootTransform에 회전변환하는 것
					auto temp = accumulatedRootTransform.Translation();
					temp.y = key.pos.y; // 높이 방향만 첫 프레임으로 보정 [높이부분의 오차가 생기면 하늘로 날아가거나 땅밑으로 꺼지는걸 보정하는 것]
										// 정확한 보정을 원한다면 땅을 추적해서 보정
					accumulatedRootTransform.Translation(temp);
				}

				prevPos = key.pos;
				key.pos = Vector3(0.0f); // 대신에 RootMotion 이였던 애니메이션 내부에서 pos 값을 제거하여 [Inplace]로 만듦
										 // 그러나 애니메이션 1번의 루프의 총 이동량이 accumulatedRootTransform에 누적되므로
										 // 총 이동량을 기반으로 자연스러운 애니메이션을 구사할 수 있음과 동시에 RootMotion을 제거하는 것

				// 총 이동거리 추출작업
				// 즉, 일련의 과정은 루트 본의 실제 이동을 accumulatedRootTransform에 누적하고, 애니메이션 데이터에서는 이동값을 제거하는 과정이였음
			}

			// TODO: parentMatrix 사용
			// 여기서 만들어진 최종 행렬은 Get()에서 사용됨
			// GetTransform을 하게 될 경우 저장된 데이터를 기반으로 Transform 반환
			boneTransforms[boneId] = key.GetTransform() * parentMatrix;	// M_{i} : 해당 뼈에 대한 월드기준 변환값 (A{i-1} * ... * A_{0})
		}
	}
};

} // namespace hlab