#include "DropTargetWindow.h"
#include <iostream>
#include "../components/Fields.h"

DropTargetWindow::DropTargetWindow(IMap* map)
    : map(map) {}
    
void DropTargetWindow::render(Draw* imgui_context, int vehicleCount) {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("DropTargetWindow", NULL, DropTargetWindowFlags);

    ImGui::InvisibleButton("FullScreenDropTarget", ImGui::GetIO().DisplaySize);

    ImVec2 mapPos(0, 0);
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FIELD")) {
            Field* field = static_cast<Field*>(payload->Data);
            ImVec2 mousePos = ImGui::GetMousePos();

            int gridX = static_cast<int>((mousePos.x - mapPos.x) / map->getSquareSize());
            int gridY = static_cast<int>((mousePos.y - mapPos.y) / map->getSquareSize());
            map->showChangeTilePanel(imgui_context, gridX, gridY, field, field->textureID);
        }
        else if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE_INDEX")) {
            int textureIndex = *(const int*)payload->Data;
            ImVec2 mousePos = ImGui::GetMousePos();

            int gridX = static_cast<int>((mousePos.x - mapPos.x) / map->getSquareSize());
            int gridY = static_cast<int>((mousePos.y - mapPos.y) / map->getSquareSize());
            
            map->showChangeTilePanel(imgui_context, gridX, gridY, nullptr, static_cast<Texture::ID>(textureIndex));
        }
    }

    ImGui::End();
}
