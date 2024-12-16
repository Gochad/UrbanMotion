#include "Map.h"

Map::Map(int w, int h, int square_size, FieldMatrix matrix) 
    : width(w), height(h), square_size(square_size), grid(matrix)  {}

void Map::draw(IDraw* context) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point min(x * square_size, y * square_size);
            Point max((x + 1) * square_size, (y + 1) * square_size);

            grid[y][x]->draw(context, min, max);
        }
    }
}

void Map::showChangeTilePanel(IDraw* context, int selectedX, int selectedY, std::shared_ptr<Field> field) {
    Point min(selectedX * square_size, selectedY * square_size);
    Point max((selectedX + 1) * square_size, (selectedX + 1) * square_size);

    grid[selectedY][selectedX] = field;
    grid[selectedY][selectedX]->draw(context, min, max);
}

