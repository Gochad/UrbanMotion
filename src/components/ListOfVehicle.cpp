#include "ListOfVehicle.h"
#include "Fields.h"

void ListOfVehicle::addVehicle(std::shared_ptr<Vehicle> vehicle) {
    for (const auto& v : vehicles) {
        if (v->getX() == vehicle->getX() && v->getY() == vehicle->getY()) {
            std::cerr << "Error: A vehicle with the same coordinates already exists at (" 
                      << vehicle->getX() << ", " << vehicle->getY() << ")" << std::endl;
            return;
        }
    }
    vehicles.push_back(vehicle);
}

void ListOfVehicle::removeVehicle(int x, int y) {
    auto it = std::remove_if(vehicles.begin(), vehicles.end(),
                             [x, y](const std::shared_ptr<Vehicle>& v) {
                                 return v->getX() == x && v->getY() == y;
                             });
    vehicles.erase(it, vehicles.end());
}

size_t ListOfVehicle::size() const {
    return vehicles.size();
}

void ListOfVehicle::printAllVehicles() const {
    for (const auto& vehicle : vehicles) {
        std::cout << "Vehicle at (" << vehicle->getX() << ", " << vehicle->getY() << ")" << std::endl;
    }
}

const std::vector<std::shared_ptr<Vehicle>>& ListOfVehicle::get() const {
    return vehicles;
}
void ListOfVehicle::setGrid(FieldMatrix newGrid) {
    grid = newGrid;
}
