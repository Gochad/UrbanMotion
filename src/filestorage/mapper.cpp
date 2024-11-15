#include "mapper.h"

template <typename T>
std::shared_ptr<Field> createFieldWithTexture(Texture::ID textureID) {
    return std::make_shared<T>(static_cast<int>(textureID));
}

std::unordered_map<char, std::function<std::shared_ptr<Field>()>> FromFileToFields = {
    {'A', []() { return createFieldWithTexture<Building>(Texture::ID::Building); }},
    {'B', []() { return createFieldWithTexture<Grass>(Texture::ID::Grass); }},
    {'C', []() { return createFieldWithTexture<Intersection>(Texture::ID::Intersection); }},
    {'D', []() { return createFieldWithTexture<Road>(Texture::ID::Road1); }},
    {'E', []() { return createFieldWithTexture<Road>(Texture::ID::Road2); }},
    {'F', []() { return createFieldWithTexture<Crossroad>(Texture::ID::Crossroad1); }},
    {'G', []() { return createFieldWithTexture<Crossroad>(Texture::ID::Crossroad2); }},
    {'H', []() { return createFieldWithTexture<Crossroad>(Texture::ID::Crossroad3); }},
    {'I', []() { return createFieldWithTexture<Crossroad>(Texture::ID::Crossroad4); }},
    {'J', []() { return createFieldWithTexture<Curve>(Texture::ID::Curve1); }},
    {'K', []() { return createFieldWithTexture<Curve>(Texture::ID::Curve2); }},
    {'L', []() { return createFieldWithTexture<Curve>(Texture::ID::Curve3); }},
    {'M', []() { return createFieldWithTexture<Curve>(Texture::ID::Curve4); }}
};
