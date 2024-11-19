#ifndef APP_H
#define APP_H

#include "imgui/Window.h"
#include "imgui/Manager.h"
#include "imgui/DropTargetWindow.h"
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
    bool is_initialized;

    bool is_map_selected;
    std::string selected_map_id;

    void renderMapSelectionPanel();

public:
    App(int grid_size, int square_size);
    ~App();
    bool init();
    void run();
    void shutdown();
};

#endif // APP_H
