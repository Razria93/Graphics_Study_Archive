#pragma once

#include "Mesh.h"

namespace hlab {

using namespace glm;

struct Constants {
    mat4 modelMatrix = mat4(1.0f);
    mat4 normalMatrix = mat4(1.0f);
    Material material;
    Light light;
    int lightType = 0;
} constants;

vec3 BlinnPhong(const vec3 &lightStrength, const vec3 &lightVec,
                const vec3 &normal, const vec3 &toEye,
                const Material &material) {
    const vec3 halfway = normalize(toEye + lightVec);
    const vec3 specular =
        material.specular *
        pow(glm::max(dot(halfway, normal), 0.0f), material.shininess);

    return material.ambient + (material.diffuse + specular) * lightStrength;
}

vec3 ComputeDirectionalLight(const Light &light, const Material &material,
                             const vec3 &normal, const vec3 &toEye) {
    const vec3 lightVec = -light.direction;
    const float ndotl = glm::max(dot(lightVec, normal), 0.0f);
    const vec3 lightStrength = light.strength * ndotl;

    return BlinnPhong(lightStrength, lightVec, normal, toEye, material);
}

float Saturate(float x) {
    return glm::max(0.0f, glm::min(1.0f, x));
}

float CalcAttenuation(float distance, float fallOffStart, float fallOffEnd) {
    return Saturate((fallOffEnd - distance) / (fallOffEnd - fallOffStart));
}

vec3 ComputePointLight(const Light &light, const Material &material,
                       const vec3 &position, const vec3 &normal,
                       const vec3 &toEye) {
    vec3 lightVec = light.position - position;
    const float distance = length(lightVec);

    if (distance > light.fallOffEnd) {
        return vec3(0.0f);
    }

    lightVec /= distance;

    const float ndotl = glm::max(dot(lightVec, normal), 0.0f);
    vec3 lightStrength = light.strength * ndotl;
    lightStrength *=
        CalcAttenuation(distance, light.fallOffStart, light.fallOffEnd);

    return BlinnPhong(lightStrength, lightVec, normal, toEye, material);
}

vec3 ComputeSpotLight(const Light &light, const Material &material,
                      const vec3 &position, const vec3 &normal,
                      const vec3 &toEye) {
    vec3 lightVec = light.position - position;
    const float distance = length(lightVec);

    if (distance > light.fallOffEnd) {
        return vec3(0.0f);
    }

    lightVec /= distance;

    const float ndotl = glm::max(dot(lightVec, normal), 0.0f);
    vec3 lightStrength = light.strength * ndotl;
    lightStrength *=
        CalcAttenuation(distance, light.fallOffStart, light.fallOffEnd);

    const float spotFactor =
        glm::pow(glm::max(0.0f, glm::dot(-lightVec, light.direction)),
                 light.spotPower);
    lightStrength *= spotFactor;

    return BlinnPhong(lightStrength, lightVec, normal, toEye, material);
}

struct VSInput {
    vec3 position;
    vec3 normal;
};

struct VSOutput {
    vec3 position;
    vec3 normal;
};

VSOutput MyVertexShader(const VSInput vsInput) {
    VSOutput vsOutput;

    const vec4 point = constants.modelMatrix * vec4(vsInput.position, 1.0f);
    const vec4 normal = constants.normalMatrix * vec4(vsInput.normal, 0.0f);

    vsOutput.position = vec3(point);
    vsOutput.normal = glm::normalize(vec3(normal));

    return vsOutput;
}

struct PSInput {
    vec3 position;
    vec3 normal;
};

vec4 MyPixelShader(const PSInput psInput) {
    const vec3 eye = vec3(0.0f, 0.0f, -1.0f);
    const vec3 toEye = glm::normalize(eye - psInput.position);
    vec3 color;

    if (constants.lightType == 0) {
        color = ComputeDirectionalLight(constants.light, constants.material,
                                        psInput.normal, toEye);
    } else if (constants.lightType == 1) {
        color = ComputePointLight(constants.light, constants.material,
                                  psInput.position, psInput.normal, toEye);
    } else {
        color = ComputeSpotLight(constants.light, constants.material,
                                 psInput.position, psInput.normal, toEye);
    }

    return vec4(color, 1.0f);
}

} // namespace hlab
