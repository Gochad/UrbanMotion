#pragma once
#include "../IApp.h"
#include "../Map.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class App : public IApp {
public:
    App(int grid_size, int square_size);
    ~App() override;

    bool init() override;
    void run() override;
    void shutdown() override;

private:
    GLFWwindow* window;
    int grid_size;
    int window_size;
    Map map;
    bool is_initialized;
};
