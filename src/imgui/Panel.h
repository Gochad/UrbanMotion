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

    void setTextures(const std::vector<Texture::ID>& textures);

private:
    int width;
    int height;
    int yOffset;

    std::vector<Texture::ID> textures;
    int selectedTextureIndex;
};
