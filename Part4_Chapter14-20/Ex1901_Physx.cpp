#include "Ex1901_PhysX.h"

#include "GeometryGenerator.h"
#include "GraphicsCommon.h"
#include "OceanModel.h"

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Ex1901_PhysX::Ex1901_PhysX() : AppBase() {}

void Ex1901_PhysX::InitPhysics(bool interactive)
{
	gFoundation =
	    PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback); // 물리엔진의 핵심

	gPvd = PxCreatePvd(*gFoundation); // 비쥬얼 디버거
	PxPvdTransport* transport =       // 오류 송부용 객체
	    PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, // 피직스, ToleranceScale (오차범위) 설정
	                           PxTolerancesScale(), true, gPvd);

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale()); // 씬에서 사용할 설정값
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2); // 쓰레드 몇개나 쓸 것인지
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc); // 씬 생성

	PxPvdSceneClient* pvdClient = gScene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES,
		                           true);
	}
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f); // 물리 관점에서 봤을 때 재질 (운동량을 얼마나 흡수할려고 하는가)
	                                                        // (staticFriction : 멈춰있다 움직일 때 / dynamicFriction : 움직이는 상황에서 마찰 계수 / restitution : 튕겨나갈 때 운동량을 얼마나 흡수할지)

	// PxPlane :
	//  - 위의 a* x_0 + b* y_0 + c* z_0 + d = 0 는 점과 벡터의 dotProduct 
	//  - 평면과 수직관계를 이루는 법선벡터 vec3(a, b, c) & 원점과 평면사이의 거리 d 를 기반으로 평면을 설정할 수 있음
	PxRigidStatic* groundPlane =
	    PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
	gScene->addActor(*groundPlane);

	for (PxU32 i = 0; i < 5; i++)
		createStack(PxTransform(PxVec3(0, 1.0f, stackZ -= 1.0f)), 15, 0.2f);	// 실행하면 위에서 아래로 떨어지는 박스들을 생성하는 코드

	if (!interactive)
		createDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10),	// 공을 만들어준는 함수 (19_01에서는 미사용)
		              PxVec3(0, -50, -100));
}

bool Ex1901_PhysX::InitScene()
{

	AppBase::m_camera.Reset(Vector3(-11.9666f, 4.85741f, -1.85711f), 0.981748f,
	                        0.239983f);

	AppBase::m_globalConstsCPU.strengthIBL = 1.0f;
	AppBase::m_globalConstsCPU.lodBias = 0.0f;

	AppBase::InitCubemaps(
	    L"../Assets/Textures/Cubemaps/HDRI/", L"clear_pureskyEnvHDR.dds",
	    L"clear_pureskySpecularHDR.dds", L"clear_pureskyDiffuseHDR.dds",
	    L"clear_pureskyBrdf.dds");

	AppBase::InitScene();

	InitPhysics(true);

	return true;
}

void Ex1901_PhysX::UpdateLights(float dt) { AppBase::UpdateLights(dt); }

void Ex1901_PhysX::Update(float dt)
{

	AppBase::Update(dt);

	gScene->simulate(1.0f / 60.0f);
	gScene->fetchResults(true);		// 시뮬레이션 한 결과글 가져올지

	// gScene->getActors()
	// PxGeometryType::eBOX: , case PxGeometryType::eSPHERE:

	PxU32 nbActors = gScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC |
	                                     PxActorTypeFlag::eRIGID_STATIC);
	std::vector<PxRigidActor*> actors(nbActors);
	gScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC |
	                      PxActorTypeFlag::eRIGID_STATIC,
	                  reinterpret_cast<PxActor**>(&actors[0]), nbActors);

	PxShape* shapes[MAX_NUM_ACTOR_SHAPES];

	int count = 0;

	for (PxU32 i = 0; i < nbActors; i++)
	{

		const PxU32 nbShapes = actors[i]->getNbShapes();
		PX_ASSERT(nbShapes <= MAX_NUM_ACTOR_SHAPES);
		actors[i]->getShapes(shapes, nbShapes);
		for (PxU32 j = 0; j < nbShapes; j++)
		{
			const PxMat44 shapePose(
			    PxShapeExt::getGlobalPose(*shapes[j], *actors[i]));				// 시뮬레이션 된 뒤에 현재 pos가 어디인지 가져오는 함수

			if (actors[i]->is<PxRigidDynamic>())
			{

				bool speeping = actors[i]->is<PxRigidDynamic>() &&
				                actors[i]->is<PxRigidDynamic>()->isSleeping();
				// cout << i << " : " << shapePose.getPosition().y << " sleeping
				// "
				//      << speeping << endl;

				m_objects[count]->UpdateWorldRow(Matrix(shapePose.front()) *
				                                 Matrix::CreateScale(1.00f));	// UpdateWorldRow :
																				//  - shapePose를 가지고 현재 사용하고 있는 Model의 4x4 월드행렬을 업데이트 함
																				// CreateScale :
																				//  - 시뮬레이션과 렌더링의 수치 Scale이 다를 경우 이를 보정해주는 함수
				m_objects[count]->UpdateConstantBuffers(m_device, m_context);

				count++;
			}
		}
	}

	/* PxContactPair 추출 하면 내 캐릭터가 어디에 닿았는지 찾을 수 있음
	* PxContactPairPoint : 
	*  - 특정 2점의 페어 -> 어떤 지점에서 어떤 물체들이 충돌했는지 체크할 때 사용하는 구조체
	*  - 게임의 본진을 공부하려면 물리엔진 필수
	*  - 그래픽같은 기술은 한번 개발이 되면 전체적으로 평준화되어 차별성이 사라지며,
	*	 게임의 본질과 재미에 직결되는 '폴레이적인 요소 (이동, 충돌, 상호작용, 현실감 등)은 모두 물리엔진, 충돌엔진과 가깝기 때문에 더 공부를 열심히 해야함
	*  - 그래픽스의 여러가지 이유로 그래픽적인 요소 (렌더링)을 먼저 배우고 물리적인 요소가 뒤에 나오나,
	*	 실질적으로 엔진에 사용되는 핵심 기저는 물리엔진이 기반이 된 상태로 렌더링 기술들을 덮어 씌우는 것이기 때문에 뼈대가 되는 물리엔진을 확실하게 공부 해야함
	*  - 물리엔진과 충돌을 찾는 자료구조

	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
	{
	    PX_UNUSED((pairHeader));
	    std::vector<PxContactPairPoint> contactPoints;

	    for(PxU32 i=0;i<nbPairs;i++)
	    {
	        PxU32 contactCount = pairs[i].contactCount;
	        if(contactCount)
	        {
	            contactPoints.resize(contactCount);
	            pairs[i].extractContacts(&contactPoints[0], contactCount);

	            for(PxU32 j=0;j<contactCount;j++)
	            {
	                gContactPositions.push_back(contactPoints[j].position);
	                gContactImpulses.push_back(contactPoints[j].impulse);
	            }
	        }
	    }
	}
	*/
}

void Ex1901_PhysX::Render()
{
	AppBase::Render();
	AppBase::PostRender();
}

void Ex1901_PhysX::UpdateGUI() { AppBase::UpdateGUI(); }

} // namespace hlab
