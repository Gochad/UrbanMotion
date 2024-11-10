#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height);
    ~Window();

    bool init();
    void renderFrame();
    void shutdown();
    GLFWwindow* getWindow() const;

private:
    int width, height;
    GLFWwindow* window;
};

#endif // WINDOW_H
