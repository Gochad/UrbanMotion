#include "GameScreen.h"
#include <iostream>
#include <map>
#include "imgui.h"
#include "../components/Map.h"
#include "../components/ListOfVehicle.h"
#include "../components/Fields.h"

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
        Texture::ID id = vehicle->getID();
        ImGui::Text("Vehicle ID: %d", id);
        ImGui::Text("Position: (%d, %d)", vehicle->getX(), vehicle->getY());

        if (vehicle->getX() > 0 && ImGui::Button("Up")) {
            setPositionWithoutVehicle(id, vehicle->getX(), vehicle->getY(), map);
            vehicle->moveUp();
            setPositionWithVehicle(id, vehicle->getX(), vehicle->getY(), map);
        }
        ImGui::SameLine();

        if (vehicle->getX() < map->grid.size()-1 && ImGui::Button("Down")) {
            setPositionWithoutVehicle(id, vehicle->getX(), vehicle->getY(), map);
            vehicle->moveDown();
            setPositionWithVehicle(id, vehicle->getX(), vehicle->getY(), map);
        }
        ImGui::SameLine();

        if (vehicle->getY() > 0 && ImGui::Button("Left")) {
            setPositionWithoutVehicle(id, vehicle->getX(), vehicle->getY(), map);
            vehicle->moveLeft();
            setPositionWithVehicle(id, vehicle->getX(), vehicle->getY(), map);
        }
        ImGui::SameLine();

        if (vehicle->getY() < map->grid.size()-1 && ImGui::Button("Right")) {
            setPositionWithoutVehicle(id, vehicle->getX(), vehicle->getY(), map);
            vehicle->moveRight();
            setPositionWithVehicle(id, vehicle->getX(), vehicle->getY(), map);
        }

        ImGui::Separator();
    }

    ImGui::End();
}
void GameScreen::setPositionWithoutVehicle(Texture::ID id, int selectedX, int selectedY, Map* map) {
    std::unique_ptr<Vehicle> vehicle;
    if (id == Texture::ID::Car) {
        vehicle = std::make_unique<Car>(selectedY, selectedX, 0);
        map->grid[selectedX][selectedY]->setVehicle(false, std::move(vehicle));
    } else if (id == Texture::ID::Bike) {
        vehicle = std::make_unique<Bike>(selectedY, selectedX, 0);
        map->grid[selectedX][selectedY]->setVehicle(false, std::move(vehicle));
    } else if (id == Texture::ID::Motorcycle) {
        vehicle = std::make_unique<Motorcycle>(selectedY, selectedX, 0);
        map->grid[selectedX][selectedY]->setVehicle(false, std::move(vehicle));
    }
}

void GameScreen::setPositionWithVehicle(Texture::ID id, int selectedX, int selectedY, Map* map) {
    std::unique_ptr<Vehicle> vehicle;
    if (id == Texture::ID::Car) {
        vehicle = std::make_unique<Car>(selectedY, selectedX, 0);
        map->grid[selectedX][selectedY]->setVehicle(true, std::move(vehicle));
    } else if (id == Texture::ID::Bike) {
        vehicle = std::make_unique<Bike>(selectedY, selectedX, 0);
        map->grid[selectedX][selectedY]->setVehicle(true, std::move(vehicle));
    } else if (id == Texture::ID::Motorcycle) {
        vehicle = std::make_unique<Motorcycle>(selectedY, selectedX, 0);
        map->grid[selectedX][selectedY]->setVehicle(true, std::move(vehicle));
    }
}
