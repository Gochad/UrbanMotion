#include "Fields.h"

Field::Field() {}
Field::Field(int id) {
    this->textureID = id;
}

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    context->DrawTexture(min, max, this->textureID);
}
