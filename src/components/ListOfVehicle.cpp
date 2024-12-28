#include "ListOfVehicle.h"
#include "Fields.h"

void ListOfVehicle::addVehicle(std::shared_ptr<Vehicle> vehicle) {
    // Ensure we are not adding a vehicle at the same position
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
                           [&vehicle](const std::shared_ptr<Vehicle>& v) {
                               return v->getX() == vehicle->getX() && v->getY() == vehicle->getY();
                           });
    
    if (it == vehicles.end()) {
        vehicles.push_back(vehicle); // Directly push the shared pointer
    } 
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
