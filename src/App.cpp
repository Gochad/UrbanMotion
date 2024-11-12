#include "App.h"
#include <iostream>
#include "imgui/Panel.h"

App::App(int grid_size, int square_size)
    : grid_size(grid_size), square_size(square_size),
      appWindow(nullptr), imguiManager(nullptr), map(nullptr),
      is_initialized(false) {}

App::~App() {
    shutdown();
}

bool App::init() {
    appWindow = new Window(grid_size * square_size, grid_size * square_size + 100);
    if (!appWindow->init()) return false;

    imguiManager = new Manager(appWindow->getWindow());
    if (!imguiManager->init()) return false;

    map = new Map(grid_size, grid_size, square_size);

    is_initialized = true;
    return true;
}

void App::run() {
    if (!is_initialized) return;

    while (!imguiManager->shouldClose()) {
        imguiManager->beginFrame();

        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        Draw imgui_context(draw_list);

        map->draw(&imgui_context);

        Panel bottomPanel = Panel(appWindow->width, 100, appWindow->height - 100);
        bottomPanel.draw();

        imguiManager->endFrame();

        appWindow->renderFrame();
    }
}

void App::shutdown() {
    if (is_initialized) {
        delete map;

        delete imguiManager;
        delete appWindow;

        is_initialized = false;
    }
}
