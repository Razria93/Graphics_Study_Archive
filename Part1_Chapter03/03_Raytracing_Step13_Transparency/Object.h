#pragma once

#include "Hit.h"
#include "Ray.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <memory>

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
        float reflection = 0.0f;
        float transparency = 0.0f;

        std::shared_ptr<Texture> ambTexture;
        std::shared_ptr<Texture> difTexture;

        Object(const vec3 &color = vec3(1.0f))
            : amb(color), dif(color), spec(color)
        {
        }

        virtual ~Object() = default;

        virtual Hit CheckRayCollision(Ray &ray) = 0;
    };
}
