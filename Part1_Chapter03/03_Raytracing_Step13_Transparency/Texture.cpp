#define GLM_ENABLE_EXPERIMENTAL
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

    Texture::Texture(const int &width, const int &height, const std::vector<vec3> &pixels)
        : width(width), height(height), channels(3)
    {
        image.resize(size_t(width) * size_t(height) * size_t(channels));

        for (int j = 0; j < height; j++)
            for (int i = 0; i < width; i++)
            {
                const auto &color = pixels[size_t(i + j * width)];
                const size_t offset = size_t(i + width * j) * size_t(channels);

                image[offset + 0] = uint8_t(glm::clamp(color.r, 0.0f, 1.0f) * 255.0f);
                image[offset + 1] = uint8_t(glm::clamp(color.g, 0.0f, 1.0f) * 255.0f);
                image[offset + 2] = uint8_t(glm::clamp(color.b, 0.0f, 1.0f) * 255.0f);
            }
    }
}
