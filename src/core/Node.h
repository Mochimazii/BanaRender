//
// Created by akaring on 2023/8/26.
//

#ifndef BANARENDER_CORE_NODE_H_
#define BANARENDER_CORE_NODE_H_

#include "Mesh.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace bana {

class Node {
private:
    std::vector<std::shared_ptr<Node>> _children;
    std::shared_ptr<Node> _parent;
    std::shared_ptr<Mesh> _mesh;
    glm::mat4 _transform;

public:
    Node(std::shared_ptr<Node> parent = nullptr);
    const glm::mat4 &GetTransform() const;
    void SetTransform(const glm::mat4 &transform);
    glm::mat4 getWorldMatrix();
    void addChild(const std::shared_ptr<Node> &node);
    void setMesh(std::shared_ptr<Mesh> mesh);
    const std::vector<std::shared_ptr<Node>> &getChildren();
    void draw();
};

} // bana

#endif //BANARENDER_CORE_NODE_H_
