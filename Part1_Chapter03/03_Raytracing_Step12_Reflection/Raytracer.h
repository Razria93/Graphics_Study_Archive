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
            auto mirrorSphere = std::make_shared<Sphere>(vec3(0.0f, -0.1f, 1.5f), 1.0f);
            mirrorSphere->amb = vec3(0.1f);
            mirrorSphere->dif = vec3(1.0f, 0.0f, 0.0f);
            mirrorSphere->spec = vec3(1.0f);
            mirrorSphere->alpha = 10.0f;
            mirrorSphere->reflection = 0.5f;
            objects.push_back(mirrorSphere);

            auto blueSphere = std::make_shared<Sphere>(vec3(1.2f, -0.1f, 0.5f), 0.4f);
            blueSphere->amb = vec3(0.0f);
            blueSphere->dif = vec3(0.0f, 0.0f, 1.0f);
            blueSphere->spec = vec3(1.0f);
            blueSphere->alpha = 50.0f;
            objects.push_back(blueSphere);

            auto groundTexture = std::make_shared<Texture>("shadertoy_abstract1.jpg");
            auto ground = std::make_shared<Square>(
                vec3(-10.0f, -1.2f, 0.0f),
                vec3(-10.0f, -1.2f, 10.0f),
                vec3(10.0f, -1.2f, 10.0f),
                vec3(10.0f, -1.2f, 0.0f),
                vec2(0.0f, 0.0f),
                vec2(1.0f, 0.0f),
                vec2(1.0f, 1.0f),
                vec2(0.0f, 1.0f));

            ground->amb = vec3(1.0f);
            ground->dif = vec3(1.0f);
            ground->spec = vec3(1.0f);
            ground->alpha = 10.0f;
            ground->ambTexture = groundTexture;
            ground->difTexture = groundTexture;
            objects.push_back(ground);

            light = Light{vec3(0.0f, 0.5f, -0.5f)};
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

        vec3 SampleAmbient(const Hit &hit) const
        {
            if (hit.obj->ambTexture)
            {
                return hit.obj->amb * hit.obj->ambTexture->SampleLinear(hit.uv);
            }

            return hit.obj->amb;
        }

        vec3 SampleDiffuse(const Hit &hit) const
        {
            if (hit.obj->difTexture)
            {
                return hit.obj->dif * hit.obj->difTexture->SampleLinear(hit.uv);
            }

            return hit.obj->dif;
        }

        vec3 ShadePhong(const Hit &hit, const Ray &ray)
        {
            vec3 color = SampleAmbient(hit);

            const vec3 dirToLight = glm::normalize(light.pos - hit.point);
            const float diffuse = glm::max(dot(hit.normal, dirToLight), 0.0f);

            const vec3 reflectDir = glm::normalize(2.0f * dot(hit.normal, dirToLight) * hit.normal - dirToLight);
            const float specular = glm::pow(glm::max(glm::dot(-ray.dir, reflectDir), 0.0f), hit.obj->alpha);

            color += diffuse * SampleDiffuse(hit);
            color += hit.obj->spec * specular;

            return color;
        }

        vec3 traceRay(Ray &ray, const int depth)
        {
            if (depth < 0)
            {
                return vec3(0.0f);
            }

            const auto hit = FindClosestCollision(ray);

            if (hit.d < 0.0f)
            {
                return vec3(0.0f);
            }

            const float localWeight = glm::clamp(1.0f - hit.obj->reflection - hit.obj->transparency, 0.0f, 1.0f);
            vec3 color = ShadePhong(hit, ray) * localWeight;

            if (hit.obj->reflection > 0.0f)
            {
                const vec3 incident = -ray.dir;
                const vec3 reflectedDir = glm::normalize(2.0f * dot(incident, hit.normal) * hit.normal - incident);
                Ray reflectedRay{hit.point + reflectedDir * 1e-4f, reflectedDir};

                color += traceRay(reflectedRay, depth - 1) * hit.obj->reflection;
            }

            return color;
        }

        void Render(std::vector<glm::vec4> &pixels)
        {
            std::fill(pixels.begin(), pixels.end(), vec4(0.0f, 0.0f, 0.0f, 1.0f));

            const vec3 eyePos(0.0f, 0.0f, -1.5f);
            const int reflectionDepth = 5;

#pragma omp parallel for
            for (int j = 0; j < height; j++)
                for (int i = 0; i < width; i++)
                {
                    const vec3 pixelPosWorld = TransformScreenToWorld(vec2(i, j));
                    Ray pixelRay{pixelPosWorld, glm::normalize(pixelPosWorld - eyePos)};
                    const vec3 pixelColor = traceRay(pixelRay, reflectionDepth);

                    pixels[size_t(i + width * j)] = vec4(glm::clamp(pixelColor, 0.0f, 1.0f), 1.0f);
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
