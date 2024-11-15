#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include "Handler.cpp"
#include "../components/Fields.h"
#include "mapper.h"

using FieldMatrix = std::vector<std::vector<std::shared_ptr<Field>>>;

class MapFile {
private:
    std::string filename;
    Handler fileHandler;
    std::vector<std::string> data;
    FieldMatrix fieldMatrix;
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

    FieldMatrix loadMap() {
        for (const auto& row : data) {
            std::vector<std::shared_ptr<Field>> fieldRow;
            for (char cell : row) {
                auto it = FromFileToFields.find(cell);
                if (it != FromFileToFields.end()) {
                    fieldRow.push_back(it->second());
                } else {
                    throw std::runtime_error(std::string("Unknown field type: ") + cell);
                }
            }
            fieldMatrix.push_back(std::move(fieldRow));
        }

        return fieldMatrix;
    }

    // Texture::ID getTexture(int x, int y) const {
    //     if (x < 0 || y < 0 || y >= fieldMatrix.size() || x >= fieldMatrix[y].size()) {
    //         throw std::out_of_range("Coordinates out of bounds");
    //     }
    //     return static_cast<Texture::ID>(fieldMatrix[y][x]->textureID);
    // }

    // bool setTexture(int x, int y, Texture::ID textureId) {
    //     for (const auto& pair : fromFileToFields) {
    //         auto tempField = pair.second();
    //         if (tempField->textureID == static_cast<int>(textureId)) {
    //             data[y][x] = pair.first;
    //             fieldMatrix[y][x] = tempField; 
    //             isDirty = true;
    //             return true;
    //         }
    //     }

    //     std::cerr << "Error: Texture ID not found in mapper." << std::endl;
    //     return false;
    // }

    void saveMap() {
        data.clear();

        std::unordered_map<int, char> reverseMapper;
        for (const auto& pair : FromFileToFields) {
            auto field = pair.second();
            reverseMapper[field->textureID] = pair.first;
        }

        for (const auto& row : fieldMatrix) {
            std::string rowString;
            for (const auto& field : row) {
                auto it = reverseMapper.find(field->textureID);
                if (it != reverseMapper.end()) {
                    rowString += it->second;
                } else {
                    throw std::runtime_error("Texture ID not found in reverseMapper");
                }
            }
            data.push_back(rowString);
        }

        fileHandler.save(filename, data);
        std::cout << "Map has been saved to " << filename << std::endl;
    }
};
