#pragma once

#include "Mesh.h"
#include <directxtk/SimpleMath.h>


namespace hlab {


struct Constants {

    Matrix modelMatrix;
    Matrix invTranspose;

    Material material;
    Light light;
    int lightType = 0;
} constants;


Vector3 BlinnPhong(Vector3 lightStrength, Vector3 lightVec, Vector3 normal,
                   Vector3 toEye, Material mat) {

    Vector3 halfway = toEye + lightVec;
    halfway.Normalize();
    Vector3 specular =
        mat.specular * pow(max(halfway.Dot(normal), 0.0f), mat.shininess);

    return mat.ambient + (mat.diffuse + specular) * lightStrength;
}

Vector3 ComputeDirectionalLight(Light L, Material mat, Vector3 normal,
                                Vector3 toEye) {
    Vector3 lightVec = -L.direction;

    float ndotl = max(lightVec.Dot(normal), 0.0f);
    Vector3 lightStrength = L.strength * ndotl;

    return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

float Saturate(float x) { return max(0.0f, min(1.0f, x)); }

float CalcAttenuation(float d, float falloffStart, float falloffEnd) {
    return Saturate((falloffEnd - d) / (falloffEnd - falloffStart));
}

Vector3 ComputePointLight(Light L, Material mat, Vector3 pos, Vector3 normal,
                          Vector3 toEye) {
    Vector3 lightVec = L.position - pos;

    float d = lightVec.Length();

    if (d > L.fallOffEnd)
        return Vector3(0.0f);

    lightVec /= d;

    float ndotl = max(lightVec.Dot(normal), 0.0f);
    Vector3 lightStrength = L.strength * ndotl;

    float att = CalcAttenuation(d, L.fallOffStart, L.fallOffEnd);
    lightStrength *= att;

    return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

Vector3 ComputeSpotLight(Light L, Material mat, Vector3 pos, Vector3 normal,
                         Vector3 toEye) {
    Vector3 lightVec = L.position - pos;

    float d = lightVec.Length();

    if (d > L.fallOffEnd)
        return Vector3(0.0f);

    lightVec /= d;

    float ndotl = max(lightVec.Dot(normal), 0.0f);
    Vector3 lightStrength = L.strength * ndotl;

    float att = CalcAttenuation(d, L.fallOffStart, L.fallOffEnd);
    lightStrength *= att;

    float spotFactor = pow(max(-lightVec.Dot(L.direction), 0.0f), L.spotPower);
    lightStrength *= spotFactor;

    return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

struct VSInput 
{
    Vector3 position;
    Vector3 normal;
    Vector3 color;
};

struct VSOutput 
{
    Vector3 position;
    Vector3 normal;
};

VSOutput MyVertexShader(const VSInput vsInput) 
{
    VSOutput vsOutput;


    Vector4 point = Vector4(vsInput.position.x, vsInput.position.y, vsInput.position.z, 1.0f);

    point = Vector4::Transform(point, constants.modelMatrix);
	
    vsOutput.position = Vector3(point.x, point.y, point.z);


    Vector4 normal = Vector4(vsInput.normal.x, vsInput.normal.y, vsInput.normal.z, 0.0f);
    normal = Vector4::Transform(normal, constants.invTranspose);
    normal.Normalize();

    vsOutput.normal = Vector3(normal.x, normal.y, normal.z);

    return vsOutput;
}

struct PSInput {
    Vector3 position;
    Vector3 normal;
};

Vector4 MyPixelShader(const PSInput psInput) {

    Vector3 eye = Vector3(0.0f, 0.0f, -1.0f);
    Vector3 toEye = eye - psInput.position;
    toEye.Normalize();

    Vector3 color;

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

    return Vector4(color.x, color.y, color.z, 1.0f);
}

}

