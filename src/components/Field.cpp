#include "Field.h"

Field::Field() {}

void Field::draw(IDraw* context, const Point& min, const Point& max, int textureid) const {
    context->DrawTexture(min, max, textureid);
}