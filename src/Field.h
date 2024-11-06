#include "IDraw.h"
#include "Point.h"

class Field {
public:
    Field();

    void draw(IDraw* context, const Point& min, const Point& max) const;
};