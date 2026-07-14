#pragma once

#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <iostream>
#include <memory>

#include "AppBase.h"
#include "BillboardPoints.h"
#include "CubeMapping.h"
#include "GeometryGenerator.h"
#include "ImageFilter.h"
#include "Light.h"
#include "TessellatedQuad.h"

namespace hlab {

using DirectX::BoundingSphere;
using DirectX::SimpleMath::Vector3;

class ExampleApp : public AppBase {
  public:
    ExampleApp();

    virtual bool Initialize() override;
    virtual void UpdateGUI() override;
    virtual void Update(float dt) override;
    virtual void Render() override;

    void MainPass();
    void DepthPass(TextureBuffer &textureBuffer,
                   ComPtr<ID3D11Buffer> &depthEyeViewProjConstBuffer);

  protected:
    shared_ptr<BasicMeshGroup> m_ground;
    shared_ptr<BasicMeshGroup> m_mainObj;
    shared_ptr<BasicMeshGroup> m_lightSphere;
    BoundingSphere m_mainBoundingSphere;
    BasicMeshGroup m_cursorSphere;
    CubeMapping m_cubeMapping;

    bool m_usePerspectiveProjection = true;

    Light m_light;
    Vector3 m_lightCenter = Vector3(0.0f, 1.5f, 2.0f);
    Vector3 m_lightOffset = Vector3(0.8f, 0.0f, 0.0f);

    // 거울이 아닌 물체들의 리스트 (for문으로 그리기 위함)
    vector<shared_ptr<BasicMeshGroup>> m_basicList;
};

} // namespace hlab
