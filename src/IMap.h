#pragma once
#include "IDraw.h"

class IMap {
public:
    virtual ~IMap() {}
    virtual void draw(IDraw* context) = 0;
};