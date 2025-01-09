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
        Road,
        Crossroad,
        Curve,
        Default,
        Car,
        Bike,
        Motorcycle
    };

    struct TextureInfo {
        Texture::ID id;
        const char* filename;
    };

    constexpr TextureInfo textureFiles[] = {
        { Texture::ID::Building,    "building.png"    },
        { Texture::ID::Grass,       "grass.png"       },
        { Texture::ID::Intersection,"intersection.png"},
        { Texture::ID::Road,        "road.png"        },
        { Texture::ID::Crossroad,   "crossroad.png"   },
        { Texture::ID::Curve,       "curve.png"       },
        { Texture::ID::Default,     "default.png"     },
        { Texture::ID::Car,         "car.png"         },
        { Texture::ID::Bike,        "bike.png"        },
        { Texture::ID::Motorcycle,  "motorcycle.png"  }
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
