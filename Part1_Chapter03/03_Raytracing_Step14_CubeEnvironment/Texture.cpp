#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

#include "stb_image.h"

#include <cstring>
#include <stdexcept>

namespace hlab
{
    Texture::Texture(const std::string &filename)
    {
        constexpr int desiredChannels = 3;
        unsigned char *img = stbi_load(filename.c_str(), &width, &height, &channels, desiredChannels);
        if (!img)
        {
            throw std::runtime_error("Failed to load texture: " + filename);
        }

        channels = desiredChannels;
        image.resize(size_t(width) * size_t(height) * size_t(channels));
        std::memcpy(image.data(), img, image.size() * sizeof(uint8_t));

        stbi_image_free(img);
    }
}
