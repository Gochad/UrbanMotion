#include "Map.h"

Map::Map(int w, int h, int square_size, MapFile* mapfile, Texture::MAP textures) 
    : width(w), height(h), square_size(square_size), grid(h, std::vector<Field>(w)), file(mapfile)  {
        this->textureMap = textures;
    }

void Map::draw(IDraw* context) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point min(x * square_size, y * square_size);
            Point max((x + 1) * square_size, (y + 1) * square_size);

            Texture::ID id = this->file->getTexture(x, y);

            grid[y][x].draw(context, min, max, this->textureMap[id]);
        }
    }
}

void Map::showChangeTilePanel(IDraw* context, int selectedX, int selectedY, Texture::ID id) {
    Point min(selectedX * square_size, selectedY * square_size);
    Point max((selectedX + 1) * square_size, (selectedX + 1) * square_size);

    this->file->setTexture(selectedX, selectedY, id);
    grid[selectedY][selectedX].draw(context, min, max, this->textureMap[id]);
}

