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
        std::string path = "../textures/";

        textures[ID::Building] = loadTexture(path + "building.png");
        textures[ID::Grass] = loadTexture(path + "grass.png");
        textures[ID::Intersection] = loadTexture(path + "intersection.png");
        textures[ID::Road] = loadTexture(path + "road.png");
        textures[ID::Crossroad] = loadTexture(path + "crossroad.png");
        textures[ID::Curve] = loadTexture(path + "curve.png");
        textures[ID::Default] = loadTexture(path + "default.png");
        textures[ID::Car] = loadTexture(path + "car.png");
        textures[ID::Bike] = loadTexture(path + "bike.png");
        textures[ID::Motorcycle] = loadTexture(path + "motorcycle.png");

        return textures;
    }
    std::ostream& operator<<(std::ostream& os, const ID& id) {
        os << static_cast<int>(id); // Assuming you want to print the integer value of the enum
        return os;
    }
}
