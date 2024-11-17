#pragma once
#include "imgui.h"
#include "Draw.h"
#include "../interfaces/IMap.h"

class DropTargetWindow {
private:
    IMap* map;
    int square_size;

public:
    DropTargetWindow(IMap* map, int square_size);

    void render(Draw* imgui_context);
};
