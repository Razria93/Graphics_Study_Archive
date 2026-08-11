#pragma once

#include <filesystem>

namespace GraphicsLab::Asset
{
    class AssetPath final
    {
    public:
        [[nodiscard]] static std::filesystem::path ExecutableDirectory();
        [[nodiscard]] static std::filesystem::path Root();
        [[nodiscard]] static std::filesystem::path Resolve(const std::filesystem::path& relativePath);
    };
}
