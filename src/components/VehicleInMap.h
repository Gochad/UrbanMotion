#pragma once

#include <iostream>
#include "../texture/Manager.h"
 

class VehicleInMap {
public:
    VehicleInMap(Texture::ID id, int x, int y);

    Texture::ID getId() const;
    int getX() const;
    int getY() const;
    bool operator==(const VehicleInMap& other) const;

private:
    Texture::ID id;
    int x;
    int y;
};
