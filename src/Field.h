#pragma once
#include "imgui.h"

class Field {
public:
    bool isActive;

    Field();
    void toggle();
    void draw(ImDrawList* draw_list, const ImVec2& p_min, const ImVec2& p_max) const;
};

