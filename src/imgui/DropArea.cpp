#include "DropArea.h"

DropArea::DropArea(const char* payloadType)
    : payloadType(payloadType) {}

void DropArea::draw() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("DropTargetWindow", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                                         ImGuiWindowFlags_NoBringToFrontOnFocus |
                                         ImGuiWindowFlags_NoBackground);

    ImGui::InvisibleButton("DropArea", ImGui::GetIO().DisplaySize);

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(payloadType)) {
            int textureIndex = *(const int*)payload->Data;
            std::cout << "Dropped textureIndex: " << textureIndex << std::endl;
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::End();
}
