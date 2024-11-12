#ifndef WINDOW_H
#define WINDOW_H
#include "Panel.h"

#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height);
    ~Window();

    int width, height;

    bool init();
    void renderFrame();
    void shutdown();
    GLFWwindow* getWindow() const;
private:
    GLFWwindow* window;
};

#endif // WINDOW_H
