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

        textures[ID::Road1] = loadTexture("../textures/road1.png");
        textures[ID::Road2] = loadTexture("../textures/road2.png");

        textures[ID::Crossroad1] = loadTexture("../textures/crossroads1.png");
        textures[ID::Crossroad2] = loadTexture("../textures/crossroads2.png");
        textures[ID::Crossroad3] = loadTexture("../textures/crossroads3.png");
        textures[ID::Crossroad4] = loadTexture("../textures/crossroads4.png");

        textures[ID::Curve1] = loadTexture("../textures/curve1.png");
        textures[ID::Curve2] = loadTexture("../textures/curve2.png");
        textures[ID::Curve3] = loadTexture("../textures/curve3.png");
        textures[ID::Curve4] = loadTexture("../textures/curve4.png");

        return textures;
    }
}
