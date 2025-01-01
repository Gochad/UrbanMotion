#ifndef FIELDS_H
#define FIELDS_H

#include <iostream>
#include <memory>
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
    void setPosition(const Point&);
    void setID(Texture::ID);
    Texture::ID getID() const;
    Point getPosition() const;
    int getX() const;
    int getY() const;

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
        : Vehicle(Texture::ID::Default, x, y, rotationDegrees) {}
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(int x, int y, int rotationDegrees = 0)
        : Vehicle(Texture::ID::Default, x, y, rotationDegrees) {}
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
    std::unique_ptr<Vehicle> vehicle;
    Texture::ID textureID;
    int rotation;

    void draw(IDraw* context, const Point& min, const Point& max) const;

    bool isOccupied() const;

    void setVehicle(bool occupied, std::shared_ptr<Vehicle> vehicle);
};

template<typename T>
class Street : public Field {
public:
    Street(Texture::ID id, int rotationDegrees = 0)
        : Field(id, rotationDegrees) {}
};

template<typename T>
class NonStreet : public Field {
public:
    NonStreet(Texture::ID id, int rotationDegrees = 0)
        : Field(id, rotationDegrees) {}

};

// Przykłady konkretnych pól
class Road : public Street<Road> {
public:
    Road(int rotationDegrees = 0)
        : Street(Texture::ID::Road, rotationDegrees) {}
};

class Crossroad : public Street<Crossroad> {
public:
    Crossroad(int rotationDegrees = 0)
        : Street(Texture::ID::Crossroad, rotationDegrees) {}
};

class Grass : public NonStreet<Grass> {
public:
    Grass(int rotationDegrees = 0)
        : NonStreet(Texture::ID::Grass, rotationDegrees) {}
};

class Building : public NonStreet<Building> {
public:
    Building(int rotationDegrees = 0)
        : NonStreet(Texture::ID::Building, rotationDegrees) {}
};

class Intersection : public Street<Crossroad>  {
public:
    Intersection(int rotationDegrees = 0)
        : Street(Texture::ID::Intersection, rotationDegrees) {}
};

class Curve : public Street<Crossroad>  {
public:
    Curve(int rotationDegrees = 0)
        : Street(Texture::ID::Curve, rotationDegrees) {}
};

class Default :public NonStreet<Grass> {
public:
    Default(int rotationDegrees = 0)
        : NonStreet(Texture::ID::Default, rotationDegrees) {}
};
#endif // FIELDS_H
