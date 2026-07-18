#include "Ex1803_Landscape.h"

#include <DirectXCollision.h> // 구와 광선 충돌 계산에 사용
#include <algorithm>
#include <directxtk/DDSTextureLoader.h>
#include <directxtk/SimpleMath.h>
#include <fstream>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "GeometryGenerator.h"
#include "GraphicsCommon.h"
#include "OceanModel.h"

namespace hlab {

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

namespace {

float SampleHeight(const vector<uint8_t> &heightMap, const int width,
                   const int x, const int z) {
    const int clampedX = std::clamp(x, 0, width - 1);
    const int clampedZ = std::clamp(z, 0, width - 1);
    return float(heightMap[clampedZ * width + clampedX]) / 255.0f;
}

MeshData MakeTerrainFromRaw(const string &filename) {
    constexpr int sourceWidth = 2049;
    constexpr int gridSlices = 256;
    constexpr float terrainSize = 20.0f;
    constexpr float heightScale = 3.0f;

    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot open terrain heightmap: " + filename);
    }

    vector<uint8_t> heightMap(sourceWidth * sourceWidth);
    file.read(reinterpret_cast<char *>(heightMap.data()), heightMap.size());
    if (file.gcount() != static_cast<streamsize>(heightMap.size())) {
        throw runtime_error("Invalid terrain heightmap size: " + filename);
    }

    MeshData mesh;
    mesh.vertices.reserve((gridSlices + 1) * (gridSlices + 1));

    const int sampleStep = (sourceWidth - 1) / gridSlices;
    const float halfSize = terrainSize * 0.5f;

    for (int z = 0; z <= gridSlices; ++z) {
        for (int x = 0; x <= gridSlices; ++x) {
            const int sourceX = x * sampleStep;
            const int sourceZ = z * sampleStep;
            const float u = float(x) / float(gridSlices);
            const float v = float(z) / float(gridSlices);

            const float h = SampleHeight(heightMap, sourceWidth, sourceX,
                                         sourceZ) *
                            heightScale;
            const float hL = SampleHeight(heightMap, sourceWidth,
                                          sourceX - sampleStep, sourceZ) *
                             heightScale;
            const float hR = SampleHeight(heightMap, sourceWidth,
                                          sourceX + sampleStep, sourceZ) *
                             heightScale;
            const float hD = SampleHeight(heightMap, sourceWidth, sourceX,
                                          sourceZ - sampleStep) *
                             heightScale;
            const float hU = SampleHeight(heightMap, sourceWidth, sourceX,
                                          sourceZ + sampleStep) *
                             heightScale;

            Vertex vertex;
            vertex.position =
                Vector3(u * terrainSize - halfSize, h, v * terrainSize - halfSize);
            vertex.normalModel = Vector3(hL - hR, 2.0f, hD - hU);
            vertex.normalModel.Normalize();
            vertex.texcoord = Vector2(u, v) * 16.0f;
            vertex.tangentModel = Vector3(1.0f, 0.0f, 0.0f);
            mesh.vertices.push_back(vertex);
        }
    }

    for (int z = 0; z < gridSlices; ++z) {
        for (int x = 0; x < gridSlices; ++x) {
            const uint32_t i0 = uint32_t(z * (gridSlices + 1) + x);
            const uint32_t i1 = i0 + 1;
            const uint32_t i2 = i0 + uint32_t(gridSlices + 1);
            const uint32_t i3 = i2 + 1;

            mesh.indices.push_back(i0);
            mesh.indices.push_back(i1);
            mesh.indices.push_back(i2);
            mesh.indices.push_back(i2);
            mesh.indices.push_back(i1);
            mesh.indices.push_back(i3);
        }
    }

    return mesh;
}

} // namespace

Ex1803_Landscape::Ex1803_Landscape() : AppBase() {}

bool Ex1803_Landscape::InitScene() {

    AppBase::m_camera.Reset(Vector3(10.9064f, 1.00741f, -7.31526f), -1.00629f,
                            0.148015f);

    AppBase::m_globalConstsCPU.strengthIBL = 1.0f;
    AppBase::m_globalConstsCPU.lodBias = 0.0f;

    AppBase::InitCubemaps(
        L"../Assets/Textures/Cubemaps/HDRI/", L"clear_pureskyEnvHDR.dds",
        L"clear_pureskySpecularHDR.dds", L"clear_pureskyDiffuseHDR.dds",
        L"clear_pureskyBrdf.dds");

    AppBase::InitScene();

    // Main Object
    {
        auto mesh = MakeTerrainFromRaw("../Assets/Textures/terrain.raw");
        auto meshes = vector{mesh};

        // auto meshes = GeometryGenerator::ReadFromFile(
        //     "../Assets/Terrain/Chalaadi/", "2.fbx", false);
        // for (auto &v : meshes[0].vertices)
        //     v.texcoord /= 1024.0f;
        // meshes[0].albedoTextureFilename =
        //     "../Assets/Terrain/Chalaadi/overlay.png";

        Vector3 center(0.0f, -1.0f, 0.0f);
        m_terrain = make_shared<Model>(m_device, m_context, meshes);
        m_terrain->m_materialConsts.GetCpu().invertNormalMapY =
            true; // GLTF는 true로
        m_terrain->m_materialConsts.GetCpu().albedoFactor =
            Vector3(0.38f, 0.44f, 0.34f);
        m_terrain->m_materialConsts.GetCpu().roughnessFactor = 0.97f;
        m_terrain->m_materialConsts.GetCpu().metallicFactor = 0.03f;
        m_terrain->UpdateWorldRow(Matrix::CreateTranslation(center));
        m_terrain->m_castShadow = true;
        m_pickedModel = m_terrain;

        m_basicList.push_back(m_terrain); // 리스트에 등록
    }

    // 바다 (블랜딩을 사용하려면 바다를 나중에 그려야 합니다.)
    {
        auto mesh = GeometryGenerator::MakeSquare(20.0, {10.0f, 10.0f});
        m_ocean = make_shared<OceanModel>(m_device, m_context, vector{mesh});
        m_ocean->m_castShadow = false;

        Vector3 position = Vector3(0.0f, -0.652f, 2.0f);
        m_ocean->UpdateWorldRow(Matrix::CreateRotationX(3.141592f * 0.5f) *
                                Matrix::CreateTranslation(position));

        m_basicList.push_back(m_ocean);
    }

    return true;
}

void Ex1803_Landscape::UpdateLights(float dt) { AppBase::UpdateLights(dt); }

void Ex1803_Landscape::Update(float dt) { AppBase::Update(dt); }

void Ex1803_Landscape::Render() {
    AppBase::Render();
    AppBase::PostRender();
}

void Ex1803_Landscape::UpdateGUI() {

    static float oceanHeight = 0.0f;
    if (ImGui::SliderFloat("OceanHeight", &oceanHeight, -1.0f, 1.0f)) {
        Vector3 position = Vector3(0.0f, oceanHeight, 2.0f);
        m_ocean->UpdateWorldRow(Matrix::CreateRotationX(3.141592f * 0.5f) *
                                Matrix::CreateTranslation(position));
    }

    ImGui::SetNextItemOpen(false, ImGuiCond_Once);
    if (ImGui::TreeNode("General")) {
        ImGui::Checkbox("Use FPV", &m_camera.m_useFirstPersonView);
        ImGui::Checkbox("Wireframe", &m_drawAsWire);
        if (ImGui::Checkbox("MSAA ON", &m_useMSAA)) {
            CreateBuffers();
        }
        ImGui::TreePop();
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Skybox")) {
        ImGui::SliderFloat("Strength", &m_globalConstsCPU.strengthIBL, 0.0f,
                           2.0f);
        ImGui::RadioButton("Env", &m_globalConstsCPU.textureToDraw, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Specular", &m_globalConstsCPU.textureToDraw, 1);
        ImGui::SameLine();
        ImGui::RadioButton("Irradiance", &m_globalConstsCPU.textureToDraw, 2);
        ImGui::SliderFloat("EnvLodBias", &m_globalConstsCPU.envLodBias, 0.0f,
                           10.0f);
        ImGui::TreePop();
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Post Effects")) {
        int flag = 0;
        flag += ImGui::RadioButton("Render", &m_postEffectsConstsCPU.mode, 1);
        ImGui::SameLine();
        flag += ImGui::RadioButton("Depth", &m_postEffectsConstsCPU.mode, 2);
        flag += ImGui::SliderFloat(
            "DepthScale", &m_postEffectsConstsCPU.depthScale, 0.0, 1.0);
        flag += ImGui::SliderFloat("Fog", &m_postEffectsConstsCPU.fogStrength,
                                   0.0, 10.0);

        if (flag)
            D3D11Utils::UpdateBuffer(m_context, m_postEffectsConstsCPU,
                                     m_postEffectsConstsGPU);

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Post Processing")) {
        int flag = 0;
        flag += ImGui::SliderFloat(
            "Bloom Strength",
            &m_postProcess.m_combineFilter.m_constData.strength, 0.0f, 1.0f);
        flag += ImGui::SliderFloat(
            "Exposure", &m_postProcess.m_combineFilter.m_constData.option1,
            0.0f, 10.0f);
        flag += ImGui::SliderFloat(
            "Motion Blur", &m_postProcess.m_combineFilter.m_constData.option3,
            0.0f, 1.0f);
        flag += ImGui::SliderFloat(
            "Gamma", &m_postProcess.m_combineFilter.m_constData.option2, 0.1f,
            5.0f);
        // 편의상 사용자 입력이 인식되면 바로 GPU 버퍼를 업데이트
        if (flag) {
            m_postProcess.m_combineFilter.UpdateConstantBuffers(m_context);
        }
        ImGui::TreePop();
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Light")) {
        // ImGui::SliderFloat3("Position",
        // &m_globalConstsCPU.lights[0].position.x,
        //                     -5.0f, 5.0f);
        ImGui::SliderFloat("Halo Radius",
                           &m_globalConstsCPU.lights[1].haloRadius, 0.0f, 2.0f);
        ImGui::SliderFloat("Halo Strength",
                           &m_globalConstsCPU.lights[1].haloStrength, 0.0f,
                           1.0f);
        ImGui::SliderFloat("Radius", &m_globalConstsCPU.lights[1].radius, 0.0f,
                           0.5f);
        ImGui::TreePop();
    }

    ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (ImGui::TreeNode("Material")) {
        ImGui::SliderFloat("LodBias", &m_globalConstsCPU.lodBias, 0.0f, 10.0f);

        int flag = 0;

        flag += ImGui::SliderFloat(
            "Metallic",
            &m_pickedModel->m_materialConsts.GetCpu().metallicFactor, 0.0f,
            1.0f);
        flag += ImGui::SliderFloat(
            "Roughness",
            &m_pickedModel->m_materialConsts.GetCpu().roughnessFactor, 0.0f,
            1.0f);
        flag += ImGui::CheckboxFlags(
            "AlbedoTexture",
            &m_pickedModel->m_materialConsts.GetCpu().useAlbedoMap, 1);
        flag += ImGui::CheckboxFlags(
            "EmissiveTexture",
            &m_pickedModel->m_materialConsts.GetCpu().useEmissiveMap, 1);
        flag += ImGui::CheckboxFlags(
            "Use NormalMapping",
            &m_pickedModel->m_materialConsts.GetCpu().useNormalMap, 1);
        flag += ImGui::CheckboxFlags(
            "Use AO", &m_pickedModel->m_materialConsts.GetCpu().useAOMap, 1);
        flag += ImGui::CheckboxFlags(
            "Use HeightMapping",
            &m_pickedModel->m_meshConsts.GetCpu().useHeightMap, 1);
        flag += ImGui::SliderFloat(
            "HeightScale", &m_pickedModel->m_meshConsts.GetCpu().heightScale,
            0.0f, 0.1f);
        flag += ImGui::CheckboxFlags(
            "Use MetallicMap",
            &m_pickedModel->m_materialConsts.GetCpu().useMetallicMap, 1);
        flag += ImGui::CheckboxFlags(
            "Use RoughnessMap",
            &m_pickedModel->m_materialConsts.GetCpu().useRoughnessMap, 1);

        if (flag) {
            m_pickedModel->UpdateConstantBuffers(m_device, m_context);
        }

        ImGui::Checkbox("Draw Normals", &m_pickedModel->m_drawNormals);

        ImGui::TreePop();
    }
}

} // namespace hlab
