//
// Created by akaring on 2023/8/29.
//

#ifndef BANARENDER_CORE_MODEL_H_
#define BANARENDER_CORE_MODEL_H_

#include "Scene.h"
#include <string>
//#include <tiny_gltf.h>
#include "tinygltf/tiny_gltf.h"
#include <vector>

namespace bana {

class Model {
private:
    tinygltf::Model _model;
    std::vector<std::shared_ptr<Scene>> _scenes;
    std::vector<std::pair<std::string, GLuint>> preDefinedAttributes;
    void loadGLTF(const std::string &path);
    void buildScenes();
    std::shared_ptr<Scene> buildScene(unsigned int sceneIndex,
                                      const std::vector<GLuint> &buffers,
                                      const std::vector<GLuint> &textures);
    std::vector<GLuint> buildBuffers(const tinygltf::Model &model);
    std::vector<GLuint> buildTextures(const tinygltf::Model &model);
    std::shared_ptr<Node> buildNode(unsigned int nodeIndex,
                                    const std::vector<GLuint> &buffers,
                                    const std::vector<GLuint> &textures,
                                    std::shared_ptr<Node> parent = nullptr);

    std::shared_ptr<Mesh> buildMesh(unsigned int meshIndex,
                                    const std::vector<GLuint> &buffers,
                                    const std::vector<GLuint> &textures);
    std::shared_ptr<Primitive> buildPrimitive(unsigned int meshIndex,
                                              unsigned int primitiveIndex,
                                              const std::vector<GLuint> &vaos,
                                              const std::vector<GLuint> &buffers,
                                              const std::vector<GLuint> &textures);
public:
    Model(const std::string &path);
    void init();
};

} // bana

#endif //BANARENDER_CORE_MODEL_H_