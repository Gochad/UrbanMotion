#include "mapper.h"

std::unordered_map<char, Texture::ID> mapper = {
    {'A', Texture::ID::Building},
    {'B', Texture::ID::Grass},
    {'C', Texture::ID::Intersection},
    {'D', Texture::ID::Road1},
    {'E', Texture::ID::Road2},
    {'F', Texture::ID::Crossroad1},
    {'G', Texture::ID::Crossroad2},
    {'H', Texture::ID::Crossroad3},
    {'I', Texture::ID::Crossroad4},
    {'J', Texture::ID::Curve1},
    {'K', Texture::ID::Curve2},
    {'L', Texture::ID::Curve3},
    {'M', Texture::ID::Curve4}
};
