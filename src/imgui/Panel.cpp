#include "Panel.h"
#include <iostream>
#include <map>
#include "imgui.h"
#include "../components/Map.h"

Panel::Panel(int width, int height, int yOffset)
    : width(width), height(height), yOffset(yOffset), selectedTextureIndex(0), mapSaved(false), finalMapSaved(false) { 
        Texture::Manager* textureManager = new Texture::Manager;
        std::cout << "Panel constructor" << std::endl;
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
bool Panel::isFinalMapSaved() const {
    return finalMapSaved;
}
void Panel::draw(std::function<void()> onSaveClick, Map* map) {
    ImGui::SetNextWindowPos(ImVec2(0, yOffset));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::Begin("Editor panel", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("Save Map")) {
        onSaveClick();
        mapSaved = true; // Set the flag to true when the map is saved
    }
    
    ImGui::NewLine();

    // Render textures only if the map has not been saved
    if (!mapSaved) {
        for (int i = 1; i <= textureRange; ++i) {
            if (i == static_cast<int>(Texture::ID::Car) || i == static_cast<int>(Texture::ID::Bike) || i == static_cast<int>(Texture::ID::Motorcycle)) {
                continue;
            }

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
    } else {
        // If the map has been saved, display a message or other UI elements if necessary
        ImGui::Text("Map has been saved. Vehicles are now visible.");
    }

    ImGui::Separator();

    // Render vehicles only if the map has been saved
    if (mapSaved) {
        ImGui::Text("Vehicles");

        Texture::ID vehicleTextures[] = { Texture::ID::Car, Texture::ID::Bike, Texture::ID::Motorcycle };
        for (Texture::ID id : vehicleTextures) {
            int textureIndex = static_cast<int>(id);
            ImGui::PushID(textureIndex);

            if (ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(textureIndex)), ImVec2(50, 50))) {
                selectedTextureIndex = textureIndex;
            }

            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
                ImGui::SetDragDropPayload("TEXTURE_INDEX", &textureIndex, sizeof(int));
                ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(textureIndex)), ImVec2(50, 50));
                ImGui::EndDragDropSource();
            }

            ImGui::PopID();
            ImGui::SameLine();
        }

        // Add the new button here
        ImGui::NewLine(); // Add some space before the button
        if (ImGui::Button("Final look, start the game")) {
        finalMapSaved = true;
            std::cout << "Starting the game with selected vehicles..." << std::endl;
        }
    }

    ImGui::End();
}
