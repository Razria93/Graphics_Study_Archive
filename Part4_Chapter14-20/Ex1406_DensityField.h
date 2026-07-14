#pragma once

#include "AppBase.h"
#include "Model.h"
#include "StructuredBuffer.h"
#include "Texture2D.h"

namespace hlab
{

class Ex1406_DensityField : public AppBase
{
  public:
	struct Particle
	{
		Vector3 position;
		Vector3 color;
	};

	Ex1406_DensityField();

	virtual bool Initialize() override;
	virtual void UpdateGUI() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	void DissipateDensity();
	void AdvectParticles();
	void DrawSprites();

  protected:
	StructuredBuffer<Particle> m_particles;
	Texture2D m_densityTex;

	// Shaders
	ComPtr<ID3D11VertexShader> m_vertexShader;			// Ex1404_StructuredBufferVS
	ComPtr<ID3D11PixelShader> m_pixelShader;			// Ex1406_SpritePS
	ComPtr<ID3D11InputLayout> m_inputLayout;
	ComPtr<ID3D11ComputeShader> m_densitySourcingCS;	// Ex1406_DensitySourcingCS
	ComPtr<ID3D11ComputeShader> m_densityDissipationCS;	// Ex1406_DensityDissipationCS
	ComPtr<ID3D11GeometryShader> m_spriteGS;			// Ex1406_SpriteGS
};

} // namespace hlab