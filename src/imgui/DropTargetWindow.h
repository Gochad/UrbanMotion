#pragma once

#include "imgui.h"
#include "Draw.h"
#include "../components/Map.h"
#include "Panel.h"
#include "../filestorage/MapFile.h"

class DropTargetWindow {
public:
    DropTargetWindow(Map* map, Panel* panel, MapFile* mapfile, int square_size);
    void render(Draw* imgui_context);

private:
    Map* map;
    Panel* panel;
    MapFile* mapfile;
    int square_size;
};
