#pragma once

#include "Hit.h"
#include "Ray.h"

namespace hlab
{
    using namespace glm;

    class Sphere
    {
    public:
        vec3 center;
        float radius;

        vec3 amb = vec3(0.0f);
        vec3 diff = vec3(0.0f);
        vec3 spec = vec3(0.0f);
        float ks = 0.0f;
        float alpha = 0.0f;

        Sphere(const vec3 &center, const float radius)
            : center(center), radius(radius)
        {
        }

        Hit IntersectRayCollision(Ray &ray)
        {
            Hit hit = Hit{-1.0f, vec3(0.0f), vec3(0.0f)};

            const vec3 oc = ray.start - this->center;
            const float a = dot(ray.dir, ray.dir);
            const float b = 2.0f * dot(ray.dir, oc);
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
