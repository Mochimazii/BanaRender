//
// Created by akaring on 2023/8/26.
//

#ifndef BANARENDER_PRIMITIVE_H
#define BANARENDER_PRIMITIVE_H

#include "macro.h"
#include "glad/glad.h"
#include <memory>

namespace bana {

class Primitive {
public:
    Primitive(GLuint vao, int type, int count, int componentType,
              int offset = -1);
    void draw();

private:
    GLuint _vao;
    int _mode;
    int _count;
    int _componentType;
    int _offset;
};

} // bana

#endif //BANARENDER_PRIMITIVE_H
