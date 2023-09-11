//
// Created by akaring on 2023/8/29.
//

#ifndef BANARENDER_CORE_SCENE_H_
#define BANARENDER_CORE_SCENE_H_

#include <functional>
#include "Node.h"

namespace bana {

class Scene {

private:
    void traverseInternal(
            const std::shared_ptr<Node> &node,
            const std::function<void(std::shared_ptr<Node> node)> &nodeProcessor);
    std::vector<std::shared_ptr<Node>> nodes_;

public:
    void addNode(const std::shared_ptr<Node> &node);
    void traverse(
            const std::function<void(std::shared_ptr<Node> node)> &nodeProcessor);

};

} // bana

#endif //BANARENDER_CORE_SCENE_H_
