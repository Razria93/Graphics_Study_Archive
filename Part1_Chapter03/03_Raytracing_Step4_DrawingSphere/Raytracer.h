#pragma once

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
        std::shared_ptr<Sphere> sphere;

        Raytracer(const int &width, const int &height)
            : width(width), height(height)
        {
            sphere = std::make_shared<Sphere>(vec3(0.0f, 0.0f, 0.5f), 0.4f, vec3(1.0f, 1.0f, 1.0f));
        }

        glm::vec3 TransformScreenToWorld(glm::vec2 posScreen)
        {
            const float xScale = 2.0f / (this->width - 1);
            const float yScale = 2.0f / (this->height - 1);
            const float aspect = float(this->width) / this->height;

            // Map the screen pixel to the z=0 orthographic camera plane.
            return glm::vec3((posScreen.x * xScale - 1.0f) * aspect, -posScreen.y * yScale + 1.0f, 0.0f);
        }

        vec3 traceRay(Ray &ray)
        {
            const Hit hit = sphere->IntersectRayCollision(ray);
            constexpr float epsilon = 1e-2f;

            if (glm::epsilonEqual(hit.d, 0.0f, epsilon) && hit.bIsOver && hit.bIsOutLiner)
            {
                return vec3{1.0f, 0.0f, 0.0f};
            }

            if (hit.d < 0.0f)
            {
                return vec3(0.0f);
            }

            if (!hit.bIsOver)
            {
                return sphere->color * hit.d;
            }

            return (vec3(1.0f) - sphere->color) * (1.0f - hit.d);
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

                    pixels[size_t(i + width * j)] = vec4(traceRay(pixelRay), 1.0f);
                }
        }
    };
}
