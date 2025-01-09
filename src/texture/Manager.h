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

    inline std::ostream& operator<<(std::ostream& os, const ID& id) {
        switch (id) {
            case ID::Default: os << "Default"; break;
            case ID::Car: os << "Car"; break;
            case ID::Bike: os << "Bike"; break;
            case ID::Motorcycle: os << "Motorcycle"; break;
            case ID::Building: os << "Building"; break;
            case ID::Grass: os << "Grass"; break;
            case ID::Intersection: os << "Intersection"; break;
            case ID::Road: os << "Road"; break;
            case ID::Crossroad: os << "Crossroad"; break;
            case ID::Curve: os << "Curve"; break;
            default: os << "Unknown"; break;
        }
        return os;
    }
    class Manager {
    public:
        Manager();
        ~Manager();

        int loadTexture(const std::string& filename);
        MAP loadTextures();
        void clear();
    };
        std::ostream& operator<<(std::ostream& os, const ID& id);

}

#endif // TEXTURE_MANAGER_H
