#pragma once
#include "IDraw.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "../texture/Manager.h"
#include "TransformTexture.h"

class Draw : public IDraw {
private:
    ImDrawList* draw_list_;
public:
    Draw(ImDrawList* draw_list) : draw_list_(draw_list) {}

    void DrawTexture(const Point& min, const Point& max, int textureid, int rotationDegrees) override {
        ImVec2 center = ImVec2((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f);
        ImVec2 halfSize = ImVec2((max.x - min.x) / 2.0f, (max.y - min.y) / 2.0f);

        ImVec2 transformedCorners[4];
<<<<<<< HEAD
        for (int i = 0; i < 4; ++i) {
            glm::vec2 rotated = rotationMatrix * corners[i];
            transformedCorners[i] = ImVec2(rotated.x + center.x, rotated.y + center.y);
        }
=======
        TransformTexture(center, halfSize, rotationDegrees, transformedCorners);
>>>>>>> 260567d4b9fdf0c4ee2d7f1b61dbda08e14683fb

        ImVec2 uvs[4] = {
            ImVec2(0.0f, 0.0f),
            ImVec2(1.0f, 0.0f),
            ImVec2(1.0f, 1.0f),
            ImVec2(0.0f, 1.0f)
        };

        draw_list_->AddImageQuad(
            reinterpret_cast<void*>(static_cast<intptr_t>(textureid)),
            transformedCorners[0], transformedCorners[1], transformedCorners[2], transformedCorners[3],
            uvs[0], uvs[1], uvs[2], uvs[3]
        );
    }
};
