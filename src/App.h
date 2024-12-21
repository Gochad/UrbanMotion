#ifndef APP_H
#define APP_H

#include "imgui/Window.h"
#include "imgui/Manager.h"
#include "imgui/DropTargetWindow.h"
#include "imgui/WelcomeScreen.h"
#include "components/Map.h"
#include <memory>

class App {
private:
    int grid_size;
    int square_size;
    std::unique_ptr<Window> appWindow;
    std::unique_ptr<Manager> imguiManager;
    std::unique_ptr<Map> map;
    std::unique_ptr<MapFile> mapfile;

    bool is_initialized;
    bool map_initialized;

    void initializeMap(const std::string& map_id);

public:
    App(int grid_size, int square_size);
    ~App();
    bool init();
    void run();
    void shutdown();
};

#endif // APP_H
