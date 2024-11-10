#include "Field.h"

Field::Field() {}

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    context->DrawTexture(min, max);

    unsigned int border_color = 0xFF000000;
    context->DrawRect(min, max, border_color);
}