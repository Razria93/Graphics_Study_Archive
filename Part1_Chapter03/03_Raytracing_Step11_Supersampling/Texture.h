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
        Texture(const int &width, const int &height, const std::vector<vec3> &pixels);

        vec3 GetClamped(int i, int j) const
        {
            i = glm::clamp(i, 0, width - 1);
            j = glm::clamp(j, 0, height - 1);
            return ReadPixel(i, j);
        }

        vec3 GetWrapped(int i, int j) const
        {
            i %= width;
            j %= height;

            if (i < 0)
            {
                i += width;
            }
            if (j < 0)
            {
                j += height;
            }

            return ReadPixel(i, j);
        }

        vec3 SamplePoint(const vec2 &uv) const
        {
            const vec2 xy = uv * vec2(width, height) - vec2(0.5f);
            return GetClamped(int(glm::round(xy.x)), int(glm::round(xy.y)));
        }

        vec3 SampleLinear(const vec2 &uv) const
        {
            const vec2 xy = uv * vec2(width, height) - vec2(0.5f);
            const int i = int(glm::floor(xy.x));
            const int j = int(glm::floor(xy.y));
            const float dx = xy.x - float(i);
            const float dy = xy.y - float(j);

            return InterpolateBilinear(
                dx,
                dy,
                GetWrapped(i, j),
                GetWrapped(i + 1, j),
                GetWrapped(i, j + 1),
                GetWrapped(i + 1, j + 1));
        }

    private:
        vec3 ReadPixel(const int i, const int j) const
        {
            const size_t offset = size_t(i + width * j) * size_t(channels);
            return vec3(
                image[offset + 0] / 255.0f,
                image[offset + 1] / 255.0f,
                image[offset + 2] / 255.0f);
        }

        vec3 InterpolateBilinear(
            const float dx,
            const float dy,
            const vec3 &c00,
            const vec3 &c10,
            const vec3 &c01,
            const vec3 &c11) const
        {
            const vec3 top = c00 * (1.0f - dx) + c10 * dx;
            const vec3 bottom = c01 * (1.0f - dx) + c11 * dx;
            return top * (1.0f - dy) + bottom * dy;
        }
    };
}
