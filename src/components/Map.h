#pragma once
#include <vector>
#include <memory>
#include "Fields.h"
#include "../imgui/Draw.h"
#include "../texture/Manager.h"
#include "../filestorage/MapFile.h"
#include "../interfaces/IMap.h"
#include "ListOfVehicle.h"

using FieldMatrix = std::vector<std::vector<std::shared_ptr<Field>>>;

class Map : public IMap {
public:
    virtual ~Map() = default;

    Map(int width, int height, int squareSize, FieldMatrix matrix);
    Map(int width, int height, int square_size);
    void draw(IDraw* context);
    void edit(IDraw* context, Point mousePosition);
    void setGrid(FieldMatrix newGrid);
    int showChangeTilePanel(IDraw* context, int selectedX, int selectedY, Field* field, Texture::ID id) override;
    int getSquareSize() override;
    ListOfVehicle listOfVehicle;
    FieldMatrix getGrid();
    FieldMatrix grid;
    bool checkingRoad(std::shared_ptr<Field> field);
    FieldMatrix getFieldMatrix();

private:
    int width;
    int height;
    int square_size;
    int selectedX = -1;
    int selectedY = -1;
    bool isEditing = false;
};
