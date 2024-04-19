//
// Created by akaring on 24-4-19.
//

#include "Texture.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <utility>

Texture2D::Texture2D(const char *_path, ImageFormat _format) : path(_path), image_format(_format)  {
    is_valid = LoadTexture2D(path.c_str(), _format);
}

Texture2D::Texture2D(std::string _path, ImageFormat _format) : path(std::move(_path)), image_format(_format) {
    is_valid = LoadTexture2D(path.c_str(), _format);
}

bool Texture2D::LoadTexture2D(const char *path, ImageFormat format) {
    // 创建纹理
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    // 设置环绕、过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data = stbi_load(path, &this->width, &this->height, &this->nrChannels, 0);
    if (data) {
        if (nrChannels == 1) {
            image_format = ImageFormat::RED;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 3) {
            if (image_format == ImageFormat::SRGB || image_format == ImageFormat::SRGBA) {
                image_format = ImageFormat::SRGB;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            } else {
                image_format = ImageFormat::RGB;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
        } else if (nrChannels == 4) {
            if (image_format == ImageFormat::SRGB || image_format == ImageFormat::SRGBA) {
                image_format = ImageFormat::SRGBA;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            } else {
                image_format = ImageFormat::RGBA;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        stbi_image_free(data);
        return false;
    }

    return true;
}
