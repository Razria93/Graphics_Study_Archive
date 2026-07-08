#pragma once

#include <glm/glm.hpp>

namespace hlab
{
    class Hit
    {
    public:
        float d;
        glm::vec3 point;
        glm::vec3 normal;

        bool bIsOver;
        bool bIsOutLiner;
    };
}
