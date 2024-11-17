#include "MapFile.h"
#include <stdexcept>
#include <iostream>

MapFile::MapFile(const std::string& mapID) {
    filename = "map" + mapID + ".txt";
    data = fileHandler.load(filename);

    if (data.empty()) {
        throw std::runtime_error("Map file is empty or not found");
    }
}

MapFile::~MapFile() {
    saveMap();
}

FieldMatrix MapFile::loadMap() {
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

void MapFile::saveMap() {
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
