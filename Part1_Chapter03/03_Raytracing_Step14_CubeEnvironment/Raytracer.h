#pragma once

#include "Object.h"
#include "Texture.h"

#include <algorithm>
#include <array>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace hlab
{
    class Raytracer
    {
    public:
        int width, height;
        std::vector<std::shared_ptr<Object>> objects;
        std::array<std::shared_ptr<Texture>, 6> environment;

        enum CubeFace
        {
            PosX,
            NegX,
            PosY,
            NegY,
            PosZ,
            NegZ
        };

        Raytracer(const int &width, const int &height)
            : width(width), height(height)
        {
            environment[PosX] = LoadTexture("posx.jpg");
            environment[NegX] = LoadTexture("negx.jpg");
            environment[PosY] = LoadTexture("posy.jpg");
            environment[NegY] = LoadTexture("negy.jpg");
            environment[PosZ] = LoadTexture("posz.jpg");
            environment[NegZ] = LoadTexture("negz.jpg");
        }

        void Render(std::vector<glm::vec4> &pixels)
        {
            const glm::vec3 eyePos(0.0f, 0.0f, -1.5f);

#pragma omp parallel for
            for (int j = 0; j < height; j++)
                for (int i = 0; i < width; i++)
                {
                    const glm::vec3 pixelPosWorld = TransformScreenToWorld(glm::vec2(i, j));
                    const glm::vec3 rayDir = glm::normalize(pixelPosWorld - eyePos);
                    const glm::vec3 color = SampleEnvironment(rayDir);

                    pixels[size_t(i + width * j)] = glm::vec4(glm::clamp(color, 0.0f, 1.0f), 1.0f);
                }
        }

    private:
        std::shared_ptr<Texture> LoadTexture(const std::string &filename)
        {
            const std::array<std::string, 3> prefixes = {
                "SaintPetersBasilica/",
                "Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/SaintPetersBasilica/",
                "../../Part1_Chapter03/03_Raytracing_Step14_CubeEnvironment/SaintPetersBasilica/"};

            for (const auto &prefix : prefixes)
            {
                try
                {
                    return std::make_shared<Texture>(prefix + filename);
                }
                catch (const std::runtime_error &)
                {
                }
            }

            throw std::runtime_error("Failed to load environment texture: " + filename);
        }

        glm::vec3 SampleEnvironment(const glm::vec3 &dir) const
        {
            const glm::vec3 absDir = glm::abs(dir);
            CubeFace face = PosX;
            float u = 0.0f;
            float v = 0.0f;

            if (absDir.x >= absDir.y && absDir.x >= absDir.z)
            {
                if (dir.x > 0.0f)
                {
                    face = PosX;
                    u = -dir.z / absDir.x;
                    v = -dir.y / absDir.x;
                }
                else
                {
                    face = NegX;
                    u = dir.z / absDir.x;
                    v = -dir.y / absDir.x;
                }
            }
            else if (absDir.y >= absDir.x && absDir.y >= absDir.z)
            {
                if (dir.y > 0.0f)
                {
                    face = PosY;
                    u = dir.x / absDir.y;
                    v = dir.z / absDir.y;
                }
                else
                {
                    face = NegY;
                    u = dir.x / absDir.y;
                    v = -dir.z / absDir.y;
                }
            }
            else
            {
                if (dir.z > 0.0f)
                {
                    face = PosZ;
                    u = dir.x / absDir.z;
                    v = -dir.y / absDir.z;
                }
                else
                {
                    face = NegZ;
                    u = -dir.x / absDir.z;
                    v = -dir.y / absDir.z;
                }
            }

            const glm::vec2 uv(u * 0.5f + 0.5f, v * 0.5f + 0.5f);
            return environment[face]->SampleLinear(uv);
        }

        glm::vec3 TransformScreenToWorld(glm::vec2 posScreen) const
        {
            const float xScale = 2.0f / width;
            const float yScale = 2.0f / height;
            const float aspect = float(width) / float(height);

            return glm::vec3((posScreen.x * xScale - 1.0f) * aspect, -posScreen.y * yScale + 1.0f, 0.0f);
        }
    };
}
