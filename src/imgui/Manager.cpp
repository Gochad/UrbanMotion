#include <GLFW/glfw3.h>                 // GLFW header
#include "stb_image.h"                  // stb_image for image loading
#include <iostream>

#include "Manager.h"                    // Manager class header
#include <imgui.h>                      // ImGui core
#include <backends/imgui_impl_glfw.h>   // ImGui GLFW backend
#include <backends/imgui_impl_opengl3.h>// ImGui OpenGL backend
#include <OpenGL/glext.h>

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

GLuint LoadTexture(const char* filename) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    GLuint textureID;

    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        stbi_image_free(data);
        return 0;
    }

    return textureID;
}

void ShowTextureWindow() {
    GLuint grassTexture = LoadTexture("../textures/grass.png");
    GLuint roadTexture = LoadTexture("../textures/road.png");
    GLuint buildingTexture = LoadTexture("../textures/building.png");
    
    ImGui::Begin("Tile Textures");

    ImGui::Image((void*)(intptr_t)grassTexture, ImVec2(64, 64));

    ImGui::Image((void*)(intptr_t)roadTexture, ImVec2(64, 64));

    ImGui::Image((void*)(intptr_t)buildingTexture, ImVec2(64, 64));

    ImGui::End();
}

void Manager::endFrame() {
    ShowTextureWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Manager::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
