#ifndef WINDOW_H
#define WINDOW_H

#include "Panel.h"
#include "GameScreen.h"
#include "WelcomeScreen.h"
#include "DropTargetWindow.h"
#include "OpenGLScreenshotHandler.h"
#include "../components/Map.h"
#include <GLFW/glfw3.h>
#include <memory>

class Window {
public:
    Window(int width, int height);
    ~Window();

    int width, height, vehicleCount;

    bool init();
    void renderFrame(bool mapInitialized);
    void shutdown();
    GLFWwindow* getWindow() const;

    Panel* getPanel() const;
    WelcomeScreen* getWelcomeScreen() const;
    DropTargetWindow* getDropTargetWindow() const;
    void setMap(Map* map);
    void setDropTargetWindow(std::unique_ptr<DropTargetWindow> newDrop);

    void renderWelcomeScreen();
    void renderMapAndPanel();
    void renderGameScreen();

    void setMapInitializationCallback(std::function<void(const std::string&)> callback);
    void setMapSaveCallback(std::function<void()> callback);

    void takeScreenshot(const std::string& filename);

    void setCounter(int value);
private:
    GLFWwindow* window;
    std::unique_ptr<Panel> panel;
    std::unique_ptr<GameScreen> gameScreen;
    std::unique_ptr<WelcomeScreen> welcomeScreen;
    std::unique_ptr<DropTargetWindow> dropTargetWindow;
    Map* map;

    std::unique_ptr<ScreenshotHandler> screenshotHandler;

    std::function<void(const std::string&)> mapInitializationCallback;
    std::function<void()> mapSaveCallback;
};

#endif // WINDOW_H
