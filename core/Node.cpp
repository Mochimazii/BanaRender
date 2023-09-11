//
// Created by akaring on 2023/8/26.
//

#include "Node.h"

namespace bana {
Node::Node(std::shared_ptr<Node> parent)
        : _parent(std::move(parent)), _transform(glm::mat4(1.0f)){}

const glm::mat4 &Node::GetTransform() const {
    return _transform;
}

void Node::SetTransform(const glm::mat4 &transform) {
    _transform = transform;
}

glm::mat4 Node::getWorldMatrix() {
    return _parent != nullptr ? _parent->getWorldMatrix() * _transform : _transform;
}

void Node::addChild(const std::shared_ptr<Node> &node) {
    _children.push_back(node);
}

void Node::setMesh(std::shared_ptr<Mesh> mesh) {
    this->_mesh = std::move(mesh);
}

const std::vector<std::shared_ptr<Node>> &Node::getChildren() {
    return _children;
}

void Node::draw() {
    if (_mesh != nullptr){
        _mesh->draw();
    }
}
} // bana