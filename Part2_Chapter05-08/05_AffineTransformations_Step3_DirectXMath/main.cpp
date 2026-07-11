#include <DirectXMath.h>
#include <directxtk/SimpleMath.h>

#include <iostream>

namespace {

std::ostream& operator<<(std::ostream& os, const DirectX::XMFLOAT4& value) {
    os << value.x << '\t' << value.y << '\t' << value.z << '\t' << value.w;
    return os;
}

std::ostream& operator<<(std::ostream& os, const DirectX::XMFLOAT4X4& value) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            os << value.m[row][col] << '\t';
        }
        os << '\n';
    }
    return os;
}

void PrintHeader(const char* title) {
    std::cout << "\n== " << title << " ==\n";
}

} // namespace

int main() {
    using namespace DirectX;

    if (!XMVerifyCPUSupport()) {
        std::cout << "DirectXMath is not supported on this CPU.\n";
        return -1;
    }

    PrintHeader("XMVECTOR length");
    XMFLOAT4 sourceVector = {1.0f, 2.0f, 3.0f, 1.0f};
    XMVECTOR simdVector = XMLoadFloat4(&sourceVector);
    simdVector = XMVector3Length(simdVector);

    float length = 0.0f;
    XMStoreFloat(&length, simdVector);
    std::cout << "length(1, 2, 3) = " << length << '\n';

    PrintHeader("DirectXMath translation");
    const XMMATRIX translation = XMMatrixTranslation(1.0f, 2.0f, 3.0f);

    XMFLOAT4X4 translationStored = {};
    XMStoreFloat4x4(&translationStored, translation);
    std::cout << translationStored;

    XMFLOAT4 point = {4.0f, 5.0f, 6.0f, 1.0f};
    XMFLOAT4 direction = {4.0f, 5.0f, 6.0f, 0.0f};

    XMStoreFloat4(&point,
                  XMVector3TransformCoord(XMLoadFloat4(&point), translation));
    XMStoreFloat4(
        &direction,
        XMVector3TransformNormal(XMLoadFloat4(&direction), translation));

    std::cout << "point transformed    : " << point << '\n';
    std::cout << "direction transformed: " << direction << '\n';

    PrintHeader("SimpleMath translation");
    using namespace DirectX::SimpleMath;

    Matrix simpleTranslation =
        Matrix::CreateTranslation(Vector3(1.0f, 2.0f, 3.0f));
    Vector4 simplePoint(4.0f, 5.0f, 6.0f, 1.0f);
    Vector4 simpleDirection(4.0f, 5.0f, 6.0f, 0.0f);

    simplePoint = Vector4::Transform(simplePoint, simpleTranslation);
    simpleDirection = Vector4::Transform(simpleDirection, simpleTranslation);

    std::cout << "point transformed    : " << simplePoint.x << '\t'
              << simplePoint.y << '\t' << simplePoint.z << '\t'
              << simplePoint.w << '\n';
    std::cout << "direction transformed: " << simpleDirection.x << '\t'
              << simpleDirection.y << '\t' << simpleDirection.z << '\t'
              << simpleDirection.w << '\n';

    XMFLOAT4X4 simpleTranslationStored = {};
    XMStoreFloat4x4(&simpleTranslationStored, simpleTranslation);
    std::cout << simpleTranslationStored;

    simpleTranslation.Translation(Vector3(0.0f));
    XMStoreFloat4x4(&simpleTranslationStored, simpleTranslation);
    std::cout << "translation reset\n" << simpleTranslationStored;

    return 0;
}
