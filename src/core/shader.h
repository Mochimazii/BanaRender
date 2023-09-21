//
// Created by akaring on 2023/6/24.
//

#ifndef BANARENDER_SHADER_H
#define BANARENDER_SHADER_H
#include <string>
#include <glad.h>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>
#include <glm/glm.hpp>

class Shader {
    unsigned int program_id;
    std::string vertex_shader_code;
    std::string fragment_shader_code;
    std::string geometry_shader_code;

public:
    Shader() = default;
    Shader(const std::string& vertex_path, const std::string& fragment_path, const std::string& geometryPath = "");
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    void checkCompileErrors(GLuint shader, std::string type);
};


#endif //BANARENDER_SHADER_H
