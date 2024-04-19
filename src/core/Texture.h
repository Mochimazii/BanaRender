//
// Created by akaring on 24-4-19.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

enum class ImageFormat {
    RED,
    RGB,
    RGBA,
    SRGB,
    SRGBA
};

class Texture2D {
public:
    unsigned int id{};
    std::string path;
    int width{};
    int height{};
    int nrChannels{};
    ImageFormat image_format;
    bool is_valid;

    Texture2D(const char *path, ImageFormat format);
    Texture2D(std::string path, ImageFormat format);
    bool LoadTexture2D(const char *path, ImageFormat format);
};



#endif //TEXTURE_H
