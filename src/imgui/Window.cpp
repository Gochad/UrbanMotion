#include "Window.h"
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <imgui_impl_glfw.h>
#include "GameScreen.h"

namespace {
    inline constexpr int kHeightOffset = 100;
    inline constexpr const char* kWindowTitle = "Urban Motion";
}

Window::Window(int width, int height)
    : width(width), height(height), window(nullptr) {}

Window::~Window() {
    shutdown();
}

bool Window::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    height += kHeightOffset;

    window = glfwCreateWindow(width, height, kWindowTitle, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    panel = std::make_unique<Panel>(width, 200, height - 200);
    welcomeScreen = std::make_unique<WelcomeScreen>(std::vector<std::string>{"1", "2", "3"});
    dropTargetWindow = nullptr;
    gameScreen = std::make_unique<GameScreen>(width, 200, height - 200, map);
    screenshotHandler = ScreenshotHandler::create<OpenGLScreenshotHandler>(width, height);

    return true;
}

void Window::setMapInitializationCallback(std::function<void(const std::string&)> callback) {
    mapInitializationCallback = callback;
}

void Window::setMapSaveCallback(std::function<void()> callback) {
   mapSaveCallback = callback;
}

void Window::renderWelcomeScreen() {
    if (welcomeScreen) {
        welcomeScreen->render(width, height, [this](const std::string& map_id) {
            mapInitializationCallback(map_id);
            
            this->setDropTargetWindow(
               std::make_unique<DropTargetWindow>(map));
        });
    }
}

void Window::setMap(Map* newMap) {
    map = newMap;
}

void Window::renderMapAndPanel() {
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    Draw imgui_context(draw_list);
    if (map) {
        map->draw(&imgui_context);
    }

    if (dropTargetWindow) {
        dropTargetWindow->render(&imgui_context,vehicleCount );
    }

    if (panel) {
        panel->draw([this]() { 
            mapSaveCallback();
        }, [this]() { 
            screenshotHandler->takeScreenshot();
        }, map);
    }
}

void Window::renderGameScreen() {
    std::cout<<"Game started"<<std::endl;
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    Draw imgui_context(draw_list);
    if (map) {
        map->draw(&imgui_context);
    }

    gameScreen->setListOfVehicle(map->listOfVehicle);
    gameScreen->setGrid(map->getFieldMatrix());
    gameScreen->draw([]() { std::cout << "Game started" << std::endl; }, map);
    map->draw(&imgui_context);
}
void Window::renderFrame(bool mapInitialized) {
    if (!mapInitialized) {
        renderWelcomeScreen();
    } else if (!(panel->isFinalMapSaved())) {
        renderMapAndPanel();
    } else {
        renderGameScreen();
    }
    glfwSwapBuffers(window);
}


void Window::shutdown() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
    }

    panel.reset();
    welcomeScreen.reset();
    dropTargetWindow.reset();
}

GLFWwindow* Window::getWindow() const {
    return window;
}

Panel* Window::getPanel() const {
    return panel.get();
}

WelcomeScreen* Window::getWelcomeScreen() const {
    return welcomeScreen.get();
}

DropTargetWindow* Window::getDropTargetWindow() const {
    return dropTargetWindow.get();
}

void Window::setDropTargetWindow(std::unique_ptr<DropTargetWindow> newDrop) {
    dropTargetWindow = std::move(newDrop);
}
void Window::setCounter(int value) {
    vehicleCount = value;
}
