#include "App.h"
#include <iostream>

App::App(int grid_size, int square_size)
    : grid_size(grid_size), square_size(square_size),
      appWindow(nullptr), imguiManager(nullptr), map(nullptr),
      is_initialized(false), mapfile(nullptr) {}

App::~App() {
    shutdown();
}

bool App::init() {
    appWindow = new Window(grid_size * square_size, grid_size * square_size + 100);
    if (!appWindow->init()) return false;

    imguiManager = new Manager(appWindow->getWindow());
    if (!imguiManager->init()) return false;

    panel = new Panel(appWindow->width, 100, appWindow->height - 100);

    Texture::Manager* textureManager = new Texture::Manager;
    std::unordered_map<Texture::ID, int> textureMap = textureManager->loadTextures();
    std::vector<Texture::ID> textureIDs;
    for (const auto& pair : textureMap) {
        textureIDs.push_back(pair.first);
    }

    panel->setTextures(textureIDs);

    mapfile = new MapFile("1");

    map = new Map(grid_size, grid_size, square_size, mapfile, textureMap);

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

        panel->draw([this]() { mapfile->saveMap(); });

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("DropTargetWindow", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                                                   ImGuiWindowFlags_NoBringToFrontOnFocus |
                                                   ImGuiWindowFlags_NoBackground);

        ImGui::InvisibleButton("FullScreenDropTarget", ImGui::GetIO().DisplaySize);

        ImVec2 mapPos(0, 0);
        int square_size = 50;  

        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE_INDEX")) {
                int textureIndex = *(const int*)payload->Data;

                ImVec2 mousePos = ImGui::GetMousePos();

                int gridX = static_cast<int>((mousePos.x - mapPos.x) / square_size);
                int gridY = static_cast<int>((mousePos.y - mapPos.y) / square_size);

                map->showChangeTilePanel(&imgui_context, gridX, gridY, static_cast<Texture::ID>(textureIndex));
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::End();

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
