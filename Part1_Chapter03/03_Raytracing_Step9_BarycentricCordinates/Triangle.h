#pragma once

#include "Object.h"

namespace hlab
{
    using namespace glm;

    class Triangle : public Object
    {
    public:
        vec3 v0, v1, v2;
        vec2 uv0, uv1, uv2;

        Triangle()
            : v0(vec3(0.0f)), v1(vec3(0.0f)), v2(vec3(0.0f)),
              uv0(vec2(0.0f)), uv1(vec2(0.0f)), uv2(vec2(0.0f))
        {
        }

        Triangle(vec3 v0, vec3 v1, vec3 v2, vec2 uv0 = vec2(0.0f), vec2 uv1 = vec2(0.0f), vec2 uv2 = vec2(0.0f))
            : v0(v0), v1(v1), v2(v2), uv0(uv0), uv1(uv1), uv2(uv2)
        {
        }

        Hit CheckRayCollision(Ray &ray) override
        {
            Hit hit = Hit{-1.0f, vec3(0.0f), vec3(0.0f), vec3(0.0f), nullptr};

            vec3 point, faceNormal, barycentric;
            float t;
            if (IntersectRayTriangle(ray.start, ray.dir, this->v0, this->v1, this->v2, point, faceNormal, barycentric, t))
            {
                hit.d = t;
                hit.point = point;
                hit.normal = faceNormal;
                hit.barycentric = barycentric;
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
            vec3 &barycentric,
            float &t)
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

            const vec3 edgeNormal0 = glm::cross(point - v2, v1 - v2);
            const vec3 edgeNormal1 = glm::cross(point - v0, v2 - v0);
            const vec3 edgeNormal2 = glm::cross(v1 - v0, point - v0);

            if (dot(edgeNormal0, faceNormal) < 0.0f)
            {
                return false;
            }
            if (dot(edgeNormal1, faceNormal) < 0.0f)
            {
                return false;
            }
            if (dot(edgeNormal2, faceNormal) < 0.0f)
            {
                return false;
            }

            const float totalArea = glm::length(glm::cross(v1 - v0, v2 - v0));
            const float w0 = glm::length(glm::cross(v1 - point, v2 - point)) / totalArea;
            const float w1 = glm::length(glm::cross(v2 - point, v0 - point)) / totalArea;
            const float w2 = 1.0f - w0 - w1;

            barycentric = vec3(w0, w1, w2);

            return true;
        }
    };
}
