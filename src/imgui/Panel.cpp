#include "Panel.h"
#include <iostream>
#include "../filestorage/mapper.h"

Panel::Panel(int width, int height, int yOffset)
    : width(width), height(height), yOffset(yOffset), selectedTextureIndex(0) {}

void Panel::setTextureRange(int range) {
    this->textureRange = range;
}

int Panel::getSelectedTexture() const {
    return selectedTextureIndex;
}

void Panel::draw(std::function<void()> onSaveClick) {
    ImGui::SetNextWindowPos(ImVec2(0, yOffset));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::Begin("Editor panel", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Save")) {
        onSaveClick();
    }

    ImGui::SameLine();

    for (const auto& [key, fieldFactory] : FromFileToFields) {
        auto field = fieldFactory();
        int textureID = field->getTextureID();
        ImGui::PushID(textureID);
        
        if (ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(textureID)), ImVec2(50, 50))) {
            selectedTextureIndex = key;
        }

        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            char payloadKey = key;
            ImGui::SetDragDropPayload("FIELD_TYPE", &payloadKey, sizeof(char));
            
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(textureID)), ImVec2(50, 50));

            ImGui::EndDragDropSource();
        }

        ImGui::PopID();
        ImGui::SameLine();
    }

    ImGui::End();
}
