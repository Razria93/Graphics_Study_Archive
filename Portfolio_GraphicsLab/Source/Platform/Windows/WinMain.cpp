#include "Application/Application.h"

#include <Windows.h>

#include <cstdlib>
#include <exception>

int WINAPI wWinMain(
    [[maybe_unused]] HINSTANCE instance,
    [[maybe_unused]] HINSTANCE previousInstance,
    [[maybe_unused]] PWSTR commandLine,
    [[maybe_unused]] int showCommand)
{
    try
    {
        return GraphicsLab::App::Application{}.Run();
    }
    catch (const std::exception&)
    {
        MessageBoxW(
            nullptr,
            L"GraphicsLab failed during startup.",
            L"GraphicsLab",
            MB_OK | MB_ICONERROR);
        return EXIT_FAILURE;
    }
}
