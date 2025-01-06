#include "Window.h"
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <imgui_impl_glfw.h>
#include "GameScreen.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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
            takeScreenshot("screenshot.png");
        }, map);
    }
}

void Window::renderGameScreen() {
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    Draw imgui_context(draw_list);
    if (map) {
        map->draw(&imgui_context);
    }

    gameScreen->setListOfVehicle(map->listOfVehicle);

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

void Window::takeScreenshot(const std::string& filename) {
    int screenshotWidth = width;
    int screenshotHeight = height;
    std::vector<unsigned char> pixels(screenshotWidth * screenshotHeight * 3);

    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, screenshotWidth, screenshotHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // Odwrócenie obrazu w osi Y (OpenGL używa układu od dołu do góry)
    for (int y = 0; y < screenshotHeight / 2; ++y) {
        for (int x = 0; x < screenshotWidth * 3; ++x) {
            std::swap(pixels[y * screenshotWidth * 3 + x], pixels[(screenshotHeight - y - 1) * screenshotWidth * 3 + x]);
        }
    }

    // Zapis do PNG
    stbi_write_png(filename.c_str(), screenshotWidth, screenshotHeight, 3, pixels.data(), screenshotWidth * 3);
    std::cout << "Screenshot saved to " << filename << std::endl;
}