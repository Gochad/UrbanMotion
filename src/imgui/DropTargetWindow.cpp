#include "DropTargetWindow.h"
#include <iostream>

#include "../filestorage/mapper.h"

DropTargetWindow::DropTargetWindow(Map* map, Panel* panel, MapFile* mapfile, int square_size)
    : map(map), panel(panel), mapfile(mapfile), square_size(square_size) {}

void DropTargetWindow::render(Draw* imgui_context) {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("DropTargetWindow", NULL,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar |
                 ImGuiWindowFlags_NoBringToFrontOnFocus |
                 ImGuiWindowFlags_NoBackground);

    ImGui::InvisibleButton("FullScreenDropTarget", ImGui::GetIO().DisplaySize);

    ImVec2 mapPos(0, 0);

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FIELD")) {
            Field* field = static_cast<Field*>(payload->Data);          
            ImVec2 mousePos = ImGui::GetMousePos();

            int gridX = static_cast<int>((mousePos.x - mapPos.x) / square_size);
            int gridY = static_cast<int>((mousePos.y - mapPos.y) / square_size);

            map->showChangeTilePanel(imgui_context, gridX, gridY, field);
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::End();
}
