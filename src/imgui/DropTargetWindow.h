#pragma once
#include "imgui.h"
#include "Draw.h"
#include "../interfaces/IMap.h"

class DropTargetWindow {
private:
    IMap* map;
    int innerCounter = 0;

public:
    DropTargetWindow(IMap* map);

    void render(Draw* imgui_context, int vehicleCount);
};
