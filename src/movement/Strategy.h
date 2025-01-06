#pragma once
#include "../components/Map.h"
#include <type_traits>
#include <queue>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void move(Texture::ID id, int startX, int startY, Map* map, int endX, int endY) const = 0;
};

class BFSStrategy : public Strategy {
public:
    void move(Texture::ID id, int startX, int startY, Map* map, int endX, int endY) const override;
};

class SequentialStrategy : public Strategy {
public:
    void move(Texture::ID id, int startX, int startY, Map* map, int endX, int endY) const override;
};

template <typename T>
void reversePoints(std::vector<T>& points) {
    static_assert(std::is_arithmetic_v<T>, "points must be arithmetic type");
    std::reverse(points.begin(), points.end());
}
