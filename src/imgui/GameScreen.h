#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include <functional>
#include "../texture/Manager.h"
#include "../components/Map.h" 
#include "../components/ListOfVehicle.h" 

class GameScreen {
public:
    GameScreen(int width, int height, int yOffset, Map* map);
    void draw(std::function<void()>, Map* map);
    int getSelectedTexture() const;

    void setTextureRange(int range);
    void setListOfVehicle(ListOfVehicle listOfVehicle);
    ListOfVehicle getListOfVehicle();
    Map* map;

private:
    int width;
    int height;
    int yOffset;
    ListOfVehicle listOfVehicle;
    int textureRange;
    int selectedTextureIndex;
};
