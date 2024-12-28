#include "VehicleInMap.h"

VehicleInMap::VehicleInMap(Texture::ID id, int x, int y)
    : id(id), x(x), y(y) {}

Texture::ID VehicleInMap::getId() const {
    return id;
}

int VehicleInMap::getX() const {
    return x;
}

int VehicleInMap::getY() const {
    return y;
}
bool VehicleInMap::operator==(const VehicleInMap& other) const {
    return this->id == other.id && this->x == other.x && this->y == other.y;
}
