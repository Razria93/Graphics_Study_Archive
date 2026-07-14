#pragma once

#include "AppBase.h"
#include "Model.h"

namespace hlab
{

class Ex1401_Basic : public AppBase
{
  public:
	// __declspec(align(256))
	//	- 시작 주소를 256바이트 경계(256-byte boundary)에 맞추기 위한 코드
	//	- GPU가 ConstantsBuffer를 읽을 때 '256B 단위 블록' 단위로 읽으려 하기 때문임
	//	[예시]
	//	- 구조체 이름 : Constants[0] / 시작주소 : 0x0000 / 실제크기 : 4Byte
	//	- 구조체 이름 : Constants[1] / 시작주소 : 0x0100 / 실제크기 : 4Byte
	//	- 구조체 이름 : Constants[2] / 시작주소 : 0x0200 / 실제크기 : 4Byte
	__declspec(align(256)) struct Constants
	{
		float scale = 1.0f;
	};

	Ex1401_Basic();

	// 템플릿 메서드 패턴(Template Method Pattern) 구조
	//	- 가상 함수를 이용한 런타임 다형성 기반 인터페이스 설계
	//	- AppBase가 실행 흐름의 공통 틀(Template Method) 을 제공
	//	- 파생 클래스들이 그 틀 안에서 자신만의 구현을 수행
	virtual bool Initialize() override;
	virtual void UpdateGUI() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

  protected:
	// 예시용이라서 GraphicsCommon.h/cpp에 구현하지 않음
	ComPtr<ID3D11ComputeShader> m_testCS;
	ComputePSO m_testComputePSO;

	ComPtr<ID3D11UnorderedAccessView> m_backUAV;

	Constants m_constsCPU;
	ComPtr<ID3D11Buffer> m_constsGPU;
};

} // namespace hlab