#include "Panel.h"
#include <iostream>
#include "../filestorage/mapper.h"
#include "TransformTexture.h"
#include <cmath>

Panel::Panel(int width, int height, int yOffset)
    : width(width), height(height), yOffset(yOffset), selectedTextureIndex(0) {}

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
        int textureID = field->getTextureID();
        ImGui::PushID(textureID);

        float angle = field->rotation * M_PI / 180.0f;
        float cos_a = cosf(angle);
        float sin_a = sinf(angle);

        ImVec2 center = ImVec2(0.5f, 0.5f);

        ImVec2 corners[4] = {
            ImVec2(-0.5f, -0.5f),
            ImVec2(0.5f, -0.5f),
            ImVec2(0.5f, 0.5f),
            ImVec2(-0.5f, 0.5f)
        };

        ImVec2 uv[4];
        for (int i = 0; i < 4; i++) {
            uv[i].x = center.x + cos_a * corners[i].x - sin_a * corners[i].y;
            uv[i].y = center.y + sin_a * corners[i].x + cos_a * corners[i].y;
        }

        ImVec2 size = ImVec2(50, 50);

        ImGui::ImageButton(reinterpret_cast<void*>(static_cast<intptr_t>(textureID)), size, uv[0], uv[2]);

        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
            Field* copiedField = field.get();

            ImGui::SetDragDropPayload("FIELD", copiedField, sizeof(Field));

            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(field->getTextureID())), size, uv[0], uv[2]);

            ImGui::EndDragDropSource();
        }

        ImGui::PopID();
        ImGui::SameLine();
    }

    ImGui::End();
}
