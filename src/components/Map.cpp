#include "Map.h"

Map::Map(int w, int h, int square_size, FieldMatrix matrix) 
    : width(w), height(h), square_size(square_size), grid(matrix) {}


Map::Map(int width, int height, int square_size)
    : width(width), height(height), square_size(square_size) {
    grid.resize(height);
    for (int y = 0; y < height; ++y) {
        grid[y].resize(width);
        for (int x = 0; x < width; ++x) {
            grid[y][x] = std::make_shared<Field>();
        }
    }

    std::cout << "Map initialized with dimensions: " << width << "x" << height << std::endl;
}

void Map::draw(IDraw* context) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point min(x * square_size, y * square_size);
            Point max((x + 1) * square_size, (y + 1) * square_size);

            grid[y][x]->draw(context, min, max);
        }
    }
}

void Map::showChangeTilePanel(IDraw* context, int selectedX, int selectedY, Field* field) {
    Point min(selectedX * square_size, selectedY * square_size);
    Point max((selectedX + 1) * square_size, (selectedX + 1) * square_size);

    grid[selectedY][selectedX] = std::make_shared<Field>(*field);
    grid[selectedY][selectedX]->draw(context, min, max);
}

int Map::getSquareSize() {
    return square_size;
}

FieldMatrix Map::getFieldMatrix() {
    return grid;
}
