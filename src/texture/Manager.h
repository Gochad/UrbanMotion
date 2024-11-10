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

namespace Texture {
    class Manager {
    public:
        Manager();
        ~Manager();

        GLuint loadTexture(const std::string& filename);

        GLuint getTexture(const std::string& name);

        void clear();

    private:
        std::unordered_map<std::string, GLuint> textures;
    };
}

#endif // TEXTURE_MANAGER_H