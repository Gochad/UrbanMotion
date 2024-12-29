#include "MapFile.h"
#include <stdexcept>
#include <iostream>

MapFile::MapFile() {
    filename = "map" + fileHandler.getNextAvailableFile() + ".txt";

    std::cout << "New filemap " << filename << std::endl;
}

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

void MapFile::saveMap() {
    data.clear();

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

    fileHandler.save(filename, data);
    std::cout << "Map has been saved to " << filename << std::endl;
}

void MapFile::setFieldMatrix(const FieldMatrix& newFieldMatrix) {
    fieldMatrix = newFieldMatrix;
}
