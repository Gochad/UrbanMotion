#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include <functional>
#include "../texture/Manager.h"
#include "../components/Map.h" 

class GameScreen {
public:
    GameScreen(int width, int height, int yOffset);
    void draw(std::function<void()>, Map* map);
    int getSelectedTexture() const;

    void setTextureRange(int range);

private:
    int width;
    int height;
    int yOffset;

    int textureRange;
    int selectedTextureIndex;
};
