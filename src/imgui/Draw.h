#pragma once
#include "IDraw.h"
#include <imgui.h>
#include <iostream>
#include "../texture/Manager.h"

class Draw : public IDraw {
public:
    Draw(ImDrawList* draw_list) : draw_list_(draw_list) {}

    void DrawFilledRect(const Point& min, const Point& max, unsigned int color) override {
        draw_list_->AddRectFilled(ImVec2(min.x, min.y), ImVec2(max.x, max.y), color);
    }

    void DrawRect(const Point& min, const Point& max, unsigned int color) override {
        draw_list_->AddRect(ImVec2(min.x, min.y), ImVec2(max.x, max.y), color);
    }

    void DrawTexture(const Point& min, const Point& max) {
        Texture::Manager textureManager;
        GLuint buildingTexture = textureManager.loadTexture("../textures/building.png");

        glBindTexture(GL_TEXTURE_2D, buildingTexture);

        draw_list_->AddImage(
            (void*)(intptr_t)(buildingTexture),
            ImVec2(min.x, min.y),
            ImVec2(max.x, max.y)
        );
    }

private:
    ImDrawList* draw_list_;
};
