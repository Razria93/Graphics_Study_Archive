#pragma once

#include "Light.h"
#include "Ray.h"
#include "Sphere.h"
#include "Square.h"
#include "Texture.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace hlab
{
    using namespace glm;

    class Raytracer
    {
    public:
        int width, height;
        Light light;
        std::vector<std::shared_ptr<Object>> objects;

        Raytracer(const int &width, const int &height)
            : width(width), height(height)
        {
            auto sphere = std::make_shared<Sphere>(vec3(1.0f, 0.0f, 1.5f), 0.4f);
            sphere->amb = vec3(0.2f);
            sphere->dif = vec3(1.0f, 0.2f, 0.2f);
            sphere->spec = vec3(0.5f);
            sphere->alpha = 10.0f;
            objects.push_back(sphere);

            auto texture = std::make_shared<Texture>("shadertoy_abstract1.jpg");
            auto square = std::make_shared<Square>(
                vec3(-2.0f, 2.0f, 2.0f),
                vec3(2.0f, 2.0f, 2.0f),
                vec3(2.0f, -2.0f, 2.0f),
                vec3(-2.0f, -2.0f, 2.0f),
                vec2(0.0f, 0.0f),
                vec2(1.0f, 0.0f),
                vec2(1.0f, 1.0f),
                vec2(0.0f, 1.0f));

            square->amb = vec3(0.0f);
            square->dif = vec3(1.0f);
            square->spec = vec3(0.0f);
            square->difTexture = texture;
            objects.push_back(square);

            light = Light{vec3(0.0f, 1.0f, 0.5f)};
        }

        Hit FindClosestCollision(Ray &ray)
        {
            Hit closestHit = Hit{-1.0f, vec3(0.0f), vec3(0.0f), vec2(0.0f), nullptr};

            for (const auto &object : objects)
            {
                auto hit = object->CheckRayCollision(ray);
                if (hit.d >= 0.0f && (closestHit.d < 0.0f || closestHit.d > hit.d))
                {
                    hit.obj = object;
                    closestHit = hit;
                }
            }

            return closestHit;
        }

        vec3 SampleDiffuse(const Hit &hit) const
        {
            if (hit.obj->difTexture)
            {
                return hit.obj->dif * hit.obj->difTexture->SampleLinear(hit.uv);
            }

            return hit.obj->dif;
        }

        vec3 traceRay(Ray &ray)
        {
            const auto hit = FindClosestCollision(ray);

            if (hit.d < 0.0f)
            {
                return vec3(0.0f);
            }

            vec3 pointColor = hit.obj->amb;

            const vec3 dirToLight = glm::normalize(light.pos - hit.point);
            const float diffuse = glm::max(dot(hit.normal, dirToLight), 0.0f);

            const vec3 reflectDir = glm::normalize(2.0f * dot(hit.normal, dirToLight) * hit.normal - dirToLight);
            const float specular = glm::pow(glm::max(glm::dot(-ray.dir, reflectDir), 0.0f), hit.obj->alpha);

            pointColor += diffuse * SampleDiffuse(hit);
            pointColor += hit.obj->spec * specular;

            return pointColor;
        }

        void Render(std::vector<glm::vec4> &pixels)
        {
            std::fill(pixels.begin(), pixels.end(), vec4(0.0f, 0.0f, 0.0f, 1.0f));

            const vec3 eyePos(0.0f, 0.0f, -1.5f);

#pragma omp parallel for
            for (int j = 0; j < height; j++)
                for (int i = 0; i < width; i++)
                {
                    const vec3 pixelPosWorld = TransformScreenToWorld(vec2(i, j));
                    Ray pixelRay{pixelPosWorld, glm::normalize(pixelPosWorld - eyePos)};

                    pixels[size_t(i + width * j)] = vec4(glm::clamp(traceRay(pixelRay), 0.0f, 1.0f), 1.0f);
                }
        }

        vec3 TransformScreenToWorld(vec2 posScreen)
        {
            const float xScale = 2.0f / this->width;
            const float yScale = 2.0f / this->height;
            const float aspect = float(this->width) / this->height;

            return vec3((posScreen.x * xScale - 1.0f) * aspect, -posScreen.y * yScale + 1.0f, 0.0f);
        }
    };
}
