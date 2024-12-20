#pragma once
#include <vector>
#include "Fields.h"
#include "../imgui/Draw.h"
#include "../texture/Manager.h"
#include "../filestorage/MapFile.h"

using FieldMatrix = std::vector<std::vector<std::shared_ptr<Field>>>;

class Map {
public:
    Map(int width, int height, int squareSize, FieldMatrix matrix);
    void draw(IDraw* context);
    void edit(IDraw* context, Point mousePosition);
    void showChangeTilePanel(IDraw* context, int selectedX, int selectedY, Field* field);

private:
    int width;
    int height;
    int square_size;
    int selectedX = -1;
    int selectedY = -1;
    bool isEditing = false;

    FieldMatrix grid;
};
