#pragma once

#include <string>
#include <vector>
#include <functional> 
#include <memory>
#include <unordered_map>
#include "Handler.h"
#include "../components/Fields.h"
#include "mapper.h"

using FieldMatrix = std::vector<std::vector<std::shared_ptr<Field>>>;

class MapFile {
private:
    Handler<std::string> fileHandler;
    std::unordered_map<std::string, FieldMatrix> maps;

public:
    MapFile();
    MapFile(const std::string& mapID);
    ~MapFile();

    FieldMatrix getMap(std::string mapID);
    void saveMaps();
    void setFieldMatrix(std::string mapID, const FieldMatrix& newFieldMatrix);
    FieldMatrix parseMapData(const std::vector<std::string>& data);
    void loadAllMaps();
};
