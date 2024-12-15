#include "Fields.h"

Field::Field() {}
Field::Field(int id, int rotationDegrees) 
    : textureID(id), rotation(rotationDegrees) {}

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    context->DrawTexture(min, max, this->textureID, this->rotation);
}

int Field::getTextureID() const {
    return this->textureID;
}
