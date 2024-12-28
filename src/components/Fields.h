#ifndef FIELDS_H
#define FIELDS_H

#include <iostream>
#include "../imgui/IDraw.h"
#include "../imgui/Point.h"
#include "../texture/Manager.h"

// Forward declaration of classes
class Vehicle; // Declare Vehicle first

class Vehicle {
public:
    Vehicle() : textureID(Texture::ID::Default), x(0), y(0), rotation(0) {}
    Vehicle(Texture::ID id, int selectedX, int selectedY, int rotationDegrees = 0)
        : textureID(id), x(selectedX), y(selectedY), rotation(rotationDegrees) {}

    virtual ~Vehicle() = default; // Ensure proper cleanup for derived classes

    virtual void move() = 0;
    void moveUp(){
        x--;
    }
    void moveDown(){
        x++;
    }
    void moveLeft(){
        y--;
    }
    void moveRight(){
        y++;
    }
    void setPosition(const Point& pos) {
        position = pos;
    }

    void setID(Texture::ID id) {
        textureID = id;
    }
    Texture::ID getID() const {
        return textureID;
    }

    Point getPosition() const {
        return position;
    }
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }

    Point position;
    Texture::ID textureID;
    int rotation;
    int x, y;
};

// Define derived classes of Vehicle
class Car : public Vehicle {
public:
    Car(int x, int y, int rotationDegrees = 0)
        : Vehicle(Texture::ID::Car, x, y, rotationDegrees) {}

    void move() override {
        std::cout << "Car is moving" << std::endl;
    }
};

class Bike : public Vehicle {
public:
    Bike(int x, int y, int rotationDegrees = 0)
        : Vehicle(Texture::ID::Default, x, y, rotationDegrees) {}

    void move() override {
        std::cout << "Bike is moving" << std::endl;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(int x, int y, int rotationDegrees = 0)
        : Vehicle(Texture::ID::Default, x, y, rotationDegrees) {}

    void move() override {
        std::cout << "Motorcycle is moving" << std::endl;
    }
};

class Field {
public:
    virtual ~Field() = default;

    Field() 
        : textureID(Texture::ID::Default), rotation(0), 
          car(0, 0), bike(0, 0), motorcycle(0, 0) {}

    Field(Texture::ID id, int rotationDegrees = 0) 
        : textureID(id), rotation(rotationDegrees), 
          car(0, 0), bike(0, 0), motorcycle(0, 0) {}

    Texture::ID idVehicle;
    bool hasVehicle = false;
    Car car;
    Bike bike;
    Motorcycle motorcycle;

    Texture::ID textureID;
    int rotation;

    void draw(IDraw* context, const Point& min, const Point& max) const;

    bool isOccupied() const {
        return hasVehicle;
    }

    void setCar(bool occupied, const Car& v) {
        hasVehicle = occupied;
        idVehicle = Texture::ID::Car;
        car = v;
    }
    void setBike(bool occupied, const Bike& v) {
        hasVehicle = occupied;
        idVehicle = Texture::ID::Bike;
        bike = v;
    }
    void setMotorcycle(bool occupied, const Motorcycle& v) {
        hasVehicle = occupied;
        idVehicle = Texture::ID::Motorcycle;
        motorcycle = v;
    }
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
