//
// Created by akaring on 2023/8/26.
//

#include "Node.h"

namespace bana {
const glm::mat4 &Node::GetTransform() const {
    return _transform;
}
void Node::SetTransform(const glm::mat4 &transform) {
    _transform = transform;
}
} // bana