#include "Window.h"
#include <imgui_impl_opengl3.h>
#include <iostream>

Window::Window(int width, int height) : width(width), height(height), window(nullptr) {}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

bool Window::init() {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "Urban Motion", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    return true;
}

void Window::shutdown() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
    }
}

void Window::renderFrame() {
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

GLFWwindow* Window::getWindow() const {
    return window;
}
