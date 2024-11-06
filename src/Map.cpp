#include "Map.h"

Map::Map(int w, int h, int square_size) 
    : width(w), height(h), square_size(square_size), grid(h, std::vector<Field>(w)) {}

void Map::draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ImVec2 p_min(x * square_size, y * square_size);
            ImVec2 p_max((x + 1) * square_size, (y + 1) * square_size);

            grid[y][x].draw(draw_list, p_min, p_max);
        }
    }

    ImGui::PopStyleVar();
}
