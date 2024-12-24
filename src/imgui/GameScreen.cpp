#include "GameScreen.h"
#include <iostream>
#include <map>
#include "imgui.h"
#include "../components/Map.h"

GameScreen::GameScreen(int width, int height, int yOffset)
    : width(width), height(height), yOffset(yOffset), selectedTextureIndex(0) {
    Texture::Manager* textureManager = new Texture::Manager;
    std::cout << "GameScreen constructor" << std::endl;
    std::map<Texture::ID, int> textureMap = textureManager->loadTextures();
    auto lastElement = *textureMap.rbegin();
    this->setTextureRange(static_cast<int>(lastElement.first));
}

void GameScreen::setTextureRange(int range) {
    this->textureRange = range;
}

int GameScreen::getSelectedTexture() const {
    return selectedTextureIndex;
}

void GameScreen::draw(std::function<void()> onSaveClick, Map* map) {
    ImGui::SetNextWindowPos(ImVec2(0, yOffset));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin("Game Screen");
    // TODO: MOVING CAR BABYYY
    ImGui::End();
}
