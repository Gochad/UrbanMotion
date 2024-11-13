#include <string>
#include <vector>
#include <stdexcept>
#include "Handler.cpp" 
#include "mapper.h"

class MapFile {
private:
    std::string filename;
    Handler fileHandler;
    std::vector<std::string> data;

public:
    MapFile(const std::string& mapID) {
        filename = "map" + mapID + ".txt";
        data = fileHandler.load(filename);

        if (data.empty()) {
            throw std::runtime_error("Map file is empty or not found");
        }
    }

    ~MapFile() {
        saveMap();
    }

    Texture::ID getTexture(int x, int y) {
        Texture::ID textureId;

        auto it = mapper.find(data[y][x]);
        if (it != mapper.end()) {
            textureId = it->second; 
        }

        return textureId;
    }


    bool setTexture(int x, int y, Texture::ID textureId) {
        for (const auto& pair : mapper) {
            if (pair.second == textureId) {
                data[y][x] = pair.first;
                return true;
            }
        }

        std::cerr << "Error: Texture ID not found in mapper." << std::endl;
        return false;
    }


    void saveMap() {
        std::cout << "kurwa to sie zapisuje " << std::endl;
        fileHandler.save(filename, data);
    }
};