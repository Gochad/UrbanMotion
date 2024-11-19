#ifndef APP_H
#define APP_H

#include "imgui/Window.h"
#include "imgui/Manager.h"
#include "imgui/DropTargetWindow.h"
#include "imgui/WelcomeScreen.h"
#include "components/Map.h"

class App {
private:
    int grid_size;
    int square_size;
    Window* appWindow;
    Manager* imguiManager;
    Map* map;
    MapFile* mapfile;
    Panel* panel;
    DropTargetWindow* dropTargetWindow;
    WelcomeScreen* welcomeScreen;

    bool is_initialized;

    void initializeMap(const std::string& map_id);

public:
    App(int grid_size, int square_size);
    ~App();
    bool init();
    void run();
    void shutdown();
};

#endif // APP_H
