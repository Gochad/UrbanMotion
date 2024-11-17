#pragma once
#include "../imgui/Draw.h"
#include "../texture/Manager.h"

class IMap {
public:
    virtual ~IMap() = default;

    virtual void showChangeTilePanel(IDraw* context, int x, int y, Texture::ID textureId) = 0;
};