#include "Field.h"

Field::Field() {}

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    unsigned int color = 0xFFB3B3B3;
    context->DrawFilledRect(min, max, color);

    unsigned int border_color = 0xFF000000;
    context->DrawRect(min, max, border_color);
}