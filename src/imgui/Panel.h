#pragma once
#include <imgui.h>
#include <string>

class Panel {
public:
    Panel(int width, int height, int yOffset);
    void draw();

private:
    int width;
    int height;
    int yOffset;
};
