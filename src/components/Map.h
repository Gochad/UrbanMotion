#pragma once
#include "../imgui/Draw.h"
#include "Field.h"
#include <vector>
#include "../filestorage/MapFile.cpp"

class Map {
public:
    Map(int width, int height, int squareSize);
    void draw(IDraw* context);
    void edit(IDraw* context, Point mousePosition);
    void showChangeTilePanel(IDraw* context, int selectedX, int selectedY);

private:
    int width;
    int height;
    int square_size;
    int selectedX = -1;
    int selectedY = -1;
    bool isEditing = false;
    std::unordered_map<Texture::ID, int> textureMap;
    std::vector<std::vector<Field>> grid;

    MapFile file;
};
