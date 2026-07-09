#pragma once

#include "Object.h"

namespace hlab
{
    using namespace glm;

    class Sphere : public Object
    {
    public:
        vec3 center;
        float radius;

        Sphere(const vec3 &center, const float radius, const vec3 &color = vec3(1.0f))
            : Object(color), center(center), radius(radius)
        {
        }

        Hit CheckRayCollision(Ray &ray) override
        {
            Hit hit = Hit{-1.0f, vec3(0.0f), vec3(0.0f), vec3(0.0f), nullptr};

            const vec3 oc = ray.start - this->center;
            const float a = dot(ray.dir, ray.dir);
            const float b = 2.0f * glm::dot(ray.dir, oc);
            const float c = dot(oc, oc) - this->radius * this->radius;
            const float discriminant = b * b - 4.0f * a * c;

            if (discriminant < 0.0f)
            {
                return hit;
            }

            const float root = sqrt(discriminant);
            const float t0 = (-b - root) / (2.0f * a);
            const float t1 = (-b + root) / (2.0f * a);

            if (t0 > 0.0f)
            {
                hit.d = t0;
            }
            else if (t1 > 0.0f)
            {
                hit.d = t1;
            }

            if (hit.d < 0.0f)
            {
                return hit;
            }

            hit.point = ray.start + ray.dir * hit.d;
            hit.normal = glm::normalize(hit.point - this->center);

            return hit;
        }
    };
}
