#include "Fields.h"

void Field::draw(IDraw* context, const Point& min, const Point& max) const {
    context->DrawTexture(min, max, this->textureID, this->rotation);

    if (hasVehicle) {
        Texture::ID vehicleTextureID = idVehicle;
        context->DrawTexture(min, max, vehicleTextureID, this->rotation);
    }
}

