#include "OpenGLScreenshotHandler.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

OpenGLScreenshotHandler::OpenGLScreenshotHandler(int width, int height)
    : width(width), height(height), screenshotCounter(0) {}

void OpenGLScreenshotHandler::takeScreenshot() {
    static_assert(sizeof(unsigned char) == 1, "Expected 1-byte pixel storage");

    std::vector<unsigned char> pixels(width * height * 3);

    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    flipImageY(pixels, width, height);

    std::string filename = generateFilename();
    stbi_write_png(filename.c_str(), width, height, 3, pixels.data(), width * 3);
    std::cout << "Screenshot saved to " << filename << std::endl;
}

std::string OpenGLScreenshotHandler::generateFilename() const {
    std::ostringstream filenameStream;

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    filenameStream << "screenshot_";
    filenameStream << std::put_time(&tm, "%Y%m%d_%H%M%S");
    filenameStream << "_";
    filenameStream << screenshotCounter++;
    filenameStream << ".png";

    return filenameStream.str();
}

template <typename T>
void OpenGLScreenshotHandler::flipImageY(std::vector<T>& pixels, int width, int height) {
    static_assert(std::is_arithmetic<T>::value, "Pixel data must be arithmetic type");

    int rowSize = width * 3;
    for (int y = 0; y < height / 2; ++y) {
        for (int x = 0; x < rowSize; ++x) {
            std::swap(pixels[y * rowSize + x], pixels[(height - y - 1) * rowSize + x]);
        }
    }
}
