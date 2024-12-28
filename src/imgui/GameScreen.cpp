#include "GameScreen.h"
#include <iostream>
#include <map>
#include "imgui.h"
#include "../components/Map.h"
#include "../components/ListOfVehicle.h"

GameScreen::GameScreen(int width, int height, int yOffset, Map* map)
    : width(width), height(height), yOffset(yOffset), selectedTextureIndex(0), map(map) {
    Texture::Manager* textureManager = new Texture::Manager;
    std::map<Texture::ID, int> textureMap = textureManager->loadTextures();
    auto lastElement = *textureMap.rbegin();
    this->setTextureRange(static_cast<int>(lastElement.first));
}

void GameScreen::setTextureRange(int range) {
    this->textureRange = range;
}

void GameScreen::setListOfVehicle(ListOfVehicle listOfVehicle) {
    this->listOfVehicle = listOfVehicle;
}

int GameScreen::getSelectedTexture() const {
    return selectedTextureIndex;
}
ListOfVehicle GameScreen::getListOfVehicle(){
    return listOfVehicle;
}
void GameScreen::draw(std::function<void()> onSaveClick, Map* map) {
    ImGui::SetNextWindowPos(ImVec2(0, yOffset));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin("Game Screen");
    
    for (const auto& vehicle : listOfVehicle.get()) {
    std::cout<<"position id: "<<vehicle->getX()<<std::endl;
        ImGui::Text("Vehicle ID: %d", vehicle->getID());
        ImGui::Text("Position: (%d, %d)", vehicle->getX(), vehicle->getY());

        if (vehicle->getX() > 0 && ImGui::Button("Up")) {
            map->grid[vehicle->getX()][vehicle->getY()]->setCar(false, *std::dynamic_pointer_cast<Car>(vehicle));
            vehicle->moveUp();
            map->grid[vehicle->getX()][vehicle->getY()]->setCar(true, *std::dynamic_pointer_cast<Car>(vehicle)); // Update grid after moving
        }
        ImGui::SameLine();

        if (ImGui::Button("Down")) {
            map->grid[vehicle->getX()][vehicle->getY()]->setCar(false, *std::dynamic_pointer_cast<Car>(vehicle));
            vehicle->moveDown();
            map->grid[vehicle->getX()][vehicle->getY()]->setCar(true, *std::dynamic_pointer_cast<Car>(vehicle)); // Update grid after moving
        }
        ImGui::SameLine();

        if (vehicle->getY() > 0 && ImGui::Button("Left")) {
        std::cout<<"Left button clicked"<<std::endl;
            map->grid[vehicle->getX()][vehicle->getY()]->setCar(false, *std::dynamic_pointer_cast<Car>(vehicle));
            vehicle->moveLeft();
            map->grid[vehicle->getX()][vehicle->getY()]->setCar(true, *std::dynamic_pointer_cast<Car>(vehicle)); // Update grid after moving
        }
        ImGui::SameLine();

        if (ImGui::Button("Right")) {
            map->grid[vehicle->getX()][vehicle->getY()]->setCar(false, *std::dynamic_pointer_cast<Car>(vehicle));
            vehicle->moveRight(); // Move the vehicle first
            map->grid[vehicle->getX()][vehicle->getY()]->setCar(true, *std::dynamic_pointer_cast<Car>(vehicle)); // Update grid after moving
        }

        ImGui::Separator();
    }
    
    ImGui::End();
}

