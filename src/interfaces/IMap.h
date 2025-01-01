#pragma once
#include "../imgui/Draw.h"
#include "../texture/Manager.h"
#include "../components/Fields.h"

class IMap {
public:
    virtual ~IMap() = default;

    virtual int showChangeTilePanel(IDraw* context, int x, int y, Field* field, Texture::ID textureId) = 0;
    virtual int getSquareSize() = 0;
};
