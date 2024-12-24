#ifndef LIST_OF_VEHICLE_H // Start of the include guard
#define LIST_OF_VEHICLE_H

#include <vector>
#include <memory>
#include "VehicleInMap.h" // Include the Vehicle header

class ListOfVehicle {
public:
    void addVehicle(const VehicleInMap& vehicle);
    void removeVehicle(int x, int y);
    void printAllVehicles() const;
    size_t size() const;
        std::vector<std::shared_ptr<VehicleInMap>> vehicles;

private:
};

#endif // End of the include guard
