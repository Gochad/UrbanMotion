#include "Strategy.h"
#include <map>
#include <thread>
#include <chrono>
#include <queue>
#include <cmath>

std::vector<std::pair<int, int>> BFSStrategy::calculatePath(std::shared_ptr<Vehicle> v, Map* map, int endX, int endY) const {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<bool>> visited(map->grid.size(), std::vector<bool>(map->grid[0].size(), false));
    std::map<std::pair<int, int>, std::pair<int, int>> parent;

    int startX = v->getX();
    int startY = v->getY();

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

    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current = {endX, endY};

    if (parent.find(current) == parent.end()) {
        return path;
    }

    while (current != std::make_pair(startX, startY)) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back({startX, startY});
    std::reverse(path.begin(), path.end());

    return path;
}

std::vector<std::pair<int, int>> SequentialStrategy::calculatePath(std::shared_ptr<Vehicle> v, Map* map, int endX, int endY) const {
    int startX = v->getX();
    int startY = v->getY();

    // Manhattan distance
    auto heuristic = [](int x1, int y1, int x2, int y2) {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    };
    
    auto compare = [](const std::tuple<int, int, int>& a, const std::tuple<int, int, int>& b) {
        return std::get<0>(a) > std::get<0>(b);
    };
    std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, decltype(compare)> pq(compare);
    
    std::vector<std::vector<int>> gScore(map->grid.size(), std::vector<int>(map->grid[0].size(), INT_MAX));
    std::vector<std::vector<bool>> closed(map->grid.size(), std::vector<bool>(map->grid[0].size(), false));
    std::map<std::pair<int, int>, std::pair<int, int>> parent;
    
    gScore[startX][startY] = 0;
    int fScore = heuristic(startX, startY, endX, endY);
    pq.push(std::make_tuple(fScore, startX, startY));
    
    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    
    while (!pq.empty()) {
        auto [_, x, y] = pq.top();
        pq.pop();
        
        if (closed[x][y]) continue;
        closed[x][y] = true;
        
        if (x == endX && y == endY) {
            break;
        }
        
        for (auto& dir : directions) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if (nx >= 0 && ny >= 0 && nx < map->grid.size() && ny < map->grid[0].size() && 
                !closed[nx][ny] && map->grid[nx][ny]->isRoad()) {
                int tentative_gScore = gScore[x][y] + 1;
                
                if (tentative_gScore < gScore[nx][ny]) {
                    parent[{nx, ny}] = {x, y};
                    gScore[nx][ny] = tentative_gScore;
                    int f = tentative_gScore + heuristic(nx, ny, endX, endY);
                    pq.push(std::make_tuple(f, nx, ny));
                }
            }
        }
    }
    
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current = {endX, endY};

    if (parent.find(current) == parent.end()) {
        return path;
    }
    
    while (current != std::make_pair(startX, startY)) {
        path.push_back(current);
        current = parent[current];
    }
    path.push_back({startX, startY});
    std::reverse(path.begin(), path.end());
    
    return path;
}