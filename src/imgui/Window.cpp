#include "Window.h"
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <imgui_impl_glfw.h>
#include "GameScreen.h"

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
    height += 100;

    window = glfwCreateWindow(width, height, "Urban Motion", NULL, NULL);
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
    gameScreen = std::make_unique<GameScreen>(width, 200, height - 200);
    return true;
}

void Window::setMapInitializationCallback(std::function<void(const std::string&)> callback) {
    mapInitializationCallback = callback;
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
        panel->draw([]() { std::cout << "Save map" << std::endl; }, map);
    }
}

void Window::renderGameScreen() {
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    Draw imgui_context(draw_list);
    if (map) {
        map->draw(&imgui_context);
    }

    if (gameScreen) {
        gameScreen->draw([]() { std::cout << "Game started" << std::endl; }, map);
    }
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
