#pragma once

#include "Hit.h"
#include "Ray.h"

#include <glm/glm.hpp>

namespace hlab
{
    using namespace glm;

    class Object
    {
    public:
        vec3 amb = vec3(0.0f);
        vec3 dif = vec3(0.0f);
        vec3 spec = vec3(0.0f);
        float alpha = 10.0f;

        Object(const vec3 &color = vec3(1.0f))
            : amb(color), dif(color), spec(color)
        {
        }

        virtual ~Object() = default;

        virtual Hit CheckRayCollision(Ray &ray) = 0;
    };
}
