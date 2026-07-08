#pragma once

#include "Light.h"
#include "Ray.h"
#include "Sphere.h"

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
        std::shared_ptr<Sphere> sphere;

        Raytracer(const int &width, const int &height)
            : width(width), height(height)
        {
            sphere = std::make_shared<Sphere>(vec3(0.0f, 0.0f, 0.5f), 0.5f);
            sphere->amb = vec3(0.0f, 0.0f, 0.0f);
            sphere->diff = vec3(0.0f, 0.0f, 1.0f);
            sphere->spec = vec3(1.0f, 1.0f, 1.0f);
            sphere->alpha = 9.0f;
            sphere->ks = 0.8f;

            light = Light{vec3(0.0f, 0.0f, -1.0f)};
        }

        vec3 traceRay(Ray &ray)
        {
            const auto hit = sphere->IntersectRayCollision(ray);

            if (hit.d < 0.0f)
            {
                return vec3(0.0f);
            }

            const vec3 dirToLight = glm::normalize(light.pos - hit.point);
            const float diffuse = glm::max(dot(hit.normal, dirToLight), 0.0f);

            const vec3 reflectDir = glm::normalize(2.0f * dot(hit.normal, dirToLight) * hit.normal - dirToLight);
            const vec3 viewDir = -ray.dir;
            const float specular = glm::pow(glm::max(dot(reflectDir, viewDir), 0.0f), sphere->alpha);

            return sphere->amb + sphere->diff * diffuse + sphere->spec * specular * sphere->ks;
        }

        void Render(std::vector<glm::vec4> &pixels)
        {
            std::fill(pixels.begin(), pixels.end(), vec4{0.0f, 0.0f, 0.0f, 1.0f});

#pragma omp parallel for
            for (int j = 0; j < height; j++)
                for (int i = 0; i < width; i++)
                {
                    const vec3 pixelPosWorld = TransformScreenToWorld(vec2(i, j));
                    const auto rayDir = vec3(0.0f, 0.0f, 1.0f);
                    Ray pixelRay{pixelPosWorld, rayDir};

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
