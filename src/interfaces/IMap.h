#pragma once
#include "../imgui/Draw.h"
#include "../texture/Manager.h"

class IMap {
public:
    virtual ~IMap() = default;

    virtual int showChangeTilePanel(IDraw* context, int x, int y, Texture::ID textureId) = 0;
    virtual int getSquareSize() = 0;
};
