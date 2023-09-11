//
// Created by akaring on 2023/8/29.
//

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Model.h"

namespace bana {

Model::Model(const std::string &path) {
    this->loadGLTF(path);
    this->preDefinedAttributes = {
        {"POSITION", 0},
        {"NORMAL", 1},
        {"TEXCOORD_0", 2},
    };
}

void Model::loadGLTF(const std::string &path) {
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;
    bool res = loader.LoadASCIIFromFile(&_model, &err, &warn, path);
    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cout << "ERR: " << err << std::endl;
    }

    if (!res)
        std::cout << "Failed to load glTF: " << path << std::endl;
    else
        std::cout << "Loaded glTF: " << path << std::endl;
}

void Model::init() {
    this->buildScenes();
}

void Model::buildScenes() {
    auto buffers = buildBuffers(this->_model);
    auto textures = buildTextures(this->_model);
    this->_scenes.resize(_model.scenes.size());
    for (size_t i = 0; i < _model.scenes.size(); ++i) {
        this->_scenes[i] = buildScene(i, buffers, textures);
    }
}

std::vector<GLuint> Model::buildBuffers(const tinygltf::Model &model) {
    auto buffers = std::vector<GLuint>(model.buffers.size(), 0);
    // 生成的缓冲区对象名称的数量, 生成的缓冲区对象名称的数组
    GL_CHECK(glGenBuffers(buffers.size(), buffers.data()));
    for (size_t i = 0; i < model.buffers.size(); ++i) {
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)));
        // 1. 指定缓冲区对象的数据存储 2. 缓冲区对象的数据大小 3. 缓冲区对象的数据指针 4. 指定数据如何使用
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, model.buffers[i].data.size(),
                              model.buffers[i].data.data(), GL_STATIC_DRAW));
    }
    return std::vector<GLuint>();
}

std::vector<GLuint> Model::buildTextures(const tinygltf::Model &model) {
    return std::vector<GLuint>();
}

std::shared_ptr<Scene> Model::buildScene(unsigned int sceneIndex,
                                         const std::vector<GLuint> &buffers,
                                         const std::vector<GLuint> &textures) {
    auto scene = std::make_shared<Scene>();
    for (size_t i = 0; i < _model.scenes[sceneIndex].nodes.size(); ++i) {
        scene->addNode(buildNode(_model.scenes[sceneIndex].nodes[i], buffers, textures));
    }
    return scene;
}

std::shared_ptr<Node> Model::buildNode(unsigned int nodeIndex,
                                       const std::vector<GLuint> &buffers,
                                       const std::vector<GLuint> &textures,
                                       std::shared_ptr<Node> parent) {
    auto node = std::make_shared<Node>(parent);
    auto nodeTrans = _model.nodes[nodeIndex].matrix;
    glm::mat4 matrix(1.0f);
    if (nodeTrans.size() == 16){
        matrix[0].x = nodeTrans[0], matrix[0].y = nodeTrans[1],
        matrix[0].z = nodeTrans[2], matrix[0].w = nodeTrans[3];
        matrix[1].x = nodeTrans[4], matrix[1].y = nodeTrans[5],
        matrix[1].z = nodeTrans[6], matrix[1].w = nodeTrans[7];
        matrix[2].x = nodeTrans[8], matrix[2].y = nodeTrans[9],
        matrix[2].z = nodeTrans[10], matrix[2].w = nodeTrans[11];
        matrix[3].x = nodeTrans[12], matrix[3].y = nodeTrans[13],
        matrix[3].z = nodeTrans[14], matrix[3].w = nodeTrans[15];
    } else {
        if (_model.nodes[nodeIndex].translation.size() == 3) {
            glm::translate(matrix, glm::vec3(_model.nodes[nodeIndex].translation[0],
                                             _model.nodes[nodeIndex].translation[1],
                                             _model.nodes[nodeIndex].translation[2]));
        }
        if (_model.nodes[nodeIndex].rotation.size() == 4) {
            matrix *= glm::mat4_cast(glm::quat(_model.nodes[nodeIndex].rotation[3],
                                               _model.nodes[nodeIndex].rotation[0],
                                               _model.nodes[nodeIndex].rotation[1],
                                               _model.nodes[nodeIndex].rotation[2]));
        }
        if (_model.nodes[nodeIndex].scale.size() == 3) {
            glm::scale(matrix, glm::vec3(_model.nodes[nodeIndex].scale[0],
                                         _model.nodes[nodeIndex].scale[1],
                                         _model.nodes[nodeIndex].scale[2]));
        }
    }
    node->SetTransform(matrix);
    if (_model.nodes[nodeIndex].mesh >= 0){
        node->setMesh(buildMesh(_model.nodes[nodeIndex].mesh, buffers, textures));
    }
    for (auto &childNodeIndex : _model.nodes[nodeIndex].children) {
        node->addChild(buildNode(childNodeIndex, buffers, textures, node));
    }
    return node;
}

std::shared_ptr<Mesh> Model::buildMesh(unsigned int meshIndex,
                                       const std::vector<GLuint> &buffers,
                                       const std::vector<GLuint> &textures) {
    std::vector<std::shared_ptr<Primitive>> meshPrimitives;
    const auto &primitives = _model.meshes[meshIndex].primitives;
    auto vaos = std::vector<GLuint>(primitives.size());
    GL_CHECK(glGenVertexArrays(vaos.size(), vaos.data()));
    for (size_t i = 0; i < primitives.size(); ++i) {
        GL_CHECK(glBindVertexArray(vaos.at(i)));
        meshPrimitives.push_back(buildPrimitive(meshIndex, i, vaos, buffers, textures));
    }
    GL_CHECK(glBindVertexArray(0));
    return std::make_shared<Mesh>(meshPrimitives);
}

std::shared_ptr<Primitive> Model::buildPrimitive(unsigned int meshIndex,
                                                 unsigned int primitiveIndex,
                                                 const std::vector<GLuint> &vaos,
                                                 const std::vector<GLuint> &buffers,
                                                 const std::vector<GLuint> &textures) {
    const auto &primitive = _model.meshes[meshIndex].primitives[primitiveIndex];
    for (auto &attribute : preDefinedAttributes) {
        const auto &attributeName = attribute.first;
        const auto &attributeLocation = attribute.second;
        const auto attrIterator = primitive.attributes.find(attributeName);
        if (attrIterator == primitive.attributes.end()) {
            continue;
        }
        const auto &attrAccessor = _model.accessors[attrIterator->second];
        const auto &bufferView = _model.bufferViews[attrAccessor.bufferView];
        const auto bufferIndex = bufferView.buffer;

        GL_CHECK(glEnableVertexAttribArray(attributeLocation));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, buffers.at(bufferIndex)));

        const auto byteOffset = attrAccessor.byteOffset + bufferView.byteOffset;
        GL_CHECK(glVertexAttribPointer(attributeLocation, attrAccessor.type,
                                       attrAccessor.componentType,
                                       attrAccessor.normalized ? GL_TRUE : GL_FALSE,
                                       bufferView.byteStride,
                                       reinterpret_cast<const GLvoid *>(byteOffset)));
    }
    std::shared_ptr<Primitive> primitivePtr;
    if (primitive.indices >= 0) {
        const auto &accessor = _model.accessors[primitive.indices];
        const auto &bufferView = _model.bufferViews[accessor.bufferView];
        const auto bufferIndex = bufferView.buffer;
        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.at(bufferIndex)));
        primitivePtr = std::make_shared<Primitive>(vaos.at(primitiveIndex),
                                                   primitive.mode,
                                                   accessor.count,
                                                   accessor.componentType,
                                                   accessor.type);
    } else {
        const auto &accessor = _model.accessors[primitive.attributes.begin()->second];
        primitivePtr = std::make_shared<Primitive>(vaos.at(primitiveIndex),
                                                   primitive.mode,
                                                   accessor.count,
                                                   accessor.componentType);
    }
    if (primitive.material >= 0) {
//        primitivePtr->setMaterial(buildMaterial(_model, primitive.material, textures));
    }
    return primitivePtr;
}

} // bana