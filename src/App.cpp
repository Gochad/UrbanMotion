#include "App.h"
#include <iostream>

App::App(int grid_size, int square_size)
    : grid_size(grid_size), square_size(square_size),
      appWindow(nullptr), imguiManager(nullptr), map(nullptr),
      is_initialized(false), mapfile(nullptr), dropTargetWindow(nullptr),
      welcomeScreen(nullptr) {}


App::~App() {
    shutdown();
}

void App::initializeMap(const std::string& map_id) {
    mapfile = new MapFile(map_id);
    map = new Map(grid_size, grid_size, square_size, mapfile->loadMap());
    dropTargetWindow = new DropTargetWindow(map, square_size);
}

bool App::init() {
    appWindow = new Window(grid_size * square_size, grid_size * square_size + 100);
    if (!appWindow->init()) return false;

    imguiManager = new Manager(appWindow->getWindow());
    if (!imguiManager->init()) return false;

    panel = new Panel(appWindow->width, 100, appWindow->height - 100);

    Texture::Manager* textureManager = new Texture::Manager;
    std::map<Texture::ID, int> textureMap = textureManager->loadTextures();
    auto lastElement = *textureMap.rbegin();

    panel->setTextureRange(static_cast<int>(lastElement.first));

    welcomeScreen = new WelcomeScreen({"1", "2", "3"});

    is_initialized = true;
    return true;
}


void App::run() {
    if (!is_initialized) return;

    bool map_initialized = false;

    while (!imguiManager->shouldClose()) {
        imguiManager->beginFrame();

        if (!map_initialized) {
            welcomeScreen->render(appWindow->width, appWindow->height, [this, &map_initialized](const std::string& map_id) {
                initializeMap(map_id);
                map_initialized = true;
            });
        } else {
            ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
            Draw imgui_context(draw_list);

            map->draw(&imgui_context);

            panel->draw([this]() { mapfile->saveMap(); });

            dropTargetWindow->render(&imgui_context);
        }

        imguiManager->endFrame();
        appWindow->renderFrame();
    }
}


void App::shutdown() {
    if (is_initialized) {
        delete map;
        delete mapfile;
        delete panel;
        delete dropTargetWindow;
        delete welcomeScreen;

        delete imguiManager;
        delete appWindow;

        is_initialized = false;
    }
}
