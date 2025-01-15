#ifndef FIELDS_H
#define FIELDS_H

#include <iostream>
#include <memory>
#include <vector>
#include "../imgui/IDraw.h"
#include "../imgui/Point.h"
#include "../texture/Manager.h"

class Vehicle {
public:
    Vehicle() : textureID(Texture::ID::Default), x(0), y(0), rotation(0) {}
    Vehicle(Texture::ID id, int selectedX, int selectedY, int rotationDegrees = 0)
        : textureID(id), x(selectedX), y(selectedY), rotation(rotationDegrees) {}

    virtual ~Vehicle() = default;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void setPosition(const Point& pos);

    void setID(Texture::ID id);
    Texture::ID getID() const; 

    Point getPosition() const;
    int getX();
    int getY();

    Point position;
    Texture::ID textureID;
    int rotation;
    int x, y;
};

class Car : public Vehicle {
public:
    Car(int x, int y, int rotationDegrees = 0)
        : Vehicle(Texture::ID::Car, x, y, rotationDegrees) {}
};

class Bike : public Vehicle {
public:
    Bike(int x, int y, int rotationDegrees = 0)
        : Vehicle(Texture::ID::Bike, x, y, rotationDegrees) {}
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(int x, int y, int rotationDegrees = 0)
        : Vehicle(Texture::ID::Motorcycle, x, y, rotationDegrees) {}
};

class Field {
public:
    virtual ~Field() = default;

    Field() 
        : textureID(Texture::ID::Default), rotation(0), vehicle(nullptr) {}

    Field(Texture::ID id, int rotationDegrees = 0) 
        : textureID(id), rotation(rotationDegrees), vehicle(nullptr) {}

    Texture::ID idVehicle;
    bool hasVehicle = false;
    std::shared_ptr<Vehicle> vehicle;
    Texture::ID textureID;
    int rotation;

    void draw(IDraw* context, const Point& min, const Point& max) const;
    Texture::ID getID();
    bool isOccupied() const;

    void setVehicle(bool occupied, std::shared_ptr<Vehicle> vehicle);

    bool isRoad() const;
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

class Default : public Field {
public:
    Default(int rotationDegrees = 0)
        : Field(Texture::ID::Default, rotationDegrees) {}
};
#endif // FIELDS_H
