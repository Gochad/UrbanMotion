#pragma once
#include "IDraw.h"
#include <imgui.h>
#include <iostream>
#include "../texture/Manager.h"

class Draw : public IDraw {
public:
    Draw(ImDrawList* draw_list) : draw_list_(draw_list) {}

    void DrawTexture(const Point& min, const Point& max, int textureid) override {
        draw_list_->AddImage(
            reinterpret_cast<void*>(static_cast<intptr_t>(textureid)),
            ImVec2(min.x, min.y),
            ImVec2(max.x, max.y)
        );
    }

private:
    ImDrawList* draw_list_;
};
