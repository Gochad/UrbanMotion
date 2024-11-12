#include "Panel.h"
#include <iostream>

Panel::Panel(int width, int height, int yOffset)
    : width(width), height(height), yOffset(yOffset) {}

void Panel::draw() {
    ImGui::SetNextWindowPos(ImVec2(0, yOffset));
    ImGui::SetNextWindowSize(ImVec2(width, height));

    ImGui::Begin("bottom panel", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

    if (ImGui::Button("button 1")) {
        std::cout << "button 1" << std::endl;
    }
    ImGui::SameLine();
    if (ImGui::Button("button 2")) {
        std::cout << "button 2" << std::endl;
    }
    ImGui::SameLine();
    ImGui::Text("text");

    ImGui::End();
}
