#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include <functional>
#include "../texture/Manager.h"
#include "../components/Map.h" 
#include "../components/ListOfVehicle.h" 
#include "../components/Fields.h"
#include "../movement/Controller.h"

using FieldMatrix = std::vector<std::vector<std::shared_ptr<Field>>>;

class GameScreen {
public:
    GameScreen(int width, int height, int yOffset, Map* map);
    void draw(std::function<void()>, Map* map);
    int getSelectedTexture() const;
    void setGrid(FieldMatrix fieldMatrix);
    void setTextureRange(int range);
    void setListOfVehicle(ListOfVehicle listOfVehicle);
    void setPositionWithoutVehicle(Texture::ID id, int x, int y, Map* map);
    void setPositionWithVehicle(Texture::ID id, int selectedX, int selectedY, Map* map, std::shared_ptr<Vehicle> vehicle);
    ListOfVehicle getListOfVehicle();
    Map* map;
    std::unique_ptr<Strategy> movementController;
    bool checkingRoad(std::shared_ptr<Field> field);

private:
    int width;
    int height;
    int yOffset;
    ListOfVehicle listOfVehicle;
    int textureRange;
    int selectedTextureIndex;
    FieldMatrix grid;
};
