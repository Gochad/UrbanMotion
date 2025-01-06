#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <regex>
#include <set>
#include <vector>
#include <type_traits>

template <typename T, typename = void>
struct is_streamable : std::false_type {};

template <typename T>
struct is_streamable<T, std::void_t<decltype(std::declval<std::istream&>() >> std::declval<T&>(),
                                      std::declval<std::ostream&>() << std::declval<const T&>())>> : std::true_type {};

template <typename T>
inline constexpr bool is_streamable_v = is_streamable<T>::value;

template <typename T, typename Enable = void>
class Handler;

template <typename T>
class Handler<T, std::enable_if_t<is_streamable_v<T>>> {
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

template <typename T>
class Handler<T, std::enable_if_t<!is_streamable_v<T>>> {
    static_assert(is_streamable_v<T>, "Handler can only be instantiated with streamable types.");
};

#endif // HANDLER_H