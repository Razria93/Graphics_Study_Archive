#pragma once

#include "Object.h"

#include <algorithm>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace hlab
{
    class Raytracer
    {
    public:
        int width, height;
        std::vector<std::shared_ptr<Object>> objects;

        Raytracer(const int &width, const int &height)
            : width(width), height(height)
        {
        }

        void Render(std::vector<glm::vec4> &pixels)
        {
            std::fill(pixels.begin(), pixels.end(), glm::vec4(0.02f, 0.03f, 0.05f, 1.0f));
        }
    };
}
