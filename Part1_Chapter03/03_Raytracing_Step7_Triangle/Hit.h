#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace hlab
{
    class Object;

    class Hit
    {
    public:
        float d;
        glm::vec3 point;
        glm::vec3 normal;

        std::shared_ptr<Object> obj;
    };
}
