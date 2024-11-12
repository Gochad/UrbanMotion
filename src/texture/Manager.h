#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <GLFW/glfw3.h>  
#include <string>
#include <unordered_map>
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/glext.h>
#else
#include <GL/glext.h>
#endif

#define TEXTURE_MAP std::unordered_map<ID, int>

namespace Texture {
    enum class ID {
        Building,
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

    class Manager {
    public:
        Manager();
        ~Manager();

        int loadTexture(const std::string& filename);
        TEXTURE_MAP loadTextures();
        void clear();
    };
}

#endif // TEXTURE_MANAGER_H