#include "Strategy.h"
#include <map>

void BFSStrategy::move(Texture::ID id, int startX, int startY, Map* map, int endX, int endY) const {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited(map->grid.size(), std::vector<bool>(map->grid[0].size(), false));
    std::map<std::pair<int, int>, std::pair<int, int>> parent;

    queue.push({startX, startY});
    visited[startX][startY] = true;

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();

        if (x == endX && y == endY) {
            break;
        }

        for (auto& dir : directions) {
            int nx = x + dir[0];
            int ny = y + dir[1];

            if (nx >= 0 && ny >= 0 && nx < map->grid.size() && ny < map->grid[0].size() &&
                !visited[nx][ny] && map->grid[nx][ny]->isRoad()) {
                queue.push({nx, ny});
                visited[nx][ny] = true;
                parent[{nx, ny}] = {x, y};
            }
        }
    }

    std::pair<int, int> current = {endX, endY};
    map->grid[startX][startY]->setVehicle(false, nullptr);
    while (current != std::make_pair(startX, startY)) {
        auto [px, py] = parent[current];
        current = {px, py};
    }
    map->grid[endX][endY]->setVehicle(true, nullptr);

    for (const auto& vehicle : map->listOfVehicle.get()) {
        if (vehicle->getID() == id) {
            vehicle->setPosition({static_cast<float>(endX), static_cast<float>(endY)});
            break;
        }
    }
}

void SequentialStrategy::move(Texture::ID id, int startX, int startY, Map* map, int endX, int endY) const {
    int currentX = startX;
    int currentY = startY;

    while (currentX != endX) {
        int step = (endX > currentX) ? 1 : -1;
        map->grid[currentX][currentY]->setVehicle(false, nullptr);
        currentX += step;
        map->grid[currentX][currentY]->setVehicle(true, nullptr);
    }

    while (currentY != endY) {
        int step = (endY > currentY) ? 1 : -1;
        map->grid[currentX][currentY]->setVehicle(false, nullptr);
        currentY += step;
        map->grid[currentX][currentY]->setVehicle(true, nullptr);
    }
}
