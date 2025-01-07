#pragma once
#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <type_traits>
#include "ScreenshotHandler.h"

class OpenGLScreenshotHandler : public ScreenshotHandler {
public:
    OpenGLScreenshotHandler(int width, int height);

    void takeScreenshot() override;

private:
    std::string generateFilename() const;

    template <typename T>
    void flipImageY(std::vector<T>& pixels, int width, int height);

    int width;
    int height;
    mutable int screenshotCounter;
};