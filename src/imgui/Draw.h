#pragma once
#include "IDraw.h"
#include <imgui.h>
#include "RotationTransform.h"
#include <iostream>
#include "../texture/Manager.h"

constexpr std::array<ImVec2, 4> getDefaultUVs()
{
    return {
        ImVec2{0.0f, 0.0f},
        ImVec2{1.0f, 0.0f},
        ImVec2{1.0f, 1.0f},
        ImVec2{0.0f, 1.0f}
    };
}

class Draw : public IDraw {
private:
    ImDrawList* draw_list_;
public:
    Draw(ImDrawList* draw_list) : draw_list_(draw_list) {}

    void DrawTexture(const Point& min, const Point& max, Texture::ID textureid, int rotationDegrees) override {
        ImVec2 center = ImVec2((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f);
        ImVec2 size = ImVec2(max.x - min.x, max.y - min.y);

        RotationTransform transform(center, size, rotationDegrees);
        auto transformedVertices = transform.getTransformedVertices();

        constexpr auto uvs = getDefaultUVs();

        draw_list_->AddImageQuad(
            reinterpret_cast<void*>(static_cast<intptr_t>(textureid)),
            transformedVertices[0], transformedVertices[1], transformedVertices[2], transformedVertices[3],
            uvs[0], uvs[1], uvs[2], uvs[3]
        );
    }
};

