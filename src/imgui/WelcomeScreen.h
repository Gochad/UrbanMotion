#pragma once
#include <string>
#include <vector>
#include <functional>

class WelcomeScreen {
private:
    std::vector<std::string> available_maps;
    std::string selected_map_id;
    bool map_selected;

public:
    WelcomeScreen(const std::vector<std::string>& maps);
    ~WelcomeScreen() = default;

    void render(
        int app_window_width, int app_window_height,
        std::function<void(const std::string&)> onMapSelected);

    bool isMapSelected() const;

    std::string getSelectedMapID() const;
};
