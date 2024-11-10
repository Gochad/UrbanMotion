#pragma once
#include "../imgui/Point.h"

class IDraw {
public:
    virtual void DrawFilledRect(const Point& p_min, const Point& p_max, unsigned int color) = 0;
    virtual void DrawRect(const Point& p_min, const Point& p_max, unsigned int color) = 0;
    virtual void DrawTexture(const Point& min, const Point& max) = 0;
};
