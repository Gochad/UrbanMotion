#include "MapReader.h"
#include <filesystem>
#include <iostream>
#include <regex>

namespace fs = std::filesystem;

std::vector<std::string> MapReader::getMapList() {
    std::vector<std::string> mapList;
    std::string folderPath = fs::current_path().string();

    std::regex mapPattern(R"(map(\d+)\.txt)");

    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                std::smatch match;
                
                if (std::regex_match(filename, match, mapPattern)) {
                    mapList.push_back(match[1].str());
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error reading directory '" << folderPath << "': " << e.what() << std::endl;
    }

    return mapList;
}
