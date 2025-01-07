#include "GameScreen.h"
#include <iostream>
#include <map>
#include "imgui.h"
#include "../components/Map.h"
#include "../components/ListOfVehicle.h"
#include "../components/Fields.h"

GameScreen::GameScreen(int width, int height, int yOffset, Map* map)
    : width(width), height(height), yOffset(yOffset), selectedTextureIndex(0), map(map), 
    movementController(nullptr) {
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
void GameScreen::setGrid(FieldMatrix fieldMatrix){
    this->grid = fieldMatrix;
}
void GameScreen::draw(std::function<void()> onSaveClick, Map* map) {
    ImGui::SetNextWindowPos(ImVec2(0, yOffset));
    ImGui::SetNextWindowSize(ImVec2(width, height));
    ImGui::Begin("Game Screen");

    if (ImGui::RadioButton("Sequential", currentStrategy == "Sequential")) {
        currentStrategy = "Sequential";
        movementController = std::make_unique<SequentialStrategy>();
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("BFS", currentStrategy == "BFS")) {
        currentStrategy = "BFS";
        movementController = std::make_unique<BFSStrategy>();
    }

    ImGui::Separator();

    for (const auto& vehicle : listOfVehicle.get()) {
        Texture::ID id = vehicle->getID();
        ImGui::Text("Vehicle ID: %d", id);
        ImGui::Text("Position: (%d, %d)", vehicle->getX(), vehicle->getY());

        if (checkingRoad(map->grid[vehicle->getX()-1][vehicle->getY()]) && vehicle->getX() > 0 && ImGui::Button("Up")) {
            setPositionWithoutVehicle(id, vehicle->getX(), vehicle->getY(), map);
            vehicle->moveUp();
            setPositionWithVehicle(id, vehicle->getX(), vehicle->getY(), map);
        }
        ImGui::SameLine();

        if (checkingRoad(map->grid[vehicle->getX()+1][vehicle->getY()]) && vehicle->getX() < map->grid.size()-1 && ImGui::Button("Down")) {
            setPositionWithoutVehicle(id, vehicle->getX(), vehicle->getY(), map);
            vehicle->moveDown();
            setPositionWithVehicle(id, vehicle->getX(), vehicle->getY(), map);
        }
        ImGui::SameLine();

        if (checkingRoad(map->grid[vehicle->getX()][vehicle->getY()-1]) && vehicle->getY() > 0 && ImGui::Button("Left")) {
            setPositionWithoutVehicle(id, vehicle->getX(), vehicle->getY(), map);
            vehicle->moveLeft();
            setPositionWithVehicle(id, vehicle->getX(), vehicle->getY(), map);
        }
        ImGui::SameLine();

        if (checkingRoad(map->grid[vehicle->getX()][vehicle->getY()+1]) && vehicle->getY() < map->grid.size()-1 && ImGui::Button("Right")) {
            setPositionWithoutVehicle(id, vehicle->getX(), vehicle->getY(), map);
            vehicle->moveRight();
            setPositionWithVehicle(id, vehicle->getX(), vehicle->getY(), map);
        }
        ImGui::SameLine();

        if (ImGui::Button("Move to End")) {
            vehiclePaths[vehicle] = movementController->calculatePath(vehicle, map, 9, 9);
            vehicleStepIndices[vehicle] = 0;
        }

        ImGui::Separator();
    }

    for (auto& [vehicle, path] : vehiclePaths) {
        if (!path.empty() && vehicleStepIndices[vehicle] < path.size() - 1) {
            auto [prevX, prevY] = path[vehicleStepIndices[vehicle]];
            map->grid[prevX][prevY]->setVehicle(false, nullptr);

            ++vehicleStepIndices[vehicle];
            auto [x, y] = path[vehicleStepIndices[vehicle]];
            map->grid[x][y]->setVehicle(true, vehicle);
            vehicle->setPosition({x, y});

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
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
bool GameScreen::checkingRoad(std::shared_ptr<Field> field) {
    return field->getID() == Texture::ID::Road || field->getID() == Texture::ID::Crossroad || field->getID() == Texture::ID::Curve || field->getID() == Texture::ID::Intersection;
}
