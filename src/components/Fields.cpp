#include "Fields.h"

Field::Field() : textureID(Texture::ID::Default), rotation(0) {}

Field::Field(Texture::ID id, int rotationDegrees)
    : textureID(id), rotation(rotationDegrees) {}

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    context->DrawTexture(min, max, this->textureID, this->rotation);

    if (hasVehicle) {
        Texture::ID vehicleTextureID = idVehicle;
        context->DrawTexture(min, max, vehicleTextureID, this->rotation);
    }
}

