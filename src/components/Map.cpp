#include "Map.h"
#include "../texture/Manager.h"

Map::Map(int w, int h, int square_size) 
    : width(w), height(h), square_size(square_size), grid(h, std::vector<Field>(w)) {
        Texture::Manager* textureManager = new Texture::Manager;
        textureID = textureManager->loadTexture("../textures/road.png");
    }

void Map::draw(IDraw* context) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point min(x * square_size, y * square_size);
            Point max((x + 1) * square_size, (y + 1) * square_size);

            grid[y][x].draw(context, min, max, textureID);
        }
    }
}