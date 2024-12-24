#include "Fields.h"

// Define the constructors
Field::Field() : textureID(Texture::ID::Default), rotation(0) {}

Field::Field(Texture::ID id, int rotationDegrees)
    : textureID(id), rotation(rotationDegrees) {}

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    // Draw the field texture
    context->DrawTexture(min, max, this->textureID, this->rotation);

    // Check if there's a vehicle on this field
    if (hasVehicle) {
        // Get the vehicle's texture ID
        Texture::ID vehicleTextureID = idVehicle;
        // Draw the vehicle texture on top of the field
        context->DrawTexture(min, max, vehicleTextureID, this->rotation);
    }
}
