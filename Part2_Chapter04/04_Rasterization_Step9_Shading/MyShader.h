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
    Light light;
    Material material;
} constants;

glm::vec3 CalculateAmbientColor(const Light &light, const Material &material) {
    return light.lightAmbient * material.matAmbient;
}

glm::vec3 CalculateDiffuseColor(const Light &light, const Material &material,
                                const glm::vec3 &normalDir,
                                const glm::vec3 &lightDir) {
    const float ndotl = glm::max(0.0f, glm::dot(lightDir, normalDir));
    if (ndotl <= 0.0f) {
        return vec3(0.0f);
    }

    return light.lightDiffuse * (material.matDiffuse * material.kd) * ndotl;
}

glm::vec3 CalculateSpecularColor(const Light &light, const Material &material,
                                 const glm::vec3 &normalDir,
                                 const glm::vec3 &lightDir,
                                 const glm::vec3 viewDir) {
    const float ndotl = glm::max(0.0f, glm::dot(lightDir, normalDir));
    if (ndotl <= 0.0f) {
        return vec3(0.0f);
    }

    const glm::vec3 halfwayVector = glm::normalize(lightDir + viewDir);
    const float specularRatio =
        glm::pow(glm::max(0.0f, glm::dot(normalDir, halfwayVector)),
                 material.shininess);

    return light.lightSpecular * (material.matSpecular * material.ks) *
           specularRatio * ndotl;
}

vec3 BlinnPhong(const Light &light, const Material &material,
                const vec3 &normalDir, const vec3 &toEyeDir,
                const vec3 &lightDir) {
    const vec3 ambient = CalculateAmbientColor(light, material);
    const vec3 diffuse =
        CalculateDiffuseColor(light, material, normalDir, lightDir);
    const vec3 specular =
        CalculateSpecularColor(light, material, normalDir, lightDir, toEyeDir);

    return ambient + diffuse + specular;
}

vec3 ComputeDirectionalLight(const Light &light, const Material &material,
                             const vec3 &normalDir, const vec3 &toEyeDir) {
    const vec3 lightDir = -light.direction;
    return BlinnPhong(light, material, normalDir, toEyeDir, lightDir);
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
    const vec3 eyePoint = vec3(0.0f, 0.0f, -1.0f);
    const vec3 toEyeDir = glm::normalize(eyePoint - psInput.position);
    const vec3 color = ComputeDirectionalLight(
        constants.light, constants.material, psInput.normal, toEyeDir);

    return vec4(color, 1.0f);
}

} // namespace hlab
