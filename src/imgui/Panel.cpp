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

    for (const auto& entry : FromFileToFields) {
        char key = entry.first;
        auto field = entry.second();

        ImGui::PushID(key);

        if (ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(field->getTextureID())), ImVec2(50, 50))) {
            selectedTextureIndex = static_cast<int>(key);
        }

        ImGui::PopID();
    }

    ImGui::End();
}