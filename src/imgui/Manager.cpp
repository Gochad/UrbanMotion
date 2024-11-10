#include "Manager.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

Manager::Manager(GLFWwindow* window) : window(window) {}

Manager::~Manager() {
    shutdown();
}

bool Manager::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) return false;
    if (!ImGui_ImplOpenGL3_Init("#version 150")) return false;
    ImGui::StyleColorsDark();
    return true;
}

bool Manager::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Manager::beginFrame() {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Manager::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Manager::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
