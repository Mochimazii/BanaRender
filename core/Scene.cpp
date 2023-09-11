//
// Created by akaring on 2023/8/29.
//

#include "Scene.h"

namespace bana {

void Scene::addNode(const std::shared_ptr<Node> &node) {
    nodes_.push_back(node);
}

void Scene::traverse(const std::function<void(std::shared_ptr<Node>)> &nodeProcessor) {
    for (auto &node : nodes_) {
        traverseInternal(node, nodeProcessor);
    }
}

void Scene::traverseInternal(const std::shared_ptr<Node> &node,
                             const std::function<void(std::shared_ptr<Node>)> &nodeProcessor) {
    nodeProcessor(node);
    auto &children = node->getChildren();
    for (auto &child : children) {
        traverseInternal(child, nodeProcessor);
    }
}

} // bana