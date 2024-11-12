#include "Panel.h"
#include <iostream>

Panel::Panel(int width, int height, int yOffset)
    : width(width), height(height), yOffset(yOffset), selectedTextureIndex(0) {}

void Panel::setTextures(const std::vector<Texture::ID>& textures) {
    this->textures = textures;
}

int Panel::getSelectedTexture() const {
    return selectedTextureIndex;
}

void Panel::draw() {
    ImGui::SetNextWindowPos(ImVec2(0, yOffset));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::Begin("Bottom Panel", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    if (!textures.empty()) {
        for (int i = 0; i < textures.size(); ++i) {
            ImGui::PushID(i);
            if (ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(textures[i])), ImVec2(50, 50))) {
                selectedTextureIndex = i;
            }
            ImGui::PopID();

            if (i < textures.size() - 1) {
                ImGui::SameLine();
            }
        }

        ImGui::Text("Selected Texture: %d", selectedTextureIndex);
    }

    ImGui::End();
}
