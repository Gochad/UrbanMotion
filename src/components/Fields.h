#ifndef FIELDS_H
#define FIELDS_H

#include <iostream>
#include <memory>
#include "../imgui/IDraw.h"
#include "../imgui/Point.h"
#include "../texture/Manager.h"

// Forward declaration of classes
class Vehicle; // Declare Vehicle first

class Vehicle {
public:
    Vehicle(Texture::ID id, int rotationDegrees = 0)
        : textureID(id), rotation(rotationDegrees) {}

    virtual ~Vehicle() = default; // Ensure proper cleanup for derived classes

    virtual void move() = 0; // Pure virtual function for movement
    void setPosition(const Point& pos) {
        position = pos;
    }

    void setID(Texture::ID id) {
        textureID = id;
    }

    Point getPosition() const {
        return position;
    }

    Texture::ID getID() const {
        return textureID;
    }
    Point position;
    Texture::ID textureID;
    int rotation;
};

// Define derived classes of Vehicle
class Car : public Vehicle {
public:
    Car(int rotationDegrees = 0)
        : Vehicle(Texture::ID::Car, rotationDegrees) {}

    void move() override {
        std::cout << "Car is moving" << std::endl;
    }
};

class Bike : public Vehicle {
public:
    Bike(int rotationDegrees = 0)
        : Vehicle(Texture::ID::Default, rotationDegrees) {}

    void move() override {
        std::cout << "Bike is moving" << std::endl;
    }
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(int rotationDegrees = 0)
        : Vehicle(Texture::ID::Default, rotationDegrees) {}

    void move() override {
        std::cout << "Motorcycle is moving" << std::endl;
    }
};

class Field {
public:
    virtual ~Field() = default;

    Texture::ID idVehicle; // Store the vehicle texture ID
    bool hasVehicle = false; // Indicates if there's a vehicle on the field
    Car car;
    Bike bike;
    Motorcycle motorcycle;

    Field(); // Default constructor
    Field(Texture::ID id, int rotationDegrees = 0); // Constructor with parameters

    Texture::ID textureID;
    int rotation;

    void draw(IDraw* context, const Point& min, const Point& max) const;

    // Getter and Setter for hasVehicle and vehicle
    bool isOccupied() const {
        return hasVehicle;
    }

    void setCar(bool occupied, const Car& v) {
        hasVehicle = occupied;
        idVehicle = Texture::ID::Car;
        car = v; // Set the vehicle if occupied
    }
    void setBike(bool occupied, const Bike& v) {
        hasVehicle = occupied;
        idVehicle = Texture::ID::Bike;
        bike = v; // Set the vehicle if occupied
    }
    void setMotorcycle(bool occupied, const Motorcycle& v) {
        hasVehicle = occupied;
        idVehicle = Texture::ID::Motorcycle;
        motorcycle = v; // Set the vehicle if occupied
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
