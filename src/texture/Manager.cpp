#include "Manager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Texture {
    Manager::Manager() {}

    Manager::~Manager() {
        clear();
    }

    GLuint Manager::loadTexture(const std::string& filename) {
        if (textures.find(filename) != textures.end()) {
            std::cout << "Texture " << filename << " already loaded, returning cached texture." << std::endl;
            return textures[filename];
        }

        int width, height, nrChannels;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
        GLuint textureID = 0;

        if (data) {
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);

            textures[filename] = textureID;

            std::cout << "Texture " << filename << " loaded successfully with ID: " << textureID << std::endl;
        } else {
            std::cerr << "Failed to load texture: " << filename << std::endl;
        }

        return textureID;
    }

    GLuint Manager::getTexture(const std::string& name) {
        if (textures.find(name) != textures.end()) {
            return textures[name];
        } else {
            std::cerr << "Texture " << name << " not found!" << std::endl;
            return 0;
        }
    }

    void Manager::clear() {
        for (auto& pair : textures) {
            glDeleteTextures(1, &pair.second);
        }
        textures.clear();
        std::cout << "All textures cleared." << std::endl;
    }
}
