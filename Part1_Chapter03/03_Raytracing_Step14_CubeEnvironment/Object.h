#pragma once

#include <glm/glm.hpp>

namespace hlab
{
    class Object
    {
    public:
        glm::vec3 amb = glm::vec3(0.0f);
        glm::vec3 dif = glm::vec3(0.0f);
        glm::vec3 spec = glm::vec3(0.0f);
        float alpha = 10.0f;
        float reflection = 0.0f;
        float transparency = 0.0f;

        Object(const glm::vec3 &color = glm::vec3(1.0f))
            : amb(color), dif(color), spec(color)
        {
        }

        virtual ~Object() = default;
    };
}
