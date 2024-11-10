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

void ShowTextureWindow(Texture::Manager& textureManager) {
    GLuint grassTexture = textureManager.loadTexture("../textures/grass.png");
    GLuint roadTexture = textureManager.loadTexture("../textures/road.png");
    GLuint buildingTexture = textureManager.loadTexture("../textures/building.png");
    
    ImGui::Begin("Tile Textures");

    ImGui::Image((void*)(intptr_t)grassTexture, ImVec2(64, 64));
    ImGui::Image((void*)(intptr_t)roadTexture, ImVec2(64, 64));
    ImGui::Image((void*)(intptr_t)buildingTexture, ImVec2(64, 64));

    ImGui::End();
}

void Manager::endFrame() {
    ShowTextureWindow(textureManager);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Manager::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
