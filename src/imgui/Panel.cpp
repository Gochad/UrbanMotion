#include "Panel.h"
#include <iostream>

Panel::Panel(int width, int height, int yOffset)
    : width(width), height(height), yOffset(yOffset), selectedTextureIndex(0) {
        Texture::Manager* textureManager = new Texture::Manager;
        std::map<Texture::ID, int> textureMap = textureManager->loadTextures();
        auto lastElement = *textureMap.rbegin();
        this->setTextureRange(static_cast<int>(lastElement.first));
    }

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

    for (int i = 1; i <= textureRange; ++i) {
        ImGui::PushID(i);
        
        if (ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(i)), ImVec2(50, 50))) {
            selectedTextureIndex = i;
        }

        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            int payloadIndex = i;
            ImGui::SetDragDropPayload("TEXTURE_INDEX", &payloadIndex, sizeof(int));
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(i)), ImVec2(50, 50));
    
            ImGui::EndDragDropSource();
        }

        ImGui::PopID();
        ImGui::SameLine();
    }
    

    ImGui::End();
}
