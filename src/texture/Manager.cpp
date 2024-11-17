#include "Manager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Texture {
    Manager::Manager() {}

    Manager::~Manager() {
        std::cout << "All textures cleared." << std::endl;
    }

    int Manager::loadTexture(const std::string& filename) {
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

            stbi_image_free(data);

            std::cout << "Texture " << filename << " loaded successfully with ID: " << textureID << std::endl;
        } else {
            std::cerr << "Failed to load texture: " << filename << std::endl;
        }

        return textureID;
    }

    MAP Manager::loadTextures() {
        MAP textures;

        textures[ID::Building] = loadTexture("../textures/building.png");
        textures[ID::Grass] = loadTexture("../textures/grass.png");
        textures[ID::Intersection] = loadTexture("../textures/intersection.png");

        textures[ID::Road] = loadTexture("../textures/road.png");
        textures[ID::Crossroad] = loadTexture("../textures/crossroad.png");
        textures[ID::Curve] = loadTexture("../textures/curve.png");

        return textures;
    }
}
