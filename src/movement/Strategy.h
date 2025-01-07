#pragma once
#include "../components/Map.h"
#include <type_traits>
#include <queue>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual std::vector<std::pair<int, int>> calculatePath(std::shared_ptr<Vehicle> v, Map* map, int endX, int endY) const = 0;
};

class BFSStrategy : public Strategy {
public:
    std::vector<std::pair<int, int>> calculatePath(std::shared_ptr<Vehicle> v, Map* map, int endX, int endY) const override;
};

class SequentialStrategy : public Strategy {
public:
    std::vector<std::pair<int, int>> calculatePath(std::shared_ptr<Vehicle> v, Map* map, int endX, int endY) const override;
};

template <typename T>
void reversePoints(std::vector<T>& points) {
    static_assert(std::is_arithmetic_v<T>, "points must be arithmetic type");
    std::reverse(points.begin(), points.end());
}
