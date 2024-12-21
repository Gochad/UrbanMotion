#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <regex>
#include <set>
#include <vector>

template <typename T>
class Handler {
public:
    std::vector<T> load(const std::string& filename) {
        std::vector<T> data;
        std::ifstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Unable to open file for reading");

        T value;
        while (file >> value) {
            data.push_back(value);
        }
        return data;
    }

    void save(const std::string& filename, const std::vector<T>& data) {
        std::ofstream file(filename);
        if (!file.is_open()) throw std::runtime_error("Unable to open file for writing");

        for (const auto& value : data) {
            file << value << '\n';
        }
    }

    std::string getNextAvailableFile() {
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

        return "map" + std::to_string(nextNumber) + ".txt";
    }
};

#endif // HANDLER_H
