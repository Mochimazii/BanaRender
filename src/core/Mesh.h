//
// Created by akaring on 2023/8/26.
//

#ifndef BANARENDER_CORE_MESH_H_
#define BANARENDER_CORE_MESH_H_

#include "Primitive.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace bana {

class Mesh {
private:
    std::vector<std::shared_ptr<Primitive>> _primitives;

public:
    Mesh(std::vector<std::shared_ptr<Primitive>> &primitives);
    void draw();
};

} // bana

#endif //BANARENDER_CORE_MESH_H_
