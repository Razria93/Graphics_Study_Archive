#include <d3d11.h>
#include <wrl.h>

#include <iostream>

namespace {

void PrintFeatureLevel(D3D_FEATURE_LEVEL featureLevel) {
    std::cout << "Created D3D feature level: 0x" << std::hex
              << static_cast<unsigned int>(featureLevel) << std::dec << '\n';
}

}

int main() {
    using Microsoft::WRL::ComPtr;

    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11DeviceContext> context;

    const UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
    const D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_12_1, D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,  D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    D3D_FEATURE_LEVEL createdFeatureLevel = D3D_FEATURE_LEVEL_11_0;

    const HRESULT hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, creationFlags,
        featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &device,
        &createdFeatureLevel, &context);

    if (FAILED(hr)) {
        std::cout << "D3D11CreateDevice failed: 0x" << std::hex << hr << '\n';
        return -1;
    }

    PrintFeatureLevel(createdFeatureLevel);

    ComPtr<ID3D11Device> copiedDevice;
    if (FAILED(device.As(&copiedDevice))) {
        std::cout << "ComPtr::As failed.\n";
        return -1;
    }

    ID3D11Device* rawDevice = copiedDevice.Get();
    std::cout << "Raw device pointer is " << rawDevice << '\n';

    copiedDevice.Reset();
    if (!copiedDevice) {
        std::cout << "copiedDevice released\n";
    }

    return 0;
}
