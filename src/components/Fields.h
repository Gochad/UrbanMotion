#ifndef FIELDS_H
#define FIELDS_H

#include <iostream>
#include <memory>
#include "../imgui/IDraw.h"
#include "../imgui/Point.h"
#include "../texture/Manager.h"

class Field {
public:
    Field();
    Field(Texture::ID id, int rotationDegrees = 0);

    Texture::ID textureID;
    int rotation;

    void draw(IDraw* context, const Point& min, const Point& max) const;
};

class Building : public Field {
public:
    Building(int rotationDegrees = 0)
        : Field(Texture::ID::Building, rotationDegrees) {}
};

class Grass : public Field {
public:
    Grass(int rotationDegrees = 0)
        : Field(Texture::ID::Grass, rotationDegrees) {}
};

class Intersection : public Field {
public:
    Intersection(int rotationDegrees = 0)
        : Field(Texture::ID::Intersection, rotationDegrees) {}
};

class Road : public Field {
public:
    Road(int rotationDegrees = 0)
        : Field(Texture::ID::Road, rotationDegrees) {}
};

class Crossroad : public Field {
public:
    Crossroad(int rotationDegrees = 0)
        : Field(Texture::ID::Crossroad, rotationDegrees) {}
};

class Curve : public Field {
public:
    Curve(int rotationDegrees = 0)
        : Field(Texture::ID::Curve, rotationDegrees) {}
};


#endif // FIELDS_H
