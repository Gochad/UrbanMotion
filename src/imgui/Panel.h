#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include <functional>
#include "../texture/Manager.h"

class Panel {
public:
    Panel(int width, int height, int yOffset);
    void draw(std::function<void()>);
    int getSelectedTexture() const;

    void setTextureRange(int range);

private:
    int width;
    int height;
    int yOffset;

    int textureRange;
    int selectedTextureIndex;
};
