#pragma once
#include <vector>
#include "Field.h"
#include "../imgui/Draw.h"
#include "../texture/Manager.h"
#include "../filestorage/MapFile.cpp"

class Map {
public:
    Map(int width, int height, int squareSize, MapFile* mapfile, Texture::MAP textures);
    void draw(IDraw* context);
    void edit(IDraw* context, Point mousePosition);
    void showChangeTilePanel(IDraw* context, int selectedX, int selectedY, Texture::ID id);

private:
    int width;
    int height;
    int square_size;
    int selectedX = -1;
    int selectedY = -1;
    bool isEditing = false;
    Texture::MAP textureMap;
    std::vector<std::vector<Field>> grid;

    MapFile* file;
};
