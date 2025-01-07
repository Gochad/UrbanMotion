#include "Controller.h"

Controller::Controller(std::unique_ptr<Strategy> strategy)
    : strategy(std::move(strategy)) {}

std::vector<std::pair<int, int>> Controller::calculatePath(std::shared_ptr<Vehicle> v, Map* map, int endX, int endY) {
    if (strategy) {
        return strategy->calculatePath(v, map, endX, endY);
    }

    return {};
}
