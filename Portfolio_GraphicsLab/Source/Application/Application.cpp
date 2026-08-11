#include "Application/Application.h"

#include "Asset/AssetPath.h"

#include <cstdlib>
#include <filesystem>

namespace GraphicsLab::App
{
    int Application::Run() const
    {
        const std::filesystem::path assetRoot = Asset::AssetPath::Root();
        return std::filesystem::is_directory(assetRoot) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
}
