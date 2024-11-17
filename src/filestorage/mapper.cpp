#include "mapper.h"

template <typename T>
std::shared_ptr<Field> createField(Texture::ID textureID, int rotation) {
    return std::make_shared<T>(static_cast<int>(textureID), rotation);
}

std::unordered_map<char, std::function<std::shared_ptr<Field>()>> FromFileToFields = {
    {'A', []() { return createField<Building>(Texture::ID::Building, 0); }},
    {'B', []() { return createField<Grass>(Texture::ID::Grass, 0); }},
    {'C', []() { return createField<Intersection>(Texture::ID::Intersection, 0); }},
    {'D', []() { return createField<Road>(Texture::ID::Road, 0); }},
    {'E', []() { return createField<Road>(Texture::ID::Road, 90); }},
    {'F', []() { return createField<Crossroad>(Texture::ID::Crossroad, 0); }},
    {'G', []() { return createField<Crossroad>(Texture::ID::Crossroad, 90); }},
    {'H', []() { return createField<Crossroad>(Texture::ID::Crossroad, 180); }},
    {'I', []() { return createField<Crossroad>(Texture::ID::Crossroad, 270); }},
    {'J', []() { return createField<Curve>(Texture::ID::Curve, 0); }},
    {'K', []() { return createField<Curve>(Texture::ID::Curve, 90); }},
    {'L', []() { return createField<Curve>(Texture::ID::Curve, 180); }},
    {'M', []() { return createField<Curve>(Texture::ID::Curve, 270); }}
};

