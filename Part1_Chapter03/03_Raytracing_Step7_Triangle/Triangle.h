#pragma once

#include "Object.h"

#include <glm/gtc/epsilon.hpp>

namespace hlab
{
    using namespace glm;

    class Triangle : public Object
    {
    public:
        vec3 v0, v1, v2;

        Triangle()
            : v0(vec3(0.0f)), v1(vec3(0.0f)), v2(vec3(0.0f))
        {
        }

        Triangle(vec3 v0, vec3 v1, vec3 v2)
            : v0(v0), v1(v1), v2(v2)
        {
        }

        Hit CheckRayCollision(Ray &ray) override
        {
            Hit hit = Hit{-1.0f, vec3(0.0f), vec3(0.0f), nullptr};

            vec3 point, faceNormal;
            float t, u, v;
            if (IntersectRayTriangle(ray.start, ray.dir, this->v0, this->v1, this->v2, point, faceNormal, t, u, v))
            {
                hit.d = t;
                hit.point = point;
                hit.normal = faceNormal;
            }

            return hit;
        }

        bool IntersectRayTriangle(
            const vec3 &origin,
            const vec3 &dir,
            const vec3 &v0,
            const vec3 &v1,
            const vec3 &v2,
            vec3 &point,
            vec3 &faceNormal,
            float &t,
            float &u,
            float &v)
        {
            faceNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

            if (glm::dot(-dir, faceNormal) < 0.0f)
            {
                return false;
            }

            const float denom = dot(dir, faceNormal);
            if (glm::abs(denom) < 1e-2f)
            {
                return false;
            }

            t = (dot(v0, faceNormal) - dot(origin, faceNormal)) / denom;
            if (t < 0.0f)
            {
                return false;
            }

            point = origin + t * dir;

            const vec3 normal0 = glm::normalize(glm::cross(v1 - v0, point - v0));
            const vec3 normal1 = glm::normalize(glm::cross(v2 - v1, point - v1));
            const vec3 normal2 = glm::normalize(glm::cross(v0 - v2, point - v2));

            if (dot(normal0, faceNormal) < 0.0f)
            {
                return false;
            }
            if (dot(normal1, faceNormal) < 0.0f)
            {
                return false;
            }
            if (dot(normal2, faceNormal) < 0.0f)
            {
                return false;
            }

            u = 0.0f;
            v = 0.0f;
            return true;
        }
    };
}
