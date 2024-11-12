#include "Map.h"
#include "../texture/Manager.h"

Map::Map(int w, int h, int square_size) 
    : width(w), height(h), square_size(square_size), grid(h, std::vector<Field>(w)), file("1") {
        Texture::Manager* textureManager = new Texture::Manager;
        this->textureMap = textureManager->loadTextures();
    }

void Map::draw(IDraw* context) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point min(x * square_size, y * square_size);
            Point max((x + 1) * square_size, (y + 1) * square_size);

            Texture::ID id = this->file.getTexture(x, y);

            grid[y][x].draw(context, min, max, this->textureMap[id]);
        }
    }
}