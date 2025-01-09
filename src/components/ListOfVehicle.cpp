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


size_t ListOfVehicle::size() const {
    return vehicles.size();
}

void ListOfVehicle::printAllVehicles() const {
    for (const auto& vehicle : vehicles) {
        std::cout << vehicle->getX() << ", " << vehicle->getY() << std::endl; // Ensure this matches expected output.
    }
}

const std::vector<std::shared_ptr<Vehicle>>& ListOfVehicle::get() const {
    return vehicles;
}
void ListOfVehicle::setGrid(FieldMatrix newGrid) {
    grid = newGrid;
}
