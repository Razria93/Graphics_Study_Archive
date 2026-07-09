#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <string>

namespace {

template <typename T>
void Print(const std::string& label, const T& value) {
    std::cout << label << '\n' << glm::to_string(value) << "\n\n";
}

} // namespace

int main() {
    const glm::mat2 a(1.0f, 2.0f,
                      3.0f, 4.0f);
    const glm::mat2 b(5.0f, 6.0f,
                      7.0f, 8.0f);

    Print("mat2 A: GLM stores matrix values in column-major order", a);
    Print("transpose(A)", glm::transpose(a));
    Print("A[1]: column access", a[1]);
    Print("A + B", a + b);
    Print("A * B", a * b);
    Print("B * A: matrix multiplication order changes the result", b * a);

    glm::mat4 m(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);
    m = 2.0f * (m * 10.0f) + (m * 10.0f);
    Print("scaled mat4 expression", m);

    const glm::mat4 translation = glm::translate(glm::vec3(1.0f, 2.0f, 3.0f));
    const glm::vec4 point(4.0f, 5.0f, 6.0f, 1.0f);
    const glm::vec4 vector(4.0f, 5.0f, 6.0f, 0.0f);

    Print("translation matrix", translation);
    Print("translation * point: w = 1 applies translation", translation * point);
    Print("translation * vector: w = 0 ignores translation", translation * vector);
    Print("inverse(translation)", glm::inverse(translation));

    const glm::mat4 rotationX =
        glm::rotate(glm::pi<float>() / 3.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    Print("rotationX", rotationX);
    Print("transpose(rotationX)", glm::transpose(rotationX));
    Print("transpose(rotationX) * rotationX", glm::transpose(rotationX) * rotationX);

    const glm::vec4 originOffset(1.0f, 0.0f, 0.0f, 1.0f);
    Print("(translation * rotationX) * point: rotate first, then translate",
          (translation * rotationX) * originOffset);
    Print("(rotationX * translation) * point: translate first, then rotate",
          (rotationX * translation) * originOffset);
    Print("row-vector style using transpose(translation * rotationX)",
          originOffset * glm::transpose(translation * rotationX));

    Print("non-uniform scale", glm::scale(glm::vec3(0.5f, 1.0f, 2.0f)));
}
