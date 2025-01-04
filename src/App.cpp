#include "App.h"
#include <iostream>

App::App(int grid_size, int square_size)
    : grid_size(grid_size), square_size(square_size), is_initialized(false) {}

App::~App() {
    shutdown();
}

void App::initializeMap(const std::string& map_id) {
    if (map_id == "new") {
        map = std::make_unique<Map>(grid_size, grid_size, square_size);
    } else {
        map = std::make_unique<Map>(grid_size, grid_size, square_size, mapfile->getMap(map_id));
    }

    appWindow->setMap(map.get());
}

bool App::init() {
    appWindow = std::make_unique<Window>(grid_size * square_size, grid_size * square_size + 100);
    if (!appWindow->init()) return false;

    mapfile = std::make_unique<MapFile>();
    std::string mapID;

    appWindow->setMapInitializationCallback([this, &mapID](const std::string& map_id) {
        try {
            initializeMap(map_id);
            mapID = map_id;
            map_initialized = true;
        } catch (const std::exception& e) {
            std::cerr << "Failed to initialize map: " << e.what() << std::endl;
        }
    });

    appWindow->setMapSaveCallback([this, &mapID]() {
        mapfile->setFieldMatrix(mapID, map->getFieldMatrix());
    });

    imguiManager = std::make_unique<Manager>(appWindow->getWindow());
    if (!imguiManager->init()) return false;

    is_initialized = true;
    return true;
}

void App::run() {
    if (!is_initialized) return;

    while (!imguiManager->shouldClose()) {
        imguiManager->beginFrame();

        appWindow->renderFrame(map_initialized);

        imguiManager->endFrame();
    }
}

void App::shutdown() {
    if (is_initialized) {
        map.reset();
        mapfile.reset();
        imguiManager.reset();
        appWindow.reset();
        is_initialized = false;
    }
}
