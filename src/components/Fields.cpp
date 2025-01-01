#include "Fields.h"

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    context->DrawTexture(min, max, this->textureID, this->rotation);

    if (hasVehicle) {
        Texture::ID vehicleTextureID = idVehicle;
        context->DrawTexture(min, max, vehicleTextureID, this->rotation);
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
        
void Vehicle::setPosition(const Point& pos) { position = pos; }
void Vehicle::setID(Texture::ID id) { textureID = id; }
Texture::ID Vehicle::getID() const { return textureID; }

Point Vehicle::getPosition() const { return position; }
int Vehicle::getX() const { return x; }
int Vehicle::getY() const { return y; }
void Vehicle::moveUp() { x--; }
void Vehicle::moveDown() { x++; }
void Vehicle::moveLeft() { y--; }
void Vehicle::moveRight() { y++; }
