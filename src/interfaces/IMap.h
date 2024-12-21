#pragma once
#include "../imgui/Draw.h"
#include "../texture/Manager.h"
#include "../components/Fields.h"

class IMap {
public:
    virtual ~IMap() = default;

    virtual void showChangeTilePanel(IDraw* context, int x, int y, Field* field) = 0;
    virtual int getSquareSize() = 0;
};