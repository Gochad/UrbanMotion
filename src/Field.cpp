#include "Field.h"

Field::Field() : isActive(false) {}

void Field::draw(ImDrawList* draw_list, const ImVec2& p_min, const ImVec2& p_max) const {
    ImU32 color = IM_COL32(179, 179, 179, 255);
    draw_list->AddRectFilled(p_min, p_max, color);

    ImU32 border_color = IM_COL32(0, 0, 0, 255);
    draw_list->AddRect(p_min, p_max, border_color);
}
