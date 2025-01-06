#include "Controller.h"

Controller::Controller(std::unique_ptr<Strategy> strategy)
    : strategy(std::move(strategy)) {}

void Controller::moveVehicle(Texture::ID id, int startX, int startY, Map* map, int endX, int endY) {
    if (strategy) {
        strategy->move(id, startX, startY, map, endX, endY);
    }
}
