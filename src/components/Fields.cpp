#include "Fields.h"

Field::Field() {}
Field::Field(Texture::ID id, int rotationDegrees)
        : textureID(id), rotation(rotationDegrees) {}

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    context->DrawTexture(min, max, this->textureID, this->rotation);
}
