#include "ListOfVehicle.h"

void ListOfVehicle::addVehicle(const VehicleInMap& vehicle) {
    auto it = std::find_if(vehicles.begin(), vehicles.end(),
                           [&vehicle](const std::shared_ptr<VehicleInMap>& v) {
                               return v->getX() == vehicle.getX() && v->getY() == vehicle.getY();
                           });
    
    if (it == vehicles.end()) {
        vehicles.push_back(std::make_shared<VehicleInMap>(vehicle.getId(), vehicle.getX(), vehicle.getY()));
    } 
}
//}
void ListOfVehicle::removeVehicle(int x, int y) {
    auto it = std::remove_if(vehicles.begin(), vehicles.end(),
                             [x, y](const std::shared_ptr<VehicleInMap>& v) {
                                 return v->getX() == x && v->getY() == y;
                             });
    vehicles.erase(it, vehicles.end());
}
size_t ListOfVehicle::size() const {
    return vehicles.size();
}


