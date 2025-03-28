#include "Fields.h"

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    context->DrawTexture(min, max, this->textureID, this->rotation);

    if (hasVehicle) {
        Texture::ID vehicleTextureID = idVehicle;
        context->DrawTexture(min, max, vehicleTextureID, 0);
    }
}
bool Field::isOccupied() const {
    return hasVehicle;
}

void Field::setVehicle(bool occupied, std::shared_ptr<Vehicle> vehicle) {
  hasVehicle = occupied;
    
  if (dynamic_cast<Car*>(vehicle.get())) {
    idVehicle = Texture::ID::Car;
  } else if (dynamic_cast<Bike*>(vehicle.get())) {
    idVehicle = Texture::ID::Bike;
  } else if (dynamic_cast<Motorcycle*>(vehicle.get())) {
    idVehicle = Texture::ID::Motorcycle;
  }
}

std::shared_ptr<Vehicle> Field::getVehicle() {
  return vehicle;
}

Texture::ID Field::getID() {
    return textureID;
}   

bool Field::isRoad() const {
    return textureID == Texture::ID::Road || textureID == Texture::ID::Intersection || textureID == Texture::ID::Crossroad || textureID == Texture::ID::Curve;
}
        
void Vehicle::setPosition(const Point& pos) { position = pos; }
void Vehicle::setID(Texture::ID id) { textureID = id; }
Texture::ID Vehicle::getID() const { return textureID; }

Point Vehicle::getPosition() const { return position; }
int Vehicle::getX()  { return x; }
int Vehicle::getY()  { return y; }
void Vehicle::moveUp() { x--; }
void Vehicle::moveDown() { x++; }
void Vehicle::moveLeft() { y--; }
void Vehicle::moveRight() { y++; }
