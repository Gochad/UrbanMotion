#ifndef ROTATIONTRANSFORM_H
#define ROTATIONTRANSFORM_H

#include <array>
#include "imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class RotationTransform {
public:
    RotationTransform(const ImVec2& center, const ImVec2& size, int rotationDegrees);

    std::array<ImVec2, 4> getTransformedVertices() const;

private:
    ImVec2 center;
    glm::vec2 halfSize;
    int rotationDegrees;
    glm::mat2 rotationMatrix;

    void calculateRotationMatrix();
};

#endif // ROTATIONTRANSFORM_H
