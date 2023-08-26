//
// Created by akaring on 2023/8/19.
//

#include <iostream>
#include <vector>
#include <tinygltf/tiny_gltf.h>
#include "glad/glad.h"

using namespace std;

bool loadModel(tinygltf::Model &model, std::string filename) {
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cout << "ERR: " << err << std::endl;
    }

    if (!res)
        std::cout << "Failed to load glTF: " << filename << std::endl;
    else
        std::cout << "Loaded glTF: " << filename << std::endl;

    return res;
}

int main() {
    std::string input_filename = "../assets/tower/tower.gltf";
    tinygltf::Model model;
    // Load gltf Model
    loadModel(model, input_filename);
    // bind Mesh
    std::pair<GLuint, std::map<int, GLuint>> vaoAndEbos;
    std::map<int, GLuint> vbos;
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    return 0;
}
