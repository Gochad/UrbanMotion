#ifndef DROPAREAT_H
#define DROPAREA_H

#include <imgui.h>
#include <iostream>

class DropArea {
public:
    DropArea(const char* payloadType);
    void draw();

private:
    const char* payloadType;
};

#endif // DROPAREA_H
