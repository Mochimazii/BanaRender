//
// Created by akaring on 24-4-19.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Texture.h"

class Material {
public:
    std::shared_ptr<Shader> shader;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    float emissive;

    std::shared_ptr<Texture2D> diffuse_map;
    std::shared_ptr<Texture2D> specular_map;
    std::shared_ptr<Texture2D> normal_map;
    std::shared_ptr<Texture2D> height_map;
};



#endif //MATERIAL_H
