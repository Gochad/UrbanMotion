#include "WelcomeScreen.h"
#include <imgui.h>

WelcomeScreen::WelcomeScreen(const std::vector<std::string>& maps)
    : available_maps(maps), map_selected(false), selected_map_id("") {}

void WelcomeScreen::render(
    int app_window_width, int app_window_height,
    std::function<void(const std::string&)> onMapSelected) {

    ImVec2 window_size(300, 200);
    ImVec2 window_pos(
        (app_window_width - window_size.x) / 2,
        (app_window_height - window_size.y) / 2
    );

    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowPos(window_pos);

    ImGui::Begin("Welcome Screen - Select a Map", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::Text("Available Maps:");
    ImGui::Separator();

    if (ImGui::Button("Create new map")) {
        selected_map_id = "new";
        map_selected = true;
        onMapSelected(selected_map_id);
    }

    for (const auto& map_id : available_maps) {
        if (ImGui::Button(("Load Map " + map_id).c_str())) {
            selected_map_id = map_id;
            map_selected = true;
            onMapSelected(map_id);
        }
    }

    ImGui::End();
}

bool WelcomeScreen::isMapSelected() const {
    return map_selected;
}

std::string WelcomeScreen::getSelectedMapID() const {
    return selected_map_id;
}
