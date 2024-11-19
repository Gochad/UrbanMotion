#pragma once
#include "../imgui/Point.h"
#include "../texture/Manager.h"

class IDraw {
public:
    virtual void DrawTexture(const Point& min, const Point& max, Texture::ID textureid, int rotationDegrees) = 0;
};
