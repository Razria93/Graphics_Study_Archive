#include "Asset/AssetPath.h"

#include <Windows.h>

#include <stdexcept>
#include <string>
#include <system_error>

namespace GraphicsLab::Asset
{
    std::filesystem::path AssetPath::ExecutableDirectory()
    {
        std::wstring executablePath(260, L'\0');

        for (;;)
        {
            const DWORD length = GetModuleFileNameW(
                nullptr,
                executablePath.data(),
                static_cast<DWORD>(executablePath.size()));

            if (length == 0)
            {
                throw std::system_error(
                    static_cast<int>(GetLastError()),
                    std::system_category(),
                    "GetModuleFileNameW failed");
            }

            if (length < executablePath.size())
            {
                executablePath.resize(length);
                return std::filesystem::path(executablePath).parent_path();
            }

            executablePath.resize(executablePath.size() * 2);
        }
    }

    std::filesystem::path AssetPath::Root()
    {
        return ExecutableDirectory() / L"Assets";
    }

    std::filesystem::path AssetPath::Resolve(const std::filesystem::path& relativePath)
    {
        if (relativePath.empty() || relativePath.is_absolute())
        {
            throw std::invalid_argument("Asset paths must be non-empty and relative");
        }

        const std::filesystem::path normalizedPath = relativePath.lexically_normal();
        if (*normalizedPath.begin() == L"..")
        {
            throw std::invalid_argument("Asset paths must remain inside the asset root");
        }

        return Root() / normalizedPath;
    }
}
