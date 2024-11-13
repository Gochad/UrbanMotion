#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <GLFW/glfw3.h>  
#include <string>
#include <map>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/glext.h>
#else
#include <GL/glext.h>
#endif

namespace Texture {
    enum class ID {
        Building = 1,
        Grass,
        Intersection,
        Road1,
        Road2,
        Crossroad1,
        Crossroad2,
        Crossroad3,
        Crossroad4,
        Curve1,
        Curve2,
        Curve3,
        Curve4,
    };

    using MAP = std::map<ID, int>;

    class Manager {
    public:
        Manager();
        ~Manager();

        int loadTexture(const std::string& filename);
        MAP loadTextures();
        void clear();
    };
}

#endif // TEXTURE_MANAGER_H