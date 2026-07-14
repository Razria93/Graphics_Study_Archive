#pragma once

#include "AppBase.h"

#include "physx/PxPhysicsAPI.h"

// pvd : PhysX Visual Debugger
// 기본 사용법은 SnippetHelloWorld.cpp
// 렌더링 관련은 SnippetHelloWorldRender.cpp

// #define PX_RELEASE(x)                                                          \
//     if (x) {                                                                   \
//         x->release();                                                          \
//         x = NULL;                                                              \
//     }

#define PVD_HOST "127.0.0.1"		// VisualDebbuger용
#define MAX_NUM_ACTOR_SHAPES 128	// 최대 물체 갯수

namespace hlab
{

using namespace physx;

class Ex1901_PhysX : public AppBase
{
  public:
	Ex1901_PhysX();

	// SmartPointer를 사용하지 않기 때문에 마지막에 청소해주어야함
	~Ex1901_PhysX()
	{
		PX_RELEASE(gScene);
		PX_RELEASE(gDispatcher);
		PX_RELEASE(gPhysics);
		if (gPvd)
		{
			PxPvdTransport* transport = gPvd->getTransport();
			gPvd->release();
			gPvd = NULL;
			PX_RELEASE(transport);
		}
		PX_RELEASE(gFoundation);
	}

	// 동적으로 움직이는 물체 만드는 것
	PxRigidDynamic* createDynamic(const PxTransform& t,
	                              const PxGeometry& geometry,
	                              const PxVec3& velocity = PxVec3(0))
	{
		PxRigidDynamic* dynamic =
		    PxCreateDynamic(*gPhysics, t, geometry, *gMaterial, 10.0f);
		dynamic->setAngularDamping(0.5f);		// 회전에 대한 Damping (각속도를 줄여주는 일종의 마찰) / (Damper : 감속기, 속도를 줄여줌)
		dynamic->setLinearVelocity(velocity);	// 이동에 대한 속도 [6자유도(x,y,z 이동 / x,y,z 회전)] / 각속도랑은 다름 (각속도는 3자유도)
		gScene->addActor(*dynamic);				
		return dynamic;
	}

	void createStack(const PxTransform& t, PxU32 size, PxReal halfExtent)
	{
		// 시작할 때 보이는 상자들을 만들어줌 (Stack)
		vector<MeshData> box = {GeometryGenerator::MakeBox(halfExtent)};

		PxShape* shape = gPhysics->createShape(
		    PxBoxGeometry(halfExtent, halfExtent, halfExtent), *gMaterial);

		for (PxU32 i = 2; i < size; i++)
		{
			for (PxU32 j = 0; j < size - i; j++)
			{
				// PxTransform : 
				// PxQuatT (float4) : 방향 (회전)
				// PxVec3T (float3) : 위치 (이동)
				// 강체는 모양의 변형이 없다고 가정하므로 Scale이 필요가 없음
				// PxReal (float) : 자료형을 다 구분해놓았음

				// PxRigidDynamic : 물리계산용
				PxTransform localTm(PxVec3(PxReal(j * 2) - PxReal(size - i),
				                           PxReal(i * 2 + 1), 0) *
				                    halfExtent);
				PxRigidDynamic* body =
				    gPhysics->createRigidDynamic(t.transform(localTm));	// localTm에 RigidDynamic을 만들어 달라고 요청
				body->attachShape(*shape);								// 해당 객체에 박스모양을 결합
				PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);		// Mess(질량 : 물체 자체의 질량) / Inertia(회전에 대한 질량 : 회전에서 질량 같은 것)
																		// 밀도에 따라서 질량을 계산하고 Inertia를 구함
				gScene->addActor(*body);

				// 렌더러 부분
				// Model : 렌더링용
				auto m_newObj =
				    std::make_shared<Model>(m_device, m_context, box);	// 최적화는 sharedPt를 지양해야하나, 교육용이거나 속도보단 안정성이 중요할 때
				m_newObj->m_materialConsts.GetCpu().albedoFactor =
				    Vector3(0.5f);
				AppBase::m_basicList.push_back(m_newObj);	// m_basicList가 Sence에 대응
				this->m_objects.push_back(m_newObj);

				// 추 후에 최적화를 하게 될 경우, 물리계산과 렌더링을 같은 객체에 담긴 정보를 기반으로 해야함
			}
		}
		shape->release();	// 다쓰고 지움
	}

	void InitPhysics(bool interactive);

	bool InitScene() override;

	void UpdateLights(float dt) override;
	void UpdateGUI() override;
	void Update(float dt) override;
	void Render() override;

  public:
	PxDefaultAllocator gAllocator;
	PxDefaultErrorCallback gErrorCallback;
	PxFoundation* gFoundation = NULL;
	PxPhysics* gPhysics = NULL;
	PxDefaultCpuDispatcher* gDispatcher = NULL;
	PxScene* gScene = NULL;
	PxMaterial* gMaterial = NULL;
	PxPvd* gPvd = NULL;
	PxReal stackZ = 10.0f;

	vector<shared_ptr<Model>> m_objects;
};

} // namespace hlab
