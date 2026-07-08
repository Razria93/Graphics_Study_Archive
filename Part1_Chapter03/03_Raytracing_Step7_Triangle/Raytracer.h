#pragma once

#include "Light.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"

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
            auto sphere = std::make_shared<Sphere>(vec3(0.6f, 0.0f, 0.5f), 0.4f);
            sphere->amb = vec3(0.1f);
            sphere->dif = vec3(1.0f, 0.1f, 0.1f);
            sphere->spec = vec3(1.0f);
            sphere->alpha = 50.0f;
            objects.push_back(sphere);

            auto triangle = std::make_shared<Triangle>(
                vec3(-2.0f, -2.0f, 2.0f),
                vec3(-2.0f, 2.0f, 2.0f),
                vec3(2.0f, 2.0f, 2.0f));
            triangle->amb = vec3(0.2f);
            triangle->dif = vec3(0.5f);
            triangle->spec = vec3(0.5f);
            triangle->alpha = 5.0f;
            objects.push_back(triangle);

            light = Light{vec3(0.0f, 1.0f, -1.0f)};
        }

        Hit FindClosestCollision(Ray &ray)
        {
            Hit closestHit = Hit{-1.0f, vec3(0.0f), vec3(0.0f), nullptr};

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

        vec3 traceRay(Ray &ray)
        {
            const auto hit = FindClosestCollision(ray);

            if (hit.d < 0.0f)
            {
                return vec3(0.0f);
            }

            const vec3 dirToLight = glm::normalize(light.pos - hit.point);
            const float diffuse = glm::max(dot(hit.normal, dirToLight), 0.0f);

            const vec3 reflectDir = glm::normalize(2.0f * dot(hit.normal, dirToLight) * hit.normal - dirToLight);
            const float specular = glm::pow(glm::max(glm::dot(-ray.dir, reflectDir), 0.0f), hit.obj->alpha);

            return hit.obj->amb + hit.obj->dif * diffuse + hit.obj->spec * specular;
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
