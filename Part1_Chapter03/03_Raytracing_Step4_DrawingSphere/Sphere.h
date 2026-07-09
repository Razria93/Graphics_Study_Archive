#pragma once

#include "Hit.h"
#include "Ray.h"

#include <glm/gtc/epsilon.hpp>

namespace hlab
{
    using namespace glm;

    class Sphere
    {
    public:
        glm::vec3 center;
        float radius;
        glm::vec3 color;

        Sphere(const glm::vec3 &center, const float radius, const glm::vec3 &color)
            : center(center), color(color), radius(radius)
        {
        }

        Hit IntersectRayCollision(Ray &ray)
        {
            Hit hit = Hit{-1.0f, vec3(0.0f), vec3(0.0f), false, false};

            const vec3 oc = ray.start - this->center;
            const float a = dot(ray.dir, ray.dir);
            const float b = 2.0f * dot(ray.dir, oc);
            const float c = dot(oc, oc) - (this->radius * this->radius);
            const float discriminant = b * b - 4.0f * a * c;
            constexpr float epsilon = 1e-2f;

            if (discriminant < 0.0f)
            {
                return hit;
            }

            const float root = sqrt(discriminant);
            const float t0 = (-b - root) / (2.0f * a);
            const float t1 = (-b + root) / (2.0f * a);
            const bool startsInside = t0 < 0.0f && t1 > 0.0f;
            const bool touchesCameraPlane = glm::epsilonEqual(t0, 0.0f, epsilon) || glm::epsilonEqual(t1, 0.0f, epsilon);

            float t = -1.0f;
            if (t0 > 0.0f)
            {
                t = t0;
            }
            else if (t1 > 0.0f)
            {
                t = t1;
            }

            if (t < 0.0f && !touchesCameraPlane)
            {
                return hit;
            }

            if (touchesCameraPlane)
            {
                t = 0.0f;
            }

            hit.d = t;
            hit.point = ray.start + ray.dir * t;
            hit.normal = glm::normalize(hit.point - this->center);
            hit.bIsOver = startsInside || touchesCameraPlane;
            hit.bIsOutLiner = touchesCameraPlane;

            return hit;
        }
    };
}
