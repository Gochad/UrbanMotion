#pragma once
#include "IMap.h"
#include "../imgui/Draw.h"
#include "Field.h"
#include <vector>

class Map : public IMap {
public:
    Map(int width, int height, int squareSize);
    void draw(IDraw* context) override;

private:
    int width;
    int height;
    int square_size;
    std::vector<std::vector<Field>> grid;
};
