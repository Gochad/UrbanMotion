#pragma once
#include "Strategy.h"

#include <memory>

class Controller {
public:
    Controller(std::unique_ptr<Strategy> strategy);
    std::vector<std::pair<int, int>> calculatePath(std::shared_ptr<Vehicle> v, Map* map, int endX, int endY);

    template <typename Strategy, typename... Args>
    void setStrategy(Args&&... args);

private:
    std::unique_ptr<Strategy> strategy;
};

template <typename Strategy, typename... Args>
void Controller::setStrategy(Args&&... args) {
    static_assert(std::is_base_of_v<Strategy, Strategy>, "Strategy must derive from movement Strategy");
    strategy = std::make_unique<Strategy>(std::forward<Args>(args)...);
}
