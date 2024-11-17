#pragma once
#include "../imgui/Point.h"

class IDraw {
public:
    virtual void DrawTexture(const Point& min, const Point& max, int textureid, int rotationDegrees) = 0;
};
