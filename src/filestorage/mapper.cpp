#include "mapper.h"

template <typename T, int rotation = 0>
std::shared_ptr<Field> createField() {
    return std::make_shared<T>(rotation);
}

std::unordered_map<char, std::function<std::shared_ptr<Field>()>> FromFileToFields = {
    {'A', createField<Building>},
    {'B', createField<Grass>},
    {'C', createField<Intersection>},
    {'D', createField<Road>},
    {'E', createField<Road, 90>},
    {'F', createField<Crossroad>},
    {'G', createField<Crossroad, 90>},
    {'H', createField<Crossroad, 180>},
    {'I', createField<Crossroad, 270>},
    {'J', createField<Curve>},
    {'K', createField<Curve, 90>},
    {'L', createField<Curve, 180>},
    {'M', createField<Curve, 270>}
//    {'N', createField<Car, 0>},
//    {'O', createField<Car, 90>},
//    {'P', createField<Car, 180>},
//    {'R', createField<Car, 270>},
//    {'T', createField<Bike, 0>},
//    {'U', createField<Bike, 90>},    
//    {'V', createField<Bike, 180>},
//    {'W', createField<Bike, 270>},
//    {'X', createField<Motorcycle, 0>},
//    {'Y', createField<Motorcycle, 90>},
//    {'Z', createField<Motorcycle, 180>},
//    {'a', createField<Motorcycle, 270>}
};

std::unordered_map<std::pair<Texture::ID, int>, char, pair_hash> FromFieldsToFile = {
    {{Texture::ID::Building, 0}, 'A'},
    {{Texture::ID::Grass, 0}, 'B'},
    {{Texture::ID::Intersection, 0}, 'C'},
    {{Texture::ID::Road, 0}, 'D'},
    {{Texture::ID::Road, 90}, 'E'},
    {{Texture::ID::Crossroad, 0}, 'F'},
    {{Texture::ID::Crossroad, 90}, 'G'},
    {{Texture::ID::Crossroad, 180}, 'H'},
    {{Texture::ID::Crossroad, 270}, 'I'},
    {{Texture::ID::Curve, 0}, 'J'},
    {{Texture::ID::Curve, 90}, 'K'},
    {{Texture::ID::Curve, 180}, 'L'},
    {{Texture::ID::Curve, 270}, 'M'}
//    {{Texture::ID::Car, 0}, 'N'},
//    {{Texture::ID::Car, 90}, 'O'},
//    {{Texture::ID::Car, 180}, 'P'},
//    {{Texture::ID::Car, 270}, 'R'},
//    {{Texture::ID::Bike, 0}, 'T'},
//    {{Texture::ID::Bike, 90}, 'U'},
//    {{Texture::ID::Bike, 180}, 'V'},
//    {{Texture::ID::Bike, 270}, 'W'},
//    {{Texture::ID::Motorcycle, 0}, 'X'},
//    {{Texture::ID::Motorcycle, 90}, 'Y'},
//    {{Texture::ID::Motorcycle, 180}, 'Z'},
//    {{Texture::ID::Motorcycle, 270}, 'a'}
};
