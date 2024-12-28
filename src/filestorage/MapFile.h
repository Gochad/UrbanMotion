#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "Handler.h"
#include "../components/Fields.h"
#include "mapper.h"

using FieldMatrix = std::vector<std::vector<std::shared_ptr<Field>>>;

class MapFile {
private:
    std::string filename;
    Handler<std::string> fileHandler;
    std::vector<std::string> data;
    FieldMatrix fieldMatrix;

public:
    MapFile();
    MapFile(const std::string& mapID);
    ~MapFile();
    int vehicleCount = 0;
    FieldMatrix loadMap();
    void saveMap();
    int counter = 0;
    void setFieldMatrix(const FieldMatrix& newFieldMatrix);
};
