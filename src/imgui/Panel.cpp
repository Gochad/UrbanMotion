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

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    for (const auto& [key, fieldFactory] : FromFileToFields) {
        auto field = fieldFactory();
        Texture::ID textureID = field->textureID;
        ImGui::PushID((std::to_string(key)).c_str());

        ImVec2 size = ImVec2(50, 50);

        ImVec2 cursorPos = ImGui::GetCursorScreenPos();
        ImVec2 center = ImVec2(cursorPos.x + size.x * 0.5f, cursorPos.y + size.y * 0.5f);
        ImVec2 halfSize = ImVec2(size.x * 0.5f, size.y * 0.5f);

        glm::vec2 corners[4] = {
            glm::vec2(-halfSize.x, -halfSize.y),
            glm::vec2(halfSize.x, -halfSize.y),
            glm::vec2(halfSize.x, halfSize.y),
            glm::vec2(-halfSize.x, halfSize.y)
        };

        float rotationRadians = glm::radians(static_cast<float>(field->rotation));
        glm::mat2 rotationMatrix = glm::mat2(
            glm::vec2(std::cos(rotationRadians), -std::sin(rotationRadians)),
            glm::vec2(std::sin(rotationRadians), std::cos(rotationRadians))
        );

        ImVec2 transformedVertices[4];
        for (int i = 0; i < 4; ++i) {
            glm::vec2 rotated = rotationMatrix * corners[i];
            transformedVertices[i] = ImVec2(rotated.x + center.x, rotated.y + center.y);
        }

        ImVec2 uv[4] = {
            ImVec2(0.0f, 0.0f),
            ImVec2(1.0f, 0.0f),
            ImVec2(1.0f, 1.0f),
            ImVec2(0.0f, 1.0f)
        };

        drawList->AddImageQuad(
            reinterpret_cast<void*>(static_cast<intptr_t>(textureID)),
            transformedVertices[0],
            transformedVertices[1],
            transformedVertices[2],
            transformedVertices[3],
            uv[0], uv[1], uv[2], uv[3]
        );

        ImGui::SetCursorScreenPos(cursorPos);
        ImGui::InvisibleButton("Tile", size);

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
