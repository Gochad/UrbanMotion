#pragma once
#include <string>
#include <vector>

class Handler {
public:
    std::vector<std::string> load(const std::string& filename);
    void save(const std::string& filename, const std::vector<std::string>& data);

    std::string getNextAvailableFile();
};