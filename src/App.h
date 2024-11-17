#ifndef APP_H
#define APP_H

#include "imgui/Window.h"
#include "imgui/Manager.h"
#include "imgui/DropTargetWindow.h"
#include "components/Map.h"

class App {
public:
    App(int grid_size, int square_size);
    ~App();

    bool init();
    void run();
    void shutdown();

private:
    int grid_size, square_size;
    bool is_initialized;

    Window* appWindow;
    Manager* imguiManager;
    Map* map;
    MapFile* mapfile;
    Panel* panel;
    DropTargetWindow* dropTargetWindow;
};

#endif // APP_H
