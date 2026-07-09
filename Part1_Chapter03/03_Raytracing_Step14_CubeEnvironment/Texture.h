#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace hlab
{
    using namespace glm;

    class Texture
    {
    public:
        int width = 0;
        int height = 0;
        int channels = 3;
        std::vector<uint8_t> image;

        explicit Texture(const std::string &filename);

        vec3 SampleLinear(const vec2 &uv) const
        {
            const vec2 xy = glm::clamp(uv, vec2(0.0f), vec2(1.0f)) * vec2(width, height) - vec2(0.5f);
            const int i = int(glm::floor(xy.x));
            const int j = int(glm::floor(xy.y));
            const float dx = xy.x - float(i);
            const float dy = xy.y - float(j);

            const vec3 top = GetClamped(i, j) * (1.0f - dx) + GetClamped(i + 1, j) * dx;
            const vec3 bottom = GetClamped(i, j + 1) * (1.0f - dx) + GetClamped(i + 1, j + 1) * dx;
            return top * (1.0f - dy) + bottom * dy;
        }

    private:
        vec3 GetClamped(int i, int j) const
        {
            i = glm::clamp(i, 0, width - 1);
            j = glm::clamp(j, 0, height - 1);

            const size_t offset = size_t(i + width * j) * size_t(channels);
            return vec3(
                image[offset + 0] / 255.0f,
                image[offset + 1] / 255.0f,
                image[offset + 2] / 255.0f);
        }
    };
}
