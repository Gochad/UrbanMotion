#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include <functional>
#include "../texture/Manager.h"
#include "../components/Map.h" 

class Panel {
public:
    Panel(int width, int height, int yOffset);
    void draw(std::function<void()>, std::function<void()>, Map* map);
    int getSelectedTexture() const;
    bool isFinalMapSaved() const;

    void setTextureRange(int range);

private:
    int width;
    int height;
    int yOffset;

    int textureRange;
    int selectedTextureIndex;
    bool mapSaved;
    bool finalMapSaved;
};
