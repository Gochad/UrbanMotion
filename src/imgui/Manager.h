#ifndef MANAGER_H
#define MANAGER_H

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "../texture/Manager.h"

class Manager {
public:
    Manager(GLFWwindow* window);
    ~Manager();

    bool init();
    bool shouldClose() const;
    void beginFrame();
    void endFrame();
    void shutdown();
    void renderMapSelectionPanel(
        const std::vector<std::string>& available_maps,
        std::function<void(const std::string&)> onMapSelected);

    void renderMap(
        std::function<void()> drawCallback, 
        std::function<void()> saveCallback);

private:
    GLFWwindow* window;
    Texture::Manager textureManager;
};

#endif // MANAGER_H
