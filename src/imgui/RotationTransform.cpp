#include "RotationTransform.h"

RotationTransform::RotationTransform(const ImVec2& center, const ImVec2& size, int rotationDegrees)
    : center(center), halfSize(size.x * 0.5f, size.y * 0.5f), rotationDegrees(rotationDegrees)
{
    calculateRotationMatrix();
}

std::array<ImVec2, 4> RotationTransform::getTransformedVertices() const
{
    std::array<glm::vec2, 4> corners = {
        glm::vec2(-halfSize.x, -halfSize.y),
        glm::vec2( halfSize.x, -halfSize.y),
        glm::vec2( halfSize.x,  halfSize.y),
        glm::vec2(-halfSize.x,  halfSize.y)
    };

    std::array<ImVec2, 4> transformedVertices;
    for (int i = 0; i < 4; ++i) {
        glm::vec2 rotated = rotationMatrix * corners[i];
        transformedVertices[i] = ImVec2(rotated.x + center.x, rotated.y + center.y);
    }

    return transformedVertices;
}

void RotationTransform::calculateRotationMatrix()
{
    float rotationRadians = glm::radians(static_cast<float>(rotationDegrees));
    rotationMatrix = glm::mat2(
        glm::vec2(std::cos(rotationRadians), -std::sin(rotationRadians)),
        glm::vec2(std::sin(rotationRadians),  std::cos(rotationRadians))
    );
}
