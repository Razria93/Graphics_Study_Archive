#pragma once

#include "Mesh.h"

namespace hlab {

using namespace glm;

vec3 RotateAboutZ(const vec3 &v, const float &theta) {
    return vec3(v.x * cos(theta) - v.y * sin(theta),
                v.x * sin(theta) + v.y * cos(theta), v.z);
}

vec3 RotateAboutY(const vec3 &v, const float &theta) {
    return vec3(v.x * cos(theta) + v.z * sin(theta), v.y,
                -v.x * sin(theta) + v.z * cos(theta));
}

vec3 RotateAboutX(const vec3 &v, const float &theta) {
    return vec3(v.x, v.y * cos(theta) - v.z * sin(theta),
                v.y * sin(theta) + v.z * cos(theta));
}

struct Constants {
    Transformation transformation;
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

    vec3 transformed = vsInput.position * constants.transformation.scale;
    transformed = RotateAboutY(transformed, constants.transformation.rotationY);
    transformed = RotateAboutX(transformed, constants.transformation.rotationX);
    transformed = RotateAboutZ(transformed, constants.transformation.rotationZ);
    transformed += constants.transformation.translation;

    vec3 normal = RotateAboutY(vsInput.normal, constants.transformation.rotationY);
    normal = RotateAboutX(normal, constants.transformation.rotationX);
    normal = RotateAboutZ(normal, constants.transformation.rotationZ);

    vsOutput.position = transformed;
    vsOutput.normal = glm::normalize(normal);

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
