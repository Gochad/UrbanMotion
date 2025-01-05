#include "MapFile.h"
#include <stdexcept>
#include <iostream>

MapFile::MapFile() {
    loadAllMaps();
}

MapFile::~MapFile() {
    saveMaps();
}

void MapFile::loadAllMaps() {
    std::vector<std::string> mapsIDs = {"1"};
    
    for (const auto& mapID : mapsIDs) {
        FieldMatrix fieldMatrix;
        std::vector<std::string> data = fileHandler.load("map" + mapID + ".txt");
        fieldMatrix = parseMapData(data);
        maps[mapID] = fieldMatrix;
    }
}
FieldMatrix MapFile::getMap(std::string mapID) {
    auto it = maps.find(mapID);
    if (it != maps.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Map ID not found: " + mapID);
    }
}

FieldMatrix MapFile::parseMapData(const std::vector<std::string>& data) {
    FieldMatrix fieldMatrix;

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


struct FieldKey {
    int textureID;
    int rotation;

    bool operator==(const FieldKey& other) const {
        return textureID == other.textureID && rotation == other.rotation;
    }
};

struct FieldKeyHash {
    std::size_t operator()(const FieldKey& key) const {
        return std::hash<int>()(key.textureID) ^ (std::hash<int>()(key.rotation) << 1);
    }
};

void MapFile::saveMaps() {
    std::vector<std::string> data;

    for (const auto& [mapID, fieldMatrix] : maps) {
        for (const auto& row : fieldMatrix) {
            std::string rowString;
            for (const auto& field : row) {
                auto key = std::make_pair(field->textureID, field->rotation);

                auto it = FromFieldsToFile.find(key);
                if (it != FromFieldsToFile.end()) {
                    rowString += it->second;
                } else {
                    throw std::runtime_error("Texture ID and rotation not found in ReverseMapper");
                }
            }
            data.push_back(rowString);
        }

        fileHandler.save("map" + mapID + ".txt", data);
    }
}

void MapFile::setFieldMatrix(std::string mapID, const FieldMatrix& newFieldMatrix) {
    maps[mapID] = newFieldMatrix;
}
