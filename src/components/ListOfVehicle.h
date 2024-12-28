#ifndef LIST_OF_VEHICLE_H // Start of the include guard
#define LIST_OF_VEHICLE_H

#include <vector>
#include <memory>
#include "Fields.h"

using FieldMatrix = std::vector<std::vector<std::shared_ptr<Field>>>;

class ListOfVehicle {
public:
    void addVehicle(std::shared_ptr<Vehicle> vehicle); // Ensure this matches the implementation
    void removeVehicle(int x, int y);
    void printAllVehicles() const;
    size_t size() const;
    const std::vector<std::shared_ptr<Vehicle>>& get() const;
    void setGrid(FieldMatrix newGrid);
    FieldMatrix grid;

private:
    std::vector<std::shared_ptr<Vehicle>> vehicles; // Keep vehicles as shared pointers
};

#endif // End of the include guard
