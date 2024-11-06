#pragma once
#include "Field.h"
#include "IDraw.h"
#include <vector>

class Map {
public:
    int width;
    int height;
    const int square_size;
    std::vector<std::vector<Field>> grid;

    Map(int w, int h, int square_size);

    void draw(IDraw* context);
};
