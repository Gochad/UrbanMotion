#include "Handler.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <regex>
#include <set>

std::vector<std::string> Handler::load(const std::string& filename) {
    std::cout << "filename: " << filename << std::endl;
    std::vector<std::string> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }

    file.close();
    return data;
}

void Handler::save(const std::string& filename, const std::vector<std::string>& data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing");
    }

    for (const auto& line : data) {
        file << line << '\n';
    }

    file.close();
}

std::string Handler::getNextAvailableFile() {
    namespace fs = std::filesystem;
    std::regex mapFilePattern(R"(map(\d+)\.txt)");
    std::smatch match;
    std::set<int> usedNumbers;

    try {
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (std::regex_match(filename, match, mapFilePattern)) {
                    if (match.size() == 2) {
                        int number = std::stoi(match[1]);
                        usedNumbers.insert(number);
                    }
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error in file system: " << e.what() << std::endl;
    }

    int nextNumber = 1;
    while (usedNumbers.find(nextNumber) != usedNumbers.end()) {
        ++nextNumber;
    }

    return std::to_string(nextNumber);
}
