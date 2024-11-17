#ifndef FIELDS_H
#define FIELDS_H

#include <iostream>
#include <memory>
#include "../imgui/IDraw.h"
#include "../imgui/Point.h"

class Field {
public:
    Field();
    Field(int id, int rotationDegrees);

    int textureID;
    int rotation;

    void draw(IDraw* context, const Point& min, const Point& max) const;
};

class Building : public Field {
public:
    using Field::Field;
};

class Grass : public Field {
public:
    using Field::Field;
};

class Intersection : public Field {
public:
    using Field::Field;
};

class Road : public Field {
public:
    using Field::Field;
};

class Crossroad : public Field {
public:
    using Field::Field;
};

class Curve : public Field {
public:
    using Field::Field;
};


#endif // FIELDS_H
