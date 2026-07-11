#pragma once

#pragma once

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

#include "Vertex.h"

namespace hlab {

using std::vector;

struct MeshData {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::string textureFilename;
	std::string meshName;
};

} // namespace hlab