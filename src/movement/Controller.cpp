#include "Controller.h"

Controller::Controller(std::unique_ptr<Strategy> strategy)
    : strategy(std::move(strategy)) {}

void Controller::moveVehicle(std::shared_ptr<Vehicle> vehicle, Map* map, int endX, int endY) {
    if (strategy) {
        strategy->calculatePath(vehicle, map, endX, endY);
    }
}
