#include <string>
#include <vector>
#include <stdexcept>
#include "Handler.cpp" 
#include "mapper.h"

class MapFile {
private:
    Handler fileHandler;
    std::vector<std::string> data;

public:
    MapFile(const std::string& mapID) {
        data = fileHandler.load("map" + mapID + ".txt");

        if (data.empty()) {
            throw std::runtime_error("Map file is empty or not found");
        }
    }

    Texture::ID getTexture(int x, int y) {
        Texture::ID textureId;

        auto it = mapper.find(data[y][x]);
        if (it != mapper.end()) {
            textureId = it->second; 
        }

        return textureId;
    }
};