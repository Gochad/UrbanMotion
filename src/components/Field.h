#include "../imgui/IDraw.h"
#include "../imgui/Point.h"

class Field {
public:
    Field();

    void draw(IDraw* context, const Point& min, const Point& max, int textureid) const;
};