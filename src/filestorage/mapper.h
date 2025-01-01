#pragma once
#include <unordered_map>
#include <utility>
#include "../texture/Manager.h"
#include "../components/Fields.h"
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ (std::hash<T2>()(pair.second) << 1);
    }
};

extern std::unordered_map<char, std::function<std::shared_ptr<Field>()>> FromFileToFields;
extern std::unordered_map<std::pair<Texture::ID, int>, char, pair_hash> FromFieldsToFile;
