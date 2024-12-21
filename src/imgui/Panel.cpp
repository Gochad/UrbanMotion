#include "Panel.h"
#include <iostream>
#include "../filestorage/mapper.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        Texture::ID textureID = field->textureID;
        ImGui::PushID((std::to_string(key)).c_str());

        float angle = field->rotation * M_PI / 180.0f;
        float cos_a = cosf(angle);
        float sin_a = sinf(angle);

        ImVec2 size = ImVec2(50, 50);

        ImVec2 uv[4] = {
            ImVec2(0.0f, 0.0f),
            ImVec2(1.0f, 0.0f),
            ImVec2(1.0f, 1.0f),
            ImVec2(0.0f, 1.0f)
        };

        switch (field->rotation) {
            case 90:
                std::swap(uv[0], uv[1]);
                std::swap(uv[2], uv[3]);
                break;
            case 180:
                std::swap(uv[0], uv[2]);
                std::swap(uv[1], uv[3]);
                break;
            case 270:
                std::swap(uv[0], uv[3]);
                std::swap(uv[1], uv[2]);
                break;
        }

        ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(textureID)), size, uv[0], uv[2]);

        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            Field* copiedField = field.get();

            ImGui::SetDragDropPayload("FIELD", copiedField, sizeof(Field*));

            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(textureID)), size, uv[0], uv[2]);

            ImGui::EndDragDropSource();
        }

        ImGui::PopID();
        ImGui::SameLine();
    }

    ImGui::End();
}
