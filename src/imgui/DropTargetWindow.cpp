#include "DropTargetWindow.h"
#include <iostream>
#include "../components/Fields.h"

DropTargetWindow::DropTargetWindow(IMap* map)
    : map(map) {}
    
void DropTargetWindow::render(Draw* imgui_context, int vehicleCount) {
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
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE_INDEX")) {
            int textureIndex = *(const int*)payload->Data;
             Field* field = static_cast<Field*>(payload->Data);          
                ImVec2 mousePos = ImGui::GetMousePos();

                int gridX = static_cast<int>((mousePos.x - mapPos.x) / map->getSquareSize());
                int gridY = static_cast<int>((mousePos.y - mapPos.y) / map->getSquareSize());
                map->showChangeTilePanel(imgui_context, gridX, gridY, field, static_cast<Texture::ID>(textureIndex));

            map->showChangeTilePanel(imgui_context, gridX, gridY, field,  static_cast<Texture::ID>(textureIndex));
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::End();
}
