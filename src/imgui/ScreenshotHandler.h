#pragma once
#include <string>
#include <memory>

class ScreenshotHandler {
public:
    virtual ~ScreenshotHandler() = default;

    virtual void takeScreenshot() = 0;

    template <typename T, typename... Args>
    static std::unique_ptr<ScreenshotHandler> create(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};