#include "Handler.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

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
