#include "Mesh.h"

namespace hlab {

void Mesh::InitBox() {
    const float scale = 0.7f;

    this->vertices.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
    this->normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
    this->normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
    this->normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
    this->normals.push_back(Vector3(0.0f, 1.0f, 0.0f));

    this->vertices.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
    this->normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    this->normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    this->normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
    this->normals.push_back(Vector3(0.0f, -1.0f, 0.0f));

    this->vertices.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
    this->normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    this->normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    this->normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
    this->normals.push_back(Vector3(0.0f, 0.0f, -1.0f));

    this->vertices.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
    this->normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    this->normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    this->normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
    this->normals.push_back(Vector3(0.0f, 0.0f, 1.0f));

    this->vertices.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
    this->normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    this->normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    this->normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
    this->normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));

    this->vertices.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
    this->vertices.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
    this->normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    this->normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    this->normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
    this->normals.push_back(Vector3(1.0f, 0.0f, 0.0f));

    this->indices = {
        0,  1,  2,  0,  2,  3,
        4,  5,  6,  4,  6,  7,
        8,  9,  10, 8,  10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };
}

void Mesh::CopyToBuffer() {

    vertexBuffer = vertices;
    indexBuffer = indices;
    normalBuffer = normals;

    vertices.clear();
    normals.clear();
    indices.clear();
}
}

