//
// Created by akaring on 2023/8/26.
//

#include "Mesh.h"

namespace bana {

Mesh::Mesh(std::vector<std::shared_ptr<Primitive>> &primitives)
    : _primitives(primitives) {}

void Mesh::draw() {
    for (auto &primitive : _primitives) {
        primitive->draw();
    }
}

} // bana