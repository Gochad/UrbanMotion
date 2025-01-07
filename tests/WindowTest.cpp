#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/imgui/Window.h"
#include "../src/components/Map.h"
#include "../src/imgui/Panel.h"
#include "../src/imgui/WelcomeScreen.h"
#include "../src/imgui/DropTargetWindow.h"
#include "../src/imgui/GameScreen.h"
#include "../src/imgui/OpenGLScreenshotHandler.h"
#include <GLFW/glfw3.h>

class WindowTest : public ::testing::Test {
protected:
    void SetUp() override {
        window = std::make_unique<Window>(800, 600);
    }

    void TearDown() override {
        window->shutdown();
    }

    std::unique_ptr<Window> window;
};

TEST_F(WindowTest, Initialization) {
    EXPECT_TRUE(window->init());
    EXPECT_NE(window->getWindow(), nullptr);
}

TEST_F(WindowTest, SetMapInitializationCallback) {
    bool callbackCalled = false;
    window->setMapInitializationCallback([&callbackCalled](const std::string& map_id) {
        callbackCalled = true;
    });

    window->renderWelcomeScreen();
    EXPECT_TRUE(callbackCalled);
}

TEST_F(WindowTest, SetMapSaveCallback) {
    bool callbackCalled = false;
    window->setMapSaveCallback([&callbackCalled]() {
        callbackCalled = true;
    });

    window->renderMapAndPanel();
    EXPECT_TRUE(callbackCalled);
}

TEST_F(WindowTest, RenderFrame) {
    window->init();
    window->renderFrame(false); // Render welcome screen
    window->renderFrame(true);  // Render map and panel or game screen
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}