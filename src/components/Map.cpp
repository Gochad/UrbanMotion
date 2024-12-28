#include "Map.h"
#include "Fields.h" 
#include <memory> 

Map::Map(int w, int h, int square_size, FieldMatrix matrix) 
    : width(w), height(h), square_size(square_size), grid(matrix) {}

Map::Map(int width, int height, int square_size)
    : width(width), height(height), square_size(square_size) {
    grid.resize(height);
    for (int y = 0; y < height; ++y) {
        grid[y].resize(width);
        for (int x = 0; x < width; ++x) {
            grid[y][x] = std::make_shared<Field>();
        }
    }

    std::cout << "Map initialized with dimensions: " << width << "x" << height << std::endl;
}

void Map::draw(IDraw* context) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point min(x * square_size, y * square_size);
            Point max((x + 1) * square_size, (y + 1) * square_size);
            if(grid[x][y]->textureID == Texture::ID::Car || grid[x][y]->textureID == Texture::ID::Bike || grid[x][y]->textureID == Texture::ID::Motorcycle) {
                VehicleInMap vehicle(grid[y][x]->textureID, x, y);
                listOfVehicle.addVehicle(vehicle);
            }
            grid[y][x]->draw(context, min, max);
        }
    }
}

int Map::showChangeTilePanel(IDraw* context, int selectedX, int selectedY, Field* field, Texture::ID id) {
    Point min(selectedX * square_size, selectedY * square_size);
    Point max((selectedX + 1) * square_size, (selectedY + 1) * square_size);
    std::cout<<"OJ OJ"<<std::endl;
    if (grid[selectedY][selectedX]->textureID == Texture::ID::Car || grid[selectedY][selectedX]->textureID == Texture::ID::Bike || grid[selectedY][selectedX]->textureID == Texture::ID::Motorcycle) {
        listOfVehicle.removeVehicle(selectedY, selectedX);
//     TODO: DOKONYCZ   grid[selectedY][selectedX]->setOccupied(false); // Clear the occupancy
    }
    if ((id == Texture::ID::Car || id == Texture::ID::Bike || id == Texture::ID::Motorcycle) && listOfVehicle.size() >= 3) {
        std::cout << "You can't add more than 3 vehicles" << std::endl;
        return -1;
    } else if ((id == Texture::ID::Car || id == Texture::ID::Bike || id == Texture::ID::Motorcycle) && listOfVehicle.size() < 3) {
        std::shared_ptr<Vehicle> vehicle;
        if (id == Texture::ID::Car) {
            Car car = Car(0);
            grid[selectedY][selectedX]->setCar(true, car);
        } else if (id == Texture::ID::Bike) {
            vehicle = std::make_shared<Bike>(0);
                        Bike car = Bike(0);
                        grid[selectedY][selectedX]->setBike(true, car);
        } else if (id == Texture::ID::Motorcycle) {
                        Motorcycle car = Motorcycle(0);
                        grid[selectedY][selectedX]->setMotorcycle(true, car);
        }
//        vehicle->setPosition(Point(selectedX, selectedY));
//       
//        vehicle->setID(id);
//        std::cout << "Vehicle added with texture ID: " << vehicle->textureID << std::endl;
//        Vehicle v =    VehicleInMap(id, selectedY, selectedX);
//        listOfVehicle.addVehicle(v); // Assuming you still want to add to listOfVehicle
//        grid[selectedY][selectedX]->setOccupied(true, v); // Pass the pointer
    }else{
        grid[selectedY][selectedX]->textureID = id;
    }
    
    std::cout << "Texture ID: " << grid[selectedY][selectedX]->textureID << std::endl;
    grid[selectedY][selectedX]->draw(context, min, max);
    return 1;
}
int Map::getSquareSize() {
    return square_size;
}
FieldMatrix Map::getFieldMatrix() {
    return grid;
}
